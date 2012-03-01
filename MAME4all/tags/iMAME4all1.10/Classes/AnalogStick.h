/*
 * This file is part of iMAME4all.
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

#import <UIKit/UIKit.h>

	#define MY_PI			3.14159265

	/* Convert between radians and degrees */
	#define RAD_TO_DEGREE(r)	((r * 180.0f) / MY_PI)
	#define DEGREE_TO_RAD(d)	(d * (MY_PI / 180.0f))

	#define absf(x)			    ((x >= 0) ? (x) : (x * -1.0f))

typedef enum
{
    StickNone,
    StickRight,
    StickUpRight,
    StickUp,
    StickUpLeft,
    StickLeft,
    StickDownLeft,
    StickDown,
    StickDownRight
} StickDirection;

@interface AnalogStickView : UIView
{
    StickDirection currentDirection;

    UIImageView *outerView;
    UIImageView *innerView;
    CGRect stickPos;

    CGPoint ptCur;

    CGPoint ptCenter;
    CGPoint ptMin;
    CGPoint ptMax;
    int stickWidth;
    int stickHeight;
    float deadZone;


	float ang;						/**< angle the joystick is being held		*/
	float mag;						/**< magnitude of the joystick (range 0-1)	*/
	float rx, ry;
}


@end
