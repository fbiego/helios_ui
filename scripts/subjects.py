import xml.etree.ElementTree as ET
import re
import os

PROJECT_NAME = "helios_ui"


PROJECT_NAME_STRIPPED = PROJECT_NAME.replace("_ui", "")


# -------------------------
# Helpers
# -------------------------
def parse_access(help_text):
    if not help_text:
        return []
    match = re.search(r"\[(.*?)\]", help_text)
    return [x.strip() for x in match.group(1).split("|")] if match else []


def parse_override(help_text):
    if not help_text:
        return None
    match = re.search(r"\{(.*?)\}", help_text)
    return match.group(1) if match else None


def parse_pointer_default(help_text):
    if not help_text:
        return None
    match = re.search(r"\((.*?)\)", help_text)
    return match.group(1).strip() if match else None


def c_type(t):
    return {
        "int": "int32_t",
        "float": "float",
        "string": "const char *",
        "pointer": "void *",
        "color": "lv_color_t"
    }[t]


def lv_get(t):
    return {
        "int": "lv_subject_get_int",
        "float": "lv_subject_get_float",
        "string": "lv_subject_get_string",
        "pointer": "lv_subject_get_pointer",
        "color": "lv_subject_get_color",
    }[t]


def lv_set(t):
    return {
        "int": "lv_subject_set_int",
        "float": "lv_subject_set_float",
        "string": "lv_subject_copy_string",
        "pointer": "lv_subject_set_pointer",
        "color": "lv_subject_set_color",
    }[t]

def log_fmt(t):
    return {
        "int": "%d",
        "float": "%f",
        "string": "%s",
        "pointer": "%p",
        "color": "0x%08X"
    }[t]

def clean_help(help_text):
    if not help_text:
        return ""

    # remove [set|get|change]
    help_text = re.sub(r"\[.*?\]", "", help_text)

    # remove {pointer}
    help_text = re.sub(r"\{.*?\}", "", help_text)

    return help_text.strip()

# -------------------------
# Parse XML
# -------------------------
def load_subjects(xml_file):
    tree = ET.parse(xml_file)
    root = tree.getroot()
    subjects = []

    for s in root.find("subjects"):
        name = s.attrib["name"]
        short = name.replace("subject_", "").replace("sb_", "")
        typ = s.tag
        help_text = s.attrib.get("help", "")

        access = parse_access(help_text)
        override = parse_override(help_text)
        pointer_default = parse_pointer_default(help_text)
        effective_type = override if override else typ

        subjects.append({
            "name": name,
            "short": short,
            "type": effective_type,
            "access": access,
            "override": override,
            "pointer_default": pointer_default,
            "help": help_text,   # <-- IMPORTANT
        })

    return subjects

def gen_doc(subject, action):
    """
    action: "set" | "get" | "change"
    """
    name = subject["short"]
    help_text = clean_help(subject.get("help", ""))
    ctype = c_type(subject["type"])

    title_map = {
        "set": "Set value of",
        "get": "Get value of",
        "change": "Called when"
    }

    # Build description
    if action == "change":
        desc = f"{help_text} change callback."
    else:
        desc = f"{help_text} {action} function."

    lines = []
    lines.append("/**")
    # lines.append(f" * {title_map[action]} {help_text.lower()}.")
    lines.append(f" * {desc}")

    if action == "set":
        lines.append(f" * @param value    New value")
    elif action == "get":
        lines.append(f" * @return         Current value")
    elif action == "change":
        lines.append(f" * @param value    Updated value")

    lines.append(" */")

    return "\n".join(lines)


# -------------------------
# Header (.h)
# -------------------------
def generate_header(subjects):
    lines = []


    lines.append("""
/**
 * @file subjects.h
 * generated from globals.xml. DO NOT EDIT MANUALLY.
 */

#ifndef SUBJECTS_H
#define SUBJECTS_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
    #include "lvgl_private.h"
#else
    #include "lvgl/lvgl.h"
    #include "lvgl/lvgl_private.h"
#endif

                 
/**********************
 * INIT
 **********************/
""")

    # -------------------------
    # 1. init
    # -------------------------
    lines.append("/**")
    lines.append(" * Re-initialize subjects and attach observers.")
    lines.append(" */")
    lines.append(f"void {PROJECT_NAME_STRIPPED}_subjects_init(void);\n")

    # -------------------------
    # 2. set
    # -------------------------
    lines.append("""
/**********************
 * SET FUNCTIONS
 **********************/
""")

    for s in subjects:
        if "set" in s["access"]:
            lines.append(gen_doc(s, "set"))
            lines.append(f"void {PROJECT_NAME_STRIPPED}_subject_set_{s['short']}({c_type(s['type'])} value);")
            lines.append("")

    # -------------------------
    # 3. get
    # -------------------------
    lines.append("""
/**********************
 * GET FUNCTIONS
 **********************/
""")

    for s in subjects:
        if "get" in s["access"]:
            lines.append(gen_doc(s, "get"))
            lines.append(f"{c_type(s['type'])} {PROJECT_NAME_STRIPPED}_subject_get_{s['short']}(void);")
            lines.append("")

    # -------------------------
    # 4. change
    # -------------------------
    lines.append("""
/**********************
 * CHANGE FUNCTIONS
 **********************/
""")

    for s in subjects:
        if "change" in s["access"]:
            lines.append(gen_doc(s, "change"))
            lines.append(f"void {PROJECT_NAME_STRIPPED}_subject_{s['short']}_change({c_type(s['type'])} value);")
            lines.append("")

    lines.append("""
#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*SUBJECTS_H*/
""")

    return "\n".join(lines)



