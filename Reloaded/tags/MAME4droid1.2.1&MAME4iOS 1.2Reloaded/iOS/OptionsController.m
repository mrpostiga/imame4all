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

#import "OptionsController.h"
#import "Helper.h"
#include <stdio.h>
//#include "shared.h"

extern int isIpad;
extern int isIphone4;

@implementation Options

@synthesize keepAspectRatioPort;
@synthesize keepAspectRatioLand;
@synthesize smoothedLand;
@synthesize smoothedPort;

@synthesize tvFilterLand;
@synthesize tvFilterPort;
@synthesize scanlineFilterLand;
@synthesize scanlineFilterPort;

@synthesize showFPS;
@synthesize showINFO;
@synthesize animatedButtons;
@synthesize fourButtonsLand;
@synthesize fullLand;
@synthesize fullPort;

@synthesize skin;

@synthesize wiiDeadZoneValue;
@synthesize touchDeadZone;

@synthesize overscanValue;
@synthesize tvoutNative;

@synthesize inputTouchType;
@synthesize analogDeadZoneValue;
@synthesize iCadeLayout;

@synthesize SoundKHZ;
@synthesize soundEnabled;

@synthesize throttle;
@synthesize fskip;
@synthesize fslevel;
@synthesize sticktype;
@synthesize numbuttons;
@synthesize aplusb;
@synthesize cheats;
@synthesize sleep;

@synthesize forcepxa;
@synthesize emures;
@synthesize p1aspx;
   
- (id)init {

    if (self = [super init]) {
        [self loadOptions];
    }

    return self;
}


