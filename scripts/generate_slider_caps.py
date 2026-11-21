"""Generate black, antialiased end overlays for rectangular sliders (stdlib only)."""

from pathlib import Path
import struct
import zlib


OUTPUT = Path(__file__).resolve().parents[1] / "images" / "slider_caps"
SAMPLES = 16


def chunk(kind, data):
    return (struct.pack(">I", len(data)) + kind + data
            + struct.pack(">I", zlib.crc32(kind + data) & 0xFFFFFFFF))


def save_png(path, width, height, alpha):
    # Grayscale + alpha: every color sample is black, only coverage varies.
    rows = bytearray()
    for y in range(height):
        rows.append(0)  # PNG filter: none
        for x in range(width):
            rows.extend((0, alpha[y * width + x]))
    header = struct.pack(">IIBBBBB", width, height, 8, 4, 0, 0, 0)
    path.write_bytes(b"\x89PNG\r\n\x1a\n" + chunk(b"IHDR", header)
                     + chunk(b"IDAT", zlib.compress(rows, 9)) + chunk(b"IEND", b""))


def main():
    OUTPUT.mkdir(parents=True, exist_ok=True)
    for height in (110, 90, 60):
        radius = height // 2
        alpha = []
        # Left cap: the transparent semicircle is centered at (radius, radius).
        # Pixel coverage uses subpixel centers; the right cap is an exact mirror.
        for y in range(height):
            for x in range(radius):
                outside = sum(
                    (x + (sx + 0.5) / SAMPLES - radius) ** 2
                    + (y + (sy + 0.5) / SAMPLES - radius) ** 2 > radius ** 2
                    for sy in range(SAMPLES) for sx in range(SAMPLES)
                )
                alpha.append(round(255 * outside / SAMPLES ** 2))
        mirrored = [alpha[y * radius + radius - 1 - x]
                    for y in range(height) for x in range(radius)]
        for side, coverage in (("left", alpha), ("right", mirrored)):
            path = OUTPUT / f"slider_cap_{side}_{height}.png"
            save_png(path, radius, height, coverage)
            print(f"{path.relative_to(OUTPUT.parent.parent)}: {radius} x {height}")


if __name__ == "__main__":
    main()
