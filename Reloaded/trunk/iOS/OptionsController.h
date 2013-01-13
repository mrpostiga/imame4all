/*
 * This file is part of MAME4iOS.
 *
 * Copyright (C) 2012 David Valdeita (Seleuco)
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

#import <UIKit/UIKit.h>

@interface Options : NSObject
{
   NSMutableArray*	  optionsArray;

   @public  int keepAspectRatioPort;
   @public  int keepAspectRatioLand;
   @public  int smoothedPort;
   @public  int smoothedLand;

   @public  int tvFilterPort;
   @public  int tvFilterLand;
   @public  int scanlineFilterPort;
   @public  int scanlineFilterLand;

   @public  int showFPS;
   @public  int animatedButtons;
   @public  int fourButtonsLand;
   @public  int fullLand;
   @public  int fullPort;

   @public  int skinValue;

   @public  int wiiDeadZoneValue;
   @public  int touchDeadZone;

   @public  int overscanValue;
   @public  int tvoutNative;

   @public  int touchtype;
   @public  int analogDeadZoneValue;
    
   @public  int controltype;
   @public  int showINFO;
    
   @public int soundValue;

   @public int throttle;
   @public int fsvalue;
   @public int sticktype;
   @public int numbuttons;
   @public int aplusb;
   @public int cheats;
   @public int sleep;

   @public int forcepxa;
   @public int emures;
   @public int p1aspx;
    
   @public int filterClones;
   @public int filterFavorites;
   @public int filterNotWorking;
   @public int manufacturerValue;
   @public int yearGTEValue;
   @public int yearLTEValue;
   @public int driverSourceValue;
   @public int categoryValue;
    
   @public NSString *filterKeyword;
    
   @public int lowlsound;
    
}

- (void)loadOptions;
- (void)saveOptions;

@property (readwrite,assign) int keepAspectRatioPort;
@property (readwrite,assign) int keepAspectRatioLand;
@property (readwrite,assign) int smoothedPort;
@property (readwrite,assign) int smoothedLand;

@property (readwrite,assign) int tvFilterPort;
@property (readwrite,assign) int tvFilterLand;

@property (readwrite,assign) int scanlineFilterPort;
@property (readwrite,assign) int scanlineFilterLand;

@property (readwrite,assign) int showFPS;
@property (readwrite,assign) int animatedButtons;
@property (readwrite,assign) int fourButtonsLand;
@property (readwrite,assign) int fullLand;
@property (readwrite,assign) int fullPort;

@property (readwrite,assign) int skinValue;

@property (readwrite,assign) int wiiDeadZoneValue;
@property (readwrite,assign) int touchDeadZone;

@property (readwrite,assign) int overscanValue;
@property (readwrite,assign) int tvoutNative;

@property (readwrite,assign) int touchtype;
@property (readwrite,assign) int analogDeadZoneValue;

@property (readwrite,assign) int controltype;
@property (readwrite,assign) int showINFO;

@property (readwrite,assign) int soundValue;

@property (readwrite,assign) int throttle;
@property (readwrite,assign) int fsvalue;
@property (readwrite,assign) int sticktype;
@property (readwrite,assign) int numbuttons;
@property (readwrite,assign) int aplusb;
@property (readwrite,assign) int cheats;
@property (readwrite,assign) int sleep;

@property (readwrite,assign) int forcepxa;
@property (readwrite,assign) int emures;
@property (readwrite,assign) int p1aspx;

@property (readwrite,assign) int filterClones;
@property (readwrite,assign) int filterFavorites;
@property (readwrite,assign) int filterNotWorking;
@property (readwrite,assign) int manufacturerValue;
@property (readwrite,assign) int yearGTEValue;
@property (readwrite,assign) int yearLTEValue;
@property (readwrite,assign) int driverSourceValue;
@property (readwrite,assign) int categoryValue;

@property (readwrite,assign) NSString *filterKeyword;

@property (readwrite,assign) int lowlsound;

@end

enum OptionSections
{
    kSupportSection = 0,
    kFilterSection = 1,
    kPortraitSection = 2,
    kLandscapeSection = 3,
    kInputSection = 4,
    kDefaultsSection = 5,
    kMiscSection = 6
};

enum ListOptionType
{
    kTypeNumButtons,
    kTypeEmuRes,
    kTypeStickType,
    kTypeTouchType,
    kTypeControlType,
    kTypeAnalogDZValue,
    kTypeWiiDZValue,
    kTypeSoundValue,
    kTypeFSValue,
    kTypeOverscanValue,
    kTypeSkinValue,
    kTypeManufacturerValue,
    kTypeYearGTEValue,
    kTypeYearLTEValue,
    kTypeDriverSourceValue,
    kTypeCategoryValue
    
};

@interface OptionsController : UIViewController  <UITableViewDelegate, UITableViewDataSource, UITextFieldDelegate>
{
   UIViewController*  emuController;
   
   UISwitch*		  switchKeepAspectPort;
   UISwitch*		  switchKeepAspectLand;
   UISwitch*		  switchSmoothedPort;
   UISwitch*		  switchSmoothedLand;

   UISwitch*		  switchTvFilterPort;
   UISwitch*		  switchScanlineFilterPort;

   UISwitch*		  switchTvFilterLand;
   UISwitch*		  switchScanlineFilterLand;

   UISwitch*		  switchShowFPS;
   UISwitch*		  switchShowINFO;
   UISwitch*		  switchAnimatedButtons;

   UISwitch*		  switchfullLand;
   UISwitch*		  switchfullPort;

   UISwitch           *switchTouchDeadZone;

   UISwitch           *switchTvoutNative;
       
   UISwitch *switchThrottle;

   UISwitch *switchAplusB;
   UISwitch *switchCheats;
   UISwitch *switchSleep;

   UISwitch *switchForcepxa;

   UISwitch *switchP1aspx;
   
   NSArray *arrayNumbuttons;
   NSArray *arrayEmuRes;
   NSArray *arrayTouchType;
   NSArray *arrayStickType;
   NSArray *arrayControlType;
   NSArray *arrayAnalogDZValue;
   NSArray *arrayWiiDZValue;
   NSArray *arraySoundValue;
   NSArray *arrayFSValue;
   NSArray *arrayOverscanValue;
   NSArray *arraySkinValue;
    
    
   UISwitch *switchFilterClones;
   UISwitch *switchFilterFavorites;
   UISwitch *switchFilterNotWorking;
   NSMutableArray  *arrayManufacturerValue;
   NSMutableArray  *arrayYearGTEValue;
   NSMutableArray  *arrayYearLTEValue;
   NSMutableArray  *arrayDriverSourceValue;
   NSMutableArray  *arrayCategoryValue;
    
   UISwitch *switchLowlsound;
    
}

- (void)optionChanged:(id)sender;

@property (nonatomic, assign) UIViewController *emuController;

@end