- (void)loadOptions
{
	
	NSString *path=[NSString stringWithCString:get_documents_path("iOS/options_v5.bin")];
	
	NSData *plistData;
	id plist;
	NSString *error;
	
	NSPropertyListFormat format;
	
    NSError *sqerr;
	plistData = [NSData dataWithContentsOfFile:path options: NSMappedRead error:&sqerr];
		
	plist = [NSPropertyListSerialization propertyListFromData:plistData			 
											 mutabilityOption:NSPropertyListImmutable			 
													   format:&format
											 errorDescription:&error];
	if(!plist)
	{
		
		//NSLog(error);
		
		//[error release];
		
		optionsArray = [[NSMutableArray alloc] init];
		
		keepAspectRatioPort=1;
		keepAspectRatioLand=1;
		smoothedPort=isIpad?1:0;
		smoothedLand=isIpad?1:0;
				
		tvFilterPort = 0;
        tvFilterLand = 0;
        scanlineFilterPort = 0;
        scanlineFilterLand = 0;
        
        showFPS = 0;
        showINFO = 1;
        fourButtonsLand = 0;
        animatedButtons = ![[Helper machine] isEqualToString: @"iPhone1,1"] 
		              && ![[Helper machine] isEqualToString: @"iPhone1,2"] 		               
		              && ![[Helper machine] isEqualToString: @"iPod1,1"]		              
		              ;
		              
        fullLand = animatedButtons;
        fullPort = 0;
        
        if(isIpad)
        {
           skin = 0;
        }
        else if( [[Helper machine] isEqualToString: @"iPhone1,1"] || 
		         [[Helper machine] isEqualToString: @"iPhone1,2"] ||
		         [[Helper machine] isEqualToString: @"iPhone2,1"] ||		               
		         [[Helper machine] isEqualToString: @"iPod1,1"]   ||
                 [[Helper machine] isEqualToString: @"iPod2,1"])
        {
           skin = 1;
        }
        else
        {
           skin = 0;
        }
        
        
        wiiDeadZoneValue = 2;
        touchDeadZone = 1;
        
        overscanValue = 3;
        tvoutNative = 1;
        
        inputTouchType = 1;
        analogDeadZoneValue = 2;		
        
        iCadeLayout = 0;
        
        SoundKHZ = 4;
        soundEnabled = 1;
        
        throttle = 1;
        fskip = 2;
        fslevel = 5;
        sticktype = 2;
        numbuttons = 5;
        aplusb = 0;
        cheats = 1;
        sleep = 1;
        
        forcepxa = 0;
        emures = 0;

        p1aspx = 0;        
		//[self saveOptions];
	}
	else
	{
		
		optionsArray = [[NSMutableArray alloc] initWithArray:plist];
		
		keepAspectRatioPort = [[[optionsArray objectAtIndex:0] objectForKey:@"KeepAspectPort"] intValue];
		keepAspectRatioLand = [[[optionsArray objectAtIndex:0] objectForKey:@"KeepAspectLand"] intValue];
		smoothedLand = [[[optionsArray objectAtIndex:0] objectForKey:@"SmoothedLand"] intValue];
		smoothedPort = [[[optionsArray objectAtIndex:0] objectForKey:@"SmoothedPort"] intValue];	
		
	    tvFilterPort = [[[optionsArray objectAtIndex:0] objectForKey:@"TvFilterPort"] intValue];
        tvFilterLand =  [[[optionsArray objectAtIndex:0] objectForKey:@"TvFilterLand"] intValue];
        
        scanlineFilterPort =  [[[optionsArray objectAtIndex:0] objectForKey:@"ScanlineFilterPort"] intValue];
        scanlineFilterLand =  [[[optionsArray objectAtIndex:0] objectForKey:@"ScanlineFilterLand"] intValue];

        showFPS =  [[[optionsArray objectAtIndex:0] objectForKey:@"showFPS"] intValue];
        showINFO =  [[[optionsArray objectAtIndex:0] objectForKey:@"showINFO"] intValue];
        fourButtonsLand =  [[[optionsArray objectAtIndex:0] objectForKey:@"fourButtonsLand"] intValue];
        animatedButtons =  [[[optionsArray objectAtIndex:0] objectForKey:@"animatedButtons"] intValue];	
        fullLand =  [[[optionsArray objectAtIndex:0] objectForKey:@"fullLand"] intValue];
        fullPort =  [[[optionsArray objectAtIndex:0] objectForKey:@"fullPort"] intValue];
        
        skin =  [[[optionsArray objectAtIndex:0] objectForKey:@"skin"] intValue];
        
        wiiDeadZoneValue =  [[[optionsArray objectAtIndex:0] objectForKey:@"wiiDeadZoneValue"] intValue];
        touchDeadZone =  [[[optionsArray objectAtIndex:0] objectForKey:@"touchDeadZone"] intValue];

        overscanValue =  [[[optionsArray objectAtIndex:0] objectForKey:@"overscanValue"] intValue];
        tvoutNative =  [[[optionsArray objectAtIndex:0] objectForKey:@"tvoutNative"] intValue];
        
        inputTouchType =  [[[optionsArray objectAtIndex:0] objectForKey:@"inputTouchType"] intValue];
        analogDeadZoneValue =  [[[optionsArray objectAtIndex:0] objectForKey:@"analogDeadZoneValue"] intValue];    
        iCadeLayout =  [[[optionsArray objectAtIndex:0] objectForKey:@"iCadeLayout"] intValue];

        SoundKHZ =  [[[optionsArray objectAtIndex:0] objectForKey:@"SoundKHZ"] intValue];
        soundEnabled =  [[[optionsArray objectAtIndex:0] objectForKey:@"soundEnabled"] intValue];
                
        throttle  =  [[[optionsArray objectAtIndex:0] objectForKey:@"throttle"] intValue];
        fskip  =  [[[optionsArray objectAtIndex:0] objectForKey:@"fskip"] intValue];
        fslevel  =  [[[optionsArray objectAtIndex:0] objectForKey:@"fslevel"] intValue];
        sticktype  =  [[[optionsArray objectAtIndex:0] objectForKey:@"sticktype"] intValue];
        numbuttons  =  [[[optionsArray objectAtIndex:0] objectForKey:@"numbuttons"] intValue];
        aplusb  =  [[[optionsArray objectAtIndex:0] objectForKey:@"aplusb"] intValue];
        cheats  =  [[[optionsArray objectAtIndex:0] objectForKey:@"cheats"] intValue];
        sleep  =  [[[optionsArray objectAtIndex:0] objectForKey:@"sleep"] intValue];
        
        forcepxa  =  [[[optionsArray objectAtIndex:0] objectForKey:@"forcepxa"] intValue];
        emures  =  [[[optionsArray objectAtIndex:0] objectForKey:@"emures"] intValue];
        
        p1aspx  =  [[[optionsArray objectAtIndex:0] objectForKey:@"p1aspx"] intValue];
                                       
	}
			
}

