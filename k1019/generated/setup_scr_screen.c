/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_screen(lv_ui *ui)
{
	//Write codes screen
	ui->screen = lv_obj_create(NULL);
	lv_obj_set_size(ui->screen, 480, 272);
	lv_obj_set_scrollbar_mode(ui->screen, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(ui->screen, &_car_480x272, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_opa(ui->screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_recolor_opa(ui->screen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_led_1
	ui->screen_led_1 = lv_led_create(ui->screen);
	lv_led_set_brightness(ui->screen_led_1, 255);
	lv_led_set_color(ui->screen_led_1, lv_color_hex(0xe3e3e3));
	lv_obj_set_pos(ui->screen_led_1, 47, 35);
	lv_obj_set_size(ui->screen_led_1, 38, 38);

	//Write codes screen_led_2
	ui->screen_led_2 = lv_led_create(ui->screen);
	lv_led_set_brightness(ui->screen_led_2, 255);
	lv_led_set_color(ui->screen_led_2, lv_color_hex(0xe3e3e3));
	lv_obj_set_pos(ui->screen_led_2, 110, 35);
	lv_obj_set_size(ui->screen_led_2, 38, 38);

	//Write codes screen_led_3
	ui->screen_led_3 = lv_led_create(ui->screen);
	lv_led_set_brightness(ui->screen_led_3, 255);
	lv_led_set_color(ui->screen_led_3, lv_color_hex(0xe3e3e3));
	lv_obj_set_pos(ui->screen_led_3, 171, 35);
	lv_obj_set_size(ui->screen_led_3, 38, 38);

	//Write codes screen_label_2
	ui->screen_label_2 = lv_label_create(ui->screen);
	lv_label_set_text(ui->screen_label_2, "Time");
	lv_label_set_long_mode(ui->screen_label_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_label_2, 216, 46);
	lv_obj_set_size(ui->screen_label_2, 100, 32);

	//Write style for screen_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_label_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_label_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_label_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_img_2
	ui->screen_img_2 = lv_img_create(ui->screen);
	lv_obj_add_flag(ui->screen_img_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_img_2, &_094940_alpha_259x156);
	lv_img_set_pivot(ui->screen_img_2, 50,50);
	lv_img_set_angle(ui->screen_img_2, 0);
	lv_obj_set_pos(ui->screen_img_2, 103, 90);
	lv_obj_set_size(ui->screen_img_2, 259, 156);

	//Write style for screen_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_recolor_opa(ui->screen_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->screen_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->screen_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_label_3
	ui->screen_label_3 = lv_label_create(ui->screen);
	lv_label_set_text(ui->screen_label_3, "5");
	lv_label_set_long_mode(ui->screen_label_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_label_3, 144, 176);
	lv_obj_set_size(ui->screen_label_3, 100, 32);

	//Write style for screen_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_label_3, lv_color_hex(0xc30909), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_label_3, &lv_font_Acme_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_label_3, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_label_3, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_btn_6
	ui->screen_btn_6 = lv_btn_create(ui->screen);
	ui->screen_btn_6_label = lv_label_create(ui->screen_btn_6);
	lv_label_set_text(ui->screen_btn_6_label, "No");
	lv_label_set_long_mode(ui->screen_btn_6_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_btn_6_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_btn_6, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_btn_6_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_btn_6, 216, 208);
	lv_obj_set_size(ui->screen_btn_6, 26, 24);

	//Write style for screen_btn_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_btn_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_btn_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_btn_6, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_btn_6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(ui->screen_btn_6, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui->screen_btn_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_spread(ui->screen_btn_6, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_x(ui->screen_btn_6, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(ui->screen_btn_6, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_btn_6, lv_color_hex(0xf00000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_btn_6, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_btn_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_btn_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_img_3
	ui->screen_img_3 = lv_img_create(ui->screen);
	lv_obj_add_flag(ui->screen_img_3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_img_3, &_back_alpha_476x278);
	lv_img_set_pivot(ui->screen_img_3, 50,50);
	lv_img_set_angle(ui->screen_img_3, 0);
	lv_obj_set_pos(ui->screen_img_3, 2, -2);
	lv_obj_set_size(ui->screen_img_3, 476, 278);

	//Write style for screen_img_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_recolor_opa(ui->screen_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->screen_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->screen_img_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_btn_7
	ui->screen_btn_7 = lv_btn_create(ui->screen);
	ui->screen_btn_7_label = lv_label_create(ui->screen_btn_7);
	lv_label_set_text(ui->screen_btn_7_label, "Start");
	lv_label_set_long_mode(ui->screen_btn_7_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_btn_7_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_btn_7, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_btn_7_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_btn_7, 182, 138);
	lv_obj_set_size(ui->screen_btn_7, 126, 39);

	//Write style for screen_btn_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_btn_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_btn_7, lv_color_hex(0xffc600), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_btn_7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_btn_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_btn_7, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_btn_7, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(ui->screen_btn_7, lv_color_hex(0x0d4b3b), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui->screen_btn_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_spread(ui->screen_btn_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_x(ui->screen_btn_7, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(ui->screen_btn_7, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_btn_7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_btn_7, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_btn_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_btn_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//The custom code of screen.
	

	//Update current screen layout.
	lv_obj_update_layout(ui->screen);

	//Init events for screen.
	events_init_screen(ui);
}
