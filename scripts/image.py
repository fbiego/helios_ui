import os
import re
from pathlib import Path

def clean_name(filename):
    return re.sub(r'^\d{3}-', '', filename)


# Folder containing the PNG files
script_dir = Path(__file__).resolve().parent
folder_path = (script_dir / "../images").resolve()

png_files = list(folder_path.rglob("*.png"))

# Generate XML lines
for path in png_files:
    filename = os.path.basename(path)
    filename = clean_name(filename)
    relative_path = path.relative_to(folder_path)
    full_relative = Path("images") / relative_path
    # print("Path:", full_relative)
    # print("Name:", filename)
    if filename.startswith('image_'):
        filename = filename[len('image_'):]
    filename = filename.replace('.png', '')
    
    folders = str(full_relative).split("/")[1:-1]
    fold = ""
    if len(folders) > 0:
        fold = folders[0] + "_"

    # Print the XML line
    print(f'<data name="icon_{fold}{filename}" src_path="{full_relative}" color_format="rgb565a8" />')
    # <data name="icon_application" src_path="images/apps/application.png" color_format="rgb565a8" />
