#include "lvgl.h"

// 假設這是一個全局變數或類成員變數
int now_light = 0;
int x=24;
bool change = false;
bool cancel=false;
int window_showtime = 4;  // 設定視窗計時器的初始值為5秒
char text[16]; // 用來存儲轉換後的字符串
const char* color_list[]={"green","yellow","red"};
const char* color;

lv_timer_t * window_timer = NULL; // 彈出視窗的計時器

// 彈出視窗的定時器回調函數
static void window_timer_cb(lv_timer_t * timer) {
    // 更新 label_3 以顯示剩餘時間
    char buffer[16];
    sprintf(buffer, "%d", window_showtime);
    lv_label_set_text(guider_ui.screen_label_3, buffer);

    // 每秒減少剩餘時間
    window_showtime--;

    if (window_showtime < 0) {
        lv_label_set_text(guider_ui.screen_label_3, "5");
        // 隱藏按鈕和文本框
        lv_obj_add_flag(guider_ui.screen_btn_6, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_img_2, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_label_3, LV_OBJ_FLAG_HIDDEN);
        window_showtime = 4;  // 重置計時器
        x=0;
        change = false;
        cancel=false;

        // 刪除計時器，避免再次調用
        if (window_timer != NULL) {
            lv_timer_del(window_timer);
            window_timer = NULL;
        }
    }
}

// 設定顯示按鈕與文本框並啟動計時器
void show_elements_for_5_seconds() {
	// 顯示按鈕和文本框
	lv_obj_clear_flag(guider_ui.screen_btn_6, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_img_2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_label_3, LV_OBJ_FLAG_HIDDEN);

	// 檢查計時器是否已存在
	if (window_timer == NULL) {
		// 啟動計時器
		window_timer = lv_timer_create(window_timer_cb, 1000, NULL);
	}
}

// 取消顯示
void kill() {
    lv_label_set_text(guider_ui.screen_label_3, "5");
    lv_obj_add_flag(guider_ui.screen_btn_6, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.screen_img_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.screen_label_3, LV_OBJ_FLAG_HIDDEN);
    cancel = true;
    window_showtime = 4; // 重置剩餘時間為5秒

    // 刪除計時器
    if (window_timer != NULL) {
        lv_timer_del(window_timer);
        window_timer = NULL;
    }
}

// 按鈕點擊的回調函數
static void btn_6_event_cb(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) {
        // 偵測到 screen_btn_6 被點擊，呼叫 kill 函數
        kill();
    }
}

static void m() {
	color=color_list[now_light%3];
	lv_label_set_text(guider_ui.screen_label_2, text);

    // 確保只在倒數計時的時候啟動五秒計時器
    if (change & !cancel) { // 確保窗口為可見
        show_elements_for_5_seconds();
    }

    // 根據顏色設置文本顏色和LED顏色
    if (strcmp(color, "red") == 0) {
        lv_obj_set_style_text_color(guider_ui.screen_label_2, lv_color_hex(0xFF0000), 0); // 設置為紅色
        lv_led_set_color(guider_ui.screen_led_1, lv_color_hex(0xFF0000));
        lv_led_set_color(guider_ui.screen_led_2, lv_color_hex(0xe3e3e3)); // LED其他
        lv_led_set_color(guider_ui.screen_led_3, lv_color_hex(0xe3e3e3)); // LED其他
    } else if (strcmp(color, "yellow") == 0) {
        lv_obj_set_style_text_color(guider_ui.screen_label_2, lv_color_hex(0xFFFF00), 0); // 設置為黃色
        lv_led_set_color(guider_ui.screen_led_2, lv_color_hex(0xFFFF00)); // LED黃燈
        lv_led_set_color(guider_ui.screen_led_1, lv_color_hex(0xe3e3e3)); // LED其他
        lv_led_set_color(guider_ui.screen_led_3, lv_color_hex(0xe3e3e3));
    } else if (strcmp(color, "green") == 0) {
        lv_obj_set_style_text_color(guider_ui.screen_label_2, lv_color_hex(0x00FF00), 0); // 設置為綠色
        lv_led_set_color(guider_ui.screen_led_3, lv_color_hex(0x00FF00));
        lv_led_set_color(guider_ui.screen_led_1, lv_color_hex(0xe3e3e3)); // LED其他
        lv_led_set_color(guider_ui.screen_led_2, lv_color_hex(0xe3e3e3)); // LED其他
    }
}

// 更新 text 的計時器回調函數
static void update_timer_cb(lv_timer_t * timer) {
	int tem=x;

	color=color_list[now_light%3];
    // 更新 buffer 並顯示
    sprintf(text, "%d", tem);
    m();
}

void setup_countdown_timer() {
	lv_obj_add_flag(guider_ui.screen_btn_7, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_img_3, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.screen_btn_6, LV_OBJ_FLAG_HIDDEN); // 剛啟動先隱藏 btn_6
    lv_obj_add_flag(guider_ui.screen_img_2, LV_OBJ_FLAG_HIDDEN); // 剛啟動先隱藏 img_2
    lv_obj_add_flag(guider_ui.screen_label_3, LV_OBJ_FLAG_HIDDEN);

    // 註冊按鈕點擊事件
    lv_obj_add_event_cb(guider_ui.screen_btn_6, btn_6_event_cb, LV_EVENT_ALL, NULL);

    lv_timer_create(update_timer_cb, 100, NULL);
}

void plus_running(lv_timer_t * timer){
	if(x!=0){
		x--;
	}
	else{
		now_light++;
		if(color_list[now_light%3]=="green"){
			x=24;
		}
		else if(color_list[now_light%3]=="yellow"){
			x=3;
			change=false;
			cancel=false;
		}
		else{
			x=53;
		}
	}

	if(color_list[now_light%3]=="green"){
		if(x<=19 & x>5){
			int ran = rand()%1000;
			char temp[16];
			sprintf(temp, "%d", ran);
			if(ran<=80){
				change=true;
			}
		}
	}
}

void plus_number(){
	srand(time(NULL));
	lv_timer_create(plus_running, 1000, NULL);
}

/*void custom_init() {
	setup_countdown_timer();
	plus_number();
}*/
