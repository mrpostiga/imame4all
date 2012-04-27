//============================================================
//
//  droidinput.c - Implementation of MAME input routines
//
//  Copyright (c) 1996-2007, Nicola Salmoria and the MAME Team.
//  Visit http://mamedev.org for licensing and usage restrictions.
//
//  MAME4DROID MAME4iOS by David Valdeita (Seleuco)
//
//============================================================

#ifdef ANDROID
#include <android/log.h>
#endif

#include "osdepend.h"
#include "emu.h"
#include "uimenu.h"

#include "myosd.h"

enum
{
	KEY_ESCAPE,
	KEY_START,
	KEY_COIN,
	KEY_BUTTON_1,
	KEY_BUTTON_2,
	KEY_BUTTON_3,
	KEY_BUTTON_4,
	KEY_BUTTON_5,
	KEY_BUTTON_6,
	KEY_JOYSTICK_U,
	KEY_JOYSTICK_D,
	KEY_JOYSTICK_L,
	KEY_JOYSTICK_R,
	KEY_SELECT,
	KEY_LOAD,
	KEY_SAVE,
	KEY_PGUP,
	KEY_PGDN,
	KEY_TOTAL
};

enum
{
	STATE_NORMAL,
	STATE_LOADSAVE
};

static int mystate = STATE_NORMAL;

// a single input device
static input_device *keyboard_device;

// the state of each key
static UINT8 keyboard_state[KEY_TOTAL];

static INT32 keyboard_get_state(void *device_internal, void *item_internal);


void droid_ios_init_input(running_machine *machine)
{
	keyboard_device = input_device_add(machine, DEVICE_CLASS_KEYBOARD, "Keyboard", NULL);
	if (keyboard_device == NULL)
		fatalerror("Error creating keyboard device");

	input_device_item_add(keyboard_device, "Exit", &keyboard_state[KEY_ESCAPE], ITEM_ID_ESC, keyboard_get_state);

	input_device_item_add(keyboard_device, "Start", &keyboard_state[KEY_START], ITEM_ID_1, keyboard_get_state);
	input_device_item_add(keyboard_device, "Coin", &keyboard_state[KEY_COIN], ITEM_ID_2, keyboard_get_state);

	input_device_item_add(keyboard_device, "Bt_B", &keyboard_state[KEY_BUTTON_1], ITEM_ID_LCONTROL, keyboard_get_state);
	input_device_item_add(keyboard_device, "Bt_X", &keyboard_state[KEY_BUTTON_2], ITEM_ID_LALT, keyboard_get_state);
	input_device_item_add(keyboard_device, "Bt_A", &keyboard_state[KEY_BUTTON_3], ITEM_ID_SPACE, keyboard_get_state);
	input_device_item_add(keyboard_device, "Bt_Y", &keyboard_state[KEY_BUTTON_4], ITEM_ID_LSHIFT, keyboard_get_state);
	input_device_item_add(keyboard_device, "Bt_L", &keyboard_state[KEY_BUTTON_5], ITEM_ID_Z, keyboard_get_state);
	input_device_item_add(keyboard_device, "Bt_R", &keyboard_state[KEY_BUTTON_6], ITEM_ID_X, keyboard_get_state);

	input_device_item_add(keyboard_device, "JoyU", &keyboard_state[KEY_JOYSTICK_U], ITEM_ID_UP, keyboard_get_state);
	input_device_item_add(keyboard_device, "JoyD", &keyboard_state[KEY_JOYSTICK_D], ITEM_ID_DOWN, keyboard_get_state);
	input_device_item_add(keyboard_device, "JoyL", &keyboard_state[KEY_JOYSTICK_L], ITEM_ID_LEFT, keyboard_get_state);
	input_device_item_add(keyboard_device, "JoyR", &keyboard_state[KEY_JOYSTICK_R], ITEM_ID_RIGHT, keyboard_get_state);

	input_device_item_add(keyboard_device, "Load", &keyboard_state[KEY_LOAD], ITEM_ID_F7, keyboard_get_state);
	input_device_item_add(keyboard_device, "Save", &keyboard_state[KEY_SAVE], ITEM_ID_F8, keyboard_get_state);

	input_device_item_add(keyboard_device, "PGUP", &keyboard_state[KEY_PGUP], ITEM_ID_PGUP, keyboard_get_state);
	input_device_item_add(keyboard_device, "PGDN", &keyboard_state[KEY_PGDN], ITEM_ID_PGDN, keyboard_get_state);
}


