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
 
#import "AnalogStick.h"
#import "Globals.h"

#include "myosd.h"

@implementation AnalogStickView


- (void) updateAnalog
{

    switch(g_pref_analog_DZ_value)
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
        if(g_pref_input_touch_type==TOUCH_INPUT_ANALOG)
		{
           joy_analog_x[0] = rx;
           if(!STICK2WAY)
		      joy_analog_y[0] = ry * -1.0f;
           else
              joy_analog_y[0] = 0;
           //printf("Sending analog %f, %f...\n",joy_analog_x[0],joy_analog_y[0] );
		}

		float v = ang;
		
		if(STICK2WAY)
		{
            if ( v < 180  ){
				myosd_pad_status |= MYOSD_RIGHT;

                myosd_pad_status &= ~MYOSD_UP;
		        myosd_pad_status &= ~MYOSD_DOWN;
		        myosd_pad_status &= ~MYOSD_LEFT;						
			}
			else if ( v >= 180  ){
				myosd_pad_status |= MYOSD_LEFT;

                myosd_pad_status &= ~MYOSD_UP;
		        myosd_pad_status &= ~MYOSD_DOWN;
		        myosd_pad_status &= ~MYOSD_RIGHT;
			}
		}
		else if(STICK4WAY)
		{
			if( v >= 315 || v < 45){
				myosd_pad_status |= MYOSD_DOWN;

                myosd_pad_status &= ~MYOSD_UP;					        
		        myosd_pad_status &= ~MYOSD_LEFT;
		        myosd_pad_status &= ~MYOSD_RIGHT;						
			}
			else if ( v >= 45 && v < 135){
				myosd_pad_status |= MYOSD_RIGHT;

                myosd_pad_status &= ~MYOSD_UP;
		        myosd_pad_status &= ~MYOSD_DOWN;
		        myosd_pad_status &= ~MYOSD_LEFT;						
			}
			else if ( v >= 135 && v < 225){
				myosd_pad_status |= MYOSD_UP;

		        myosd_pad_status &= ~MYOSD_DOWN;
		        myosd_pad_status &= ~MYOSD_LEFT;
		        myosd_pad_status &= ~MYOSD_RIGHT;
			}
			else if ( v >= 225 && v < 315 ){
				myosd_pad_status |= MYOSD_LEFT;

                myosd_pad_status &= ~MYOSD_UP;
		        myosd_pad_status &= ~MYOSD_DOWN;
		        myosd_pad_status &= ~MYOSD_RIGHT;
			}						
		}
        else
        {
			if( v >= 330 || v < 30){
				myosd_pad_status |= MYOSD_DOWN;

                myosd_pad_status &= ~MYOSD_UP;					        
		        myosd_pad_status &= ~MYOSD_LEFT;
		        myosd_pad_status &= ~MYOSD_RIGHT;						
			}
			else if ( v >= 30 && v <60  )  {
				myosd_pad_status |= MYOSD_DOWN;
				myosd_pad_status |= MYOSD_RIGHT;

                myosd_pad_status &= ~MYOSD_UP;
		        myosd_pad_status &= ~MYOSD_LEFT;						
			}
			else if ( v >= 60 && v < 120  ){
				myosd_pad_status |= MYOSD_RIGHT;

                myosd_pad_status &= ~MYOSD_UP;
		        myosd_pad_status &= ~MYOSD_DOWN;
		        myosd_pad_status &= ~MYOSD_LEFT;						
			}
			else if ( v >= 120 && v < 150  ){
				myosd_pad_status |= MYOSD_RIGHT;
				myosd_pad_status |= MYOSD_UP;

		        myosd_pad_status &= ~MYOSD_DOWN;
		        myosd_pad_status &= ~MYOSD_LEFT;
			}
			else if ( v >= 150 && v < 210  ){
				myosd_pad_status |= MYOSD_UP;

		        myosd_pad_status &= ~MYOSD_DOWN;
		        myosd_pad_status &= ~MYOSD_LEFT;
		        myosd_pad_status &= ~MYOSD_RIGHT;
			}
			else if ( v >= 210 && v < 240  ){
				myosd_pad_status |= MYOSD_UP;
				myosd_pad_status |= MYOSD_LEFT;

		        myosd_pad_status &= ~MYOSD_DOWN;
		        myosd_pad_status &= ~MYOSD_RIGHT;						
			}
			else if ( v >= 240 && v < 300  ){
				myosd_pad_status |= MYOSD_LEFT;

                myosd_pad_status &= ~MYOSD_UP;
		        myosd_pad_status &= ~MYOSD_DOWN;
		        myosd_pad_status &= ~MYOSD_RIGHT;
			}
			else if ( v >= 300 && v < 330  ){
				myosd_pad_status |= MYOSD_LEFT;
				myosd_pad_status |= MYOSD_DOWN;
				
                myosd_pad_status &= ~MYOSD_UP;
		        myosd_pad_status &= ~MYOSD_RIGHT;
			}
		}												
	}
	else
	{
	    joy_analog_x[0]=0.0f;
	    joy_analog_y[0]=0.0f;
        //printf("Sending analog %f, %f...\n",joy_analog_x[0],joy_analog_y[0] );
	     
	    myosd_pad_status &= ~MYOSD_UP;
	    myosd_pad_status &= ~MYOSD_DOWN;
	    myosd_pad_status &= ~MYOSD_LEFT;
	    myosd_pad_status &= ~MYOSD_RIGHT;		    	    				    
	}
					
	switch (myosd_pad_status & (MYOSD_UP|MYOSD_DOWN|MYOSD_LEFT|MYOSD_RIGHT))
    {
        case    MYOSD_UP:    currentDirection = StickUp; break;
        case    MYOSD_DOWN:  currentDirection = StickDown; break;
        case    MYOSD_LEFT:  currentDirection = StickLeft; break;
        case    MYOSD_RIGHT: currentDirection = StickRight; break;
            
        case    MYOSD_UP | MYOSD_LEFT:  currentDirection = StickUpLeft; break;
        case    MYOSD_UP | MYOSD_RIGHT: currentDirection = StickUpRight; break;
        case    MYOSD_DOWN | MYOSD_LEFT:  currentDirection = StickDownLeft; break;
        case    MYOSD_DOWN | MYOSD_RIGHT: currentDirection = StickDownRight; break;
            
        default: currentDirection = StickNone;
    }
    					 
}

