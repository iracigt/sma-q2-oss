/*
 * app_notification.h
 *
 *  Created on: Feb 12, 2020
 *      Author: iracigt
 */

#ifndef APP_APP_NOTIFICATION_H_
#define APP_APP_NOTIFICATION_H_

#include <stdint.h>

#include "applet.h"
#include "icon.h"
#include "lcd.h"
#include "nrf_gfx.h"

typedef struct{
	char *title;
	uint8_t icon;
	uint8_t fg_color;
	uint8_t bg_color;
} app_theme_t;

void notification_show(void);
void notification_set_message(char *message);
void notification_set_app(char *app_title);

void notification_process(void);
void notification_draw(void);
void notification_handle_button_evt(button_event_t *evt);

#endif /* APP_APP_NOTIFICATION_H_ */
