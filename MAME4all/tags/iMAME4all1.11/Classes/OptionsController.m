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

#import "OptionsController.h"
#import "Helper.h"
#include <stdio.h>
#include "shared.h"

extern int isIpad;
extern int isIphone4;

@implementation Options

@synthesize keepAspectRatioPort;
@synthesize keepAspectRatioLand;
@synthesize smoothedLand;
@synthesize smoothedPort;
@synthesize safeRenderPath;

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
@synthesize SoundSTEREO;

@synthesize buttonReload;

- (id)init {

    if (self = [super init]) {
        [self loadOptions];
    }

    return self;
}


- (void)loadOptions
{
	
	NSString *path=[NSString stringWithCString:get_documents_path("iOS/options_v10.bin")];
	
	NSData *plistData;
	id plist;
	NSString *error;
	
	NSPropertyListFormat format;
	
    buttonReload = FALSE;
    
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
		
		//todos menos iPad, iPhone4=iPhone3,1
		safeRenderPath = 
		                 ![[Helper machine] isEqualToString: @"iPhone1,1"] 
		              && ![[Helper machine] isEqualToString: @"iPhone1,2"]
		              //&& ![[Helper machine] isEqualToString: @"iPhone2,1"] 		               
		              && ![[Helper machine] isEqualToString: @"iPod1,1"]
                      //&& ![[Helper machine] isEqualToString: @"iPod2,1"]		              
		              ;
		  
		
		//safeRenderPath = isIpad?1:0;
		
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
        
        iCadeLayout = 1;
        
        SoundKHZ = 3;
        SoundSTEREO = 2;
        
		//[self saveOptions];
	}
	else
	{
		
		optionsArray = [[NSMutableArray alloc] initWithArray:plist];
		
		keepAspectRatioPort = [[[optionsArray objectAtIndex:0] objectForKey:@"KeepAspectPort"] intValue];
		keepAspectRatioLand = [[[optionsArray objectAtIndex:0] objectForKey:@"KeepAspectLand"] intValue];
		smoothedLand = [[[optionsArray objectAtIndex:0] objectForKey:@"SmoothedLand"] intValue];
		smoothedPort = [[[optionsArray objectAtIndex:0] objectForKey:@"SmoothedPort"] intValue];	
		safeRenderPath =  (isIpad || isIphone4)?1:[[[optionsArray objectAtIndex:0] objectForKey:@"safeRenderPath"] intValue];
		
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
        SoundSTEREO =  [[[optionsArray objectAtIndex:0] objectForKey:@"SoundSTEREO"] intValue];
        
        buttonReload =  [[[optionsArray objectAtIndex:0] objectForKey:@"buttonReload"] intValue];

        
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
							 [NSString stringWithFormat:@"%d", safeRenderPath], @"safeRenderPath",
							 
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
                             [NSString stringWithFormat:@"%d", SoundSTEREO], @"SoundSTEREO",
                             
                             [NSString stringWithFormat:@"%d", buttonReload], @"buttonReload",
                             
							 nil]];	

	
    NSString *path=[NSString stringWithCString:get_documents_path("iOS/options_v10.bin")];
	
	NSData *plistData;
	
	NSString *error;
		
	plistData = [NSPropertyListSerialization dataFromPropertyList:optionsArray				 
										     format:NSPropertyListBinaryFormat_v1_0				 
										     errorDescription:&error];	
	if(plistData)		
	{
	   NSError*err;
	
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
        
        switchSafeRender=nil;
        
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
        segmentedSoundSTEREO=nil;
        
//        buttonReload=nil;
    }

    return self;
}

