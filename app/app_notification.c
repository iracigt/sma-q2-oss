/*
 * app_notification.c
 *
 *  Created on: Feb 12, 2020
 *      Author: iracigt
 */

#include <stdint.h>

#include "app_time.h"
#include "app_notification.h"
#include "screen_mgr.h"
#include "backlight.h"
#include "vibration.h"

#define NOTIF_APP_TITLE_LEN 16
#define NOTIF_MESSAGE_LEN 256
#define NOTIF_TITLE_BAR_HEIGHT 20
#define NOTIF_DISPLAY_TIME_SEC 30

static const nrf_gfx_font_desc_t * p_title_font = &m1c_14ptbFontInfo;
static const nrf_gfx_font_desc_t * p_body_font = &m1c_10ptFontInfo;
static const nrf_lcd_t * p_lcd = &nrf_lcd_lpm013m126a;

static uint8_t notif_title_fg_color = WHITE;
static uint8_t notif_title_bg_color = BLUE;
static uint8_t notif_icon = ICON_BLUETOOTH;
static time_t notif_expiration_time = 0;

static char notif_app_title[NOTIF_APP_TITLE_LEN+1] = {0};
static char notif_message[NOTIF_MESSAGE_LEN+1] = {0};

static const app_theme_t app_themes[] = {
	// {"IFTTT", ICON_PLAY, WHITE, BLACK},
	{NULL, ICON_BLUETOOTH, WHITE, GREEN},
};


void notification_set_message(char *message)
{
	strncpy(notif_message, message, NOTIF_MESSAGE_LEN);
}

void notification_set_app(char *app_title)
{
	int i;
	strncpy(notif_app_title, app_title, NOTIF_APP_TITLE_LEN);

	i = 0;
	while(app_themes[i].title) {
		if (strncmp(app_themes[i].title, notif_app_title, NOTIF_APP_TITLE_LEN) == 0) break;
		i++;
	}

	notif_title_fg_color = app_themes[i].fg_color;
	notif_title_bg_color = app_themes[i].bg_color;
	notif_icon = app_themes[i].icon;
}

void notification_show() {
	notif_expiration_time = current_time + NOTIF_DISPLAY_TIME_SEC;
	printf("CUR_TIME: %lld\n DISMISS AT: %lld\n", current_time, notif_expiration_time);
	screen_switch(APPLET_NOTIFICATION);
	backlight_on();
	vibration_alert();
}


void notification_process(void){
	if (current_time >= notif_expiration_time) {
		printf("%lld >= %lld\n", current_time, notif_expiration_time);
		screen_return();
	}
}

void notification_draw(void){

	lcd_clear(WHITE);

	int y = 20;
	nrf_gfx_rect_t appbar_bg = NRF_GFX_RECT(0, 20, LCD_WIDTH, NOTIF_TITLE_BAR_HEIGHT);
	nrf_gfx_rect_draw(p_lcd, &appbar_bg, 0, notif_title_bg_color, true);

	// Draw (notifying) app icon
	lcd_draw_icon(8, y+2, icons[notif_icon]);
	nrf_gfx_point_t title_text = NRF_GFX_POINT(32, y + (NOTIF_TITLE_BAR_HEIGHT - p_title_font->height)/2);
	nrf_gfx_print(p_lcd, &title_text, notif_title_fg_color, notif_app_title, p_title_font, false);

	y += NOTIF_TITLE_BAR_HEIGHT;

	// nrf_gfx_point_t body_text = NRF_GFX_POINT(0, y);
	// nrf_gfx_print(p_lcd, &body_text, BLACK, notif_message, p_body_font, true);
	nrf_gfx_rect_t textarea = NRF_GFX_RECT(4, y, LCD_WIDTH - 8, LCD_HEIGHT - y);
	nrf_gfx_flow_text(p_lcd, &textarea, BLACK, p_body_font, notif_message);
}

void notification_handle_button_evt(button_event_t *evt){

	if (evt->button == BUTTON_BACK && (evt->press_type == SHORT_PRESS_RELEASE|| evt->press_type == LONG_PRESS)) {
		screen_return();
	}
	else if (evt->button == BUTTON_UP && evt->press_type == SHORT_PRESS_RELEASE) {
		screen_redraw_request();
	}
	else if (evt->button == BUTTON_DOWN && evt->press_type == SHORT_PRESS_RELEASE) {
		screen_redraw_request();
	}
	else if (evt->button == BUTTON_OK && evt->press_type == SHORT_PRESS_RELEASE) {
		screen_return();
	}

}
