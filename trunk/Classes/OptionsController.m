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
@synthesize animatedButtons;
@synthesize lowlatencySound;
@synthesize fourButtonsLand;
@synthesize fullLand;
@synthesize fullPort;

@synthesize skin;

@synthesize deadZoneValue;
@synthesize touchDeadZone;


- (id)init {

    if (self = [super init]) {
        [self loadOptions];
    }

    return self;
}


- (void)loadOptions
{
	
	NSString *path=[NSString stringWithCString:get_documents_path("iOS/options_v6.bin")];
	
	NSData *plistData;
	id plist;
	NSString *error;
	
	NSPropertyListFormat format;
	
	plistData = [NSData dataWithContentsOfFile:path];
		
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
        fourButtonsLand = 0;
        lowlatencySound =isIpad?1:0;
        animatedButtons = ![[Helper machine] isEqualToString: @"iPhone1,1"] 
		              && ![[Helper machine] isEqualToString: @"iPhone1,2"] 		               
		              && ![[Helper machine] isEqualToString: @"iPod1,1"]		              
		              ;
		              
        fullLand = animatedButtons;
        fullPort = 0;
        
        skin = isIpad ? 2 : 1;
        deadZoneValue = 2;
        touchDeadZone = 1;
		
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
        fourButtonsLand =  [[[optionsArray objectAtIndex:0] objectForKey:@"fourButtonsLand"] intValue];
        lowlatencySound =  [[[optionsArray objectAtIndex:0] objectForKey:@"lowlatencySound"] intValue];
        animatedButtons =  [[[optionsArray objectAtIndex:0] objectForKey:@"animatedButtons"] intValue];	
        fullLand =  [[[optionsArray objectAtIndex:0] objectForKey:@"fullLand"] intValue];
        fullPort =  [[[optionsArray objectAtIndex:0] objectForKey:@"fullPort"] intValue];
        
        skin =  [[[optionsArray objectAtIndex:0] objectForKey:@"skin"] intValue];
        
        deadZoneValue =  [[[optionsArray objectAtIndex:0] objectForKey:@"deadZoneValue"] intValue];
        touchDeadZone =  [[[optionsArray objectAtIndex:0] objectForKey:@"touchDeadZone"] intValue];
        		
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
							 [NSString stringWithFormat:@"%d", fourButtonsLand], @"fourButtonsLand",
							 [NSString stringWithFormat:@"%d", lowlatencySound], @"lowlatencySound",							 
							 [NSString stringWithFormat:@"%d", animatedButtons], @"animatedButtons",							 							 							 											 
							 [NSString stringWithFormat:@"%d", fullLand], @"fullLand",
							 [NSString stringWithFormat:@"%d", fullPort], @"fullPort",
							 
							 [NSString stringWithFormat:@"%d", skin], @"skin",
							  
							 [NSString stringWithFormat:@"%d", deadZoneValue], @"deadZoneValue",
							 [NSString stringWithFormat:@"%d", touchDeadZone], @"touchDeadZone",
							 nil]];	

	
    NSString *path=[NSString stringWithCString:get_documents_path("iOS/options_v6.bin")];
	
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
	   switchAnimatedButtons=nil;
   	   switchLowlatencySound=nil;
	   switch4buttonsLand=nil;
	   switchfullLand=nil;
	   switchfullPort=nil;
	   
	   segmentedSkin= nil;
	   
	   segmentedDeadZoneValue = nil;
	   switchTouchDeadZone = nil;

    }

    return self;
}

