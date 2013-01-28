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

@interface Options : NSObject
{
   NSMutableArray*	  optionsArray;

   @public  int keepAspectRatioPort;
   @public  int keepAspectRatioLand;
   @public  int smoothedPort;
   @public  int smoothedLand;
   @public  int safeRenderPath;

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
   @public int SoundSTEREO;
    
   @public int buttonReload;
}

- (void)loadOptions;
- (void)saveOptions;

@property (readwrite,assign) int keepAspectRatioPort;
@property (readwrite,assign) int keepAspectRatioLand;
@property (readwrite,assign) int smoothedPort;
@property (readwrite,assign) int smoothedLand;
@property (readwrite,assign) int safeRenderPath;

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
@property (readwrite,assign) int SoundSTEREO;

@property (readwrite,assign) int buttonReload;


@end


@interface OptionsController : UIViewController  <UITableViewDelegate, UITableViewDataSource>
{

   UISwitch*		  switchKeepAspectPort;
   UISwitch*		  switchKeepAspectLand;
   UISwitch*		  switchSmoothedPort;
   UISwitch*		  switchSmoothedLand;
   UISwitch*		  switchSafeRender;

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
   UISegmentedControl *segmentedSoundSTEREO;
    
//   UIButton           *buttonReload;

}

- (void)optionChanged:(id)sender;


@end
