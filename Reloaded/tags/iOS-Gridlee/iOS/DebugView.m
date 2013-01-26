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

#import "DebugView.h"

@implementation DebugView


- (id)initWithFrame:(CGRect)frame withEmuController:(EmulatorController*)emulatorController{
    if (self = [super initWithFrame:frame]) {
        // Initialization code
		self.backgroundColor = [UIColor clearColor];
		self.multipleTouchEnabled = NO;
	    self.userInteractionEnabled = NO;
	
	    emuController = emulatorController;
    }
    return self;
}


- (void)drawRect:(CGRect)rect {
	//printf("draw dview\n");
	
    
   // printf("Drawing Rect");
    
    //Get the CGContext from this view
	CGContextRef context = UIGraphicsGetCurrentContext();
	 
   	//Set the stroke (pen) color
	CGContextSetStrokeColorWithColor(context, [UIColor redColor].CGColor);
	//Set the width of the pen mark
	CGContextSetLineWidth(context, 2.0);
	
    int i=0;
    int ndrects = [emuController num_debug_rects];
    CGRect *drects = [emuController getDebugRects];
    
	for(i=0; i<ndrects;i++)
	  CGContextStrokeRect(context, drects[i]);
    
	
	//CGContextAddRect(context, drects[1]);
	//Draw it
	CGContextFillPath(context);
	       
    CGContextSelectFont(context, "Helvetica", 16, kCGEncodingMacRoman); 
    CGContextSetTextDrawingMode (context, kCGTextFillStroke);
    CGContextSetRGBFillColor (context, 0, 5, 0, .5);
    CGRect viewBounds = self.bounds;
    CGContextTranslateCTM(context, 0, viewBounds.size.height);
    CGContextScaleCTM(context, 1, -1);
    CGContextSetRGBStrokeColor (context, 0, 1, 1, 1);
 
   if(!g_isIpad)
   {
 //     CGContextShowTextAtPoint(context, 10, 10, "Es un iPhone",12 );
   }
   else
   {
      //CGContextShowTextAtPoint(context, 10, 10, "Es un iPad",10 );
   }
		
}


- (void)dealloc {

    [super dealloc];
}


@end
