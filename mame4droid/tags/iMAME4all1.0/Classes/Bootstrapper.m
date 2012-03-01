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

#import "Bootstrapper.h"
#import "Helper.h"
#include <stdio.h>
#include <sys/stat.h>
#include "shared.h"

int isIpad = 0;

@implementation Bootstrapper

-(void)applicationDidFinishLaunching:(NSNotification *)aNotification {

	struct CGRect rect = [[UIScreen mainScreen] bounds];
	rect.origin.x = rect.origin.y = 0.0f;
	
	//printf("Machine: '%s'\n",[[Helper machine] UTF8String]) ;
	
	//mkdir("/var/mobile/Media/ROMs/iXpectrum/downloads", 0755);
	
	mkdir(get_documents_path("iOS"), 0755);

    [[UIApplication sharedApplication] setStatusBarHidden:YES animated:NO];
    
	[[UIApplication sharedApplication] setIdleTimerDisabled:YES];//TODO ???
	/*
	BOOL iPad = NO;
	UIDevice* dev = [UIDevice currentDevice];
    if ([dev respondsToSelector:@selector(isWildcat)])
    {
       iPad = [dev isWildcat];
    }
	
	isIpad = iPad != NO;
	*/
	
	isIpad = [[Helper machine] rangeOfString:@"iPad"].location != NSNotFound;
	//isIpad = 1;

	hrViewController = [[EmulatorController alloc] init];
	
	window = [[UIWindow alloc] initWithFrame:rect];
	window.backgroundColor = [UIColor redColor];
	[window addSubview: hrViewController.view ];
	
	[window makeKeyAndVisible];
		
	[hrViewController startEmulation];

}

-(void)dealloc {
    [hrViewController release];
	[window dealloc];
	[super dealloc];
}

@end