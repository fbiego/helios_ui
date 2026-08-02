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
emcmake cmake -S web -B build-web -DCMAKE_BUILD_TYPE=Release
emmake cmake --build build-web -j
```

The output is written to:

- `build-web/bin/index.html` - small, editable HTML shell
- `build-web/bin/index.js` - Emscripten runtime with the WebAssembly payload
  embedded via `-sSINGLE_FILE=1`

There is no required separate `.wasm` fetch.

## Run

Serve the output over HTTP:

```bash
python3 -m http.server 8000 -d build-web/bin
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

## Reuse

- `web/CMakeLists.txt` fetches LVGL, generates `lv_conf.h`, and adds the parent
  UI project as `lib-ui`.
- `file_list_gen.cmake` and `user_config.cmake` remain the shared source lists,
  so generated UI files and custom code are automatically reused.
- `web/lv_conf_emscripten.defaults` contains only the LVGL options that differ
  for the browser target.
