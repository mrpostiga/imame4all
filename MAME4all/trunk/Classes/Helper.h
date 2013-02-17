/*
 * This file is part of iMAME4all.
 *
 * Copyright (C) 2011-2013 David Valdeita (Seleuco)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses>.
 *
 * Linking iMAME4all statically or dynamically with other modules is
 * making a combined work based on iMAME4all. Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * In addition, as a special exception, the copyright holders of iMAME4all
 * give you permission to combine iMAME4all with free software programs
 * or libraries that are released under the GNU LGPL and with code included
 * in the standard release of MAME under the MAME License (or modified
 * versions of such code, with unchanged license). You may copy and
 * distribute such a system following the terms of the GNU GPL for iMAME4all
 * and the licenses of the other code concerned, provided that you include
 * the source code of that other code when and as the GNU GPL requires
 * distribution of source code.
 *
 * Note that people who make modified versions of iMAME4all are not
 * obligated to grant this special exception for their modified versions; it
 * is their choice whether to do so. The GNU General Public License
 * gives permission to release a modified version without this exception;
 * this exception also makes it possible to release a modified version
 * which carries forward this exception.
 *
 * iMAME4all is dual-licensed: Alternatively, you can license iMAME4all
 * under a MAME license, as set out in http://mamedev.org/
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

#define self_parentViewController (([self parentViewController] != nil || ![self respondsToSelector:@selector(presentingViewController)]) ? [self parentViewController] : [self presentingViewController])
#define my_parentViewController(c) (([c parentViewController] != nil || ![c respondsToSelector:@selector(presentingViewController)]) ? [c parentViewController] : [c presentingViewController])

#import <UIKit/UIKit.h>
#import "BTInquiryViewController.h"

//BTInquiryViewController *inqViewControl = nil;

@interface Helper : NSObject <BTInquiryDelegate>{



}

+ (NSString *)machine;
+ (void)startwiimote:(UIViewController *)controller;
+ (void)endwiimote;
+ (void)cancelWiiMoteSearch;

@end





