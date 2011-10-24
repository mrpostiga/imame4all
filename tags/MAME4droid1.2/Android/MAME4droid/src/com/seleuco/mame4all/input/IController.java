/*
 * This file is part of MAME4droid.
 *
 * Copyright (C) 2011 David Valdeita (Seleuco)
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

package com.seleuco.mame4all.input;

public interface IController {
	
	final public static int UP_VALUE = 0x1;
	final public static int LEFT_VALUE=0x4;
	final public static int DOWN_VALUE=0x10;
	final public static int RIGHT_VALUE=0x40;
	final public static int START_VALUE=1<<8;   
	final public static int SELECT_VALUE=1<<9;
	final public static int L1_VALUE=1<<10;
	final public static int R1_VALUE=1<<11;   
	final public static int A_VALUE=1<<12;
	final public static int B_VALUE=1<<13;
	final public static int X_VALUE=1<<14;
	final public static int Y_VALUE=1<<15;
	final public static int L2_VALUE=1<<16;
	final public static int R2_VALUE=1<<17;
	
	final public static int STICK_NONE = 0;
	final public static int STICK_UP_LEFT = 1;	
	final public static int STICK_UP = 2;
	final public static int STICK_UP_RIGHT = 3;
	final public static int STICK_LEFT = 4;	
	final public static int STICK_RIGHT = 5;
	final public static int STICK_DOWN_LEFT = 6;	
	final public static int STICK_DOWN = 7;
	final public static int STICK_DOWN_RIGHT = 8;
	
	final public static int NUM_BUTTONS = 10;
	
	final public static int BTN_Y = 0;
	final public static int BTN_A = 1;
	final public static int BTN_B = 2;
	final public static int BTN_X = 3;
	final public static int BTN_L1 = 4;
	final public static int BTN_R1 = 5;
	final public static int BTN_L2 = 6;
	final public static int BTN_R2 = 7;
	final public static int BTN_SELECT = 8;
	final public static int BTN_START = 9;
	
	final public static int BTN_PRESS_STATE = 0;
	final public static int BTN_NO_PRESS_STATE = 1;
	
	
	
	//http://stackoverflow.com/questions/2949036/android-how-to-get-a-custom-view-to-redraw-partially
	//http://stackoverflow.com/questions/3874051/getting-the-dirty-region-inside-draw
	
}