- (id)initWithFrame:(CGRect)frame withEmuController:(EmulatorController*)emulatorController{
    if ((self = [super initWithFrame:frame])) {
        // Initialization code
		self.backgroundColor = [UIColor clearColor];
        
        emuController = emulatorController;
        
        CGRect rStickArea = emuController.rStickArea;
        
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
        
        if((g_device_is_landscape && g_pref_full_screen_land) || (!g_device_is_landscape && g_pref_full_screen_port) /*|| iOS_skin==1*/)
        {
            name = [NSString stringWithFormat:@"./SKIN_%d/%@",g_pref_skin,@"./stick-outer.png"];
            outerView = [ [ UIImageView alloc ] initWithImage:[emuController loadImage: name]];
            //outerView.frame = CGRectMake(0,0,frame.size.width,frame.size.height);//frame;
            outerView.frame = rImg;//frame;
            
            [outerView setAlpha:((float)g_controller_opacity / 100.0f)];
            
            [self addSubview: outerView];
        }
        
        int stick_radio = emuController.stick_radio;
        
        name = [NSString stringWithFormat:@"./SKIN_%d/%@",g_pref_skin,@"./stick-inner.png"];
        stickWidth =  rImg.size.width * (stick_radio/100.0f);//0.60;
        stickHeight = rImg.size.height * (stick_radio/100.0f);//0.60;
        innerView = [ [ UIImageView alloc ] initWithImage:[emuController loadImage: name]];
        [self calculateStickPosition: ptCenter];
        innerView.frame =  stickPos;
        
        if((g_device_is_landscape && g_pref_full_screen_land) || (!g_device_is_landscape && g_pref_full_screen_port))
            [innerView setAlpha:((float)g_controller_opacity / 100.0f)];
        
        [self addSubview: innerView];
    }
    
    //self.exclusiveTouch = YES;
    self.multipleTouchEnabled = YES;//NO;
	//self.userInteractionEnabled = NO;
    
    return self;    
}

- (void)drawRect:(CGRect)rect 
{
    if(g_enable_debug_view)
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
   
    if(g_pref_input_touch_type==TOUCH_INPUT_ANALOG)
    {
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
    }
    else
    {
        switch (currentDirection){
            case StickNone:{stickPos.origin.x =ptCenter.x - (stickWidth/2);stickPos.origin.y=ptCenter.y - (stickHeight/2);break;}
            case StickUp:{stickPos.origin.x =ptCenter.x - (stickWidth/2);stickPos.origin.y=ptMin.y;break;}
            case StickDown:{stickPos.origin.x =ptCenter.x - (stickWidth/2);stickPos.origin.y=ptMax.y-stickHeight;break;}
            case StickLeft:{stickPos.origin.x =ptMin.x;stickPos.origin.y=ptCenter.y - (stickHeight/2);break;}
            case StickRight:{stickPos.origin.x =ptMax.x-stickWidth;stickPos.origin.y=ptCenter.y - (stickHeight/2);break;}
            case StickUpLeft:{stickPos.origin.x =ptMin.x;stickPos.origin.y=ptMin.y;break;}
            case StickUpRight:{stickPos.origin.x =ptMax.x-stickWidth;stickPos.origin.y=ptMin.y;break;}
            case StickDownLeft:{stickPos.origin.x =ptMin.x;stickPos.origin.y=ptMax.y-stickHeight;break;}
            case StickDownRight:{stickPos.origin.x =ptMax.x-stickWidth;stickPos.origin.y=ptMax.y-stickHeight;break;}
        }
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

- (void)analogTouches:(UITouch *)touch withEvent:(UIEvent *)event
{
    static float oldRx;
    static float oldRy;

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
    
    if((fabs(oldRx - rx) >= 0.03 || fabs(oldRy - ry) >= 0.03) && g_pref_animated_DPad)
    {
        oldRx = rx;
        oldRy = ry;
        
        [self calculateStickPosition: (mag >= deadZone ? ptCur : ptCenter)];
        
        innerView.center = CGPointMake(CGRectGetMidX(stickPos),CGRectGetMidY(stickPos));
        if(g_enable_debug_view)[self setNeedsDisplay];
        [innerView setNeedsDisplay];
    }  
}

- (void)dealloc {

    [outerView release]; 
    [innerView release];
	   
	[super dealloc];
}

@end