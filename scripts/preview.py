#!/usr/bin/env python3
"""Create a glow-border watchface preview PNG from an existing image."""

from __future__ import annotations

import argparse
from pathlib import Path

try:
    from PIL import Image, ImageDraw, ImageFilter
except ImportError as exc:  # pragma: no cover - this is an environment hint.
    raise SystemExit(
        "create_preview.py needs Pillow. Install it with: python3 -m pip install Pillow"
    ) from exc


def process_preview(
    src_path: Path,
    dest_path: Path,
    scale: float = 0.75,
    glow_color: tuple[int, int, int, int] = (255, 255, 255, 255),
    glow_radius: int = 10,
    corner_radius: int | None = None,
    antialias_scale: int = 4,
) -> Image.Image:
    """Create and save a preview with a soft glow and black background.

    `corner_radius` is the radius for the source image's full-size display.
    When supplied it is scaled by `scale` so the preview keeps the same shape.
    When omitted, half of the preview size is used, which creates a circular
    crop for square watchface images.
    """
    source = Image.open(src_path).convert("RGBA")
    final_size = (
        max(1, int(source.width * scale)),
        max(1, int(source.height * scale)),
    )

    if corner_radius is None:
        scaled_corner_radius = min(final_size) // 2
    else:
        scaled_corner_radius = max(0, int(corner_radius * scale))

    shrink = max(0, glow_radius)
    antialias_scale = max(1, int(antialias_scale))
    inner_size = (
        max(1, final_size[0] - 2 * shrink),
        max(1, final_size[1] - 2 * shrink),
    )

    resampling = getattr(Image, "Resampling", Image).BILINEAR
    image = source.resize(inner_size, resampling)

    mask_size = (inner_size[0] * antialias_scale, inner_size[1] * antialias_scale)
    mask = Image.new("L", mask_size, 0)
    draw = ImageDraw.Draw(mask)
    draw.rounded_rectangle(
        [(0, 0), (mask_size[0] - 1, mask_size[1] - 1)],
        radius=max(0, scaled_corner_radius - shrink) * antialias_scale,
        fill=255,
    )
    mask = mask.resize(inner_size, resampling)
    image.putalpha(mask)

    canvas = Image.new("RGBA", final_size, (0, 0, 0, 0))
    # Build the glow from the same antialiased mask as the image.  This avoids
    # weaker corners when the display radius is rounded but not circular.
    glow_mask = Image.new("L", final_size, 0)
    glow_mask.paste(mask, (shrink, shrink))

    blurred = glow_mask.filter(ImageFilter.GaussianBlur(glow_radius / 2))
    glow = Image.new("RGBA", final_size, glow_color)
    glow.putalpha(blurred)

    result = Image.alpha_composite(canvas, glow)
    result.paste(image, (shrink, shrink), image)

    black_background = Image.new("RGBA", final_size, (0, 0, 0, 255))
    result = Image.alpha_composite(black_background, result)
    dest_path.parent.mkdir(parents=True, exist_ok=True)
    result.save(dest_path, format="PNG")
    return result


def parse_color(value: str) -> tuple[int, int, int, int]:
    """Parse RRGGBB, #RRGGBB, RRGGBBAA, or #RRGGBBAA into RGBA."""
    text = value.strip().removeprefix("#")
    if len(text) not in (6, 8):
        raise argparse.ArgumentTypeError("color must be RRGGBB or RRGGBBAA")
    try:
        red = int(text[0:2], 16)
        green = int(text[2:4], 16)
        blue = int(text[4:6], 16)
        alpha = int(text[6:8], 16) if len(text) == 8 else 255
    except ValueError as exc:
        raise argparse.ArgumentTypeError("color must contain only hex digits") from exc
    return red, green, blue, alpha


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Create a black-background glow preview PNG from an existing image."
    )
    parser.add_argument("input", type=Path, help="Source image, for example watchface.png")
    parser.add_argument(
        "output",
        type=Path,
        nargs="?",
        help="Output preview PNG path; defaults to preview.png beside the input",
    )
    parser.add_argument(
        "--scale",
        type=float,
        default=0.75,
        help="Preview size as a fraction of the source image size",
    )
    parser.add_argument(
        "--corner-radius",
        type=int,
        default=None,
        help="Full-size display corner radius; scaled to the preview size",
    )
    parser.add_argument("--glow-radius", type=int, default=10, help="Glow margin/blur radius")
    parser.add_argument(
        "--antialias-scale",
        type=int,
        default=4,
        help="Mask supersampling factor for smoother rounded edges",
    )
    parser.add_argument(
        "--glow-color",
        type=parse_color,
        default=(255, 255, 255, 255),
        help="Glow color as RRGGBB or RRGGBBAA",
    )
    args = parser.parse_args()

    output = args.output if args.output is not None else args.input.with_name("preview.png")
    preview = process_preview(
        args.input,
        output,
        scale=args.scale,
        glow_color=args.glow_color,
        glow_radius=args.glow_radius,
        corner_radius=args.corner_radius,
        antialias_scale=args.antialias_scale,
    )
    print(f"Saved {output} ({preview.width}x{preview.height})")


if __name__ == "__main__":
    main()
