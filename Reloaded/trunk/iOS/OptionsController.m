/*
 * This file is part of MAME4iOS.
 *
 * Copyright (C) 2013 David Valdeita (Seleuco)
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
 * Linking MAME4iOS statically or dynamically with other modules is
 * making a combined work based on MAME4iOS. Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * In addition, as a special exception, the copyright holders of MAME4iOS
 * give you permission to combine MAME4iOS with free software programs
 * or libraries that are released under the GNU LGPL and with code included
 * in the standard release of MAME under the MAME License (or modified
 * versions of such code, with unchanged license). You may copy and
 * distribute such a system following the terms of the GNU GPL for MAME4iOS
 * and the licenses of the other code concerned, provided that you include
 * the source code of that other code when and as the GNU GPL requires
 * distribution of source code.
 *
 * Note that people who make modified versions of MAME4iOS are not
 * obligated to grant this special exception for their modified versions; it
 * is their choice whether to do so. The GNU General Public License
 * gives permission to release a modified version without this exception;
 * this exception also makes it possible to release a modified version
 * which carries forward this exception.
 *
 * MAME4iOS is dual-licensed: Alternatively, you can license MAME4iOS
 * under a MAME license, as set out in http://mamedev.org/
 */

#include "myosd.h"

#import "OptionsController.h"
#import "Globals.h"
#import "ListOptionController.h"
#import "DonateController.h"
#import "HelpController.h"
#import "EmulatorController.h"

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

@synthesize skinValue;

@synthesize btDeadZoneValue;
@synthesize touchDeadZone;

@synthesize overscanValue;
@synthesize tvoutNative;

@synthesize touchtype;
@synthesize analogDeadZoneValue;
@synthesize controltype;

@synthesize soundValue;

@synthesize throttle;
@synthesize fsvalue;
@synthesize sticktype;
@synthesize numbuttons;
@synthesize aplusb;
@synthesize cheats;
@synthesize sleep;

@synthesize forcepxa;
@synthesize emures;
@synthesize p1aspx;

@synthesize filterClones;
@synthesize filterFavorites;
@synthesize filterNotWorking;
@synthesize manufacturerValue;
@synthesize yearGTEValue;
@synthesize yearLTEValue;
@synthesize driverSourceValue;
@synthesize categoryValue;

@synthesize filterKeyword;

@synthesize lowlsound;
@synthesize vsync;
@synthesize threaded;
@synthesize dblbuff;

@synthesize mainPriority;
@synthesize videoPriority;

@synthesize autofire;

@synthesize hiscore;

@synthesize buttonSize;
@synthesize stickSize;

- (id)init {

    if (self = [super init]) {
        [self loadOptions];
    }

    return self;
}