- (void)loadView {

	UIViewController *pctrl = self_parentViewController;		
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
   UIBarButtonItem *backButton = [[UIBarButtonItem alloc] initWithTitle:@"OK" style:UIBarButtonItemStyleBordered target:self_parentViewController  action:  @selector(done:) ];
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
                       [NSArray arrayWithObjects: @"Digital", @"Analog", nil]];
                    segmentedTouchType.selectedSegmentIndex = [op inputTouchType];
                  
                    CGRect r = segmentedTouchType.frame;
                    r.size.height = 30;
                    segmentedTouchType.frame = r;
                    
                    [segmentedTouchType addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];
                    segmentedAnalogDeadZoneValue.segmentedControlStyle = UISegmentedControlStylePlain; 
                    //UISegmentedControlStyleBar;
                     cell.accessoryView = segmentedTouchType;     
                   break;
              } 
               case 2:
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
              case 3:
               {
                   cell.text  = @"Digital Touch DZ";
                   switchTouchDeadZone  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchTouchDeadZone ;
                   [switchTouchDeadZone setOn:[op touchDeadZone] animated:NO];
                   [switchTouchDeadZone addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }                              
               case 4:
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
                case 5:
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
                                           [NSArray arrayWithObjects: @"11", @"22", @"33", @"44", nil]];
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
                   cell.text  = @"Sound Stereo";
                   
                   segmentedSoundSTEREO = [[UISegmentedControl alloc] initWithItems:
                                        [NSArray arrayWithObjects: @"Fast", @"Mono", @"Stereo", nil]];
                   segmentedSoundSTEREO.selectedSegmentIndex = [op SoundSTEREO];
                   
                   CGRect r = segmentedSoundSTEREO.frame;
                   r.size.height = 30;
                   segmentedSoundSTEREO.frame = r;
                   
                   [segmentedSoundSTEREO addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];
                   segmentedSoundSTEREO.segmentedControlStyle = UISegmentedControlStylePlain; 
                   cell.accessoryView = segmentedSoundSTEREO;     
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
                   cell.text  = @"Show Info/Warnings";
                   switchShowINFO  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchShowINFO ;
                   [switchShowINFO setOn:[op showINFO] animated:NO];
                   [switchShowINFO addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }
               case 2:
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
               case 3:
               {
                   cell.text  = @"Native TV-OUT";
                   switchTvoutNative  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchTvoutNative ;
                   [switchTvoutNative setOn:[op tvoutNative] animated:NO];
                   [switchTvoutNative addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }                
               case 4:
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
               case 5:
               {
                   cell.text  = @"Safe Render Path";
                   switchSafeRender  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchSafeRender ;
                   [switchSafeRender setOn:[op safeRenderPath] animated:NO];
                   [switchSafeRender addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }
            }
            break;   
        }
           
//       case 5:  //Reload ROMS
//       {
//           UIButton *buttonReload = [UIButton buttonWithType:UIButtonTypeRoundedRect];
//            buttonReload.frame = cell.bounds;
//           [buttonReload setTitle:@"Rescan All ROMS" forState:UIControlStateNormal];
//           [buttonReload setTitle:@"Rescan All ROMS" forState:UIControlStateSelected];
//           [buttonReload addTarget:self action:@selector(buttontapped:) forControlEvents:UIControlEventTouchUpInside];
//           [cell.contentView addSubview:buttonReload];
//           cell.accessoryView = buttonReload;
//           
//           break;
//       }
       case 5:  //Reload ROMS
       {
           cell.selectionStyle = UITableViewCellSelectionStyleBlue;
           cell.text = @"Rescan All ROMS";
           cell.textAlignment = UITextAlignmentCenter;
           break;
           
           break;
       }
       

   }
     
   [op release];
           
   return cell;    
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    NSUInteger section = [indexPath section];
    
    switch (section) 
	{
    	case 5:
        {
            Options *op = [[Options alloc] init];           
            op.buttonReload = TRUE;
            
            [op saveOptions];
            [op release];
                                 
            [tableView deselectRowAtIndexPath:indexPath animated:YES];
            
            UIAlertView *warnAlert; 
            warnAlert = [[UIAlertView alloc] initWithTitle:@"ROM Rescan" 
                    message:[NSString stringWithFormat: @"The ROM directory has been rescanned"]
                      delegate:self cancelButtonTitle:@"Dismiss" otherButtonTitles: nil];
            [warnAlert show];
            [warnAlert release];
            
            break;
        }
    }
}


- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
      return 6;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    
    switch (section)
    {
        case 0: return @"Portrait";
        case 1: return @"Landscape";
        case 2: return @"Input";
        case 3: return @"Game Defaults";  
        case 4: return @"Miscellaneous";
        case 5: return @"";
    }
}
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    
    switch (section)
    {
        case 0: return 5;
        case 1: return 5;
        case 2: return 6;
        case 3: return 2;
        case 4: return (isIpad | isIphone4) ? 5 : 6;
        case 5: return 1;
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
   if(switchSafeRender!=nil)
     [switchSafeRender release];
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
    if(segmentedSoundSTEREO!=nil)
        [segmentedSoundSTEREO release]; 
    
//    if(buttonReload!=nil)
//        [buttonReload release];
         
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
	
	if(sender == switchSafeRender)
	   op.safeRenderPath =  [switchSafeRender isOn];
	   
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
    if(sender == segmentedSoundSTEREO)
        op.SoundSTEREO = [segmentedSoundSTEREO selectedSegmentIndex];
    

    
	[op saveOptions];
		
	[op release];
}

- (void)buttontapped:(id)sender
{
    Options *op = [[Options alloc] init];
    
    op.buttonReload = TRUE;
    
    [op saveOptions];
    
	[op release];
}


@end
