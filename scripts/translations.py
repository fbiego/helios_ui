
import os
import time
import urllib.request
import hashlib
import sys
import unicodedata

SEPARATOR = '\t'  # adjust as needed

TRANSLATION_URL = "https://docs.google.com/spreadsheets/d/1Kkhgm7S61I0Yse7eFHJrI1lAU6e6LqbRIZnrsK28svI/export?format=tsv"  # Change this to your actual URL
LOCAL_FILE = "translations.tsv"
MAX_AGE_SECONDS = 60 * 5  # 5 minutes
HASH_FILE = ".translations.hash"

build = False
root = "./"

def file_folder(file_name):
    res_dir = os.path.join(root, "scripts")
    if not os.path.exists(res_dir):
        os.makedirs(res_dir)
        print("Created output folder")
    file_path = os.path.join(res_dir, file_name)
    return file_path

def download_file(url, local_filename):
    try:
        print(f"Downloading file from {url}...")
        urllib.request.urlretrieve(url, local_filename)
        print(f"Saved as {local_filename}")
        return True
    except Exception as e:
        print(f"Error downloading file: {e}")
        return False

def is_file_outdated(file_path, max_age_seconds):
    if not os.path.exists(file_path):
        return True
    file_age = time.time() - os.path.getmtime(file_path)
    return file_age > max_age_seconds

def calculate_hash(file_path):
    sha256 = hashlib.sha256()
    with open(file_path, 'rb') as f:
        while chunk := f.read(8192):
            sha256.update(chunk)
    return sha256.hexdigest()

def read_stored_hash():
    if os.path.exists(file_folder(HASH_FILE)):
        with open(file_folder(HASH_FILE), 'r') as f:
            return f.read().strip()
    return ""

def store_hash(new_hash):
    with open(file_folder(HASH_FILE), 'w') as f:
        f.write(new_hash)

def main():
    force = "--force" in sys.argv
    build = "--build" in sys.argv

    global root
    if build:
        root = "./scripts"
        print("Checking translation file from build...")
    else:
        root = "."
        print("Checking translation file...")

    if is_file_outdated(file_folder(LOCAL_FILE), MAX_AGE_SECONDS):
        print("Translation file outdated, downloading")
        if not download_file(TRANSLATION_URL, file_folder(LOCAL_FILE)):
            print("Translation file download failed")
            return

    if not os.path.exists(file_folder(LOCAL_FILE)):
        print("Translation file not found.")
        return

    current_hash = calculate_hash(file_folder(LOCAL_FILE))
    stored_hash = read_stored_hash()

    if current_hash == stored_hash and not force:
        print("No changes detected. Skipping generation.")
        return

    with open(file_folder(LOCAL_FILE), 'r', encoding='utf-8') as f:
        data = [line.strip() for line in f if line.strip()]

    if data:
        generate(data)
        store_hash(current_hash)
        print("-----Done-------")
    else:
        print(f"Could not read from {LOCAL_FILE}")

def generate(strings):
    lang = strings[0].count(SEPARATOR)
    print(f"Languages: {lang}")
    
    res_dir = os.path.join(root)
    # res_dir = os.path.join("test", "res")
    if not os.path.exists(res_dir):
        os.makedirs(res_dir)
        print("Created output folder")

    tags = []
    output = ""
    for s in strings:
        word = s.split(SEPARATOR)
        if word[0].strip() == "" or word[0] == "formula" or word[0] == "ai" or word[0] == "unique" or word[0] == "#VALUE!":
            continue
        if word[0] == "id":
            tags.extend(word[1:])
            print(tags)
            output = f'<translations languages="{' '.join(tags)}">\n'

            # for t in tags:
            #     print(f'case {tags.index(t)}: lv_translation_set_language("{t}"); break;\n')
        if word[0] == "locale":
            print('\n'.join(word[1:]))

        max_length = max(len(w) for w in word[1:]) + 1

        trans = ""
        x = 0
        for w in word[1:]:
            trans += f'{tags[x]}="{w}" '
            x+=1
        output += (f'\t<translation tag="{word[0]}" char_count="{max_length}" {trans} />\n')


    output = output.replace("&", "&amp;") #.replace("'", "\\'")
    # add = add.replace("&", "&amp;").replace("'", "\\'")

    output += "</translations>"


    file_path = os.path.join(res_dir, "translations.xml")
    if os.path.exists(file_path):
        with open(file_path, 'w', encoding='utf-8') as f:
            f.write(output)
    else:
        with open(file_path, 'w', encoding='utf-8') as f:
            f.write(output)

    print(f"Generated: translations.xml")


if __name__ == "__main__":
    main()