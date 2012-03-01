/*
 * This file is part of iMAME4all.
 *
 * Copyright (C) 2011 David Valdeita (Seleuco)
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
 
#import "AnalogStick.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "minimal.h"

@implementation AnalogStickView

CGRect rStickArea;

extern float joy_analog_x[4];
extern float joy_analog_y[4];
extern unsigned long gp2x_pad_status;

extern int iphone_is_landscape;
extern int iphone_controller_opacity;
extern int iOS_full_screen_land;
extern int iOS_full_screen_port;
extern int iOS_inGame;
extern int iOS_animated_DPad;
extern int iOS_skin;
extern int iOS_waysStick;
extern int iOS_analogDeadZoneValue;
extern int enable_dview;

int iOS_stick_radio = 60;

#define STICK4WAY (iOS_waysStick == 4 && iOS_inGame)
#define STICK2WAY (iOS_waysStick == 2 && iOS_inGame)

- (void) updateAnalog
{

    switch(iOS_analogDeadZoneValue)
    {
      case 0: deadZone = 0.01f;break;
      case 1: deadZone = 0.05f;break;
      case 2: deadZone = 0.1f;break;
      case 3: deadZone = 0.15f;break;
      case 4: deadZone = 0.2f;break;
      case 5: deadZone = 0.3f;break;
    }

	if(mag >= deadZone)
	{
		joy_analog_x[0] = rx;
		joy_analog_y[0] = ry * -1.0f;

		float v = ang;
		
		if(STICK2WAY)
		{
            if ( v < 180  ){
				gp2x_pad_status |= GP2X_RIGHT;

                gp2x_pad_status &= ~GP2X_UP;
		        gp2x_pad_status &= ~GP2X_DOWN;
		        gp2x_pad_status &= ~GP2X_LEFT;						
			}
			else if ( v >= 180  ){
				gp2x_pad_status |= GP2X_LEFT;

                gp2x_pad_status &= ~GP2X_UP;
		        gp2x_pad_status &= ~GP2X_DOWN;
		        gp2x_pad_status &= ~GP2X_RIGHT;
			}
		}
		else if(STICK4WAY)
		{
			if( v >= 315 || v < 45){
				gp2x_pad_status |= GP2X_DOWN;

                gp2x_pad_status &= ~GP2X_UP;					        
		        gp2x_pad_status &= ~GP2X_LEFT;
		        gp2x_pad_status &= ~GP2X_RIGHT;						
			}
			else if ( v >= 45 && v < 135){
				gp2x_pad_status |= GP2X_RIGHT;

                gp2x_pad_status &= ~GP2X_UP;
		        gp2x_pad_status &= ~GP2X_DOWN;
		        gp2x_pad_status &= ~GP2X_LEFT;						
			}
			else if ( v >= 135 && v < 225){
				gp2x_pad_status |= GP2X_UP;

		        gp2x_pad_status &= ~GP2X_DOWN;
		        gp2x_pad_status &= ~GP2X_LEFT;
		        gp2x_pad_status &= ~GP2X_RIGHT;
			}
			else if ( v >= 225 && v < 315 ){
				gp2x_pad_status |= GP2X_LEFT;

                gp2x_pad_status &= ~GP2X_UP;
		        gp2x_pad_status &= ~GP2X_DOWN;
		        gp2x_pad_status &= ~GP2X_RIGHT;
			}						
		}
        else
        {
			if( v >= 330 || v < 30){
				gp2x_pad_status |= GP2X_DOWN;

                gp2x_pad_status &= ~GP2X_UP;					        
		        gp2x_pad_status &= ~GP2X_LEFT;
		        gp2x_pad_status &= ~GP2X_RIGHT;						
			}
			else if ( v >= 30 && v <60  )  {
				gp2x_pad_status |= GP2X_DOWN;
				gp2x_pad_status |= GP2X_RIGHT;

                gp2x_pad_status &= ~GP2X_UP;
		        gp2x_pad_status &= ~GP2X_LEFT;						
			}
			else if ( v >= 60 && v < 120  ){
				gp2x_pad_status |= GP2X_RIGHT;

                gp2x_pad_status &= ~GP2X_UP;
		        gp2x_pad_status &= ~GP2X_DOWN;
		        gp2x_pad_status &= ~GP2X_LEFT;						
			}
			else if ( v >= 120 && v < 150  ){
				gp2x_pad_status |= GP2X_RIGHT;
				gp2x_pad_status |= GP2X_UP;

		        gp2x_pad_status &= ~GP2X_DOWN;
		        gp2x_pad_status &= ~GP2X_LEFT;
			}
			else if ( v >= 150 && v < 210  ){
				gp2x_pad_status |= GP2X_UP;

		        gp2x_pad_status &= ~GP2X_DOWN;
		        gp2x_pad_status &= ~GP2X_LEFT;
		        gp2x_pad_status &= ~GP2X_RIGHT;
			}
			else if ( v >= 210 && v < 240  ){
				gp2x_pad_status |= GP2X_UP;
				gp2x_pad_status |= GP2X_LEFT;

		        gp2x_pad_status &= ~GP2X_DOWN;
		        gp2x_pad_status &= ~GP2X_RIGHT;						
			}
			else if ( v >= 240 && v < 300  ){
				gp2x_pad_status |= GP2X_LEFT;

                gp2x_pad_status &= ~GP2X_UP;
		        gp2x_pad_status &= ~GP2X_DOWN;
		        gp2x_pad_status &= ~GP2X_RIGHT;
			}
			else if ( v >= 300 && v < 330  ){
				gp2x_pad_status |= GP2X_LEFT;
				gp2x_pad_status |= GP2X_DOWN;
				
                gp2x_pad_status &= ~GP2X_UP;
		        gp2x_pad_status &= ~GP2X_RIGHT;
			}
		}												
	}
	else
	{
	    joy_analog_x[0]=0.0f;
	    joy_analog_y[0]=0.0f;
	     
	    gp2x_pad_status &= ~GP2X_UP;
	    gp2x_pad_status &= ~GP2X_DOWN;
	    gp2x_pad_status &= ~GP2X_LEFT;
	    gp2x_pad_status &= ~GP2X_RIGHT;		    	    				    
	}
					
	switch (gp2x_pad_status & (GP2X_UP|GP2X_DOWN|GP2X_LEFT|GP2X_RIGHT))
    {
        case    GP2X_UP:    currentDirection = StickUp; break;
        case    GP2X_DOWN:  currentDirection = StickDown; break;
        case    GP2X_LEFT:  currentDirection = StickLeft; break;
        case    GP2X_RIGHT: currentDirection = StickRight; break;
            
        case    GP2X_UP | GP2X_LEFT:  currentDirection = StickUpLeft; break;
        case    GP2X_UP | GP2X_RIGHT: currentDirection = StickUpRight; break;
        case    GP2X_DOWN | GP2X_LEFT:  currentDirection = StickDownLeft; break;
        case    GP2X_DOWN | GP2X_RIGHT: currentDirection = StickDownRight; break;
            
        default: currentDirection = StickNone;
    }
    					 
}

- (id)initWithFrame:(CGRect)frame {
    if ((self = [super initWithFrame:frame])) {
        // Initialization code
		self.backgroundColor = [UIColor clearColor];
	  	    
	 ptMin.x = rStickArea.origin.x - frame.origin.x;
	 ptMin.y = rStickArea.origin.y - frame.origin.y;
	 ptMax.x = ptMin.x + rStickArea.size.width;
	 ptMax.y = ptMin.y + rStickArea.size.height;
	 ptCenter.x = (rStickArea.size.width/ 2) + ptMin.x;
	 ptCenter.y = (rStickArea.size.height / 2) + ptMin.y;
	 CGRect rImg = CGRectMake(ptMin.x,ptMin.y,rStickArea.size.width,rStickArea.size.height);
	 
	 //ptMax = CGPointMake(self.bounds.size.width, self.bounds.size.height);
	 //ptCenter = CGPointMake(self.bounds.size.width/2, self.bounds.size.height/2);
         	 
	 NSString *name;
	 
	 if((iphone_is_landscape && iOS_full_screen_land) || (!iphone_is_landscape && iOS_full_screen_port) /*|| iOS_skin==1*/)
	 {   
	     name = [NSString stringWithFormat:@"./SKIN_%d/%@",iOS_skin,@"./stick-outer.png"];
	     outerView = [ [ UIImageView alloc ] initWithImage:[UIImage imageNamed:name]];
	     //outerView.frame = CGRectMake(0,0,frame.size.width,frame.size.height);//frame;
	     outerView.frame = rImg;//frame;
	         
	     [outerView setAlpha:((float)iphone_controller_opacity / 100.0f)];
	      
	     [self addSubview: outerView];   
    }
    name = [NSString stringWithFormat:@"./SKIN_%d/%@",iOS_skin,@"./stick-inner.png"];
    stickWidth =  rImg.size.width * (iOS_stick_radio/100.0f);//0.60;
    stickHeight = rImg.size.height * (iOS_stick_radio/100.0f);//0.60; 
    innerView = [ [ UIImageView alloc ] initWithImage:[UIImage imageNamed:name]];
    [self calculateStickPosition: ptCenter];
    innerView.frame =  stickPos;
 
    if((iphone_is_landscape && iOS_full_screen_land) || (!iphone_is_landscape && iOS_full_screen_port))
         [innerView setAlpha:((float)iphone_controller_opacity / 100.0f)];
           
       [self addSubview: innerView];
    }
    
    //self.exclusiveTouch = YES;
    self.multipleTouchEnabled = NO;
	//self.userInteractionEnabled = NO;
    
    return self;    
}

