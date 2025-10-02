# gtkmm_app

Create a simple app using the GTKmm library

- Menubar
- Toolbar
- Workspace(Horizontal)
  - file panel(Vertical)
    - pipeline browser
    - property viewer/editor
  - rendering window(Vertical)
    - toolbar
    - rendering area
  - Data inspector area
- Status bar

## build

```[]
# Windows build
cmake -B build/ -DCMAKE_TOOLCHAIN_FILE:PATH=C:/DevTools/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 17 2022" -A x64

# if without specifying: -G "Visual Studio 17 2022" -A x64
# Ninja will be the default build tool, which would fail when building libiconv on Windows

# Linux build
cmake -B build/ -DCMAKE_TOOLCHAIN_FILE:PATH=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Debug

cmake --build build/ --config Debug --parallel 12
```