- (void)loadOptions
{
	
	//NSString *path=[NSString stringWithCString:get_documents_path("iOS/options_v5.bin")];
    NSString *path=[NSString stringWithUTF8String:get_documents_path("iOS/options_v18.bin")];
	
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
		smoothedPort=g_isIpad?1:0;
		smoothedLand=g_isIpad?1:0;
				
		tvFilterPort = 0;
        tvFilterLand = 0;
        scanlineFilterPort = 0;
        scanlineFilterLand = 0;
        
        showFPS = 0;
        showINFO = 1;
        fourButtonsLand = 0;
        animatedButtons = 1;
		              
        fullLand = animatedButtons;
        fullPort = 0;
        
        skinValue = 0;
        
        btDeadZoneValue = 2;
        touchDeadZone = 1;
        
        overscanValue = 0;
        tvoutNative = 1;
        
        touchtype = 1;
        analogDeadZoneValue = 2;		
        
        controltype = 0;
        
        soundValue = 5;
        
        throttle = 1;
        fsvalue = 0;
        sticktype = 0;
        numbuttons = 0;
        aplusb = 0;
        cheats = 1;
        sleep = 1;
        
        forcepxa = 0;
        emures = 0;
        p1aspx = 0;
        
        filterClones=0;
        filterFavorites=0;
        filterNotWorking=1;
        manufacturerValue=0;
        yearGTEValue=0;
        yearLTEValue=0;
        driverSourceValue=0;
        categoryValue=0;
        
        filterKeyword = nil;
        
        lowlsound = 0;
        vsync = 0;
        threaded = 1;
        dblbuff = 1;
        
        mainPriority = 5;
        videoPriority = 5;
        
        autofire = 0;
        hiscore = 0;
        
        stickSize = 2;
        buttonSize= 2;
        
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
        
        skinValue =  [[[optionsArray objectAtIndex:0] objectForKey:@"skinValue"] intValue];
        
        btDeadZoneValue =  [[[optionsArray objectAtIndex:0] objectForKey:@"btDeadZoneValue"] intValue];
        touchDeadZone =  [[[optionsArray objectAtIndex:0] objectForKey:@"touchDeadZone"] intValue];

        overscanValue =  [[[optionsArray objectAtIndex:0] objectForKey:@"overscanValue"] intValue];
        tvoutNative =  [[[optionsArray objectAtIndex:0] objectForKey:@"tvoutNative"] intValue];
        
        touchtype =  [[[optionsArray objectAtIndex:0] objectForKey:@"inputTouchType"] intValue];
        analogDeadZoneValue =  [[[optionsArray objectAtIndex:0] objectForKey:@"analogDeadZoneValue"] intValue];    
        controltype =  [[[optionsArray objectAtIndex:0] objectForKey:@"controlType"] intValue];

        soundValue =  [[[optionsArray objectAtIndex:0] objectForKey:@"soundValue"] intValue];
                
        throttle  =  [[[optionsArray objectAtIndex:0] objectForKey:@"throttle"] intValue];
        fsvalue  =  [[[optionsArray objectAtIndex:0] objectForKey:@"fsvalue"] intValue];
        sticktype  =  [[[optionsArray objectAtIndex:0] objectForKey:@"sticktype"] intValue];
        numbuttons  =  [[[optionsArray objectAtIndex:0] objectForKey:@"numbuttons"] intValue];
        aplusb  =  [[[optionsArray objectAtIndex:0] objectForKey:@"aplusb"] intValue];
        cheats  =  [[[optionsArray objectAtIndex:0] objectForKey:@"cheats"] intValue];
        sleep  =  [[[optionsArray objectAtIndex:0] objectForKey:@"sleep"] intValue];
        
        forcepxa  =  [[[optionsArray objectAtIndex:0] objectForKey:@"forcepxa"] intValue];
        emures  =  [[[optionsArray objectAtIndex:0] objectForKey:@"emures"] intValue];
        
        p1aspx  =  [[[optionsArray objectAtIndex:0] objectForKey:@"p1aspx"] intValue];
                
        filterClones  =  [[[optionsArray objectAtIndex:0] objectForKey:@"filterClones"] intValue];
        filterFavorites  =  [[[optionsArray objectAtIndex:0] objectForKey:@"filterFavorites"] intValue];
        filterNotWorking  =  [[[optionsArray objectAtIndex:0] objectForKey:@"filterNotWorking"] intValue];
        manufacturerValue  =  [[[optionsArray objectAtIndex:0] objectForKey:@"manufacturerValue"] intValue];
        yearGTEValue  =  [[[optionsArray objectAtIndex:0] objectForKey:@"yearGTEValue"] intValue];
        yearLTEValue  =  [[[optionsArray objectAtIndex:0] objectForKey:@"yearLTEValue"] intValue];
        driverSourceValue  =  [[[optionsArray objectAtIndex:0] objectForKey:@"driverSourceValue"] intValue];
        categoryValue  =  [[[optionsArray objectAtIndex:0] objectForKey:@"categoryValue"] intValue];
        
        filterKeyword  =  [[optionsArray objectAtIndex:0] objectForKey:@"filterKeyword"];
        
        lowlsound  =  [[[optionsArray objectAtIndex:0] objectForKey:@"lowlsound"] intValue];
        vsync  =  [[[optionsArray objectAtIndex:0] objectForKey:@"vsync"] intValue];
        threaded  =  [[[optionsArray objectAtIndex:0] objectForKey:@"threaded"] intValue];
        dblbuff  =  [[[optionsArray objectAtIndex:0] objectForKey:@"dblbuff"] intValue];
        
        mainPriority  =  [[[optionsArray objectAtIndex:0] objectForKey:@"mainPriority"] intValue];
        videoPriority  =  [[[optionsArray objectAtIndex:0] objectForKey:@"videoPriority"] intValue];
        
        autofire =  [[[optionsArray objectAtIndex:0] objectForKey:@"autofire"] intValue];
        
        hiscore  =  [[[optionsArray objectAtIndex:0] objectForKey:@"hiscore"] intValue];
        
        buttonSize =  [[[optionsArray objectAtIndex:0] objectForKey:@"buttonSize"] intValue];
        stickSize =  [[[optionsArray objectAtIndex:0] objectForKey:@"stickSize"] intValue];
        
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
							 
							 [NSString stringWithFormat:@"%d", skinValue], @"skinValue",
							  
							 [NSString stringWithFormat:@"%d", btDeadZoneValue], @"btDeadZoneValue",
							 [NSString stringWithFormat:@"%d", touchDeadZone], @"touchDeadZone",
							 
							 [NSString stringWithFormat:@"%d", overscanValue], @"overscanValue",
							 [NSString stringWithFormat:@"%d", tvoutNative], @"tvoutNative",
							 
							 [NSString stringWithFormat:@"%d", touchtype], @"inputTouchType",
							 [NSString stringWithFormat:@"%d", analogDeadZoneValue], @"analogDeadZoneValue",
							 					
                             [NSString stringWithFormat:@"%d", controltype], @"controlType",

                             [NSString stringWithFormat:@"%d", soundValue], @"soundValue",

                             [NSString stringWithFormat:@"%d", throttle], @"throttle",
                             [NSString stringWithFormat:@"%d", fsvalue], @"fsvalue",
                             [NSString stringWithFormat:@"%d", sticktype], @"sticktype",
                             [NSString stringWithFormat:@"%d", numbuttons], @"numbuttons",
                             [NSString stringWithFormat:@"%d", aplusb], @"aplusb",
                             [NSString stringWithFormat:@"%d", cheats], @"cheats",                             
                             [NSString stringWithFormat:@"%d", sleep], @"sleep",
                             
                             [NSString stringWithFormat:@"%d", forcepxa], @"forcepxa",                             
                             [NSString stringWithFormat:@"%d", emures], @"emures",
                             
                             [NSString stringWithFormat:@"%d", p1aspx], @"p1aspx",
                             
                             [NSString stringWithFormat:@"%d", filterClones], @"filterClones",
                             [NSString stringWithFormat:@"%d", filterFavorites], @"filterFavorites",
                             [NSString stringWithFormat:@"%d", filterNotWorking], @"filterNotWorking",
                             [NSString stringWithFormat:@"%d", manufacturerValue], @"manufacturerValue",
                             [NSString stringWithFormat:@"%d", yearGTEValue], @"yearGTEValue",
                             [NSString stringWithFormat:@"%d", yearLTEValue], @"yearLTEValue",
                             [NSString stringWithFormat:@"%d", driverSourceValue], @"driverSourceValue",
                             [NSString stringWithFormat:@"%d", categoryValue], @"categoryValue",
                             [NSString stringWithFormat:@"%d", lowlsound], @"lowlsound",
                             [NSString stringWithFormat:@"%d", vsync], @"vsync",
                             [NSString stringWithFormat:@"%d", threaded], @"threaded",
                             [NSString stringWithFormat:@"%d", dblbuff], @"dblbuff",
                             
                             [NSString stringWithFormat:@"%d", mainPriority], @"mainPriority",
                             [NSString stringWithFormat:@"%d", videoPriority], @"videoPriority",
                             
                             [NSString stringWithFormat:@"%d", autofire], @"autofire",
                             [NSString stringWithFormat:@"%d", hiscore], @"hiscore",
                             
                             [NSString stringWithFormat:@"%d", stickSize], @"stickSize",
                             [NSString stringWithFormat:@"%d", buttonSize], @"buttonSize",
                             
                             filterKeyword, @"filterKeyword", //CUIADO si es nill termina la lista
                                                                                     
							 nil]];


	
    //NSString *path=[NSString stringWithCString:get_documents_path("iOS/options_v5.bin")];
	NSString *path=[NSString stringWithUTF8String:get_documents_path("iOS/options_v18.bin")];
    
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
															@"Preferences cannot be saved.\n Check for write permissions. 'chmod -R 777 /var/mobile/Media/ROMs' if needed. Look at the help for details!." 
															delegate:self 
													        cancelButtonTitle:@"OK" 
													        otherButtonTitles: nil];	
	           [errAlert show];
	           [errAlert release];
		}		
	}
	else
	{

		NSLog(@"%@",error);		
		[error release];		
	}	
}

- (void)dealloc {
    
    [optionsArray dealloc];

	[super dealloc];
}

@end

@implementation OptionsController

