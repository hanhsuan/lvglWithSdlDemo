# How to use lvgl, lv_drivers, SDL2 and cmake to create a GUI application

This demo code gives a brief guide for creating a GUI application with [lvgl](https://github.com/lvgl/lvgl), [lv_drivers](https://github.com/lvgl/lv_drivers), [SDL2](https://github.com/libsdl-org/SDL) and [cmake](https://cmake.org/).

## THANKS
This demo code refers from [here](https://github.com/Maldus512/lvgl_base_sdl_simulator), then modified to be compiled on Windows, MacOS and linux.

## NOTICE
* This demo will compile SDL2 from source, and you have to install development files for it on Linux. Otherwise, the GUI application wouldn't show anything on the screen. What development files are needed could be found [here for SDL2.26.x](https://github.com/libsdl-org/SDL/blob/release-2.26.x/.github/workflows/main.yml).

## COMPILE
Generating compiler configuration
```shell
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
```
Compile
```shell
cmake --build build --target all package --config Release
```
Then, there is one `LvglWithSdlDemo` binary under build/output/bin could show hello for you.