- (void)drawRect:(CGRect)rect 
{
    if(enable_dview)
    {
	    CGContextRef context = UIGraphicsGetCurrentContext();	 
	    	       
	    CGContextSelectFont(context, "Helvetica", 10, kCGEncodingMacRoman); 
	    
	    CGContextSetTextDrawingMode (context, kCGTextFillStroke);
	    CGContextSetRGBFillColor (context, 0, 5, 0, .5);
	
	    CGRect viewBounds = self.bounds;
	
	    CGContextTranslateCTM(context, 0, viewBounds.size.height);
	
	    CGContextScaleCTM(context, 1, -1);
	    
	    //CGContextSetRGBStrokeColor (context, 0, 1, 1, 1);
	    CGContextSetStrokeColorWithColor(context, [UIColor redColor].CGColor);
	    NSString *msg =   
	    [NSString stringWithFormat:@"%4d,%4d,d:%d %1.2f %1.2f %1.2f %1.2f",(int)ptCur.x,(int)ptCur.y,currentDirection,rx,ry,ang,mag];
	    
		CGContextShowTextAtPoint(context, 10, 10, [msg UTF8String],msg.length );
	}
	
}

- (void)calculateStickPosition:(CGPoint)pt {
   
    if(STICK2WAY)
    {
       stickPos.origin.x =  MIN(ptMax.x-stickWidth,MAX(ptMin.x,pt.x - (stickWidth/2)));
       stickPos.origin.y =  ptCenter.y - (stickHeight/2);
    }
    else if(STICK4WAY)
    {    
       if(currentDirection == StickRight || currentDirection == StickLeft)
       {
          stickPos.origin.x =  MIN(ptMax.x-stickWidth,MAX(ptMin.x,pt.x - (stickWidth/2)));
          stickPos.origin.y =  ptCenter.y - (stickHeight/2);
       }  
       else
       {
          stickPos.origin.x =  ptCenter.x - (stickWidth/2);
          stickPos.origin.y =  MIN(ptMax.y-stickHeight,MAX(ptMin.y,pt.y - (stickHeight/2)));
       }
    }
    else
    {
        stickPos.origin.x =  MIN(ptMax.x-stickWidth,MAX(ptMin.x,pt.x - (stickWidth/2)));
        stickPos.origin.y =  MIN(ptMax.y-stickHeight,MAX(ptMin.y,pt.y - (stickHeight/2)));
    }
    stickPos.size.width = stickWidth;
    stickPos.size.height = stickHeight;

}

