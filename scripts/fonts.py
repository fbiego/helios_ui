import os
from fontTools.ttLib import TTFont
from fontTools.merge import Merger
from fontTools.subset import Subsetter, Options

import tempfile


def sanitize_font(font):
    # Remove problematic tables that often break merging
    DROP_TABLES = [
        "GPOS", "GSUB", "GDEF",  # shaping tables (cause conflicts)
        "BASE",
        "JSTF",
        "vhea", "vmtx",          # vertical metrics (your current crash)
        "DSIG",
    ]

    for tag in DROP_TABLES:
        if tag in font:
            del font[tag]

def subset_font_to_temp(font_path, chars):
    import tempfile

    font = TTFont(font_path)

    options = Options()
    options.set(layout_features="*")

    subsetter = Subsetter(options=options)
    subsetter.populate(text="".join(chars))
    subsetter.subset(font)

    # 🔥 sanitize BEFORE saving
    sanitize_font(font)

    tmp = tempfile.NamedTemporaryFile(delete=False, suffix=".ttf")
    font.save(tmp.name)
    tmp.close()

    return tmp.name

def get_script_dir():
    return os.path.dirname(os.path.abspath(__file__))


def load_charset(chars_file, fallback_text):
    if os.path.exists(chars_file):
        with open(chars_file, "r", encoding="utf-8") as f:
            return f.read()
    return fallback_text


def get_cmap(font):
    cmap = {}
    for table in font["cmap"].tables:
        cmap.update(table.cmap)
    return cmap


def subset_font(font_path, chars):
    font = TTFont(font_path)

    options = Options()
    options.set(layout_features="*")

    subsetter = Subsetter(options=options)
    subsetter.populate(text="".join(chars))
    subsetter.subset(font)

    return font


def main():
    script_dir = get_script_dir()
    project_root = os.path.abspath(os.path.join(script_dir, ".."))

    # -------- PATHS --------
    fonts_dir = os.path.join(project_root, "fonts", "raw")
    lang_dir = os.path.join(fonts_dir, "languages")

    main_font_path = os.path.join(fonts_dir, "NotoSans-Medium.ttf")

    fallback_fonts = [
        os.path.join(lang_dir, "NotoSansJP-Medium.ttf"),
        os.path.join(lang_dir, "NotoSansSC-Medium.ttf"),
        os.path.join(lang_dir, "NotoSansKR-Medium.ttf"),
        os.path.join(lang_dir, "NotoSansThaiLooped-Medium.ttf"),
        os.path.join(lang_dir, "NotoNaskhArabic-Medium.ttf"),
    ]

    output_font_path = os.path.join(fonts_dir, "NotoSans-Medium-Merged.otf")

    chars_file = os.path.join(script_dir, "chars.txt")
    fallback_text = "Hello 世界 สวัสดี 😊"
    # -----------------------

    # 1. Load charset
    text = load_charset(chars_file, fallback_text)
    required_chars = set(text)

    # 2. Load main font cmap
    main_font = TTFont(main_font_path)
    main_cmap = get_cmap(main_font)

    # 3. Split supported vs missing
    main_supported = {c for c in required_chars if ord(c) in main_cmap}
    missing_chars = required_chars - main_supported

    print(f"Missing chars: {''.join(sorted(missing_chars))}")

    fonts = []

    subset_paths = []

    # Main font
    if main_supported:
        subset_paths.append(subset_font_to_temp(main_font_path, main_supported))

    # Fallbacks
    remaining = missing_chars.copy()

    for fb_path in fallback_fonts:
        fb_font = TTFont(fb_path)
        fb_cmap = get_cmap(fb_font)

        supported = {c for c in remaining if ord(c) in fb_cmap}

        if supported:
            print(f"{os.path.basename(fb_path)} provides: {''.join(sorted(supported))}")
            subset_paths.append(subset_font_to_temp(fb_path, supported))
            remaining -= supported

        if not remaining:
            break

    if remaining:
        print(f"⚠️ Still missing: {''.join(sorted(remaining))}")

    # 6. Merge subset fonts
    merger = Merger()
    merged_font = merger.merge(subset_paths)

    # 7. Save output
    merged_font.save(output_font_path)
    print(f"Saved merged font → {output_font_path}")


if __name__ == "__main__":
    main()