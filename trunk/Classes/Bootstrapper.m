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
#import <UIKit/UIKit.h>
#include <stdio.h>
#include <sys/stat.h>
#include "shared.h"


int isIpad = 0;
extern __emulation_run; 
//extern int iOS_external_width;
//extern int iOS_external_height;
CGRect rExternal;

@implementation Bootstrapper

-(void)applicationDidFinishLaunching:(NSNotification *)aNotification {

	struct CGRect rect = [[UIScreen mainScreen] bounds];
	rect.origin.x = rect.origin.y = 0.0f;
	
	//printf("Machine: '%s'\n",[[Helper machine] UTF8String]) ;
	
	//mkdir("/var/mobile/Media/ROMs/iXpectrum/downloads", 0755);
	
	mkdir(get_documents_path("iOS"), 0755);
	mkdir(get_documents_path("cfg"), 0755);
	mkdir(get_documents_path("hi"), 0755);

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
	
	deviceWindow = [[UIWindow alloc] initWithFrame:rect];
	deviceWindow.backgroundColor = [UIColor redColor];
	[deviceWindow addSubview: hrViewController.view ];
	
	[deviceWindow makeKeyAndVisible];
	 
	externalWindow = [[UIWindow alloc] initWithFrame:CGRectZero];
	externalWindow.hidden = YES;
	 	
	[[NSNotificationCenter defaultCenter] addObserver:self 
												 selector:@selector(prepareScreen) 
													 name:@"UIScreenDidConnectNotification"
												   object:nil];
        
		
    [[NSNotificationCenter defaultCenter] addObserver:self 
												 selector:@selector(prepareScreen) 
													 name:@"UIScreenDidDisconnectNotification" 
												   object:nil];
    [self prepareScreen];
	
}


- (void)applicationWillTerminate:(UIApplication *)application {
//TODO???.
/*
    // disconnect
    if (wiiMoteConHandle) {
          bt_send_cmd(&hci_disconnect, wiiMoteConHandle, 0x13); // remote closed connection
    }
    // bt_send_cmd(&btstack_set_power_mode, HCI_POWER_OFF );

    bt_close();
 */   
}

- (void)prepareScreen
{
	 @try
    {												   										       
	    if ([[UIScreen screens] count] > 1) {
	    											 	        	   					
			// Internal display is 0, external is 1.
			externalScreen = [[[UIScreen screens] objectAtIndex:1] retain];			
			screenModes =  [[externalScreen availableModes] retain];
					
			// Allow user to choose from available screen-modes (pixel-sizes).
			UIAlertView *alert = [[[UIAlertView alloc] initWithTitle:@"External Display Detected!" 
															 message:@"Choose a size for the external display." 
															delegate:self 
												   cancelButtonTitle:nil 
												   otherButtonTitles:nil] autorelease];
			for (UIScreenMode *mode in screenModes) {
				CGSize modeScreenSize = mode.size;
				[alert addButtonWithTitle:[NSString stringWithFormat:@"%.0f x %.0f pixels", modeScreenSize.width, modeScreenSize.height]];
			}
			[alert show];
			
		} else {
		     if(!__emulation_run)
		     {
		        [hrViewController startEmulation];
		     }   
		     else
		     {
		        [hrViewController setExternalView:nil];
		        externalWindow.hidden = YES;
		        [hrViewController changeUI];
		     }   
		    	
		}
	}
	 @catch(NSException* ex)
    {
        NSLog(@"Not supported tv out API!");
        if(!__emulation_run)
          [hrViewController startEmulation];
    }	
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
	//UIScreenMode *desiredMode = [screenModes objectAtIndex:buttonIndex];
	
	[externalScreen setCurrentMode:[screenModes objectAtIndex:buttonIndex]];
	[externalWindow setScreen:externalScreen];
	
	CGRect rect = CGRectZero;
/*	
	rect.size = desiredMode.size;
	rect.size.width =desiredMode.size.width;
	rect.size.height =desiredMode.size.height;
*/	 
	
	rect = externalScreen.bounds;
	externalWindow.frame = rect;
	externalWindow.clipsToBounds = YES;
	
	int  external_width = externalWindow.frame.size.width;
	int  external_height = externalWindow.frame.size.height;
	
	int width = (int)(external_width * 0.90);//overscan
    int height = (int)((width * 3) / 4);
      
    rExternal = CGRectMake( (external_width - width)/2, (external_height - height)/2, width, height);
    
    for (UIView *view in [externalWindow subviews]) {
       [view removeFromSuperview];
    }
    
    UIView *view= [[UIView alloc] initWithFrame:rect];
    view.backgroundColor = [UIColor blackColor];
    [externalWindow addSubview:view];
    [view release];
		
	[hrViewController setExternalView:view];
	externalWindow.hidden = NO;
	//[externalWindow makeKeyAndVisible];
	if(__emulation_run)
	    [hrViewController changeUI];
	else
	    [hrViewController startEmulation];
	    
    [screenModes release];
	[externalScreen release];
}

-(void)dealloc {
    [hrViewController release];
	[deviceWindow dealloc];	
	[externalWindow dealloc];
	[super dealloc];
}

@end