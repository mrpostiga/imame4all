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
#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

#define MANUFACTURER_LIST @"All", @"Atari", @"Capcom", @"Cinematronics", @"Data East", @"Exidy", @"Gremlin", @"Irem", @"Jaleco", @"Leland", @"Konami", @"Midway", @"Namco", @"NeoGeo", @"Nichibutsu", @"Nintendo", @"Other", @"Sega", @"SNK", @"Stern", @"Taito", @"Technos", @"Tecmo", @"Toaplan", @"Universal", @"Video System", @"Williams"

#define CATEGORY_LIST @"All", @"Ball & Paddle", @"Breakout", @"Casino", @"Climbing", @"Driving", @"Fighter", @"Maze", @"Mini-Games", @"Misc", @"Multiplay", @"Pinball", @"Platform", @"Puzzle", @"Quiz", @"Shooter", @"Sports", @"Tabletop", @"Wrestling"

#define YEAR_LIST @"All", @"1975",@"1976",@"1977",@"1978",@"1979",@"1980", @"1981", @"1982", @"1983", @"1984", @"1985", @"1986", @"1987", @"1988", @"1989", @"1990", @"1991", @"1992", @"1993", @"1994", @"1995", @"1996", @"1997", @"1998"


@interface FilterOptions : NSObject {
    NSMutableArray* filterArray;

    @public NSInteger flt_filter;
    @public NSInteger flt_clones;
    @public NSInteger flt_manufacturer;
    @public NSInteger flt_category;
    @public NSInteger flt_year;

}

- (void)loadFilterOptions;
- (void)saveFilterOptions;

@property (readwrite,assign) NSInteger flt_filter;
@property (readwrite,assign) NSInteger flt_clones;
@property (readwrite,assign) NSInteger flt_manufacturer;
@property (readwrite,assign) NSInteger flt_category;
@property (readwrite,assign) NSInteger flt_year;


@end


@interface FilterController : UITableViewController {
    UISwitch          *switchclones;
    UIViewController  *savedparent;
    NSInteger         local_filter;
}

@property (nonatomic, retain) UIViewController *savedparent;
@property (nonatomic, assign) NSInteger local_filter;

@end
