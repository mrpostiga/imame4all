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

#import "FilterYearController.h"
#import "FilterController.h"


@implementation FilterYearController;

@synthesize list;
@synthesize fyear;



- (void)viewDidLoad {
	NSArray *array = [[NSArray alloc] initWithObjects:YEAR_LIST, nil];
	self.list = array;
	[array release];
    [super viewDidLoad];
}

- (void)viewDidUnload {
	[super viewDidUnload];
}

- (void)dealloc {
	[list release];
	[super dealloc];
}

- (void)viewWillAppear:(BOOL)animated {
    self.title = @"Year";
    
    FilterOptions *op = [[FilterOptions alloc] init];
    fyear = op.flt_year;
    [op release];
    
    [super viewWillAppear:animated];
    
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    if (fyear > 10) {
        NSIndexPath *scrollIndexPath = [NSIndexPath indexPathForRow:(fyear) inSection:0];
        [[self tableView] scrollToRowAtIndexPath:scrollIndexPath atScrollPosition:UITableViewScrollPositionMiddle animated:NO];
    }
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    
    FilterOptions *op = [[FilterOptions alloc] init];
    op.flt_year = fyear;
    
    [op saveFilterOptions];
    [op release];
    
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [list count];
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *CheckMarkCellIdentifier = @"CheckMarkCellIdentifier";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CheckMarkCellIdentifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault
                                       reuseIdentifier:CheckMarkCellIdentifier] autorelease];
    }
    NSUInteger row = [indexPath row];
    cell.textLabel.text = [list objectAtIndex:row];
    cell.accessoryType = (row == fyear) ? UITableViewCellAccessoryCheckmark : UITableViewCellAccessoryNone;
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    int row = [indexPath row];
    if (row != fyear) {
        fyear = row;
    }
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    [self.tableView reloadData];
    
}



@end
