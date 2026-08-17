include(FetchContent)

# Silence the FetchContent_Populate deprecation warning (CMake >= 3.30).
if(POLICY CMP0169)
  cmake_policy(SET CMP0169 OLD)
endif()

set(LVGL_SHARED_DEPS_DIR
    "${UI_DIR}/build/_deps"
    CACHE PATH
    "Shared FetchContent download directory for simulator targets")
set(LVGL_SHARED_SOURCE_DIR
    "${LVGL_SHARED_DEPS_DIR}/lvgl-src"
    CACHE PATH
    "Shared LVGL source directory")

FetchContent_Declare(
  lvgl
  GIT_REPOSITORY https://github.com/lvgl/lvgl.git
  GIT_TAG ${LVGL_VERSION}
  GIT_SHALLOW TRUE
  SOURCE_DIR "${LVGL_SHARED_SOURCE_DIR}"
  BINARY_DIR "${CMAKE_BINARY_DIR}/_deps/lvgl-build"
  SUBBUILD_DIR "${CMAKE_BINARY_DIR}/_deps/lvgl-subbuild")

FetchContent_GetProperties(lvgl)
if(EXISTS "${LVGL_SHARED_SOURCE_DIR}/CMakeLists.txt")
  set(lvgl_POPULATED TRUE)
  set(lvgl_SOURCE_DIR "${LVGL_SHARED_SOURCE_DIR}")
  set(lvgl_BINARY_DIR "${CMAKE_BINARY_DIR}/_deps/lvgl-build")
  message(STATUS "Using shared LVGL source at ${LVGL_SHARED_SOURCE_DIR}")
elseif(NOT lvgl_POPULATED)
  message(STATUS "Fetching LVGL ${LVGL_VERSION} into ${LVGL_SHARED_SOURCE_DIR}. It might take a few minutes ...")
  FetchContent_Populate(lvgl)
endif()
