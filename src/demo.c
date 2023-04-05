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

static int demo_status;

static void demo_release(int signal) {
    printf("get singal[%d]\n", signal);
    demo_status = 0;
}

static void btn_event_cb(lv_event_t *e){
    printf("get event:[%d], and user data:[%.10s]\n", e->code, (char *)e->user_data);
}

static void create_ui(void) {
    lv_obj_t *btn = lv_btn_create(lv_scr_act());
    lv_obj_t *lbl = lv_label_create(btn);

    lv_label_set_text(lbl, "Hello world!");

    /* add event to btn, LV_EVENT_ALL will pass all events to callback function. The final argument
     * will be store in user_data of lv_event_t object as void pointer.
     * */
    lv_obj_add_event(btn, btn_event_cb, LV_EVENT_ALL, "test");

    lv_obj_center(lbl);
    lv_obj_center(btn);
}

int main(void) {

    demo_status = 1;
    signal(SIGINT, demo_release);
    signal(SIGTERM, demo_release);

    lv_init();

    lv_disp_t *sdl_disp =  lv_sdl_window_create(1024, 768);

    lv_theme_default_init(sdl_disp, lv_color_make(0x77, 0x44, 0xBB), lv_color_make(0x14, 0x14, 0x3C), 1, lv_font_default());

    lv_indev_t *sdl_indev = lv_sdl_mouse_create();

    sdl_indev->type = LV_INDEV_TYPE_POINTER;

    create_ui();

    while(demo_status) {
        // Run LVGL engine
        lv_tick_inc(1);
        lv_timer_handler();

        SLEEP(1);
    }

    return 0;
}
