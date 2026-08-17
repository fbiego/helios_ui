#!/usr/bin/env python3
"""
Update fallback font symbols in globals.xml from translations.xml.

The generated LVGL fonts are cascaded, so a glyph only needs to be present in
the first fallback font that can render it. By default this script keeps that
cascade order and removes duplicate codepoints from later fallback fonts.
"""

from __future__ import annotations

import argparse
import html
import os
import re
import sys
import unicodedata
import xml.etree.ElementTree as ET
from dataclasses import dataclass
from typing import Iterable

try:
    from fontTools.ttLib import TTFont
except ImportError:  # pragma: no cover - optional dependency
    TTFont = None


DEFAULT_GROUPS = {
    "latin": ("pt", "de", "es", "fr", "hu", "vi"),
    "ru": ("ru",),
    "el": ("el",),
    "hi": ("hi",),
    "th": ("th",),
    "zh": ("zh",),
    "ja": ("ja",),
}

DEFAULT_ORDER = ("latin", "ru", "el", "hi", "th", "zh", "ja")
BASE_RANGE_MAX = 0x7F
LANG_ALIASES = {
    "jp": "ja",
}


@dataclass(frozen=True)
class FontInfo:
    prefix: str
    src_path: str | None


def project_root() -> str:
    return os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))


def parse_args() -> argparse.Namespace:
    root = project_root()
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--translations", default=os.path.join(root, "translations.xml"))
    parser.add_argument("--globals", dest="globals_xml", default=os.path.join(root, "globals.xml"))
    parser.add_argument("--project-root", default=root, help="Base directory for font src_path values.")
    parser.add_argument(
        "--order",
        default=",".join(DEFAULT_ORDER),
        help="Comma-separated fallback order. Later fonts drop glyphs already kept by earlier fonts.",
    )
    parser.add_argument("--write", action="store_true", help="Write changes to globals.xml.")
    parser.add_argument("--keep-duplicates", action="store_true", help="Do not remove glyphs from later fallback fonts.")
    parser.add_argument("--include-ascii", action="store_true", help="Include ASCII characters too.")
    parser.add_argument(
        "--no-font-filter",
        action="store_true",
        help="Do not filter symbols through each font's cmap.",
    )
    parser.add_argument(
        "languages",
        nargs="*",
        help="Optional font groups to update, e.g. zh ja. Omit to update all groups.",
    )
    args = parser.parse_args()
    args.languages = normalize_languages(args.languages)
    return args


def normalize_languages(languages: list[str]) -> list[str]:
    normalized = []
    valid = set(DEFAULT_GROUPS)

    for language in languages:
        prefix = LANG_ALIASES.get(language, language)
        if prefix not in valid:
            valid_text = ", ".join(DEFAULT_ORDER)
            raise SystemExit(f"Unknown language/group '{language}'. Expected one of: {valid_text}")
        if prefix not in normalized:
            normalized.append(prefix)

    return normalized


def load_translation_chars(path: str) -> dict[str, set[str]]:
    tree = ET.parse(path)
    root = tree.getroot()
    langs = root.attrib.get("languages", "").split()
    chars = {lang: set() for lang in langs}

    for node in root.findall("translation"):
        if node.attrib.get("tag") == "unique":
            continue
        for lang in langs:
            value = node.attrib.get(lang)
            if value:
                chars[lang].update(value)

    return chars


def is_candidate_char(ch: str, include_ascii: bool) -> bool:
    if not include_ascii and ord(ch) <= BASE_RANGE_MAX:
        return False
    if unicodedata.category(ch).startswith("C"):
        return False
    return True


def collect_group_chars(chars_by_lang: dict[str, set[str]], include_ascii: bool) -> dict[str, set[str]]:
    result: dict[str, set[str]] = {}
    for prefix, langs in DEFAULT_GROUPS.items():
        chars: set[str] = set()
        for lang in langs:
            chars.update(chars_by_lang.get(lang, set()))
        result[prefix] = {ch for ch in chars if is_candidate_char(ch, include_ascii)}
    return result


def load_font_info(globals_xml: str) -> dict[str, FontInfo]:
    tree = ET.parse(globals_xml)
    root = tree.getroot()
    fonts = root.find("fonts")
    info: dict[str, FontInfo] = {}
    if fonts is None:
        return info

    for node in fonts.findall("bin"):
        name = node.attrib.get("name", "")
        match = re.fullmatch(r"NS_Medium_(latin|ru|el|hi|th|zh|jp|vi)_(\d+)", name)
        if not match:
            continue
        prefix = "ja" if match.group(1) == "jp" else match.group(1)
        info.setdefault(prefix, FontInfo(prefix=prefix, src_path=node.attrib.get("src_path")))

    return info


def font_cmap(project_dir: str, src_path: str | None) -> set[int] | None:
    if TTFont is None or not src_path:
        return None

    font_path = os.path.join(project_dir, src_path)
    if not os.path.exists(font_path):
        return None

    font = TTFont(font_path, lazy=True)
    cmap: set[int] = set()
    for table in font["cmap"].tables:
        cmap.update(table.cmap.keys())
    font.close()
    return cmap


def sort_chars(chars: Iterable[str]) -> str:
    return "".join(sorted(chars, key=lambda ch: (ord(ch), ch)))


def compute_symbols(args: argparse.Namespace) -> dict[str, str]:
    chars_by_lang = load_translation_chars(args.translations)
    grouped = collect_group_chars(chars_by_lang, args.include_ascii)
    font_info = load_font_info(args.globals_xml)
    root = os.path.abspath(args.project_root)

    order = [item.strip() for item in args.order.split(",") if item.strip()]
    selected = set(args.languages or order)
    supplied: set[str] = set()
    result: dict[str, str] = {}

    for prefix in order:
        chars = set(grouped.get(prefix, set()))
        if not args.keep_duplicates:
            chars -= supplied

        if not args.no_font_filter:
            cmap = font_cmap(root, font_info.get(prefix, FontInfo(prefix, None)).src_path)
            if cmap is not None:
                chars = {ch for ch in chars if ord(ch) in cmap}

        if prefix in selected:
            result[prefix] = sort_chars(chars)
        supplied.update(chars)

    return result


def replace_symbols(globals_text: str, prefix: str, symbols: str) -> tuple[str, int]:
    xml_prefix = "jp" if prefix == "ja" else prefix
    escaped = html.escape(symbols, quote=True)
    pattern = re.compile(
        rf'(<bin\b(?=[^>]*\bname="NS_Medium_{xml_prefix}_\d+")[^>]*?\bsymbols=")([^"]*)(")',
        re.DOTALL,
    )
    return pattern.subn(rf"\g<1>{escaped}\g<3>", globals_text)


def main() -> int:
    args = parse_args()
    symbols_by_prefix = compute_symbols(args)

    with open(args.globals_xml, "r", encoding="utf-8") as f:
        globals_text = f.read()

    updated = globals_text
    total_replacements = 0

    for prefix, symbols in symbols_by_prefix.items():
        updated, count = replace_symbols(updated, prefix, symbols)
        total_replacements += count
        print(f"{prefix:>5}: {len(symbols):4d} glyphs, updated {count} font node(s)")

    if updated == globals_text:
        print("No changes.")
        return 0

    if args.write:
        with open(args.globals_xml, "w", encoding="utf-8") as f:
            f.write(updated)
        print(f"Updated {args.globals_xml} ({total_replacements} symbol attributes).")
    else:
        print("Dry run only. Re-run with --write to update globals.xml.")

    return 0


if __name__ == "__main__":
    sys.exit(main())
