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

   @public  int skin;

   @public  int wiiDeadZoneValue;
   @public  int touchDeadZone;

   @public  int overscanValue;
   @public  int tvoutNative;

   @public  int inputTouchType;
   @public  int analogDeadZoneValue;
    
   @public  int iCadeLayout;
   @public  int showINFO;
    
   @public int SoundKHZ;
   @public int soundEnabled;

   @public int throttle;
   @public int fskip;
   @public int fslevel;
   @public int sticktype;
   @public int numbuttons;
   @public int aplusb;
   @public int cheats;
   @public int sleep;

   @public int forcepxa;
   @public int emures;
   @public int p1aspx;

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

@property (readwrite,assign) int skin;

@property (readwrite,assign) int wiiDeadZoneValue;
@property (readwrite,assign) int touchDeadZone;

@property (readwrite,assign) int overscanValue;
@property (readwrite,assign) int tvoutNative;

@property (readwrite,assign) int inputTouchType;
@property (readwrite,assign) int analogDeadZoneValue;

@property (readwrite,assign) int iCadeLayout;
@property (readwrite,assign) int showINFO;

@property (readwrite,assign) int SoundKHZ;
@property (readwrite,assign) int soundEnabled;

@property (readwrite,assign) int throttle;
@property (readwrite,assign) int fskip;
@property (readwrite,assign) int fslevel;
@property (readwrite,assign) int sticktype;
@property (readwrite,assign) int numbuttons;
@property (readwrite,assign) int aplusb;
@property (readwrite,assign) int cheats;
@property (readwrite,assign) int sleep;

@property (readwrite,assign) int forcepxa;
@property (readwrite,assign) int emures;
@property (readwrite,assign) int p1aspx;

@end


@interface OptionsController : UIViewController  <UITableViewDelegate, UITableViewDataSource>
{

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
   UISwitch*		  switch4buttonsLand;
   UISwitch*		  switchfullLand;
   UISwitch*		  switchfullPort;

   UISegmentedControl *segmentedWiiDeadZoneValue;

   UISegmentedControl *segmentedSkin;
   UISwitch           *switchTouchDeadZone;

   UISegmentedControl *segmentedOverscanValue;
   UISwitch           *switchTvoutNative;

   UISegmentedControl *segmentedTouchType;
   UISegmentedControl *segmentedAnalogDeadZoneValue;
   
   UISegmentedControl *segmentediCadeLayout;
    
   UISegmentedControl *segmentedSoundKHZ;
   UISwitch *switchSound;

   UISwitch *switchThrottle;
   UISegmentedControl *segmentedFSkip;
   UISegmentedControl *segmentedFSlevel;
   UISegmentedControl *segmentedSticktype;
   UISegmentedControl *segmentedNumbuttons;
   UISwitch *switchAplusB;
   UISwitch *switchCheats;
   UISwitch *switchSleep;

   UISwitch *switchForcepxa;
   UISegmentedControl *segmentedEmures;

   UISwitch *switchP1aspx;
}

- (void)optionChanged:(id)sender;


@end
