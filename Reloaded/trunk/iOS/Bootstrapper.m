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
//#include "shared.h"


int isIpad = 0;
int isIphone4 = 0;
extern int __emulation_run; 
CGRect rExternal;
int nativeTVOUT = 1;
int overscanTVOUT = 1;

@implementation Bootstrapper

-(void)applicationDidFinishLaunching:(NSNotification *)aNotification {

	struct CGRect rect = [[UIScreen mainScreen] bounds];
	rect.origin.x = rect.origin.y = 0.0f;
	
	//printf("Machine: '%s'\n",[[Helper machine] UTF8String]) ;
	
	//mkdir("/var/mobile/Media/ROMs/iXpectrum/downloads", 0755);
	
	int r = chdir ("/var/mobile/Media/ROMs/MAME4iOS/");
	printf("running %d\n",r);
	
	mkdir(get_documents_path("iOS"), 0755);
	mkdir(get_documents_path("artwork"), 0755);
	mkdir(get_documents_path("cfg"), 0755);
	mkdir(get_documents_path("nvram"), 0755);
	mkdir(get_documents_path("ini"), 0755);
	mkdir(get_documents_path("snap"), 0755);
	mkdir(get_documents_path("sta"), 0755);
	mkdir(get_documents_path("hi"), 0755);
	mkdir(get_documents_path("inp"), 0755);
	mkdir(get_documents_path("memcard"), 0755);
	mkdir(get_documents_path("samples"), 0755);
	mkdir(get_documents_path("roms"), 0755);

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
	isIphone4 = [[Helper machine] rangeOfString:@"iPhone3"].location != NSNotFound;
	//isIpad = 1;
    
    // do this so we can detect keyboard in viewDidLoad
    [deviceWindow makeKeyWindow];

	hrViewController = [[EmulatorController alloc] init];
	
	deviceWindow = [[UIWindow alloc] initWithFrame:rect];
	deviceWindow.backgroundColor = [UIColor redColor];
	[deviceWindow addSubview: hrViewController.view ];
	
	[deviceWindow makeKeyAndVisible];
	 
	externalWindow = [[UIWindow alloc] initWithFrame:CGRectZero];
	externalWindow.hidden = YES;
	 	
	if(nativeTVOUT)
	{ 	
		[[NSNotificationCenter defaultCenter] addObserver:self 
													 selector:@selector(prepareScreen) 
														 name:@"UIScreenDidConnectNotification"
													   object:nil];
	        
			
	    [[NSNotificationCenter defaultCenter] addObserver:self 
													 selector:@selector(prepareScreen) 
														 name:@"UIScreenDidDisconnectNotification" 
													   object:nil];
	}	
    
    [self prepareScreen];
}

- (void)applicationWillResignActive:(UIApplication *)application {

   [Helper endwiimote]; 
   [hrViewController runMenu];
   usleep(1000000);   
}
/*
- (void)applicationDidBecomeActive:(UIApplication  *)application {
  
}

- (void)applicationWillTerminate:(UIApplication *)application {
 
}
*/

- (void)prepareScreen
{
	 @try
    {												   										       
	    if ([[UIScreen screens] count] > 1 && nativeTVOUT) {
	    											 	        	   					
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
	UIScreenMode *desiredMode = [screenModes objectAtIndex:buttonIndex];
	
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
	
	//float overscan = (desiredMode.size.width== 720) ? 0.92f : 1.0f;
	float overscan = 1 - (overscanTVOUT *  0.025f);
	
	
	//int width = (int)(external_width /* * overscan */);//overscan
    //int height = (int)((width * 3) / 4);
    
    //if(height > external_height)
    //{
    //   int  height = (int)(external_height /** overscan*/);//overscan
    //   int  width = (int)((height * 4) / 3);       
    //}
    
    //?????
    int width=external_width;
    int height=external_height; 
    /*
    	                                       UIAlertView* alert = 
                                               [[UIAlertView alloc] initWithTitle:@"Ventana"
       message:[NSString stringWithFormat:@"%@ %@ %@ %@",
       [NSNumber numberWithInt:width],
       [NSNumber numberWithInt:height],
       [NSNumber numberWithInt:overscan],
       [NSNumber numberWithInt:overscanTVOUT]
       ] 
                                                                     delegate:nil cancelButtonTitle:@"Dismiss" otherButtonTitles: nil];
                                               [alert show];                                           
                                                                                      
                                               [alert release];
    */
    width = width * overscan;    
    height = height * overscan;
    int x = (external_width - width)/2;
    int y = (external_height - height)/2;
                                       
      
    rExternal = CGRectMake( x, y, width, height);
    
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