- (void)loadView {

	struct CGRect rect = [self parentViewController].view.frame;//[[UIScreen mainScreen] bounds];
	rect.origin.x = rect.origin.y = 0.0f;
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
       case 0: 
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
                   cell.text  = @"TV Filter";
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
       case 1:
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
                   cell.text  = @"TV Filter";
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
        case 2:
        {
            switch (indexPath.row) 
            {
               case 0:
               {
                   cell.text  = @"Animated DPad";
                   switchAnimatedButtons  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchAnimatedButtons ;
                   [switchAnimatedButtons setOn:[op animatedButtons] animated:NO];
                   [switchAnimatedButtons addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }
               case 1:
               {
                   cell.text  = @"Low Latency Sound";
                   switchLowlatencySound  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchLowlatencySound ;
                   [switchLowlatencySound setOn:[op lowlatencySound] animated:NO];
                   [switchLowlatencySound addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }
              case 2:
               {
                   cell.text  = @"Show FPS";
                   switchShowFPS  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchShowFPS ;
                   [switchShowFPS setOn:[op showFPS] animated:NO];
                   [switchShowFPS addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }
              case 3:
               {
                   cell.text  = @"Touch DeadZone";
                   switchTouchDeadZone  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchTouchDeadZone ;
                   [switchTouchDeadZone setOn:[op touchDeadZone] animated:NO];
                   [switchTouchDeadZone addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
                   break;
               }               
               case 4:
               {                                      
                   cell.text  = @"Wii Classic DZ";
                   
                    segmentedDeadZoneValue = [[UISegmentedControl alloc] initWithItems:
                       [NSArray arrayWithObjects: @"1", @"2", @"3",@"4", @"5", @"6", nil]];
                    //segmentedDeadZoneValue.frame = CGRectMake(145, 5, 150, 35);
                    segmentedDeadZoneValue.selectedSegmentIndex = [op deadZoneValue];
                    //actionControl.tag = 3;
                    [segmentedDeadZoneValue addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];
                    segmentedDeadZoneValue.segmentedControlStyle = UISegmentedControlStyleBar;
                    //[cell addSubview:segmentedDeadZoneValue];
                     cell.accessoryView = segmentedDeadZoneValue;

                   break;
               }
               case 5:
               {
                   cell.text  = @"Skin";                   
                   segmentedSkin = [[UISegmentedControl alloc] initWithItems:
                   [NSArray arrayWithObjects: @"A", @"B", @"B+Retina", nil]];
                    //segmentedDeadZoneValue.frame = CGRectMake(145, 5, 150, 35);
                   segmentedSkin.selectedSegmentIndex = [op skin];
                    //actionControl.tag = 3;
                   [segmentedSkin addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];
                   segmentedSkin.segmentedControlStyle = UISegmentedControlStyleBar;
                   //[cell addSubview:segmentedDeadZoneValue];
                   cell.accessoryView = segmentedSkin;
                   break;
               }               
               case 6:
               {
                   cell.text  = @"Safe Render Path";
                   switchSafeRender  = [[UISwitch alloc] initWithFrame:CGRectZero];                
                   cell.accessoryView = switchSafeRender ;
                   [switchSafeRender setOn:[op safeRenderPath] animated:NO];
                   [switchSafeRender addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];   
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
      return 3;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
		
    switch (section)
    {
          case 0: return @"Portrait";
          case 1: return @"Landscape";
          case 2: return @"Miscellaneous";
    }
}
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
   
      switch (section)
      {
          case 0: return 5;
          case 1: return 5;
          case 2: return (isIpad | isIphone4) ? 6 : 7;
      }
}

-(void)viewDidLoad{	

}


-(BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
     return (interfaceOrientation == UIInterfaceOrientationPortrait);
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
   if(switchAnimatedButtons!=nil)
     [switchAnimatedButtons release];
   if(switchLowlatencySound!=nil)
     [switchLowlatencySound release];
   if(switch4buttonsLand!=nil)
     [switch4buttonsLand release];
   if(switchfullLand!=nil)
     [switchfullLand release];      
   if(switchfullPort!=nil)
     [switchfullPort release]; 
          
   if(segmentedSkin!=nil)
     [segmentedSkin release];  
     
   if(segmentedDeadZoneValue!=nil)
    [segmentedDeadZoneValue release];
    
   if(switchTouchDeadZone!=nil)
     [switchTouchDeadZone release];
     
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
	
	/*
	if(isIpad)
	   op.safeRenderPath = 1;
	else
	*/
	
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
	
	if(sender == switchAnimatedButtons) 
	   op.animatedButtons=  [switchAnimatedButtons isOn];

    if(sender == switchLowlatencySound)
	   op.lowlatencySound =  [switchLowlatencySound isOn];
	
	if(sender == switch4buttonsLand) 
	   op.fourButtonsLand =  [switch4buttonsLand isOn];	
	
	if(sender == switchfullLand) 
	   op.fullLand =  [switchfullLand isOn];

	if(sender == switchfullPort) 
	   op.fullPort =  [switchfullPort isOn];
	   
    if(sender == segmentedSkin) 
	   op.skin =  [segmentedSkin selectedSegmentIndex];   
	   
	if(sender == segmentedDeadZoneValue)
	   op.deadZoneValue = [segmentedDeadZoneValue selectedSegmentIndex];   
	   
	if(sender == switchTouchDeadZone)
	  op.touchDeadZone = [switchTouchDeadZone isOn];
	   
	[op saveOptions];
		
	[op release];
}


@end