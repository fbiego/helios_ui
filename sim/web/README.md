# Emscripten Web Build

This folder builds the exported LVGL Editor project as `index.html` using the
same generated UI library used by the desktop simulator.

## Prerequisites

Install and activate Emscripten before configuring this target. The official
recommended path is `emsdk`:

```bash
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
```

After activation, these commands should be available in the same terminal:

```bash
emcc --version
emcmake --version
emmake --version
```

If you open a new terminal or restart the editor, activate the environment
again:

```bash
source /path/to/emsdk/emsdk_env.sh
```

This project also needs CMake, Python 3 and a native C compiler. On macOS,
install the Xcode Command Line Tools if `cc` or `git` is missing.

## Build

From the project root, configure and build with the Emscripten wrappers:

```bash
emcmake cmake -S sim/web -B build/web -DCMAKE_BUILD_TYPE=Release
emmake cmake --build build/web -j
```

Or use the convenience wrapper:

```bash
scripts/web_editor.sh --serve
```

The output is written to:

- `build/web/bin/index.html` - small, editable HTML shell
- `build/web/bin/index.js` - Emscripten runtime with the WebAssembly payload
  embedded via `-sSINGLE_FILE=1`
- `build/web/bin/fbd_ui.html` - self-contained standalone HTML with the runtime,
  fallback config and hardware frame embedded

There is no required separate `.wasm` fetch.

The standalone file is named from the UI project name in `project.xml`. Disable
it with `-DWEB_STANDALONE_HTML=OFF` if you only want the split output.
The same standalone file is also copied to `preview-bin/web/fbd_ui.html`.

To build only one self-contained `index.html` instead, enable `WEB_SINGLE_HTML`:

```bash
emcmake cmake -S sim/web -B build/web-single \
  -DUI_DIR=/path/to/exported/ui \
  -DWEB_SINGLE_HTML=ON
emmake cmake --build build/web-single -j --target index
```

or:

```bash
scripts/web_editor.sh --single-html
```

In the default mode, `-sSINGLE_FILE=1` embeds the WebAssembly payload into
`index.js`, and the build also emits a standalone HTML file named after the UI.
The split output keeps separate `index.html`, `index.js`, `key_overlay.json`
and `hardware_frame.png` files. The standalone output embeds the runtime,
`key_overlay.json` fallback and `hardware_frame.png`. Runtime JSON/image edits
only affect the split output; the standalone file needs a rebuild.

## Run

Serve the output over HTTP:

```bash
python3 -m http.server 8000 -d build/web/bin
```

Then open:

```text
http://127.0.0.1:8000/
```

The first display size in `project.xml` is used by default. Override it with
query parameters when testing another target:

```text
http://127.0.0.1:8000/?w=240&h=280
```

## Assets

`sim/web/assets` is copied next to the generated `index.html` and `index.js`.
The bundled assets add a hardware frame plus clickable button hit regions and
an on-screen key overlay.

The assets are:

- `assets/key_overlay.json` - frame image path, display offset, button positions,
  labels, keyboard mappings and memory diagnostics defaults.
- `assets/hardware_frame.png` - the hardware image referenced by the
  JSON.

At build time, CMake embeds `key_overlay.json` into `index.html` as a fallback
and also copies the assets next to the generated web files. At runtime,
`index.html` fetches `key_overlay.json` from beside itself and uses that JSON to:

- place the LVGL canvas inside the frame via `hardwareFrame.ui.x/y`;
- load the frame image from `hardwareFrame.image` and use the loaded image's
  natural dimensions as the frame size;
- create invisible clickable hardware button regions from each button's
  `x/y/width/height` and optional `radius`;
- create the floating key overlay from `label`, `key`, `columns` and
  `controlsOverlay`.
- set memory diagnostics defaults from `memory.limitKiB` and
  `memory.openByDefault`.

Because the JSON is fetched at runtime, you can change `key_overlay.json` after
the build and reload the browser to try new button mappings or frame geometry.
The frame PNG can also be replaced after the build as long as the filename still
matches `hardwareFrame.image`, or the JSON is updated to the new filename.
When `WEB_SINGLE_HTML=ON`, the embedded build-time JSON and frame image are used
instead, so changes need a rebuild.

Button hit-region rounding is configured in the JSON. Use top-level
`buttonRadius` as the default for all hardware regions, and use `radius` on a
button to override it. Numeric values are treated as pixels; strings are passed
through as CSS, so both `18` and `"50%"` are valid.

Memory diagnostics are configured with the top-level `memory` object. Set
`limitKiB` to a positive KiB value to prefill the warning limit, or `0` to leave
the limit disabled. Set `openByDefault` to `true` to show the memory dialog as
soon as the page loads. These values are embedded into `index.html` at build
time as the fallback config and are also read from the runtime
`key_overlay.json` in the default multi-file build.

Use `maxScale` to cap how far the preview is enlarged. A value of `1` keeps the
UI and frame at native pixel size unless the viewport is smaller, in which case
the whole device shrinks to fit.

The frame is only shown at the native display size from `project.xml`. If you
override the display with `?w=` or `?h=`, the preview shows the bare canvas and
keeps the key overlay available, so the frame cut-out and button coordinates do
not drift out of alignment.

If `key_overlay.json` is missing or contains `{ "enabled": false }`, the web
preview falls back to a plain LVGL canvas centered in the browser. No hardware
frame image is shown, no clickable button regions are created, and no floating
key overlay is displayed. The canvas still uses the display size from
`project.xml`, or the `?w=` / `?h=` query parameters.

To reuse the web editor for another project, either replace the files in
`sim/web/assets` or point CMake at a different assets directory:

```bash
emcmake cmake -S sim/web -B build/web \
  -DUI_DIR=/path/to/exported/ui \
  -DWEB_ASSETS_DIR=/path/to/my-assets
```

Disable the frame and controls by passing a directory without
`key_overlay.json`, or by using a JSON file with:

```json
{ "enabled": false }
```

## Reuse

- `sim/web/CMakeLists.txt` fetches LVGL via `sim/shared_lvgl.cmake` into the shared `build/_deps/lvgl-src`
  folder, generates `lv_conf.h`, and adds the
  selected UI project as `lib-ui`.
- `file_list_gen.cmake` and `user_config.cmake` remain the shared source lists,
  so generated UI files and custom code are automatically reused.
- `sim/web/lv_conf_emscripten.defaults` contains only the LVGL options that
  differ for the browser target.
