/*
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
 */

#import "FilterManuController.h"
#import "FilterController.h"


@implementation FilterManuController;

@synthesize list;
@synthesize manufacturer;



- (void)viewDidLoad {
	NSArray *array = [[NSArray alloc] initWithObjects:MANUFACTURER_LIST, nil];
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
    self.title = @"Manufacturer";
    
    FilterOptions *op = [[FilterOptions alloc] init];
    manufacturer = op.flt_manufacturer;
    [op release];

    [super viewWillAppear:animated];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    if (manufacturer > 10) {
        NSIndexPath *scrollIndexPath = [NSIndexPath indexPathForRow:(manufacturer) inSection:0];
        [[self tableView] scrollToRowAtIndexPath:scrollIndexPath atScrollPosition:UITableViewScrollPositionMiddle animated:NO];
    }
}


- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    
    FilterOptions *op = [[FilterOptions alloc] init];
    op.flt_manufacturer = manufacturer;
    
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
    cell.accessoryType = (row == manufacturer) ? UITableViewCellAccessoryCheckmark : UITableViewCellAccessoryNone;

    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    int row = [indexPath row];
    if (row != manufacturer) {
        manufacturer = row;
    }
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    [self.tableView reloadData];
    
}



@end
