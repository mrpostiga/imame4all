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

#import "Globals.h"

@interface UINavigationController (KeyboardDismiss)

- (BOOL)disablesAutomaticKeyboardDismissal;

@end

@class DebugView;
@class AnalogStickView;
@class iCadeView;

@interface EmulatorController : UIViewController <UIActionSheetDelegate>
{

  UIView			* screenView;
  UIImageView	    * imageBack;
  UIImageView	    * imageOverlay;
  DebugView         * dview;
  @public UIView	* externalView;

  UIImageView	    * dpadView;
  UIImageView	    * buttonViews[NUM_BUTTONS];

  AnalogStickView   * analogStickView;
    
  iCadeView         *iCade;

  UIActionSheet     * menu;
  
  //input rects
  CGRect input[INPUT_LAST_VALUE];
    
  //current rect emulation window
  CGRect rScreenView;
    
  //views frames
  CGRect rFrames[FRAME_RECT_LAST_VALUE];

  //buttons & Dpad images & states
  CGRect rDPad_image;
  NSString *nameImgDPad[NUM_DPAD_ELEMENTS];

  CGRect rButton_image[NUM_BUTTONS];

  NSString *nameImgButton_Press[NUM_BUTTONS];
  NSString *nameImgButton_NotPress[NUM_BUTTONS];
    
  int dpad_state;
  int old_dpad_state;
    
  int btnStates[NUM_BUTTONS];
  int old_btnStates[NUM_BUTTONS];
    
  //analog stick stuff
  int stick_radio;
  CGRect rStickWindow;
  CGRect rStickArea;
    
  //tvout external view
  CGRect RectExternalView;
    
  //input debug stuff
  CGRect debug_rects[100];
  int num_debug_rects;

}

- (int *)getBtnStates;

- (void)getControllerCoords:(int)orientation;

- (void)getConf;
- (void)filldebugRects;

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

- (CGRect *)getDebugRects;

- (UIImage *)loadImage:(NSString *)name;
- (FILE *)loadFile:(const char *)name;

- (void)moveROMS;

@property (readwrite,assign)  UIView *externalView;
@property (readwrite,assign) int dpad_state;
@property (readonly,assign) int num_debug_rects;
@property (readwrite,assign) CGRect rExternalView;
@property (readonly,assign) int stick_radio;
@property (readonly,assign) CGRect rStickArea;

@end
