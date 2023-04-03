#include <stdio.h>
#include <signal.h>
#include <time.h>
#ifdef WIN32
#include <windows.h>
#define SLEEP(s) Sleep((DWORD)s)
#else
#include <unistd.h>
#define SLEEP(s) usleep(s * 1000)
#endif
#include "lvgl.h"
#include "sdl/sdl.h"

static int demo_status;

static void demo_release(int signal) {
    printf("get singal[%d]\n", signal);
    demo_status = 0;
}

static void create_ui(void) {
    lv_obj_t *btn = lv_btn_create(lv_scr_act());
    lv_obj_t *lbl = lv_label_create(btn);
    lv_obj_set_style_text_font(lbl, &lv_font_simsun_16_cjk, 0);

    lv_label_set_text(lbl, "Hello world! 歡迎");

    lv_obj_center(lbl);
    lv_obj_center(btn);
}

static void driver_init(void) {
#define BUFFER_SIZE (SDL_HOR_RES * SDL_VER_RES)
    /*A static or global variable to store the buffers*/
    static lv_disp_draw_buf_t disp_buf;

    /*Static or global buffer(s). The second buffer is optional*/
    static lv_color_t *buf_1[BUFFER_SIZE] = {0};

    /*Initialize `disp_buf` with the buffer(s). With only one buffer use NULL instead buf_2 */
    lv_disp_draw_buf_init(&disp_buf, buf_1, NULL, BUFFER_SIZE);

    static lv_disp_drv_t disp_drv;         /*A variable to hold the drivers. Must be static or global.*/
    lv_disp_drv_init(&disp_drv);           /*Basic initialization*/
    disp_drv.draw_buf = &disp_buf;         /*Set an initialized buffer*/
    disp_drv.flush_cb = sdl_display_flush; /*Set a flush callback to draw to the display*/
    disp_drv.hor_res  = SDL_HOR_RES;       /*Set the horizontal resolution in pixels*/
    disp_drv.ver_res  = SDL_VER_RES;       /*Set the vertical resolution in pixels*/

    lv_disp_t *disp = lv_disp_drv_register(&disp_drv); /*Register the driver and save the created display objects*/
    lv_theme_default_init(disp, lv_color_make(0x77, 0x44, 0xBB), lv_color_make(0x14, 0x14, 0x3C), 1, lv_font_default());

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv); /*Basic initialization*/
    indev_drv.type    = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = sdl_mouse_read;
    lv_indev_drv_register(&indev_drv);
}

int main(void) {

    demo_status = 1;
    signal(SIGINT, demo_release);
    signal(SIGTERM, demo_release);

    lv_init();
    sdl_init();

    driver_init();
    create_ui();

    while(demo_status) {
        // Run LVGL engine
        lv_tick_inc(1);
        lv_timer_handler();

        SLEEP(1);
    }

    return 0;
}
