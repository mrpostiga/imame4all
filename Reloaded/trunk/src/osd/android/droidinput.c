//============================================================
//
//  droidinput.c - Implementation of MAME input routines
//
//  Copyright (c) 1996-2007, Nicola Salmoria and the MAME Team.
//  Visit http://mamedev.org for licensing and usage restrictions.
//
//  MAME4DROID by David Valdeita (Seleuco)
//
//============================================================

#ifdef ANDROID
#include <android/log.h>
#endif

#include "osdepend.h"
#include "mame.h"

#include "myosd.h"

enum
{
	KEY_ESCAPE,
	KEY_P1_START,
	KEY_P2_START,
	KEY_P3_START,
	KEY_P4_START,
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
	KEY_P1_COIN,
	KEY_P2_COIN,
	KEY_P3_COIN,
	KEY_P4_COIN,
	KEY_MENU,
	KEY_SELECT,
	KEY_LOADSAVE,
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


void droid_init_input(running_machine *machine)
{
	keyboard_device = input_device_add(machine, DEVICE_CLASS_KEYBOARD, "Keyboard", NULL);
	if (keyboard_device == NULL)
		fatalerror("Error creating keyboard device");

	input_device_item_add(keyboard_device, "Esc", &keyboard_state[KEY_ESCAPE], ITEM_ID_ESC, keyboard_get_state);

	input_device_item_add(keyboard_device, "P1", &keyboard_state[KEY_P1_START], ITEM_ID_1, keyboard_get_state);
	input_device_item_add(keyboard_device, "P2", &keyboard_state[KEY_P2_START], ITEM_ID_2, keyboard_get_state);
	input_device_item_add(keyboard_device, "P3", &keyboard_state[KEY_P3_START], ITEM_ID_3, keyboard_get_state);
	input_device_item_add(keyboard_device, "P4", &keyboard_state[KEY_P4_START], ITEM_ID_4, keyboard_get_state);

	input_device_item_add(keyboard_device, "B1", &keyboard_state[KEY_BUTTON_1], ITEM_ID_LCONTROL, keyboard_get_state);
	input_device_item_add(keyboard_device, "B2", &keyboard_state[KEY_BUTTON_2], ITEM_ID_LALT, keyboard_get_state);
	input_device_item_add(keyboard_device, "B3", &keyboard_state[KEY_BUTTON_3], ITEM_ID_SPACE, keyboard_get_state);
	input_device_item_add(keyboard_device, "B4", &keyboard_state[KEY_BUTTON_4], ITEM_ID_LSHIFT, keyboard_get_state);
	input_device_item_add(keyboard_device, "B5", &keyboard_state[KEY_BUTTON_5], ITEM_ID_Z, keyboard_get_state);
	input_device_item_add(keyboard_device, "B6", &keyboard_state[KEY_BUTTON_6], ITEM_ID_X, keyboard_get_state);

	input_device_item_add(keyboard_device, "JoyU", &keyboard_state[KEY_JOYSTICK_U], ITEM_ID_UP, keyboard_get_state);
	input_device_item_add(keyboard_device, "JoyD", &keyboard_state[KEY_JOYSTICK_D], ITEM_ID_DOWN, keyboard_get_state);
	input_device_item_add(keyboard_device, "JoyL", &keyboard_state[KEY_JOYSTICK_L], ITEM_ID_LEFT, keyboard_get_state);
	input_device_item_add(keyboard_device, "JoyR", &keyboard_state[KEY_JOYSTICK_R], ITEM_ID_RIGHT, keyboard_get_state);

	input_device_item_add(keyboard_device, "C1", &keyboard_state[KEY_P1_COIN], ITEM_ID_5, keyboard_get_state);
	input_device_item_add(keyboard_device, "C2", &keyboard_state[KEY_P2_COIN], ITEM_ID_6, keyboard_get_state);
	input_device_item_add(keyboard_device, "C3", &keyboard_state[KEY_P3_COIN], ITEM_ID_7, keyboard_get_state);
	input_device_item_add(keyboard_device, "C4", &keyboard_state[KEY_P4_COIN], ITEM_ID_8, keyboard_get_state);

	input_device_item_add(keyboard_device, "Menu", &keyboard_state[KEY_MENU], ITEM_ID_TAB, keyboard_get_state);
	input_device_item_add(keyboard_device, "Select", &keyboard_state[KEY_SELECT], ITEM_ID_ENTER, keyboard_get_state);
	input_device_item_add(keyboard_device, "LOADSAVE", &keyboard_state[KEY_LOADSAVE], ITEM_ID_F7, keyboard_get_state);

	input_device_item_add(keyboard_device, "PGUP", &keyboard_state[KEY_PGUP], ITEM_ID_PGUP, keyboard_get_state);
	input_device_item_add(keyboard_device, "PGDN", &keyboard_state[KEY_PGDN], ITEM_ID_PGDN, keyboard_get_state);
}


void droid_poll_input(running_machine *machine)
{

	if(mystate == STATE_NORMAL)
	{
		keyboard_state[KEY_JOYSTICK_U] = ((myosd_pad_status & MYOSD_UP) != 0) ? 0x80 : 0;
		keyboard_state[KEY_JOYSTICK_D] = ((myosd_pad_status & MYOSD_DOWN) != 0) ? 0x80 : 0;
		keyboard_state[KEY_JOYSTICK_L] = ((myosd_pad_status & MYOSD_LEFT) != 0) ? 0x80 : 0;
		keyboard_state[KEY_JOYSTICK_R] = ((myosd_pad_status & MYOSD_RIGHT) != 0) ? 0x80 : 0;

		keyboard_state[KEY_BUTTON_1] = ((myosd_pad_status & MYOSD_B) != 0) ? 0x80 : 0;
		keyboard_state[KEY_BUTTON_2] = ((myosd_pad_status & MYOSD_X) != 0) ? 0x80 : 0;
		keyboard_state[KEY_BUTTON_3] = ((myosd_pad_status & MYOSD_A) != 0) ? 0x80 : 0;
		keyboard_state[KEY_BUTTON_4] = ((myosd_pad_status & MYOSD_Y) != 0) ? 0x80 : 0;
		keyboard_state[KEY_BUTTON_5] = ((myosd_pad_status & MYOSD_L1) != 0) ? 0x80 : 0;
		keyboard_state[KEY_BUTTON_6] = ((myosd_pad_status & MYOSD_R1) != 0) ? 0x80 : 0;

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

		if(myosd_exitGame)
		{
			keyboard_state[KEY_ESCAPE] = 0x80;
			myosd_exitGame = 0;
		}
		else
		{
			keyboard_state[KEY_ESCAPE] = 0;
		}

		keyboard_state[KEY_SELECT] = ((myosd_pad_status & MYOSD_B) != 0) ? 0x80 : 0;

		keyboard_state[KEY_MENU] = 0;
		keyboard_state[KEY_P1_COIN] = 0;
		keyboard_state[KEY_P2_COIN] = 0;
		keyboard_state[KEY_P3_COIN] = 0;
		keyboard_state[KEY_P4_COIN] = 0;
		keyboard_state[KEY_P1_START] = 0;
		keyboard_state[KEY_P2_START] = 0;
		keyboard_state[KEY_P3_START] = 0;
		keyboard_state[KEY_P4_START] = 0;
		if(((myosd_pad_status & MYOSD_SELECT) != 0) &&  ((myosd_pad_status & MYOSD_START) != 0))
		{
		   keyboard_state[KEY_MENU] = 0x80;
		}
		else
		{
		   if(((myosd_pad_status & MYOSD_SELECT ) != 0) && ((myosd_pad_status & MYOSD_RIGHT ) != 0))
			   keyboard_state[KEY_P3_COIN] = 0x80;
		   else if(((myosd_pad_status & MYOSD_SELECT ) != 0 && (myosd_pad_status & MYOSD_UP ) != 0))
			   keyboard_state[KEY_P2_COIN] = 0x80;
		   else if(((myosd_pad_status & MYOSD_SELECT ) != 0 && (myosd_pad_status & MYOSD_DOWN ) != 0))
			   keyboard_state[KEY_P4_COIN] = 0x80;
		   else if ((myosd_pad_status & MYOSD_SELECT ) != 0)
			   keyboard_state[KEY_P1_COIN] = 0x80;

		   if((myosd_pad_status & MYOSD_START ) != 0 && (myosd_pad_status & MYOSD_DOWN ) != 0)
			   keyboard_state[KEY_P4_START] = 0x80;
		   else if((myosd_pad_status & MYOSD_START ) != 0 && (myosd_pad_status & MYOSD_RIGHT ) != 0)
			   keyboard_state[KEY_P3_START] = 0x80;
		   else if((myosd_pad_status & MYOSD_START ) != 0 && (myosd_pad_status & MYOSD_UP ) != 0)
			   keyboard_state[KEY_P2_START] = 0x80;
		   else if ((myosd_pad_status & MYOSD_START ) != 0)
			   keyboard_state[KEY_P1_START] = 0x80;

		}


		keyboard_state[KEY_LOADSAVE] =  0;
		//crear save state
		if(myosd_savestate)
		{
			keyboard_state[KEY_LOADSAVE] =  0x80;
			keyboard_state[KEY_BUTTON_4] =  0x80;
			myosd_savestate = 0;
			mystate = STATE_LOADSAVE;
		}
		//leer save state
		if(myosd_loadstate)
		{
			keyboard_state[KEY_LOADSAVE] =  0x80;
			myosd_loadstate = 0;
			mystate = STATE_LOADSAVE;
		}
	}
	else if(mystate == STATE_LOADSAVE)
	{
		keyboard_state[KEY_ESCAPE] = 0;
		keyboard_state[KEY_P1_START] = 0;
		keyboard_state[KEY_P2_START] = 0;
		keyboard_state[KEY_P3_START] = 0;
		keyboard_state[KEY_P4_START] = 0;

		if(myosd_exitGame)
		{
			keyboard_state[KEY_ESCAPE] = 0x80;
			myosd_exitGame = 0;
			mystate = STATE_NORMAL;
		}

		if ((myosd_pad_status & MYOSD_START ) != 0)
		{
			keyboard_state[KEY_P1_START] = 0x80;
			mystate = STATE_NORMAL;
		}

		if ((myosd_pad_status & MYOSD_SELECT ) != 0)
		{
			keyboard_state[KEY_P2_START] = 0x80;
			mystate = STATE_NORMAL;
		}

		if ((myosd_pad_status & MYOSD_B) != 0)
		{
			keyboard_state[KEY_P3_START] = 0x80;
			mystate = STATE_NORMAL;
		}

		if ((myosd_pad_status & MYOSD_X) != 0)
		{
			keyboard_state[KEY_P4_START] = 0x80;
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

}

static INT32 keyboard_get_state(void *device_internal, void *item_internal)
{
	// this function is called by the input system to get the current key
	// state; it is specified as a callback when adding items to input
	// devices
	UINT8 *keystate = (UINT8 *)item_internal;
	return *keystate;
}