void droid_ios_poll_input(running_machine *machine)
{

	long _pad_status = myosd_joystick_read(0);

	if(mystate == STATE_NORMAL)
	{
		keyboard_state[KEY_JOYSTICK_U] = ((_pad_status & MYOSD_UP) != 0) ? 0x80 : 0;
		keyboard_state[KEY_JOYSTICK_D] = ((_pad_status & MYOSD_DOWN) != 0) ? 0x80 : 0;
		keyboard_state[KEY_JOYSTICK_L] = ((_pad_status & MYOSD_LEFT) != 0) ? 0x80 : 0;
		keyboard_state[KEY_JOYSTICK_R] = ((_pad_status & MYOSD_RIGHT) != 0) ? 0x80 : 0;

		keyboard_state[KEY_BUTTON_1] = ((_pad_status & MYOSD_B) != 0) ? 0x80 : 0;
		keyboard_state[KEY_BUTTON_2] = ((_pad_status & MYOSD_X) != 0) ? 0x80 : 0;
		keyboard_state[KEY_BUTTON_3] = ((_pad_status & MYOSD_A) != 0) ? 0x80 : 0;
		keyboard_state[KEY_BUTTON_4] = ((_pad_status & MYOSD_Y) != 0) ? 0x80 : 0;
		keyboard_state[KEY_BUTTON_5] = ((_pad_status & MYOSD_L1) != 0) ? 0x80 : 0;
		keyboard_state[KEY_BUTTON_6] = ((_pad_status & MYOSD_R1) != 0) ? 0x80 : 0;

		if(myosd_exitGame)
		{
			keyboard_state[KEY_ESCAPE] = 0x80;
			myosd_exitGame = 0;
		}
	    else
	    {
			keyboard_state[KEY_ESCAPE] = 0;
        }

		if(!myosd_inGame)
		{
			keyboard_state[KEY_PGUP] = ((myosd_pad_status & MYOSD_LEFT) != 0) ? 0x80 : 0;
			keyboard_state[KEY_PGDN] = ((myosd_pad_status & MYOSD_RIGHT) != 0) ? 0x80 : 0;
		}
		else
		{
			keyboard_state[KEY_PGUP] = 0;
			keyboard_state[KEY_PGDN] = 0;
		}

	    keyboard_state[KEY_START] = ((_pad_status & MYOSD_START ) != 0) ? 0x80 : 0;

		keyboard_state[KEY_COIN] = ((_pad_status & MYOSD_SELECT ) != 0) ? 0x80 : 0;

		keyboard_state[KEY_LOAD] =  0;
		keyboard_state[KEY_SAVE] =  0;

		if(myosd_savestate)
		{
			keyboard_state[KEY_SAVE] =  0x80;
			myosd_savestate = 0;
			mystate = STATE_LOADSAVE;
		}

		if(myosd_loadstate)
		{
			keyboard_state[KEY_LOAD] =  0x80;
			myosd_loadstate = 0;
			mystate = STATE_LOADSAVE;
		}
	}
	else if(mystate == STATE_LOADSAVE)
	{
		keyboard_state[KEY_ESCAPE] = 0;
		keyboard_state[KEY_START] = 0;
		keyboard_state[KEY_COIN] = 0;

		if(myosd_exitGame)
		{
			keyboard_state[KEY_ESCAPE] = 0x80;
			myosd_exitGame = 0;
			mystate = STATE_NORMAL;
		}

		if ((_pad_status & MYOSD_B) != 0)
		{
			keyboard_state[KEY_START] = 0x80;
			mystate = STATE_NORMAL;
		}

		if ((_pad_status & MYOSD_X) != 0)
		{
			keyboard_state[KEY_COIN] = 0x80;
			mystate = STATE_NORMAL;
		}

	}
	else {/*???*/}
}

//============================================================
//  osd_customize_inputport_list
//============================================================

void osd_customize_input_type_list(input_type_desc *typelist)
{
	input_type_desc *typedesc;

	for (typedesc = typelist; typedesc != NULL; typedesc = typedesc->next)
	{
		switch (typedesc->type)
		{
			case IPT_UI_UP:
			case IPT_UI_DOWN:
			case IPT_UI_LEFT:
			case IPT_UI_RIGHT:
			case IPT_UI_CANCEL:
			case IPT_UI_PAGE_UP:
			case IPT_UI_PAGE_DOWN:
				continue;
		}

		if(typedesc->type >= __ipt_ui_start && typedesc->type <= __ipt_ui_end)
			input_seq_set_0(&typedesc->seq[SEQ_TYPE_STANDARD]);
	}

	for (typedesc = typelist; typedesc != NULL; typedesc = typedesc->next)
	{

		switch (typedesc->type)
		{
			case IPT_UI_CONFIGURE:
				input_seq_set_2(&typedesc->seq[SEQ_TYPE_STANDARD], KEYCODE_1, KEYCODE_2);
				break;
			case IPT_START1:
				input_seq_set_1(&typedesc->seq[SEQ_TYPE_STANDARD], KEYCODE_1);
				break;
			case IPT_COIN1:
				input_seq_set_1(&typedesc->seq[SEQ_TYPE_STANDARD], KEYCODE_2);
				break;
			case IPT_START2:
				input_seq_set_2(&typedesc->seq[SEQ_TYPE_STANDARD], KEYCODE_1, KEYCODE_UP);
				break;
			case IPT_COIN2:
				input_seq_set_2(&typedesc->seq[SEQ_TYPE_STANDARD], KEYCODE_2,  KEYCODE_UP);
				break;
			case IPT_START3:
				input_seq_set_2(&typedesc->seq[SEQ_TYPE_STANDARD], KEYCODE_1, KEYCODE_RIGHT);
				break;
			case IPT_COIN3:
				input_seq_set_2(&typedesc->seq[SEQ_TYPE_STANDARD], KEYCODE_2,KEYCODE_RIGHT);
				break;
			case IPT_START4:
				input_seq_set_2(&typedesc->seq[SEQ_TYPE_STANDARD], KEYCODE_1, KEYCODE_DOWN);
				break;
			case IPT_COIN4:
				input_seq_set_2(&typedesc->seq[SEQ_TYPE_STANDARD], KEYCODE_2,KEYCODE_DOWN);
				break;
			case IPT_UI_LOAD_STATE:
				input_seq_set_1(&typedesc->seq[SEQ_TYPE_STANDARD], KEYCODE_F7);
				break;
			case IPT_UI_SAVE_STATE:
				input_seq_set_1(&typedesc->seq[SEQ_TYPE_STANDARD], KEYCODE_F8);
				break;
			case IPT_UI_SELECT:
				input_seq_set_1(&typedesc->seq[SEQ_TYPE_STANDARD], KEYCODE_LCONTROL);
				break;
		}
	}
}

static INT32 keyboard_get_state(void *device_internal, void *item_internal)
{
	// this function is called by the input system to get the current key
	// state; it is specified as a callback when adding items to input
	// devices
	UINT8 *keystate = (UINT8 *)item_internal;
	return *keystate;
}

