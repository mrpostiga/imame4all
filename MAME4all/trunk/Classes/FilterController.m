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
#import "FilterController.h"
#import "FilterManuController.h"
#import "FilterCategoryController.h"
#import "FilterYearController.h"


@implementation FilterOptions

enum ControlTableSections
{
    kFilterMainSection,
	kFilterFilterSection,
    kFilterOtherSection,
    kFilterClearSection
};

@synthesize flt_filter;
@synthesize flt_clones;
@synthesize flt_manufacturer;
@synthesize flt_category;
@synthesize flt_year;


- (id)init {
    
    if (self = [super init]) {
        [self loadFilterOptions];
    }
    
    return self;
}

- (void)loadFilterOptions
{
	
	NSString *path=[NSString stringWithCString:get_documents_path("iOS/filter_v10.bin")];
	
	NSData *plistData;
	id plist;
	NSString *error;
	
	NSPropertyListFormat format;
	
    NSError *sqerr;
	plistData = [NSData dataWithContentsOfFile:path options: NSMappedRead error:&sqerr];
    
	plist = [NSPropertyListSerialization propertyListFromData:plistData			 
				mutabilityOption:NSPropertyListImmutable format:&format errorDescription:&error];
	if(!plist)
	{
		filterArray = [[NSMutableArray alloc] init];
		
        flt_manufacturer=0;
		flt_clones=1;
        flt_filter=0;
        flt_category=0;
        flt_year=0;
	}
	else
	{
		filterArray = [[NSMutableArray alloc] initWithArray:plist];
		
		flt_manufacturer = [[[filterArray objectAtIndex:0] objectForKey:@"Manufacturer"] intValue];
		flt_clones = [[[filterArray objectAtIndex:0] objectForKey:@"showClones"] intValue];
		flt_filter = [[[filterArray objectAtIndex:0] objectForKey:@"Filter"] intValue];
		flt_category = [[[filterArray objectAtIndex:0] objectForKey:@"Category"] intValue];
        flt_year = [[[filterArray objectAtIndex:0] objectForKey:@"Year"] intValue];
	}
    
}

- (void)saveFilterOptions
{
    
	[filterArray removeAllObjects];
	[filterArray addObject:[NSDictionary dictionaryWithObjectsAndKeys:
             [NSString stringWithFormat:@"%d", flt_filter], @"Filter",
             [NSString stringWithFormat:@"%d", flt_clones], @"showClones",
             [NSString stringWithFormat:@"%d", flt_manufacturer], @"Manufacturer",                
             [NSString stringWithFormat:@"%d", flt_category], @"Category",                
             [NSString stringWithFormat:@"%d", flt_year], @"Year",  
                    nil]];	
    
    NSString *path=[NSString stringWithCString:get_documents_path("iOS/filter_v10.bin")];
	NSData *plistData;
	NSString *error;
    
	plistData = [NSPropertyListSerialization dataFromPropertyList:filterArray				 
                    format:NSPropertyListBinaryFormat_v1_0  errorDescription:&error];	
	if(plistData) {
        NSError*err;
        
		BOOL b = [plistData writeToFile:path atomically:NO];
		if(!b) {
            UIAlertView *errAlert = [[UIAlertView alloc] initWithTitle:@"Error saving filter!" 
                                        message://[NSString stringWithFormat:@"Error:%@",[err localizedDescription]]  
                                        @"Filter couldn't be saved.\n Check for write permissions. chmod 777 if needed. See help." 
                                        delegate:self cancelButtonTitle:@"OK" otherButtonTitles: nil];	
            [errAlert show];
            [errAlert release];
		}		
	} else {        
		NSLog(error);		
		[error release];		
	}	
}

- (void)dealloc {
    [filterArray dealloc];
	[super dealloc];
}

@end

@implementation FilterController

@synthesize savedparent;
@synthesize local_filter;

- (id)init {
    
    if (self = [super init]) {
        switchclones=nil;
    }
    
    return self;
}


- (void)viewDidLoad {
    [super viewDidLoad];
}

- (void)viewDidUnload {
	[super viewDidUnload];
}

- (void)didReceiveMemoryWarning {
	[super didReceiveMemoryWarning];
}

- (void)loadView {
    
    UIBarButtonItem *backButton = [[UIBarButtonItem alloc] initWithTitle:@"Done" 
                                                            style:UIBarButtonItemStyleBordered 
                                                            target:savedparent  action:  @selector(done:) ];
    self.navigationItem.rightBarButtonItem = backButton;
    [backButton release];

    self.title = NSLocalizedString(@"Game Filter", @"");
       
    CGRect frame = CGRectMake(0, 0, 240, 200);

    UITableView *tableView = [[UITableView alloc] 
            initWithFrame:frame style:UITableViewStyleGrouped];
    
    tableView.delegate = self;
    tableView.dataSource = self;
    tableView.autoresizesSubviews = YES;
    self.view = tableView;
    [tableView release];
    
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 4;
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
      switch (section)
      {
          case kFilterMainSection: return 2;
          case kFilterFilterSection: return 3;
          case kFilterOtherSection: return 1;
		  case kFilterClearSection: return 1;
      }
}

//- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
//    switch (section)
//    {
//        case kFilterMainSection: return @"Filters";
//        case kFilterOtherSection: return @"Other Filters";
//        default: return @" ";
//    }
//}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    NSString *cellIdentifier = [NSString stringWithFormat: @"%d:%d", [indexPath indexAtPosition:0], [indexPath indexAtPosition:1]];
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:cellIdentifier];
    
    if (cell == nil)
    {
        //If not possible create a new cell
        if (indexPath.section == kFilterClearSection) {
            cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"CellIdentifier"] autorelease];
        } else {
            cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:@"CellIdentifier"] autorelease];
        }
        cell.accessoryType = UITableViewCellAccessoryNone;
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
    }
    
    FilterOptions *op = [[FilterOptions alloc] init];

	switch (indexPath.section)
	{
		case kFilterMainSection:
		{
            switch (indexPath.row) 
            {
                case 0:
                {
                    cell.text  = @"All";
					cell.accessoryType = (local_filter == 0) ? UITableViewCellAccessoryCheckmark : UITableViewCellAccessoryNone;
                    break;
                }

                case 1:
                {
                    cell.text  = @"Favorites";
					cell.accessoryType = (local_filter == 1) ? UITableViewCellAccessoryCheckmark : UITableViewCellAccessoryNone;
                    break;
                }
            }
			break;
		}

		case kFilterFilterSection:
		{
			switch (indexPath.row)
			{
                case 0:
                {
                    cell.text  = @"Category";
                    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
                    
                    NSArray *array = [[NSArray alloc] initWithObjects:CATEGORY_LIST, nil];
                    cell.detailTextLabel.text = [array objectAtIndex:op.flt_category];
                    [array release];
                    break;
                }

                case 1:
                {
                    cell.text  = @"Manufacturer";
                    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
                    
                    NSArray *array = [[NSArray alloc] initWithObjects:MANUFACTURER_LIST, nil];
                    cell.detailTextLabel.text = [array objectAtIndex:op.flt_manufacturer];
                    [array release];
                    break;
                }
                case 2:
                {
                    cell.text  = @"Year";
                    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
                    
                    NSArray *array = [[NSArray alloc] initWithObjects:YEAR_LIST, nil];
                    cell.detailTextLabel.text = [array objectAtIndex:op.flt_year];
                    [array release];
                    break;
                }

			}
			break;
		}

		case kFilterOtherSection:
		{
            cell.text  = @"Show Clones";
            switchclones = [[UISwitch alloc] initWithFrame:CGRectZero];                
            cell.accessoryView = switchclones;
            [switchclones setOn:[op flt_clones] animated:NO];
            [switchclones addTarget:self action:@selector(optionChanged:) forControlEvents:UIControlEventValueChanged];                   
            break;
		}

		case kFilterClearSection:
		{
	        cell.selectionStyle = UITableViewCellSelectionStyleBlue;
	        cell.text = @"Reset Filters to Default";
	        cell.textAlignment = UITextAlignmentCenter;
	        break;
		}

	}

    [op release];
    
    return cell;  
}
            

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    FilterOptions *op = [[FilterOptions alloc] init];
    NSUInteger row = [indexPath row];
    NSUInteger section = [indexPath section];
    
    switch (section) 
	{
    	case kFilterFilterSection:
        {
            if (row == 0) {
                FilterCategoryController *filterCategoryController = [[FilterCategoryController alloc] initWithStyle:UITableViewStyleGrouped];
                
                filterCategoryController.category = op.flt_category; 
                // Push the detail view controller.
                [[self navigationController] pushViewController:filterCategoryController animated:YES];
                [filterCategoryController release];
            }

            if (row == 1) {
                FilterManuController *filterManuController = [[FilterManuController alloc] initWithStyle:UITableViewStyleGrouped];
                
                filterManuController.manufacturer = op.flt_manufacturer; 
                // Push the detail view controller.
                [[self navigationController] pushViewController:filterManuController animated:YES];
                [filterManuController release];
            }
            
            
            if (row == 2) {
                FilterYearController *filterYearController = [[FilterYearController alloc] initWithStyle:UITableViewStyleGrouped];
                
                filterYearController.fyear = op.flt_year; 
                // Push the detail view controller.
                [[self navigationController] pushViewController:filterYearController animated:YES];
                [filterYearController release];
            }
            
    		break;
        }
    
    	case kFilterMainSection:
        {
    		if (row != local_filter) {
            	local_filter = row;
    		}
            [self.tableView reloadData];
			break;
        }

		case kFilterClearSection:
        {
            op.flt_filter = 0;
			op.flt_manufacturer = 0;
			op.flt_category = 0;
            op.flt_year = 0;
			local_filter = 0;

            [op saveFilterOptions];
			[self.tableView reloadData];
			break;
        }
	}
    
    [op release];
}


- (void)dealloc {
    if(switchclones!=nil)   [switchclones release];     

    [savedparent release];
    
    [super dealloc];
}

- (void)optionChanged:(id)sender {
    FilterOptions *op = [[FilterOptions alloc] init];
	
    if(sender==switchclones) op.flt_clones = [switchclones isOn];
    
	[op saveFilterOptions];
	[op release];
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];

    FilterOptions *op = [[FilterOptions alloc] init];
    op.flt_filter = local_filter;

    [op saveFilterOptions];
    [op release];
}

- (void) viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];

    FilterOptions *op = [[FilterOptions alloc] init];
	local_filter = op.flt_filter;
    [op release];
    
    //SQ: reload view from any sub table changes
    [self.tableView reloadData];
}

-(BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    //return (interfaceOrientation == UIInterfaceOrientationPortrait);
    return YES;
}

@end
