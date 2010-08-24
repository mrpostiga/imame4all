/*
 * This file is part of iMAME4all.
 *
 * Copyright (C) 2010 David Valdeita (Seleuco)
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

/*

iPhone Simulator == i386
iPhone == iPhone1,1
3G iPhone == iPhone1,2
3GS iPhone == iPhone2,1
1st Gen iPod == iPod1,1
2nd Gen iPod == iPod2,1

1st Gen iPad == iPad1,1
iPhone 4 == iPhone3,1

I imagine the iPod Touch 4 will be == iPod3,1
and the 2011 next generation iPad will be == iPad2,1

 */

enum  { GP2X_UP=0x1,       GP2X_LEFT=0x4,       GP2X_DOWN=0x10,  GP2X_RIGHT=0x40,
	      GP2X_START=1<<8,   GP2X_SELECT=1<<9,    GP2X_L=1<<10,    GP2X_R=1<<11,
	      GP2X_A=1<<12,      GP2X_B=1<<13,        GP2X_X=1<<14,    GP2X_Y=1<<15,
        GP2X_VOL_UP=1<<23, GP2X_VOL_DOWN=1<<22, GP2X_PUSH=1<<27 };

extern unsigned long gp2x_pad_status;


#import <UIKit/UIKit.h>
#import "BTInquiryViewController.h"

//BTInquiryViewController *inqViewControl = nil;

@interface Helper : NSObject <BTInquiryDelegate>{



}

+ (NSString *)machine;
+ (void)startwiimote:(UIViewController *)controller;
+ (void)cancelWiiMoteSearch;

@end





