/*
 * applet.c
 *
 *  Created on: Jan 15, 2020
 *      Author: andrju
 */

#include "applet.h"
#include "screen_mgr.h"
#include "app_hrm.h"
#include "app_music.h"
#include "tetris.h"
#include "watchface.h"
#include "app_menu.h"
#include "app_battery.h"
#include "app_notification.h"

applet_t applets[NUM_APPLETS]={
		{APPLET_WATCHFACE,watchface_process,watchface_draw,watchface_handle_button_evt,NULL,NULL,APPLET_WATCHFACE},
		{APPLET_MENU,menu_process,menu_draw,menu_handle_button_evt,NULL,NULL,0},
		{APPLET_TETRIS,tetris_process,tetris_draw,tetris_handle_button_evt,NULL,NULL,0},
		{APPLET_HRM,hrm_process,hrm_draw,hrm_handle_button_evt,hrm_enter,hrm_exit,0},
		{APPLET_MUSIC,music_process,music_draw,music_handle_button_evt,NULL,NULL,0},
		{APPLET_BATTERY,battery_process,battery_draw,battery_handle_button_evt,NULL,NULL,0},
		{APPLET_NOTIFICATION,notification_process,notification_draw,notification_handle_button_evt,NULL,NULL,0},
};