# -------------------------
# Source (.c)
# -------------------------
def generate_source(subjects):
    lines = []

    lines.append(f"""
/**
 * @file subjects.c
 * generated from globals.xml. DO NOT EDIT MANUALLY.
 */

/*********************
 *      INCLUDES
 *********************/
                 
#include \"subjects.h\"
#include \"../../{PROJECT_NAME}.h\" 
""")

    # detect used types
    used_types = sorted(set(s["type"] for s in subjects if "change" in s["access"]))

    # -------------------------
    # 1. static prototypes
    # -------------------------
    lines.append("/**********************")
    lines.append(" *  STATIC PROTOTYPES")
    lines.append(" **********************/\n")
    for t in used_types:
        lines.append(
            f"static void {t}_subject_observer_cb(lv_observer_t * observer, lv_subject_t * subject);"
        )
    lines.append("")

    # -------------------------
    # 2. init
    # -------------------------
    lines.append("/**********************")
    lines.append(" *  INIT ")
    lines.append(" **********************/\n")
    
    lines.append(f"void {PROJECT_NAME_STRIPPED}_subjects_init(void)")
    lines.append("{")

    lines.append("    /* Re-initialize non-supported subjects in the Editor */")

    # overrides first
    for s in subjects:
        if s["override"] == "pointer":
            default_value = f"(void *){s['pointer_default']}" if s["pointer_default"] else "NULL"
            lines.append(f"    lv_subject_deinit(&{s['name']});")
            lines.append(f"    lv_subject_init_pointer(&{s['name']}, {default_value});")

        elif s["type"] == "color":
            lines.append(f"    lv_subject_deinit(&{s['name']});")
            lines.append(f"    lv_subject_init_color(&{s['name']}, lv_color_hex(0xFFFFFF));")
    
    lines.append("")
    lines.append("    /* Attach observers for change notifications */")

    # observers
    for s in subjects:
        if "change" in s["access"]:
            lines.append(
                f"    lv_subject_add_observer(&{s['name']}, {s['type']}_subject_observer_cb, {PROJECT_NAME_STRIPPED}_subject_{s['short']}_change);"
            )
    lines.append("")
    lines.append("}\n")

    # -------------------------
    # 3. set
    # -------------------------
    lines.append("/**********************")
    lines.append(" * SET FUNCTIONS")
    lines.append(" **********************/\n")
    for s in subjects:
        if "set" in s["access"]:
            lines.append(f"void {PROJECT_NAME_STRIPPED}_subject_set_{s['short']}({c_type(s['type'])} value)")
            lines.append("{")
            lines.append(f"    lv_lock();")
            lines.append(f"    {lv_set(s['type'])}(&{s['name']}, value);")
            lines.append(f"    lv_unlock();")
            lines.append("}\n")

    # -------------------------
    # 4. get
    # -------------------------
    lines.append("/**********************")
    lines.append(" * GET FUNCTIONS")
    lines.append(" **********************/\n")
    for s in subjects:
        if "get" in s["access"]:
            lines.append(f"{c_type(s['type'])} {PROJECT_NAME_STRIPPED}_subject_get_{s['short']}(void)")
            lines.append("{")
            lines.append(f"    return {lv_get(s['type'])}(&{s['name']});")
            lines.append("}\n")

    # -------------------------
    # 5. weak
    # -------------------------
    lines.append("/**********************")
    lines.append(" * WEAK FUNCTIONS")
    lines.append(" **********************/\n")
    for s in subjects:
        if "change" in s["access"]:
            ctype = c_type(s["type"])
            fmt = log_fmt(s["type"])

            lines.append(
                f"void __attribute__((weak)) {PROJECT_NAME_STRIPPED}_subject_{s['short']}_change({ctype} value)"
            )
            lines.append("{")

            if s["type"] == "color":
                lines.append("    uint32_t c = lv_color_to_u32(value);")
                lines.append(
                    f"    LV_LOG_USER(\"Subject {s['short']} changed {fmt}\", c);"
                )
            else:
                lines.append(
                    f"    LV_LOG_USER(\"Subject {s['short']} changed {fmt}\", value);"
                )

            lines.append("}\n")

    # -------------------------
    # 6. static (ONE per type)
    # -------------------------
    lines.append("/**********************")
    lines.append(" * STATIC FUNCTIONS")
    lines.append(" **********************/\n")

    for t in used_types:
        lines.append(
            f"static void {t}_subject_observer_cb(lv_observer_t * observer, lv_subject_t * subject)"
        )
        lines.append("{")

        lines.append(f"    {c_type(t)} value = {lv_get(t)}(subject);")
        lines.append(f"    void (*fn)({c_type(t)}) = lv_observer_get_user_data(observer);")
        lines.append("    if(fn) fn(value);")

        lines.append("}\n")

    return "\n".join(lines)


# -------------------------
# Entry
# -------------------------
def main():
    subjects = load_subjects("globals.xml")

    custom_dir = "custom"
    if not os.path.exists(custom_dir):
        os.makedirs(custom_dir)

    subjects_dir = "custom/subjects"
    if not os.path.exists(subjects_dir):
        os.makedirs(subjects_dir)

    with open("custom/subjects/subjects.h", "w") as f:
        f.write(generate_header(subjects))

    with open("custom/subjects/subjects.c", "w") as f:
        f.write(generate_source(subjects))

    print("Generated subjects.h and subjects.c")


if __name__ == "__main__":
    main()