- (void)saveOptions
{

	[optionsArray removeAllObjects];
	[optionsArray addObject:[NSDictionary dictionaryWithObjectsAndKeys:
							 [NSString stringWithFormat:@"%d", keepAspectRatioPort], @"KeepAspectPort",
							 [NSString stringWithFormat:@"%d", keepAspectRatioLand], @"KeepAspectLand",
							 [NSString stringWithFormat:@"%d", smoothedLand], @"SmoothedLand",
							 [NSString stringWithFormat:@"%d", smoothedPort], @"SmoothedPort",
							 
							 [NSString stringWithFormat:@"%d", tvFilterPort], @"TvFilterPort",
							 [NSString stringWithFormat:@"%d", tvFilterLand], @"TvFilterLand",
							 
							 [NSString stringWithFormat:@"%d", scanlineFilterPort], @"ScanlineFilterPort",
							 [NSString stringWithFormat:@"%d", scanlineFilterLand], @"ScanlineFilterLand",

							 [NSString stringWithFormat:@"%d", showFPS], @"showFPS",							 
							 [NSString stringWithFormat:@"%d", showINFO], @"showINFO",							 
							 [NSString stringWithFormat:@"%d", fourButtonsLand], @"fourButtonsLand",							 
							 [NSString stringWithFormat:@"%d", animatedButtons], @"animatedButtons",							 							 							 											 
							 [NSString stringWithFormat:@"%d", fullLand], @"fullLand",
							 [NSString stringWithFormat:@"%d", fullPort], @"fullPort",
							 
							 [NSString stringWithFormat:@"%d", skin], @"skin",
							  
							 [NSString stringWithFormat:@"%d", wiiDeadZoneValue], @"wiiDeadZoneValue",
							 [NSString stringWithFormat:@"%d", touchDeadZone], @"touchDeadZone",
							 
							 [NSString stringWithFormat:@"%d", overscanValue], @"overscanValue",
							 [NSString stringWithFormat:@"%d", tvoutNative], @"tvoutNative",
							 
							 [NSString stringWithFormat:@"%d", inputTouchType], @"inputTouchType",
							 [NSString stringWithFormat:@"%d", analogDeadZoneValue], @"analogDeadZoneValue",
							 					
                             [NSString stringWithFormat:@"%d", iCadeLayout], @"iCadeLayout",

                             [NSString stringWithFormat:@"%d", SoundKHZ], @"SoundKHZ",
                             [NSString stringWithFormat:@"%d", soundEnabled], @"soundEnabled",

                             [NSString stringWithFormat:@"%d", throttle], @"throttle",
                             [NSString stringWithFormat:@"%d", fskip], @"fskip",
                             [NSString stringWithFormat:@"%d", fslevel], @"fslevel",
                             [NSString stringWithFormat:@"%d", sticktype], @"sticktype",
                             [NSString stringWithFormat:@"%d", numbuttons], @"numbuttons",
                             [NSString stringWithFormat:@"%d", aplusb], @"aplusb",
                             [NSString stringWithFormat:@"%d", cheats], @"cheats",                             
                             [NSString stringWithFormat:@"%d", sleep], @"sleep",
                             
                             [NSString stringWithFormat:@"%d", forcepxa], @"forcepxa",                             
                             [NSString stringWithFormat:@"%d", emures], @"emures",
                             
                             [NSString stringWithFormat:@"%d", p1aspx], @"p1aspx",
                             
							 nil]];	

	
    NSString *path=[NSString stringWithCString:get_documents_path("iOS/options_v5.bin")];
	
	NSData *plistData;
	
	NSString *error;
		
	plistData = [NSPropertyListSerialization dataFromPropertyList:optionsArray				 
										     format:NSPropertyListBinaryFormat_v1_0				 
										     errorDescription:&error];	
	if(plistData)		
	{
	    //NSError*err;
	
		BOOL b = [plistData writeToFile:path atomically:NO];
		//BOOL b = [plistData writeToFile:path options:0  error:&err];
		if(!b)
		{
			    UIAlertView *errAlert = [[UIAlertView alloc] initWithTitle:@"Error saving preferences!" 
															message://[NSString stringWithFormat:@"Error:%@",[err localizedDescription]]  
															@"Preferences couldn't be saved.\n Check for write permissions. chmod 777 if needed. See help." 
															delegate:self 
													        cancelButtonTitle:@"OK" 
													        otherButtonTitles: nil];	
	           [errAlert show];
	           [errAlert release];
		}		
	}
	else
	{

		NSLog(error);		
		[error release];		
	}	
}

- (void)dealloc {
    
    [optionsArray dealloc];

	[super dealloc];
}

@end

@implementation OptionsController


- (id)init {

    if (self = [super init]) {
        
        switchKeepAspectPort=nil;
        switchKeepAspectLand=nil;
        switchSmoothedPort=nil;
        switchSmoothedLand=nil;
        
        switchTvFilterPort=nil;
        switchTvFilterLand=nil;
        switchScanlineFilterPort=nil;
        switchScanlineFilterLand=nil;
        
        switchShowFPS=nil;
        switchShowINFO=nil;
        switchAnimatedButtons=nil;
        switch4buttonsLand=nil;
        switchfullLand=nil;
        switchfullPort=nil;
        
        segmentedSkin= nil;
        
        segmentedWiiDeadZoneValue = nil;
        switchTouchDeadZone = nil;
        
        segmentedOverscanValue = nil;
        switchTvoutNative = nil;
        
        segmentedTouchType = nil;
        segmentedAnalogDeadZoneValue = nil;
        
        segmentediCadeLayout=nil;
        
        segmentedSoundKHZ=nil;
        switchSound=nil;
        
        switchThrottle = nil;
        segmentedFSkip = nil;
        segmentedFSlevel = nil;
        segmentedSticktype = nil;
        segmentedNumbuttons = nil;
        switchAplusB = nil;
        switchCheats = nil;
        switchSleep = nil;
        
        switchForcepxa = nil;
        segmentedEmures = nil;
    }

    return self;
}

