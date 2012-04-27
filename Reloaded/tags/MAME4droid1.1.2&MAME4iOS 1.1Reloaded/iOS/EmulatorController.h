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

#import <Foundation/Foundation.h>
#import <QuartzCore/CALayer.h>
#import "DView.h"
#import "AnalogStick.h"

#import <pthread.h>
#import <sched.h>
#import <unistd.h>
#import <sys/time.h>

#define NUM_BUTTONS 10

#ifdef IOS3
@protocol UIKeyInput <UITextInputTraits>

- (BOOL)hasText;
- (void)insertText:(NSString *)text;
- (void)deleteBackward;

@end
#endif

@interface EmulatorController : UIViewController <UIActionSheetDelegate, UIKeyInput>
{

  UIView			* screenView;
  UIImageView	    * imageBack;
  UIImageView	    * imageOverlay;
  DView             * dview;
  //NSTimer           * touchTimer;
  @public UIView	*externalView;

  UIImageView	    * dpadView;
  UIImageView	    * buttonViews[NUM_BUTTONS];

  AnalogStickView   * analogStickView;

  UIActionSheet     * menu;


  //joy controller
  CGRect ButtonUp;
  CGRect ButtonLeft;
  CGRect ButtonDown;
  CGRect ButtonRight;
  CGRect ButtonUpLeft;
  CGRect ButtonDownLeft;
  CGRect ButtonUpRight;
  CGRect ButtonDownRight;
  CGRect Up;
  CGRect Left;
  CGRect Down;
  CGRect Right;
  CGRect UpLeft;
  CGRect DownLeft;
  CGRect UpRight;
  CGRect DownRight;
  CGRect Select;
  CGRect Start;
  CGRect LPad;
  CGRect RPad;
  CGRect LPad2;
  CGRect RPad2;
  CGRect Menu;

  //buttons & Dpad images
  CGRect rDPad_image;
  NSString *nameImgDPad[9];

  CGRect rButton_image[NUM_BUTTONS];

  NSString *nameImgButton_Press[NUM_BUTTONS];
  NSString *nameImgButton_NotPress[NUM_BUTTONS];

  //NSTimer						*	timer;
}



- (void)getControllerCoords:(int)orientation;

- (void)getConf;
- (void)filldrectsController;

- (void)startEmulation;

- (void)removeDPadView;
- (void)buildDPadView;

- (void)changeUI;

- (void)buildPortraitImageBack;
- (void)buildPortraitImageOverlay;
- (void)buildPortrait;
- (void)buildLandscapeImageOverlay;
- (void)buildLandscapeImageBack;
- (void)buildLandscape;

- (void)runMenu;
- (void)endMenu;

- (void)handle_DPAD;
- (void)handle_MENU;

- (void)touchesController:(NSSet *)touches withEvent:(UIEvent *)event;

- (void)updateOptions;

@property (readwrite,assign)   UIView	 *externalView;

@end
