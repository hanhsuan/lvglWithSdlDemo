# How to use lvgl, lv_drivers, SDL2 and cmake to create a GUI application

This demo code gives a brief guide for creating a GUI application with [lvgl](https://github.com/lvgl/lvgl), [lv_drivers](https://github.com/lvgl/lv_drivers), [SDL2](https://github.com/libsdl-org/SDL) and [cmake](https://cmake.org/).

## THANKS
Code in demo.c is copied from [here](https://github.com/Maldus512/lvgl_base_sdl_simulator).

## NOTICE
* For now, this could be compiled on Linux only and will be supported Windows and MacOS in the future.
* This demo will compile SDL2 from source, and you have to install development files for it. Otherwise, the GUI application wouldn't show anything on the screen. What development files are needed could be found [here for SDL2.26.x](https://github.com/libsdl-org/SDL/blob/release-2.26.x/.github/workflows/main.yml).

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
