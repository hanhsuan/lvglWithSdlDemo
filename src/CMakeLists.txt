ADD_EXECUTABLE(${PROJECT_NAME} demo.c)

SET(LV_CONF_PATH
    ${PROJECT_SOURCE_DIR}/include/lv_conf.h
    CACHE STRING "" FORCE)

SET(LV_CONF_INCLUDE_SIMPLE
   ${PROJECT_SOURCE_DIR}/include/
   CACHE STRING "" FORCE)

SET(SDL_TEST OFF)
SET(SDL_SHARED OFF)
INCLUDE(FetchContent)
FetchContent_Declare(sdl
                     GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
		     GIT_TAG release-2.26.4)


FetchContent_Declare(lvgl
                     GIT_REPOSITORY https://github.com/lvgl/lvgl.git
                     GIT_TAG release/v8.3)


FetchContent_Declare(lv_drivers
                     GIT_REPOSITORY https://github.com/lvgl/lv_drivers
                     GIT_TAG release/v8.3)
FetchContent_MakeAvailable(sdl lv_drivers lvgl)

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
TARGET_INCLUDE_DIRECTORIES(lv_drivers PUBLIC ${sdl_SOURCE_DIR}/include)
IF(MSVC)
    # don't show console window
    TARGET_LINK_OPTIONS(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
    TARGET_LINK_OPTIONS(${PROJECT_NAME} PRIVATE "/ENTRY:mainCRTStartup")

    TARGET_COMPILE_OPTIONS(${PROJECT_NAME} PUBLIC "/W4" "Zc:preprocessor")
    ADD_COMPILE_DEFINITIONS(_CRT_SECURE_NO_WARNINGS)
ELSE()
    TARGET_COMPILE_OPTIONS(${PROJECT_NAME} PUBLIC "-pedantic" "-Wall" "-Wextra" "-Wpedantic" "-Werror")
ENDIF()
TARGET_LINK_LIBRARIES(${PROJECT_NAME} PRIVATE lvgl::lvgl lvgl::drivers SDL2::SDL2-static SDL2::SDL2main)