- (void)calculateStickState:(CGPoint)pt min:(CGPoint)min max:(CGPoint)max center:(CGPoint)center{

    if(pt.x > max.x)pt.x=max.x;
    if(pt.x < min.x)pt.x=min.x;
    if(pt.y > max.y)pt.y=max.y;
    if(pt.y < min.y)pt.y=min.y;

	if (pt.x == center.x)
		rx = 0;
	else if (pt.x >= center.x)
		rx = ((float)(pt.x - center.x) / (float)(max.x - center.x));
	else
		rx = ((float)(pt.x - min.x) / (float)(center.x - min.x)) - 1.0f;

	if (pt.y == center.y)
		ry = 0;
	else if (pt.y >= center.y)
		ry = ((float)(pt.y - center.y) / (float)(max.y - center.y));
	else
		ry = ((float)(pt.y - min.y) / (float)(center.y - min.y)) - 1.0f;

	/* calculate the joystick angle and magnitude */
	ang = RAD_TO_DEGREE(atanf(ry / rx));
	ang -= 90.0f;
	if (rx < 0.0f)
		ang -= 180.0f;
	ang = absf(ang);
	mag = (float) sqrt((rx * rx) + (ry * ry));
	
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    static float oldRx;
    static float oldRy;
    
    UITouch *touch = [touches anyObject];
    CGPoint pt = [touch locationInView:self];
    
    ptCur = pt;
       
  	if( touch.phase == UITouchPhaseBegan		||
		touch.phase == UITouchPhaseMoved		||
		touch.phase == UITouchPhaseStationary	)
	{		  	    
	    [self calculateStickState:ptCur min:ptMin max:ptMax center:ptCenter];
    }
    else
    {
       ptCur =ptCenter;
       currentDirection = StickNone;
       rx=0;
       ry=0;
       mag=0;
       oldRx = oldRy = -999;
    }
        
    [self updateAnalog];
    
    if((fabs(oldRx - rx) >= 0.03 || fabs(oldRy - ry) >= 0.03) && iOS_animated_DPad)
    {
      oldRx = rx;
      oldRy = ry;
      
      [self calculateStickPosition: (mag >= deadZone ? ptCur : ptCenter)];      
      
      innerView.center = CGPointMake(CGRectGetMidX(stickPos),CGRectGetMidY(stickPos));
      if(enable_dview)[self setNeedsDisplay];
      [innerView setNeedsDisplay];
    }  
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
	[self touchesBegan:touches withEvent:event];
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
	[self touchesBegan:touches withEvent:event];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
	[self touchesBegan:touches withEvent:event];
}

- (void)dealloc {

    if(outerView!=nil)
      [outerView release];
 
    if(innerView!=nil)
      [innerView release];	   	   
	   
	[super dealloc];
}

@end