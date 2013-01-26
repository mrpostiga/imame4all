/*
 * This file is part of MAME4iOS.
 *
 * Copyright (C) 2012 David Valdeita (Seleuco)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * In addition, as a special exception, Seleuco
 * gives permission to link the code of this program with
 * the MAME library (or with modified versions of MAME that use the
 * same license as MAME), and distribute linked combinations including
 * the two.  You must obey the GNU General Public License in all
 * respects for all of the code used other than MAME.  If you modify
 * this file, you may extend this exception to your version of the
 * file, but you are not obligated to do so.  If you do not wish to
 * do so, delete this exception statement from your version.
 */

#ifndef MAME4iOS_Globals_h
#define MAME4iOS_Globals_h

/* Convert between radians and degrees */
#ifndef RAD_TO_DEGREE
#define RAD_TO_DEGREE(r)	((r * 180.0f) / M_PI)
#endif
#ifndef DEGREE_TO_RAD
#define DEGREE_TO_RAD(d)	(d * (M_PI / 180.0f))
#endif

#define absf(x)			    ((x >= 0) ? (x) : (x * -1.0f))

#define NUM_BUTTONS 10
#define NUM_DPAD_ELEMENTS 9
//#define STICK4WAY (myosd_waysStick == 4 && myosd_inGame)
#define STICK4WAY (myosd_waysStick == 4 || !myosd_inGame || myosd_in_menu)
#define STICK2WAY (myosd_waysStick == 2 && myosd_inGame && !myosd_in_menu)

#define MyCGRectContainsPoint(rect, point)						\
(((point.x >= rect.origin.x) &&								\
(point.y >= rect.origin.y) &&							\
(point.x <= rect.origin.x + rect.size.width) &&			\
(point.y <= rect.origin.y + rect.size.height)) ? 1 : 0)


// See http://omegadelta.net/2011/11/04/oh-my-god-they-killed-parentviewcontroller/
#define self_parentViewController (([self parentViewController] != nil || ![self respondsToSelector:@selector(presentingViewController)]) ? [self parentViewController] : [self presentingViewController])
#define my_parentViewController(c) (([c parentViewController] != nil || ![c respondsToSelector:@selector(presentingViewController)]) ? [c parentViewController] : [c presentingViewController])

extern int myosd_video_threaded;
extern int myosd_video_width;
extern int myosd_video_height;
extern int myosd_waysStick;
extern int myosd_pxasp1;
extern int myosd_num_of_joys;
extern int myosd_inGame;
extern int myosd_exitGame;
extern int myosd_exitPause;

extern void change_pause(int value);
extern int iOS_main (int argc, char **argv);

extern unsigned long myosd_pad_status;
extern unsigned long myosd_joy_status[4];
extern float joy_analog_x[4];
extern float joy_analog_y[4];

extern int g_isIpad;
extern int g_isIphone5;

extern int g_emulation_initiated;
extern int g_emulation_paused;

extern int g_joy_used;
extern int g_iCade_used;
extern int g_wiimote_avalible;

extern int g_menu_option;

extern int g_controller_opacity;
extern int g_enable_debug_view;

extern int g_device_is_landscape;

extern int g_pref_tv_filter_land;
extern int g_pref_tv_filter_port;
extern int g_pref_scanline_filter_land;
extern int g_pref_scanline_filter_port;
extern int g_pref_smooth_land;
extern int g_pref_smooth_port;
extern int g_pref_keep_aspect_ratio_land;
extern int g_pref_keep_aspect_ratio_port;
extern int g_pref_full_screen_land;
extern int g_pref_full_screen_port;
extern int g_pref_animated_DPad;
extern int g_pref_4buttonsLand;
extern int g_pref_hide_LR;
extern int g_pref_BplusX;
extern int g_pref_full_num_buttons;
extern int g_pref_skin;
extern int g_pref_wii_DZ_value;
extern int g_pref_touch_DZ;
extern int g_pref_analog_DZ_value;
extern int g_pref_input_touch_type;
extern int g_pref_ext_control_type;
extern int g_pref_aplusb;
extern int g_pref_nativeTVOUT;
extern int g_pref_overscanTVOUT;

extern int ga_btnStates[NUM_BUTTONS];
extern int g_dpad_state;

enum { PORTRAIT_VIEW_FULL=0,
    PORTRAIT_VIEW_NOT_FULL=1,
    PORTRAIT_IMAGE_BACK=2,
    PORTRAIT_IMAGE_OVERLAY=3,
    LANDSCAPE_VIEW_FULL=4,
    LANDSCAPE_VIEW_NOT_FULL=5,
    LANDSCAPE_IMAGE_BACK=6,
    LANDSCAPE_IMAGE_OVERLAY=7,
    FRAME_RECT_LAST_VALUE=8
};

enum {
    BTN_Y_RECT=0,
    BTN_A_RECT=1,
    BTN_X_RECT=2,
    BTN_B_RECT=3,
    BTN_A_Y_RECT=4,
    BTN_X_A_RECT=5,
    BTN_B_Y_RECT=6,
    BTN_B_X_RECT=7,
    DPAD_UP_RECT=8,
    DPAD_LEFT_RECT=9,
    DPAD_DOWN_RECT=10,
    DPAD_RIGHT_RECT=11,
    DPAD_UP_LEFT_RECT=12,
    DPAD_DOWN_LEFT_RECT=13,
    DPAD_UP_RIGHT_RECT=14,
    DPAD_DOWN_RIGHT_RECT=15,
    BTN_SELECT_RECT=16,
    BTN_START_RECT=17,
    BTN_L1_RECT=18,
    BTN_R1_RECT=19,
    BTN_L2_RECT=20,
    BTN_R2_RECT=21,
    BTN_MENU_RECT=22,
    INPUT_LAST_VALUE=23
};

enum { BTN_B=0,BTN_X=1,BTN_A=2,BTN_Y=3,BTN_SELECT=4,BTN_START=5,BTN_L1=6,BTN_R1=7,BTN_L2=8,BTN_R2=9};
enum { BUTTON_PRESS=0,BUTTON_NO_PRESS=1};
enum { DPAD_NONE=0,DPAD_UP=1,DPAD_DOWN=2,DPAD_LEFT=3,DPAD_RIGHT=4,DPAD_UP_LEFT=5,DPAD_UP_RIGHT=6,DPAD_DOWN_LEFT=7,DPAD_DOWN_RIGHT=8};

enum {
    MENU_NONE               =  0,
    MENU_EXIT               =  4,
    MENU_HELP               =  5,
    MENU_OPTIONS            =  6,
    MENU_DONATE             =  9,
    MENU_DOWNLOAD           = 11,
    MENU_WIIMOTE            = 12};


enum { TOUCH_INPUT_DPAD=0,TOUCH_INPUT_DSTICK=1, TOUCH_INPUT_ANALOG=2};

enum { EXT_CONTROL_NONE=0,EXT_CONTROL_ICADE=1,EXT_CONTROL_ICP = 2,EXT_CONTROL_IMPULSE = 3};

extern const char* get_resource_path(const char* file);
extern const char* get_documents_path(const char* file);

extern int isGridlee;


#endif