- (void)loadView {

	UIViewController *pctrl = [self parentViewController];		
	struct CGRect rect = pctrl.view.frame;//[[UIScreen mainScreen] bounds];
	rect.origin.x = rect.origin.y = 0.0f;
	if(pctrl.interfaceOrientation==UIInterfaceOrientationLandscapeLeft 
	||pctrl.interfaceOrientation==UIInterfaceOrientationLandscapeRight )
	{
	     int tmp = rect.size.width;
	     rect.size.width = rect.size.height; 
	     rect.size.height = tmp;	     
	}

	UIView *view= [[UIView alloc] initWithFrame:rect];	
	self.view = view;
	[view release];
    self.view.backgroundColor = [UIColor whiteColor];

    
   UINavigationBar    *navBar = [ [ UINavigationBar alloc ] initWithFrame: CGRectMake(rect.origin.x, rect.origin.y, rect.size.width, 45.0f)];
   [ navBar setDelegate: self ];

   UINavigationItem *item = [[ UINavigationItem alloc ] initWithTitle:@"Options" ];
   UIBarButtonItem *backButton = [[UIBarButtonItem alloc] initWithTitle:@"OK" style:UIBarButtonItemStyleBordered target:[self parentViewController]  action:  @selector(done:) ];
   item.rightBarButtonItem = backButton;
   [backButton release];
   [ navBar pushNavigationItem: item  animated:YES];
     
   [ self.view addSubview: navBar ];
   [navBar release];
   
    UITableView *tableView = [[UITableView alloc] 
    initWithFrame:CGRectMake(rect.origin.x, rect.origin.y + 45.0f, rect.size.width,rect.size.height - 45.0f) style:UITableViewStyleGrouped];
    //[tableView setSeparatorColor:[UIColor clearColor]];
          
    tableView.delegate = self;
    tableView.dataSource = self;
    [self.view addSubview:tableView];
    [tableView release];
   

    
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {

   //UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"CellIdentifier"];
   
   NSString *cellIdentifier = [NSString stringWithFormat: @"%d:%d", [indexPath indexAtPosition:0], [indexPath indexAtPosition:1]];
   UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:cellIdentifier];
   
   if (cell == nil)
   {
      //If not possible create a new cell
      cell = [[[UITableViewCell alloc] initWithFrame:CGRectZero reuseIdentifier:@"CellIdentifier"]
                            autorelease];
      cell.accessoryType = UITableViewCellAccessoryNone;
      cell.selectionStyle = UITableViewCellSelectionStyleNone;
   }
   
   Options *op = [[Options alloc] init];
   
   switch (indexPath.section) 
   {
       case 0: //Portraint
       {
           switch (indexPath.row) 
           {
               case 0: 
               {
                   cell.text  = @"Smoothed Image";
                   switchSmoothedPort = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchSmoothedPort;
                   [switchSmoothedPort setOn:[op smoothedPort] animated:NO];
                   [switchSmoothedPort addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];                   
                   break;
               }
               
               case 1:
               {
                   cell.text  = @"CRT Filter";
                   switchTvFilterPort  = [[UISwitch alloc] initWithFrame:CGRectZero];                               
                   cell.accessoryView = switchTvFilterPort ;
                   [switchTvFilterPort setOn:[op tvFilterPort] animated:NO];
                   [switchTvFilterPort addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];  
                   break;
               }
               case 2:
               {
                   cell.text  = @"Scanline Filter";
                   switchScanlineFilterPort  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchScanlineFilterPort ;
                   [switchScanlineFilterPort setOn:[op scanlineFilterPort] animated:NO];
                   [switchScanlineFilterPort addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }          
               case 3:
               {
                   cell.text  = @"Full Screen";
                   switchfullPort  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchfullPort;
                   [switchfullPort setOn:[op fullPort] animated:NO];
                   [switchfullPort addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged]; 
                   break;
               }   
               case 4:
               {
	                cell.text  = @"Keep Aspect Ratio";
	                switchKeepAspectPort  = [[UISwitch alloc] initWithFrame:CGRectZero];                
	                cell.accessoryView = switchKeepAspectPort;
	                [switchKeepAspectPort setOn:[op keepAspectRatioPort] animated:NO];
	                [switchKeepAspectPort addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }             
                           
           }    
           break;
       }
       case 1:  //Landscape
       {
           switch (indexPath.row) 
           {
               case 0: 
               {
                   cell.text  = @"Smoothed Image";
                   switchSmoothedLand = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchSmoothedLand;
                   [switchSmoothedLand setOn:[op smoothedLand] animated:NO];
                   [switchSmoothedLand addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];  
                   break;
               }
               case 1:
               {
                   cell.text  = @"CRT Filter";
                   switchTvFilterLand  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchTvFilterLand ;
                   [switchTvFilterLand setOn:[op tvFilterLand] animated:NO];
                   [switchTvFilterLand addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];  
                   break;
               }
               case 2:
               {
                   cell.text  = @"Scanline Filter";
                   switchScanlineFilterLand  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchScanlineFilterLand ;
                   [switchScanlineFilterLand setOn:[op scanlineFilterLand] animated:NO];
                   [switchScanlineFilterLand addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }
               /*
               case 3:
               {
                   cell.text  = @"Show 4 Buttons";
                   switch4buttonsLand  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switch4buttonsLand ;
                   [switch4buttonsLand setOn:[op fourButtonsLand] animated:NO];
                   [switch4buttonsLand addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }
               */
               case 3:
               {
                   cell.text  = @"Full Screen";
                   switchfullLand  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchfullLand ;
                   [switchfullLand setOn:[op fullLand] animated:NO];
                   [switchfullLand addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }

               case 4:
               {

                    cell.text  = @"Keep Aspect Ratio";
                    switchKeepAspectLand  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                    cell.accessoryView = switchKeepAspectLand;
                    [switchKeepAspectLand setOn:[op keepAspectRatioLand] animated:NO];
                    [switchKeepAspectLand addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];
   
                   break;
               }
           }
           break;
        }    
        case 2:  //Input
        {
            switch (indexPath.row) 
            {
               case 0:
               {
                   cell.text  = @"Animated";
                   switchAnimatedButtons  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchAnimatedButtons ;
                   [switchAnimatedButtons setOn:[op animatedButtons] animated:NO];
                   [switchAnimatedButtons addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
              }
              case 1:
              {
                   cell.text  = @"Touch Type";

                    segmentedTouchType = [[UISegmentedControl alloc] initWithItems:
                       [NSArray arrayWithObjects: @"D-PAD",@"D-Stick", @"Analog", nil]];
                    segmentedTouchType.selectedSegmentIndex = [op inputTouchType];
                  
                    CGRect r = segmentedTouchType.frame;
                    r.size.height = 30;
                    segmentedTouchType.frame = r;
                    
                    [segmentedTouchType addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];
                    segmentedTouchType.segmentedControlStyle = UISegmentedControlStylePlain; 
                    //UISegmentedControlStyleBar;
                     cell.accessoryView = segmentedTouchType;     
                   break;
               }
               case 2:
               {
                   cell.text  = @"Stick Type";

                    segmentedSticktype = [[UISegmentedControl alloc] initWithItems:
                       [NSArray arrayWithObjects: @"2-way", @"4-way", @"8-way", nil]];
                    segmentedSticktype.selectedSegmentIndex = [op sticktype];
                  
                    CGRect r = segmentedSticktype.frame;
                    r.size.height = 30;
                    segmentedSticktype.frame = r;
                    
                    [segmentedSticktype addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];
                    segmentedSticktype.segmentedControlStyle = UISegmentedControlStylePlain; 
                    //UISegmentedControlStyleBar;
                     cell.accessoryView = segmentedSticktype;     
                   break;
               }
               case 3:
               {
                    cell.text  = @"Buttons";

                    segmentedNumbuttons = [[UISegmentedControl alloc] initWithItems:
                       [NSArray arrayWithObjects: @"0",@"1", @"2", @"3",@"4", @"all", nil]];
                    segmentedNumbuttons.selectedSegmentIndex = [op numbuttons];
                  
                    [segmentedNumbuttons addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];
                    segmentedNumbuttons.segmentedControlStyle = UISegmentedControlStyleBar;
                    cell.accessoryView = segmentedNumbuttons;     
                   break;
               }       
               case 4:
               {
                   cell.text  = @"Button A = B + X";
                   switchAplusB  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchAplusB ;
                   [switchAplusB setOn:[op aplusb] animated:NO];
                   [switchAplusB addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }                                        
               case 5:
               {                                      
                   cell.text  = @"Analog Touch DZ";
                   
                    segmentedAnalogDeadZoneValue = [[UISegmentedControl alloc] initWithItems:
                       [NSArray arrayWithObjects: @"1", @"2", @"3",@"4", @"5", @"6", nil]];
                    segmentedAnalogDeadZoneValue.selectedSegmentIndex = [op analogDeadZoneValue];
                    //actionControl.tag = 3;
                    [segmentedAnalogDeadZoneValue addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];
                    segmentedAnalogDeadZoneValue.segmentedControlStyle = UISegmentedControlStyleBar;
                    //[cell addSubview:segmentedDeadZoneValue];
                     cell.accessoryView = segmentedAnalogDeadZoneValue;                     
                   break;
               }                            
              case 6:
               {
                   cell.text  = @"Digital Touch DZ";
                   switchTouchDeadZone  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchTouchDeadZone ;
                   [switchTouchDeadZone setOn:[op touchDeadZone] animated:NO];
                   [switchTouchDeadZone addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }                              
               case 7:
               {                                      
                   cell.text  = @"Wii Classic DZ";
                   
                    segmentedWiiDeadZoneValue = [[UISegmentedControl alloc] initWithItems:
                       [NSArray arrayWithObjects: @"1", @"2", @"3",@"4", @"5", @"6", nil]];
                    //segmentedDeadZoneValue.frame = CGRectMake(145, 5, 150, 35);
                    segmentedWiiDeadZoneValue.selectedSegmentIndex = [op wiiDeadZoneValue];
                    //actionControl.tag = 3;
                    [segmentedWiiDeadZoneValue addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];
                    segmentedWiiDeadZoneValue.segmentedControlStyle = UISegmentedControlStyleBar;
                    //[cell addSubview:segmentedDeadZoneValue];
                     cell.accessoryView = segmentedWiiDeadZoneValue;

                   break;
               }       
                case 8:
                {
                    cell.text  = @"Control Layout";

                    segmentediCadeLayout = [[UISegmentedControl alloc] initWithItems:
                       [NSArray arrayWithObjects: @"iCP", @"iCade", nil]];
                    segmentediCadeLayout.selectedSegmentIndex = [op iCadeLayout];
                  
                    CGRect r = segmentediCadeLayout.frame;
                    r.size.height = 30;
                    segmentediCadeLayout.frame = r;
                    
                    [segmentediCadeLayout addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];
                    segmentediCadeLayout.segmentedControlStyle = UISegmentedControlStylePlain; 
                    cell.accessoryView = segmentediCadeLayout;     
                   break;
                }    
                
               case 9:
               {
                   cell.text  = @"P1 as P2,P3,P4";
                   switchP1aspx  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchP1aspx ;
                   [switchP1aspx setOn:[op p1aspx] animated:NO];
                   [switchP1aspx addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }                          
            }   
            break;
        }        
       case 3:  //Sound
       {
           switch (indexPath.row) 
           {
               case 0:
               {
                   cell.text  = @"Sound Rate (kHz)";
                   
                   segmentedSoundKHZ = [[UISegmentedControl alloc] initWithItems:
                                           [NSArray arrayWithObjects: @"11", @"22", @"33", @"44", @"48",nil]];
                   segmentedSoundKHZ.selectedSegmentIndex = [op SoundKHZ];
                   
                   CGRect r = segmentedSoundKHZ.frame;
                   r.size.height = 30;
                   segmentedSoundKHZ.frame = r;
                   
                   [segmentedSoundKHZ addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];
                   segmentedSoundKHZ.segmentedControlStyle = UISegmentedControlStylePlain; 
                   cell.accessoryView = segmentedSoundKHZ;     
                   break;               
               }
               case 1:
               {
                   cell.text  = @"Sound Enabled";
                   switchSound  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchSound ;
                   [switchSound setOn:[op soundEnabled] animated:NO];
                   [switchSound addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];                          
                   break;             
               } 
               case 2:
               {
                   cell.text  = @"Cheats";
                   switchCheats  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchCheats ;
                   [switchCheats setOn:[op cheats] animated:NO];
                   [switchCheats addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }
           }
           break;
       }

        case 4:  //Miscellaneous
        {
            switch (indexPath.row) 
            {
              case 0:
               {
                   cell.text  = @"Show FPS";
                   switchShowFPS  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchShowFPS ;
                   [switchShowFPS setOn:[op showFPS] animated:NO];
                   [switchShowFPS addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }
               case 1:
               {                                      
                    cell.text  = @"Emu Res";
                   
                    segmentedEmures = [[UISegmentedControl alloc] initWithItems:
                       [NSArray arrayWithObjects: @"auto", @"320", @"512",@"640", @"800", @"1024", nil]];
                                                              
                    segmentedEmures.selectedSegmentIndex = [op emures];
                    [segmentedEmures addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];
                    segmentedEmures.segmentedControlStyle = UISegmentedControlStyleBar;
                    cell.accessoryView = segmentedEmures;

                   break;
               }               
              case 2:
               {
                   cell.text  = @"Throttle";
                   switchThrottle  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchThrottle ;
                   [switchThrottle setOn:[op throttle] animated:NO];
                   [switchThrottle addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }
               case 3:
               {
                   cell.text  = @"FS";

                    segmentedFSkip = [[UISegmentedControl alloc] initWithItems:
                       [NSArray arrayWithObjects: @"None", @"Manual", @"Auto", nil]];
                    segmentedFSkip.selectedSegmentIndex = [op fskip];
                  
                    CGRect r = segmentedFSkip.frame;
                    r.size.height = 30;
                    segmentedFSkip.frame = r;
                    
                    [segmentedFSkip addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];
                    segmentedFSkip.segmentedControlStyle = UISegmentedControlStylePlain; 
                    cell.accessoryView = segmentedFSkip;     
                   break;
               }
               case 4:
               {                                      
                    cell.text  = @"FS Value";
                   
                    segmentedFSlevel = [[UISegmentedControl alloc] initWithItems:
                       [NSArray arrayWithObjects: @"1", @"2", @"3",@"4", @"5", @"6",@"7",@"8",@"9", nil]];
                                                              
                    segmentedFSlevel.selectedSegmentIndex = [op fslevel];
                    [segmentedFSlevel addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];
                    segmentedFSlevel.segmentedControlStyle = UISegmentedControlStyleBar;
                    cell.accessoryView = segmentedFSlevel;

                   break;
               }
               case 5:
               {
                   cell.text  = @"Force Pixel Aspect";
                   switchForcepxa  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchForcepxa ;
                   [switchForcepxa setOn:[op forcepxa] animated:NO];
                   [switchForcepxa addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }  
              case 6:
               {
                   cell.text  = @"Sleep on idle";
                   switchSleep  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchSleep ;
                   [switchSleep setOn:[op sleep] animated:NO];
                   [switchSleep addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }                                                                             
              case 7:
               {
                   cell.text  = @"Show Info/Warnings";
                   switchShowINFO  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchShowINFO ;
                   [switchShowINFO setOn:[op showINFO] animated:NO];
                   [switchShowINFO addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }
               case 8:
               {
                   cell.text  = @"Skin";                   
                   segmentedSkin = [[UISegmentedControl alloc] initWithItems:
                   (isIpad ?
                   [NSArray arrayWithObjects: @"A", @"B (Layout 2)", @"B ", nil]
                   :[NSArray arrayWithObjects: @"A", @"B ( Lo )", @"B", nil])];
                    
                    CGRect r = segmentedTouchType.frame;
                    r.size.height = 30;
                    segmentedTouchType.frame = r;
                    
                    //segmentedDeadZoneValue.frame = CGRectMake(145, 5, 150, 35);
                   segmentedSkin.selectedSegmentIndex = [op skin];
                    //actionControl.tag = 3;
                   [segmentedSkin addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];
                   segmentedSkin.segmentedControlStyle = UISegmentedControlStyleBar;
                   //[cell addSubview:segmentedDeadZoneValue];
                   cell.accessoryView = segmentedSkin;
                   break;
               }
               case 9:
               {
                   cell.text  = @"Native TV-OUT";
                   switchTvoutNative  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchTvoutNative ;
                   [switchTvoutNative setOn:[op tvoutNative] animated:NO];
                   [switchTvoutNative addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }                
               case 10:
               {
                   cell.text  = @"Overscan TV-OUT";                   
                   segmentedOverscanValue = [[UISegmentedControl alloc] initWithItems:
                   [NSArray arrayWithObjects: @"0", @"1", @"2",@"3",@"4",@"5",@"6", nil]];
                                      
                   segmentedOverscanValue.selectedSegmentIndex = [op overscanValue];
                   [segmentedOverscanValue addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];
                   segmentedOverscanValue.segmentedControlStyle = UISegmentedControlStyleBar;
                   cell.accessoryView = segmentedOverscanValue;
                   break;
               }               

            }
            break;   
        }
   }
     
   [op release];
           
   return cell;    
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
      return 5;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
		
    switch (section)
    {
          case 0: return @"Portrait";
          case 1: return @"Landscape";
          case 2: return @"Input";
          case 3: return @"Game Defaults";  
          case 4: return @"Miscellaneous";
    }
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
   
      switch (section)
      {
          case 0: return 5;
          case 1: return 5;
          case 2: return 10;
          case 3: return 3;
          case 4: return 9+2;
      }
}

-(void)viewDidLoad{	

}


-(BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
     //return (interfaceOrientation == UIInterfaceOrientationPortrait);
     return YES;
}

- (void)didReceiveMemoryWarning {
	[super didReceiveMemoryWarning];
}


- (void)dealloc {
   if(switchKeepAspectPort!=nil)
     [switchKeepAspectPort release];
   if(switchKeepAspectLand!=nil)
     [switchKeepAspectLand release];     
   if(switchSmoothedPort!=nil)  
     [switchSmoothedPort release];
   if(switchSmoothedLand!=nil)  
     [switchSmoothedLand release];
   if(switchTvFilterPort!=nil)
     [switchTvFilterPort release];
   if(switchTvFilterLand!=nil)
     [switchTvFilterLand release];
   if(switchScanlineFilterPort!=nil)
     [switchScanlineFilterPort release];
   if(switchScanlineFilterLand!=nil)
     [switchScanlineFilterLand release];
     
   if(switchShowFPS!=nil)
     [switchShowFPS release];
   if(switchShowINFO!=nil)
     [switchShowINFO release];
   if(switchAnimatedButtons!=nil)
     [switchAnimatedButtons release];
   if(switch4buttonsLand!=nil)
     [switch4buttonsLand release];
   if(switchfullLand!=nil)
     [switchfullLand release];      
   if(switchfullPort!=nil)
     [switchfullPort release]; 
          
   if(segmentedSkin!=nil)
     [segmentedSkin release];  
     
   if(segmentedWiiDeadZoneValue!=nil)
    [segmentedWiiDeadZoneValue release];
    
   if(switchTouchDeadZone!=nil)
     [switchTouchDeadZone release];
     
   if(segmentedOverscanValue!=nil)
    [segmentedOverscanValue release];
    
   if(switchTvoutNative!=nil)
     [switchTvoutNative release]; 

   if(segmentedTouchType!=nil)
     [segmentedTouchType release]; 

   if(segmentedAnalogDeadZoneValue!=nil)
    [segmentedAnalogDeadZoneValue release];
    
   if(segmentediCadeLayout!=nil)
    [segmentediCadeLayout release]; 

    if(segmentedSoundKHZ!=nil)
        [segmentedSoundKHZ release]; 
    if(switchSound!=nil)
        [switchSound release]; 
        
    if(switchThrottle != nil)
        [switchThrottle release];    
    if(segmentedFSkip != nil)
        [segmentedFSkip release];        
    if(segmentedFSlevel != nil)
        [segmentedFSlevel release];        
    if(segmentedSticktype != nil)
        [segmentedSticktype release];        
    if(segmentedNumbuttons != nil)
        [segmentedNumbuttons release];        
    if(switchAplusB != nil)
        [switchAplusB release];        
    if(switchCheats != nil)
        [switchCheats release];        
    if(switchSleep != nil)
        [switchSleep release];              

    if(switchForcepxa != nil)
        [switchForcepxa release];        
    if(segmentedEmures != nil)
        [segmentedEmures release];  
    
    if(switchP1aspx != nil)
        [switchP1aspx release];   
                 
   [super dealloc];
}

- (void)optionChanged:(id)sender
{
    Options *op = [[Options alloc] init];
	
	if(sender==switchKeepAspectPort)    		
	   op.keepAspectRatioPort = [switchKeepAspectPort isOn];
	
	if(sender==switchKeepAspectLand)    		
	   op.keepAspectRatioLand = [switchKeepAspectLand isOn];
	   	   
	if(sender==switchSmoothedPort)   
	   op.smoothedPort =  [switchSmoothedPort isOn];
	
	if(sender==switchSmoothedLand)
	   op.smoothedLand =  [switchSmoothedLand isOn];
		   
	if(sender == switchTvFilterPort)  
	   op.tvFilterPort =  [switchTvFilterPort isOn];
	   
	if(sender == switchTvFilterLand)   
	   op.tvFilterLand =  [switchTvFilterLand isOn];
	   
	if(sender == switchScanlineFilterPort)   
	   op.scanlineFilterPort =  [switchScanlineFilterPort isOn];
	   
	if(sender == switchScanlineFilterLand)
	   op.scanlineFilterLand =  [switchScanlineFilterLand isOn];    

    if(sender == switchShowFPS)
	   op.showFPS =  [switchShowFPS isOn];

    if(sender == switchShowINFO)
	   op.showINFO =  [switchShowINFO isOn];
	
	if(sender == switchAnimatedButtons) 
	   op.animatedButtons=  [switchAnimatedButtons isOn];
	
	if(sender == switch4buttonsLand) 
	   op.fourButtonsLand =  [switch4buttonsLand isOn];	
	
	if(sender == switchfullLand) 
	   op.fullLand =  [switchfullLand isOn];

	if(sender == switchfullPort) 
	   op.fullPort =  [switchfullPort isOn];
	   
    if(sender == segmentedSkin) 
	   op.skin =  [segmentedSkin selectedSegmentIndex];   
	   
	if(sender == segmentedWiiDeadZoneValue)
	   op.wiiDeadZoneValue = [segmentedWiiDeadZoneValue selectedSegmentIndex];   
	   
	if(sender == switchTouchDeadZone)
	  op.touchDeadZone = [switchTouchDeadZone isOn];
	  
	if(sender == segmentedOverscanValue)
	   op.overscanValue = [segmentedOverscanValue selectedSegmentIndex];   
	   
	if(sender == switchTvoutNative)
	  op.tvoutNative = [switchTvoutNative isOn];  

	if(sender == segmentedTouchType)
	  op.inputTouchType = [segmentedTouchType selectedSegmentIndex];
	  
	if(sender == segmentedAnalogDeadZoneValue)
	   op.analogDeadZoneValue = [segmentedAnalogDeadZoneValue selectedSegmentIndex];  	
    
    if(sender == segmentediCadeLayout)
        op.iCadeLayout = [segmentediCadeLayout selectedSegmentIndex];

    if(sender == segmentedSoundKHZ)
        op.SoundKHZ = [segmentedSoundKHZ selectedSegmentIndex];
    if(sender == switchSound)
        op.soundEnabled = [switchSound isOn];
    
    if(sender == switchThrottle)
        op.throttle = [switchThrottle isOn];    
    if(sender == segmentedFSkip)
        op.fskip = [segmentedFSkip selectedSegmentIndex];    
    if(sender == segmentedFSlevel)
        op.fslevel = [segmentedFSlevel selectedSegmentIndex]; 
    if(sender == segmentedSticktype)
        op.sticktype = [segmentedSticktype selectedSegmentIndex];        
    if(sender == segmentedNumbuttons)
        op.numbuttons = [segmentedNumbuttons selectedSegmentIndex];
    if(sender == switchAplusB)
        op.aplusb = [switchAplusB isOn];   
    if(sender == switchCheats)
        op.cheats = [switchCheats isOn];   
    if(sender == switchSleep)
        op.sleep = [switchSleep isOn];

    if(sender == switchForcepxa)
        op.forcepxa = [switchForcepxa isOn];
    if(sender == segmentedEmures)
        op.emures = [segmentedEmures selectedSegmentIndex];
    
    if(sender == switchP1aspx)
        op.p1aspx = [switchP1aspx isOn];
            
	[op saveOptions];
		
	[op release];
}



@end