@synthesize emuController;


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
        
        switchfullLand=nil;
        switchfullPort=nil;
                
        switchTouchDeadZone = nil;
        
        switchTvoutNative = nil;
                
        switchThrottle = nil;
        
        switchAplusB = nil;
        switchCheats = nil;
        switchSleep = nil;
        
        switchForcepxa = nil;
            
        arrayNumbuttons = [[NSArray alloc] initWithObjects:@"Auto",@"0 Buttons",@"1 Buttons",@"2 Buttons",@"3 Buttons",@"4 Buttons",@"All Buttons", nil];
        
        arrayEmuRes = [[NSArray alloc] initWithObjects:@"Auto",@"320x200",@"320x240",@"400x300",@"480x300",@"512x384",@"640x400",@"640x480",@"800x600",@"1024x768", nil];
        
        arrayTouchType = [[NSArray alloc] initWithObjects:@"Digital DPAD",@"Digital Stick",@"Analog Stick", nil];
        
        arrayStickType = [[NSArray alloc] initWithObjects:@"Auto",@"2-Way",@"4-Way",@"8-Way", nil];
        
        arrayControlType = [[NSArray alloc] initWithObjects:@"None",@"iCade",@"iCP, Gametel",@"iMpulse", nil];
        
        arrayAnalogDZValue = [[NSArray alloc] initWithObjects:@"1", @"2", @"3",@"4", @"5", @"6", nil];
        arrayBTDZValue = [[NSArray alloc] initWithObjects:@"1", @"2", @"3",@"4", @"5", @"6", nil];
        
        arraySoundValue = [[NSArray alloc] initWithObjects:@"Off", @"On (11 KHz)", @"On (22 KHz)",@"On (33 KHz)", @"On (44 KHz)", @"On (48 KHz)", nil];
        
        arrayFSValue = [[NSArray alloc] initWithObjects:@"Auto",@"None", @"1", @"2", @"3",@"4", @"5", @"6", @"7", @"8", @"9", @"10",nil];
        
        arrayOverscanValue = [[NSArray alloc] initWithObjects:@"None",@"1", @"2", @"3",@"4", @"5", @"6", nil];
        
        arraySkinValue = 
        [[NSArray alloc] initWithObjects: @"A", @"B (Layout 1)", @"B (Layout 2)", nil];
        
        
        switchFilterClones = nil;
        switchFilterFavorites = nil;
        switchFilterNotWorking = nil;
        arrayManufacturerValue = [[NSMutableArray  alloc] initWithObjects:@"# All",nil];
        arrayYearGTEValue = [[NSMutableArray  alloc] initWithObjects:@"Any",nil];
        arrayYearLTEValue = [[NSMutableArray  alloc] initWithObjects:@"Any",nil];
        arrayDriverSourceValue = [[NSMutableArray  alloc] initWithObjects:@"# All",nil];
        arrayCategoryValue = [[NSMutableArray  alloc] initWithObjects:@"# All",nil];
        
        arrayMainPriorityValue = [[NSArray alloc] initWithObjects:@"0", @"1", @"2", @"3",@"4", @"5", @"6", @"7", @"8", @"9", @"10",nil];
        arrayVideoPriorityValue = [[NSArray alloc] initWithObjects:@"0", @"1", @"2", @"3",@"4", @"5", @"6", @"7", @"8", @"9", @"10",nil];
        
        arrayAutofireValue = [[NSArray alloc] initWithObjects:@"Disabled", @"Speed 1", @"Speed 2",@"Speed 3",
                              @"Speed 4", @"Speed 5",@"Speed 6",@"Speed 7",@"Speed 8",@"Speed 9",nil];
        
        arrayStickSizeValue = [[NSArray alloc] initWithObjects:@"Smaller", @"Small", @"Normal", @"Big", @"Bigger",nil];
        arrayButtonSizeValue = [[NSArray alloc] initWithObjects:@"Smaller", @"Small", @"Normal", @"Big", @"Bigger",nil];
        
        int i = 0;
                
        while(myosd_array_years[i][0]!='\0'){
            [arrayYearGTEValue addObject:[NSString stringWithUTF8String: myosd_array_years[i]]];
            [arrayYearLTEValue addObject:[NSString stringWithUTF8String: myosd_array_years[i]]];
            i++;
        }
        i=0;
        while(myosd_array_main_manufacturers[i][0]!='\0'){
            [arrayManufacturerValue addObject:[NSString stringWithUTF8String: myosd_array_main_manufacturers[i]]];
            i++;
        }
        i=0;
        while(myosd_array_main_driver_source[i][0]!='\0'){
            [arrayDriverSourceValue addObject:[NSString stringWithUTF8String: myosd_array_main_driver_source[i]]];
            i++;
        }
        [arrayManufacturerValue replaceObjectAtIndex:[arrayManufacturerValue indexOfObject:@"Other"] withObject: @"# Other / Unknow"];
        [arrayDriverSourceValue replaceObjectAtIndex:[arrayDriverSourceValue indexOfObject:@"Other"] withObject: @"# Other / Unknow"];
        i=0;
        while(myosd_array_categories[i][0]!='\0'){
            [arrayCategoryValue addObject:[NSString stringWithUTF8String: myosd_array_categories[i]]];
            i++;
        }
        
        switchLowlsound = nil;
        switchVsync = nil;
        switchThreaded = nil;
        switchDblbuff = nil;
        switchHiscore = nil;
        
    }

    return self;
}

