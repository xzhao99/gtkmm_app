# gtkmm_app

Create a simple app using the GTKmm library

## build

```[]
cmake -B build/ -DCMAKE_TOOLCHAIN_FILE:PATH=C:/DevTools/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 17 2022" -A x64

cmake --build build/ --config Debug --parallel 12
```
