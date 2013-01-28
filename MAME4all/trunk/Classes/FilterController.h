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