- (void)loadView {
    

    UIBarButtonItem *backButton = [[UIBarButtonItem alloc] initWithTitle:@"Done"
                                                                   style:UIBarButtonItemStyleBordered
                                                                  target: emuController  action:  @selector(done:) ];
    self.navigationItem.rightBarButtonItem = backButton;
    [backButton release];
    
    self.title = NSLocalizedString(@"Settings", @"");
    
    UITableView *tableView = [[UITableView alloc] 
    initWithFrame:CGRectMake(0, 0, 240, 200) style:UITableViewStyleGrouped];
          
    tableView.delegate = self;
    tableView.dataSource = self;
    tableView.autoresizesSubviews = YES;
    self.view = tableView;
    [tableView release];

}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
   
   NSString *cellIdentifier = [NSString stringWithFormat: @"%d:%d", [indexPath indexAtPosition:0], [indexPath indexAtPosition:1]];
   UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:cellIdentifier];
   
   if (cell == nil)
   {
       
      UITableViewCellStyle style;
       
      if((indexPath.section==kFilterSection && indexPath.row==9) || indexPath.section==kCustomLayout )
          style = UITableViewCellStyleDefault;
       else
          style = UITableViewCellStyleValue1;
       
      cell = [[[UITableViewCell alloc] initWithStyle:style
                                      //UITableViewCellStyleDefault
                                      //UITableViewCellStyleValue1
                                      reuseIdentifier:@"CellIdentifier"] autorelease];
       
      cell.accessoryType = UITableViewCellAccessoryNone;
      cell.selectionStyle = UITableViewCellSelectionStyleNone;
   }
   
   Options *op = [[Options alloc] init];
   
   switch (indexPath.section)
   {
           
       case kSupportSection:
       {
           switch (indexPath.row)
           {
               case 0:
               {
                   cell.textLabel.text   = @"Help";
                   cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
                   break;
               }
                   
               case 1:
               {
                   cell.textLabel.text   = @"Donate";
                   cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
                   break;
               }
           }
           break;
       }
           
       case kPortraitSection: //Portrait
       {
           switch (indexPath.row) 
           {
               case 0: 
               {
                   cell.textLabel.text   = @"Smoothed Image";
                   [switchSmoothedPort release];
                   switchSmoothedPort = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchSmoothedPort;
                   [switchSmoothedPort setOn:[op smoothedPort] animated:NO];
                   [switchSmoothedPort addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];                   
                   break;
               }
               
               case 1:
               {
                   cell.textLabel.text   = @"CRT Effect";
                   [switchTvFilterPort release];
                   switchTvFilterPort  = [[UISwitch alloc] initWithFrame:CGRectZero];                               
                   cell.accessoryView = switchTvFilterPort ;
                   [switchTvFilterPort setOn:[op tvFilterPort] animated:NO];
                   [switchTvFilterPort addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];
                   break;
               }
               case 2:
               {
                   cell.textLabel.text   = @"Scanline Effect";
                   [switchScanlineFilterPort release];
                   switchScanlineFilterPort  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchScanlineFilterPort ;
                   [switchScanlineFilterPort setOn:[op scanlineFilterPort] animated:NO];
                   [switchScanlineFilterPort addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }          
               case 3:
               {
                   cell.textLabel.text   = @"Full Screen";
                   [switchfullPort release];
                   switchfullPort  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchfullPort;
                   [switchfullPort setOn:[op fullPort] animated:NO];
                   [switchfullPort addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged]; 
                   break;
               }   
               case 4:
               {
	                cell.textLabel.text   = @"Keep Aspect Ratio";
                   [switchKeepAspectPort release];
	                switchKeepAspectPort  = [[UISwitch alloc] initWithFrame:CGRectZero];                
	                cell.accessoryView = switchKeepAspectPort;
	                [switchKeepAspectPort setOn:[op keepAspectRatioPort] animated:NO];
	                [switchKeepAspectPort addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }             
                           
           }    
           break;
       }
       case kLandscapeSection:  //Landscape
       {
           switch (indexPath.row) 
           {
               case 0: 
               {
                   cell.textLabel.text  = @"Smoothed Image";
                   [switchSmoothedLand release];
                   switchSmoothedLand = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchSmoothedLand;
                   [switchSmoothedLand setOn:[op smoothedLand] animated:NO];
                   [switchSmoothedLand addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];  
                   break;
               }
               case 1:
               {
                   cell.textLabel.text   = @"CRT Effect";
                   [switchTvFilterLand release];
                   switchTvFilterLand  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchTvFilterLand ;
                   [switchTvFilterLand setOn:[op tvFilterLand] animated:NO];
                   [switchTvFilterLand addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];  
                   break;
               }
               case 2:
               {
                   cell.textLabel.text   = @"Scanline Effect";
                   [switchScanlineFilterLand release];
                   switchScanlineFilterLand  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchScanlineFilterLand ;
                   [switchScanlineFilterLand setOn:[op scanlineFilterLand] animated:NO];
                   [switchScanlineFilterLand addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }
               case 3:
               {
                   cell.textLabel.text   = @"Full Screen";
                   [switchfullLand release];
                   switchfullLand  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchfullLand ;
                   [switchfullLand setOn:[op fullLand] animated:NO];
                   [switchfullLand addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }

               case 4:
               {

                    cell.textLabel.text   = @"Keep Aspect Ratio";
                   [switchKeepAspectLand release];
                    switchKeepAspectLand  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                    cell.accessoryView = switchKeepAspectLand;
                    [switchKeepAspectLand setOn:[op keepAspectRatioLand] animated:NO];
                    [switchKeepAspectLand addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];
   
                   break;
               }
           }
           break;
        }    
        case kInputSection:  //Input
        {
            switch (indexPath.row) 
            {
               case 0:
               {
                   cell.textLabel.text   = @"Animated";
                   [switchAnimatedButtons release];
                   switchAnimatedButtons  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchAnimatedButtons ;
                   [switchAnimatedButtons setOn:[op animatedButtons] animated:NO];
                   [switchAnimatedButtons addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
              }
              case 1:
              {
                   cell.textLabel.text   = @"Touch Type";
                   cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
                   cell.detailTextLabel.text = [arrayTouchType objectAtIndex:op.touchtype];
                   break;
               }
               case 2:
               {                   
                   cell.textLabel.text   = @"Stick Type";
                   cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
                   cell.detailTextLabel.text = [arrayStickType objectAtIndex:op.sticktype];
                   
                   break;
               }
               case 3:
               {                
                   cell.textLabel.text   = @"Fullscreen Buttons";
                   cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
                   cell.detailTextLabel.text = [arrayNumbuttons objectAtIndex:op.numbuttons];
                   
                   break;
               }
               case 4:
               {
                   cell.textLabel.text   = @"Button A = B + X";
                   [switchAplusB release];
                   switchAplusB  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchAplusB ;
                   [switchAplusB setOn:[op aplusb] animated:NO];
                   [switchAplusB addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }
                case 5:
                {
                    cell.textLabel.text   = @"Buttons Size";
                    
                    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
                    cell.detailTextLabel.text = [arrayButtonSizeValue objectAtIndex:op.buttonSize];
                    
                    break;
                }
                case 6:
                {
                    cell.textLabel.text   = @"Fullscreen Stick Size";
                    
                    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
                    cell.detailTextLabel.text = [arrayStickSizeValue objectAtIndex:op.stickSize];
                    
                    break;
                }
                    
                case 7:
                {
                    cell.textLabel.text   = @"External Controller";

                    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
                    cell.detailTextLabel.text = [arrayControlType objectAtIndex:op.controltype];
                    
                   break;
                }    
                
               case 8:
               {
                   cell.textLabel.text   = @"P1 as P2,P3,P4";
                   [switchP1aspx release];
                   switchP1aspx  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchP1aspx ;
                   [switchP1aspx setOn:[op p1aspx] animated:NO];
                   [switchP1aspx addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }
                case 9:
                {
                    
                    cell.textLabel.text   = @"Button B as Autofire";
                    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
                    cell.detailTextLabel.text = [arrayAutofireValue objectAtIndex:op.autofire];
                    break;
                }
                case 10:
                {
                    cell.textLabel.text   = @"DPAD Touch DZ";
                    [switchTouchDeadZone release];
                    switchTouchDeadZone  = [[UISwitch alloc] initWithFrame:CGRectZero];
                    cell.accessoryView = switchTouchDeadZone ;
                    [switchTouchDeadZone setOn:[op touchDeadZone] animated:NO];
                    [switchTouchDeadZone addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];
                    break;
                }
                case 11:
                {
                    cell.textLabel.text   = @"Stick Touch DZ";
                    
                    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
                    cell.detailTextLabel.text = [arrayAnalogDZValue objectAtIndex:op.analogDeadZoneValue];
                    break;
                }
                case 12:
                {
                    if(g_btjoy_available)
                    {
                        cell.textLabel.text   = @"BT Analog DZ";
                        
                        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
                        cell.detailTextLabel.text = [arrayBTDZValue objectAtIndex:op.btDeadZoneValue];
                    }
                    
                    break;
                }

            }   
            break;
        }
           
       case kCustomLayout:
       {
           switch (indexPath.row)
           {
               case 0:
               {

                   cell.selectionStyle = UITableViewCellSelectionStyleBlue;
                   cell.textLabel.text = @"Change Current Layout";
                   cell.textLabel.textAlignment = UITextAlignmentCenter;
                   break;
               }
               case 1:
               {

                   cell.selectionStyle = UITableViewCellSelectionStyleBlue;
                   cell.textLabel.text = @"Reset Current Layout to Default";
                   cell.textLabel.textAlignment = UITextAlignmentCenter;
                   break;
               }
           }
           break;
       }
           
       case kGameDefaultsSection:
       {
           switch (indexPath.row) 
           {
               case 0:
               {
                   cell.textLabel.text   = @"Sound";
                   
                   cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
                   cell.detailTextLabel.text = [arraySoundValue objectAtIndex:op.soundValue];
                   break;
               }
               case 1:
               {
                   cell.textLabel.text   = @"Cheats";
                   [switchCheats release];
                   switchCheats  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchCheats ;
                   [switchCheats setOn:[op cheats] animated:NO];
                   [switchCheats addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }
               case 2:
               {
                   cell.textLabel.text   = @"Force 60Hz Sync";
                   [switchVsync release];
                   switchVsync  = [[UISwitch alloc] initWithFrame:CGRectZero];
                   cell.accessoryView = switchVsync ;
                   [switchVsync setOn:[op vsync] animated:NO];
                   [switchVsync addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];
                   break;
               }
               case 3:
               {
                   cell.textLabel.text   = @"Save Hiscores";
                   [switchHiscore release];
                   switchHiscore  = [[UISwitch alloc] initWithFrame:CGRectZero];
                   cell.accessoryView = switchHiscore ;
                   [switchHiscore setOn:[op hiscore] animated:NO];
                   [switchHiscore addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];
                   break;
               }
           }
           break;
       }
           
       case kAppDefaultsSection:
       {
           switch (indexPath.row)
           {
               case 0:
               {
                       cell.textLabel.text   = @"Native TV-OUT";
                       [switchTvoutNative release];
                       switchTvoutNative  = [[UISwitch alloc] initWithFrame:CGRectZero];
                       cell.accessoryView = switchTvoutNative ;
                       [switchTvoutNative setOn:[op tvoutNative] animated:NO];
                       [switchTvoutNative addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];
                       break;
               }
               case 1:
               {
                   cell.textLabel.text   = @"Threaded Video";
                   [switchThreaded release];
                   switchThreaded  = [[UISwitch alloc] initWithFrame:CGRectZero];
                   cell.accessoryView = switchThreaded ;
                   [switchThreaded setOn:[op threaded] animated:NO];
                   [switchThreaded addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];
                   break;
               }
               case 2://video thread p
               {

                   cell.textLabel.text   = @"Video Thread Priority";
                   cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
                   cell.detailTextLabel.text = [arrayVideoPriorityValue objectAtIndex:op.videoPriority];
                   break;
               }
               case 3:
               {
                   cell.textLabel.text   = @"Double Buffer";
                   [switchDblbuff release];
                   switchDblbuff  = [[UISwitch alloc] initWithFrame:CGRectZero];
                   cell.accessoryView = switchDblbuff ;
                   [switchDblbuff setOn:[op dblbuff] animated:NO];
                   [switchDblbuff addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];
                   break;
                   
                   break;
               }
               case 4:
               {
                       
                   cell.textLabel.text   = @"Main Thread Priority";
                   cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
                   cell.detailTextLabel.text = [arrayMainPriorityValue objectAtIndex:op.mainPriority];
                   break;
               }
            
           }
           break;
       }

        case kMiscSection:  //Miscellaneous
        {
            switch (indexPath.row) 
            {
              case 0:
               {
                   cell.textLabel.text   = @"Show FPS";
                   [switchShowFPS release];
                   switchShowFPS  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchShowFPS ;
                   [switchShowFPS setOn:[op showFPS] animated:NO];
                   [switchShowFPS addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }
               case 1:
               {                                                         
                   cell.textLabel.text   = @"Emulated Resolution";
                   cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
                   cell.detailTextLabel.text = [arrayEmuRes objectAtIndex:op.emures];

                   break;
               }               
              case 2:
               {
                   cell.textLabel.text   = @"Throttle";
                   [switchThrottle release];
                   switchThrottle  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchThrottle ;
                   [switchThrottle setOn:[op throttle] animated:NO];
                   [switchThrottle addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }
               case 3:
               {
                   cell.textLabel.text   = @"Frame Skip";
                   cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
                   cell.detailTextLabel.text = [arrayFSValue objectAtIndex:op.fsvalue];
    
                   break;
               }
               case 4:
               {
                   cell.textLabel.text   = @"Force Pixel Aspect";
                   [switchForcepxa release];
                   switchForcepxa  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchForcepxa ;
                   [switchForcepxa setOn:[op forcepxa] animated:NO];
                   [switchForcepxa addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }  
              case 5:
               {
                   cell.textLabel.text   = @"Sleep on Idle";
                   [switchSleep release];
                   switchSleep  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchSleep ;
                   [switchSleep setOn:[op sleep] animated:NO];
                   [switchSleep addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }                                                                             
              case 6:
               {
                   cell.textLabel.text   = @"Show Info/Warnings";
                   [switchShowINFO release];
                   switchShowINFO  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchShowINFO ;
                   [switchShowINFO setOn:[op showINFO] animated:NO];
                   [switchShowINFO addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }
               case 7:
               {
                    cell.textLabel.text   = @"Low Latency Audio";
                    [switchLowlsound release];
                    switchLowlsound  = [[UISwitch alloc] initWithFrame:CGRectZero];
                    cell.accessoryView = switchLowlsound ;
                    [switchLowlsound setOn:[op lowlsound] animated:NO];
                    [switchLowlsound addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];
                    break;
               }
               case 8:
               {
                   cell.textLabel.text   = @"Skin";
                   
                   cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
                   cell.detailTextLabel.text = [arraySkinValue objectAtIndex:op.skinValue];

                   break;
               }
               case 9:
               {
                   cell.textLabel.text   = @"Overscan TV-OUT";
                   
                   cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
                   cell.detailTextLabel.text = [arrayOverscanValue objectAtIndex:op.overscanValue];
                   
                   break;
               }               

            }
            break;   
        }
       case kFilterSection:
       {
           switch (indexPath.row)
           {
               case 0:
               {
                   cell.textLabel.text = @"Hide Non-Favorites";
                   [switchFilterFavorites release];
                   switchFilterFavorites  = [[UISwitch alloc] initWithFrame:CGRectZero];
                   cell.accessoryView = switchFilterFavorites ;
                   [switchFilterFavorites setOn:[op filterFavorites] animated:NO];
                   [switchFilterFavorites addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];
                   break;
                   
                   break;
               }
               
               case 1:
               {
                   cell.textLabel.text = @"Hide Clones";
                   [switchFilterClones release];
                   switchFilterClones  = [[UISwitch alloc] initWithFrame:CGRectZero];
                   cell.accessoryView = switchFilterClones ;
                   [switchFilterClones setOn:[op filterClones] animated:NO];
                   [switchFilterClones addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];
                   break;
               }

               case 2:
               {
                   cell.textLabel.text = @"Hide Not Working";
                   [switchFilterNotWorking release];
                   switchFilterNotWorking  = [[UISwitch alloc] initWithFrame:CGRectZero];
                   cell.accessoryView = switchFilterNotWorking ;
                   [switchFilterNotWorking setOn:[op filterNotWorking] animated:NO];
                   [switchFilterNotWorking addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];
                   break;
               }
                   
               case 3:
               {
                   cell.textLabel.text   = @"Keyword";
                   UITextField *textField = [[UITextField alloc] initWithFrame:CGRectMake(110, 40, 185, 25)] ;
                   textField.placeholder = @"Empty Text";
                   textField.text =  op.filterKeyword;
                   textField.tag = indexPath.row/2;
                   textField.returnKeyType = UIReturnKeyDone;
                   textField.autocorrectionType = UITextAutocorrectionTypeNo;
                   textField.autocapitalizationType = UITextAutocapitalizationTypeNone;
                   textField.spellCheckingType = UITextSpellCheckingTypeNo;
                   textField.clearButtonMode = UITextFieldViewModeNever;
                   textField.textAlignment = UITextAlignmentRight;
                   textField.keyboardType = UIKeyboardTypeASCIICapable;
                   textField.clearsOnBeginEditing = YES;
                   //textField.borderStyle = UITextBorderStyleRoundedRect;
                   textField.delegate = self;
                   cell.accessoryView = textField;
                   //[cell.contentView addSubview:textField];
                   [textField release];
                   
                   break;
               }
                   
               case 4:
               {
                   cell.textLabel.text   = @"Year >=";
                   cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
                   cell.detailTextLabel.text = [arrayYearGTEValue objectAtIndex:op.yearGTEValue];
                   break;
               }
               case 5:
               {
                   cell.textLabel.text   = @"Year <=";
                   cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
                   cell.detailTextLabel.text = [arrayYearLTEValue objectAtIndex:op.yearLTEValue];
                   break;
               }
                   
               case 6:
               {
                   cell.textLabel.text   = @"Manufacturer";
                   cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
                   cell.detailTextLabel.text = [[arrayManufacturerValue objectAtIndex:op.manufacturerValue] stringByReplacingOccurrencesOfString:@"#" withString:@""];
                   break;
               }
                   
               case 7:
               {
                   
                   cell.textLabel.text   = @"Driver Source";
                   cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
                   cell.detailTextLabel.text = [[arrayDriverSourceValue objectAtIndex:op.driverSourceValue]
                   stringByReplacingOccurrencesOfString:@"#" withString:@""];
                   break;
               }
               case 8:
               {
                   
                   cell.textLabel.text   = @"Category";
                   cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
                   cell.detailTextLabel.text = [[arrayCategoryValue objectAtIndex:op.categoryValue]
                                                stringByReplacingOccurrencesOfString:@"#" withString:@""];
                   break;
               }
               case 9:
               {
                    cell.selectionStyle = UITableViewCellSelectionStyleBlue;
                    cell.textLabel.text = @"Reset Filters to Default";
                    cell.textLabel.textAlignment = UITextAlignmentCenter;
                   break;
               }
           }
       }
   }
     
   [op release];
           
   return cell;    
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
      return kNumSections;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
		
    switch (section)
    {
          case kSupportSection: return @"Support";
          case kPortraitSection: return @"Portrait";
          case kLandscapeSection: return @"Landscape";
          case kInputSection: return @"Input";
          case kCustomLayout: return @"Custom Layout";
          case kGameDefaultsSection: return @"Game Defaults";
          case kAppDefaultsSection: return @"App Defaults";
          case kMiscSection: return @"Miscellaneous";
          case kFilterSection: return @"Game Filter";
    }
    return @"Error!";
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
   
      switch (section)
      {
          case kSupportSection: return 2;
          case kPortraitSection: return 5;
          case kLandscapeSection: return 5;
          case kInputSection: return 13-!g_btjoy_available;
          case kCustomLayout: return 2;
          case kGameDefaultsSection: return 4;
          case kAppDefaultsSection: return 5;
          case kMiscSection: return 10;
          case kFilterSection: return 10;
      }
    return -1;
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
    
    [switchKeepAspectPort release];
    [switchKeepAspectLand release];
    [switchSmoothedPort release];
    [switchSmoothedLand release];
    [switchTvFilterPort release];
    [switchTvFilterLand release];
    [switchScanlineFilterPort release];
    [switchScanlineFilterLand release];
    
    [switchShowFPS release];
    [switchShowINFO release];
    [switchAnimatedButtons release];
    
    [switchfullLand release];
    [switchfullPort release];
    
    [switchTouchDeadZone release];
    
    [switchTvoutNative release];
    
    [switchThrottle release];
    [switchAplusB release];
    [switchCheats release];
    [switchSleep release];
    [switchForcepxa release];
    
    [switchP1aspx release];
    
    [arrayNumbuttons release];
    [arrayEmuRes release];
    [arrayStickType release];
    [arrayTouchType release];
    [arrayControlType release];
    [arrayAnalogDZValue release];
    [arrayBTDZValue release];
    [arraySoundValue release];
    [arrayFSValue release];
    [arrayOverscanValue release];
    [arraySkinValue release];
    
    [switchFilterClones release];
    [switchFilterFavorites release];
    [switchFilterNotWorking release];
    [arrayManufacturerValue release];
    [arrayYearGTEValue release];
    [arrayYearLTEValue release];
    [arrayDriverSourceValue release];
    [arrayCategoryValue release];
    
    [switchLowlsound release];
    [switchVsync release];
    [switchThreaded release];
    [switchDblbuff release];
    
    [arrayMainPriorityValue release];
    [arrayVideoPriorityValue release];
    
    [arrayAutofireValue release];
    [switchHiscore release];
    
    [arrayButtonSizeValue release];
    [arrayStickSizeValue release];
    
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
			
	if(sender == switchfullLand) 
	   op.fullLand =  [switchfullLand isOn];

	if(sender == switchfullPort) 
	   op.fullPort =  [switchfullPort isOn];
  	   	   
	if(sender == switchTouchDeadZone)
	  op.touchDeadZone = [switchTouchDeadZone isOn];
  	   
	if(sender == switchTvoutNative)
	  op.tvoutNative = [switchTvoutNative isOn];  
	         
    if(sender == switchThrottle)
        op.throttle = [switchThrottle isOn];    
     
    if(sender == switchAplusB)
        op.aplusb = [switchAplusB isOn];   
    if(sender == switchCheats)
        op.cheats = [switchCheats isOn];   
    if(sender == switchSleep)
        op.sleep = [switchSleep isOn];

    if(sender == switchForcepxa)
        op.forcepxa = [switchForcepxa isOn];
    
    if(sender == switchP1aspx)
        op.p1aspx = [switchP1aspx isOn];
    
    if(sender == switchFilterClones)
        op.filterClones = [switchFilterClones isOn];
    if(sender == switchFilterFavorites)
        op.filterFavorites = [switchFilterFavorites isOn];
    if(sender == switchFilterNotWorking)
        op.filterNotWorking = [switchFilterNotWorking isOn];
    
    if(sender == switchLowlsound)
        op.lowlsound = [switchLowlsound isOn];
    
    if(sender == switchVsync)
        op.vsync = [switchVsync isOn];
    
    if(sender == switchThreaded)
        op.threaded = [switchThreaded isOn];
    
    if(sender == switchDblbuff)
        op.dblbuff = [switchDblbuff isOn];
    
    if(sender == switchHiscore)
        op.hiscore = [switchHiscore isOn];
    
	[op saveOptions];
		
	[op release];
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
    NSUInteger row = [indexPath row];
    NSUInteger section = [indexPath section];
    //printf("%d %d\n",section,row);
    
    switch (section)
    {
        case kSupportSection:
        {
            if (row==0){
                HelpController *controller = [[HelpController alloc] init];
                [[self navigationController] pushViewController:controller animated:YES];
                [controller release];
            }
            
            if (row==1){
                DonateController *controller = [[DonateController alloc] init];
                [[self navigationController] pushViewController:controller animated:YES];
                [controller release];
            }

            break;
        }
        case kInputSection:
        {
            if (row==1){
                ListOptionController *listController = [[ListOptionController alloc] initWithStyle:UITableViewStyleGrouped type:kTypeTouchType list:arrayTouchType];
                [[self navigationController] pushViewController:listController animated:YES];
                [listController release];
            }
            if (row==2){
                ListOptionController *listController = [[ListOptionController alloc] initWithStyle:UITableViewStyleGrouped
                                                        type:kTypeStickType list:arrayStickType];
                [[self navigationController] pushViewController:listController animated:YES];
                [listController release];
            }
            if (row==3){
                ListOptionController *listController = [[ListOptionController alloc] initWithStyle:UITableViewStyleGrouped
                                                   type:kTypeNumButtons list:arrayNumbuttons];      
                [[self navigationController] pushViewController:listController animated:YES];
                [listController release];
            }
            if (row==5){
                ListOptionController *listController = [[ListOptionController alloc] initWithStyle:UITableViewStyleGrouped
                                                                                              type:kTypeButtonSizeValue list:arrayButtonSizeValue];
                [[self navigationController] pushViewController:listController animated:YES];
                [listController release];
            }
            if (row==6){
                ListOptionController *listController = [[ListOptionController alloc] initWithStyle:UITableViewStyleGrouped
                                                                                              type:kTypeStickSizeValue list:arrayStickSizeValue];
                [[self navigationController] pushViewController:listController animated:YES];
                [listController release];
            }
            if (row==7){
                ListOptionController *listController = [[ListOptionController alloc] initWithStyle:UITableViewStyleGrouped
                                               type:kTypeControlType list:arrayControlType]; 
                [[self navigationController] pushViewController:listController animated:YES];
                [listController release];
            }
            if (row==9){
                ListOptionController *listController = [[ListOptionController alloc] initWithStyle:UITableViewStyleGrouped
                                                                                              type:kTypeAutofireValue list:arrayAutofireValue];
                [[self navigationController] pushViewController:listController animated:YES];
                [listController release];
            }
            if (row==11){
                ListOptionController *listController = [[ListOptionController alloc] initWithStyle:UITableViewStyleGrouped
                                    type:kTypeAnalogDZValue list:arrayAnalogDZValue];
                [[self navigationController] pushViewController:listController animated:YES];
                [listController release];
            }
            if (row==12){
                ListOptionController *listController = [[ListOptionController alloc] initWithStyle:UITableViewStyleGrouped
                                type:kTypeBTDZValue list:arrayBTDZValue];                        
                [[self navigationController] pushViewController:listController animated:YES];
                [listController release];
            }
            break;
        }
        case kGameDefaultsSection:
        {
            if (row==0){
                ListOptionController *listController = [[ListOptionController alloc] initWithStyle:UITableViewStyleGrouped
                                                         type:kTypeSoundValue list:arraySoundValue]; 
                [[self navigationController] pushViewController:listController animated:YES];
                [listController release];
            }
            break;
        }
        case kAppDefaultsSection:
        {
            if (row==2){
                ListOptionController *listController = [[ListOptionController alloc] initWithStyle:UITableViewStyleGrouped
                                                                                              type:kTypeVideoPriorityValue list:arrayVideoPriorityValue];
                [[self navigationController] pushViewController:listController animated:YES];
                [listController release];
            }
            if (row==4){
                ListOptionController *listController = [[ListOptionController alloc] initWithStyle:UITableViewStyleGrouped
                                                                                              type:kTypeMainPriorityValue list:arrayMainPriorityValue];
                [[self navigationController] pushViewController:listController animated:YES];
                [listController release];
            }
            break;
        }
        case kMiscSection:
        {
            if (row==1){
                ListOptionController *listController = [[ListOptionController alloc] initWithStyle:UITableViewStyleGrouped
                               type:kTypeEmuRes list:arrayEmuRes];                         
                [[self navigationController] pushViewController:listController animated:YES];
                [listController release];
            }
            if (row==3){
                ListOptionController *listController = [[ListOptionController alloc] initWithStyle:UITableViewStyleGrouped
                                type:kTypeFSValue list:arrayFSValue];                         
                [[self navigationController] pushViewController:listController animated:YES];
                [listController release];
            }
            if (row==8){
                ListOptionController *listController = [[ListOptionController alloc] initWithStyle:UITableViewStyleGrouped
                                                        type:kTypeSkinValue list:arraySkinValue];  
                [[self navigationController] pushViewController:listController animated:YES];
                [listController release];
            }
            if (row==10){
                ListOptionController *listController = [[ListOptionController alloc] initWithStyle:UITableViewStyleGrouped
                                                        type:kTypeOverscanValue list:arrayOverscanValue];
                [[self navigationController] pushViewController:listController animated:YES];
                [listController release];
            }
            break;
        }
        case kFilterSection:
        {
            
            if(row==3)
            {
                UITableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];
                [(UITextField *)cell.accessoryView  becomeFirstResponder];
            }
            
            
            if (row==4){
                ListOptionController *listController = [[ListOptionController alloc] initWithStyle:UITableViewStylePlain
                                                         type:kTypeYearGTEValue list:arrayYearGTEValue];

                [[self navigationController] pushViewController:listController animated:YES];
                [listController release];
            }
            if (row==5){
                ListOptionController *listController = [[ListOptionController alloc] initWithStyle:UITableViewStylePlain
                                                        type:kTypeYearLTEValue list:arrayYearLTEValue];

                [[self navigationController] pushViewController:listController animated:YES];
                [listController release];
            }
            
            if (row==6){
                ListOptionController *listController = [[ListOptionController alloc] initWithStyle:UITableViewStylePlain
                                                        type:kTypeManufacturerValue list:arrayManufacturerValue];
                
                [[self navigationController] pushViewController:listController animated:YES];
                [listController release];
            }
            
            if (row==7){
                ListOptionController *listController = [[ListOptionController alloc] initWithStyle:UITableViewStylePlain
                                                          type:kTypeDriverSourceValue list:arrayDriverSourceValue];
                                                        
                [[self navigationController] pushViewController:listController animated:YES];
                [listController release];
            }
            
            if (row==8){
                ListOptionController *listController = [[ListOptionController alloc] initWithStyle:UITableViewStylePlain
                                                                                              type:kTypeCategoryValue list:arrayCategoryValue];
                
                [[self navigationController] pushViewController:listController animated:YES];
                [listController release];
            }

            if (row==9){
                Options *op = [[Options alloc] init];
                
                op.filterClones=0;
                op.filterFavorites=0;
                op.filterNotWorking=0;
                op.yearLTEValue =0;
                op.yearGTEValue =0;
                op.manufacturerValue =0;
                op.driverSourceValue =0;
                op.categoryValue =0;
                op.filterKeyword = nil;
                
                [op saveOptions];
                [op release];
                
               [tableView reloadData];
                /*
                NSFileManager *filemgr = [[NSFileManager alloc] init];
                NSError *error = nil;
                [filemgr removeItemAtPath:[NSString stringWithUTF8String:get_documents_path("cfg")] error:&error];
                [filemgr release];
                */
            }
            break;
        }
        case kCustomLayout:
        {
            
            if(row==0)
            {
                [emuController beginCustomizeCurrentLayout];
                [tableView reloadData];
            }
            if(row==1)
            {
                [emuController resetCurrentLayout];
                [tableView reloadData];
            }
            break;
        }
    }
    
}
           
 - (void) viewWillAppear:(BOOL)animated {
     [super viewWillAppear:animated];
     UITableView *tableView = (UITableView *)self.view;
     [tableView reloadData];
}

- (void) textFieldDidBeginEditing:(UITextField *)textField {
    UITableViewCell *cell = (UITableViewCell*) [textField superview];
    UITableView *tableView = (UITableView *)self.view;
    [tableView scrollToRowAtIndexPath:[tableView indexPathForCell:cell] atScrollPosition:/*UITableViewScrollPositionMiddle*/UITableViewScrollPositionTop animated:YES];
}

- (void) textFieldDidEndEditing:(UITextField *)textField {
    Options *op = [[Options alloc] init];
    if(textField.text == nil ||  textField.text.length==0)
        op.filterKeyword = nil;
    else
        op.filterKeyword = [textField.text substringToIndex:MIN(MAX_FILTER_KEYWORD-1,textField.text.length)];
    [op saveOptions];
    [op release];
    /*
    UITableViewCell *cell = (UITableViewCell*) [textField superview];
    UITableView *tableView = (UITableView *)self.view;
    [tableView scrollToRowAtIndexPath:[tableView indexPathForCell:cell] atScrollPosition:UITableViewScrollPositionMiddle animated:YES];*/
}

- (BOOL) textFieldShouldReturn:(UITextField *)textField
{
    [textField resignFirstResponder];
    return YES;
}

- (BOOL) textFieldShouldClear:(UITextField *)textField {
    Options *op = [[Options alloc] init];
    op.filterKeyword = nil;
    [op saveOptions];
    [op release];
    return YES;
}

@end
