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
 
#import "ScreenView.h"
#include "myosd.h"

#define RADIANS( degrees ) ( degrees * M_PI / 180 )

static ScreenView *sharedInstance = nil;

//unsigned short* screenbuffer = NULL;
//static 
unsigned short img_buffer [1024 * 768 * 4];//max driver res? STANDARD VGA!

extern int myosd_video_width;
extern int myosd_video_height;

CGRect rEmulatorFrame;
//CGRect rPortraitViewFrame;
//CGRect rPortraitNoKeepAspectViewFrame;
//CGRect rLandscapeNoKeepAspectViewFrame;
//CGRect rLandscapeViewFrame;
//extern CGRect rLandscapeImageViewFrame;

extern int iphone_is_landscape;
extern int iphone_smooth_land;
extern int iphone_smooth_port;
extern int iphone_keep_aspect_ratio;

//extern crop_border_land;
extern int crop_border_port;
//extern crop_state;

extern int isIpad;
extern int __emulation_paused;


/*
void reset_video(){
   myosd_screen15  = img_buffer;
}
*/
void iphone_UpdateScreen()
{
  //return;
  //usleep(100);
  //sched_yield();
  /*
  	while(__emulation_paused )
	{
        usleep(100);
    }
   */
   
   if(sharedInstance==nil) return;
    
   [sharedInstance performSelectorOnMainThread:@selector(setNeedsDisplay) withObject:nil waitUntilDone:NO];  
}


@implementation ScreenLayer

+ (id) defaultActionForKey:(NSString *)key
{
    return nil;
}

- (id)init {
//printf("Crean layer %ld\n",self);
	if (self = [super init])
	{		    
	   bitmapContext = nil;
	   
	       //screenbuffer = img_buffer;
	       //myosd_screen15 = img_buffer;
	       	        
	       CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();    
           bitmapContext = CGBitmapContextCreate(
             img_buffer,
             myosd_video_width,//512,//320,
             myosd_video_height,//480,//240,
             /*8*/5, // bitsPerComponent
             2*myosd_video_width,//2*512,///*4*320*/2*320, // bytesPerRow
             colorSpace,
             kCGImageAlphaNoneSkipFirst  | kCGBitmapByteOrder16Little/*kCGImageAlphaNoneSkipLast */);

            CFRelease(colorSpace);
             
		        		
        //rotateTransform = CGAffineTransformMakeRotation(RADIANS(90));
        rotateTransform = CGAffineTransformIdentity;
        self.affineTransform = rotateTransform;
                       		
		if((iphone_smooth_land && iphone_is_landscape) || (iphone_smooth_port && !iphone_is_landscape))
		{
		   [self setMagnificationFilter:kCAFilterLinear];
  	       [self setMinificationFilter:kCAFilterLinear];
		}
		else
		{

  	       [self setMagnificationFilter:kCAFilterNearest];
		   [self setMinificationFilter:kCAFilterNearest];
  	    } 
  	    
  	    if (0) {
		    [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
            [[NSNotificationCenter defaultCenter] addObserver:self 
                                                     selector:@selector(orientationChanged:) 
                                                         name:@"UIDeviceOrientationDidChangeNotification" 
                                                       object:nil];
		}
		
	}
	return self;
}
	
- (void) orientationChanged:(NSNotification *)notification
{
    UIDeviceOrientation orientation = [[UIDevice currentDevice] orientation];
    if (orientation == UIDeviceOrientationLandscapeLeft) {
        rotateTransform = CGAffineTransformMakeRotation(RADIANS(90));
    } else if (orientation == UIDeviceOrientationLandscapeRight) {
        rotateTransform = CGAffineTransformMakeRotation(RADIANS(270));
    }
    
}	

- (void)display {
        
        CGImageRef cgImage = CGBitmapContextCreateImage(bitmapContext);
        
        self.contents = (id)cgImage;
    
        CFRelease(cgImage);               
}

- (void)dealloc {
        
                    
    if(bitmapContext!=nil)
    {

       CFRelease(bitmapContext);
       bitmapContext=nil;
    }   
        
    [super dealloc];
}
@end

@implementation ScreenView


+ (Class) layerClass
{
    return [ScreenLayer class];
}


- (id)initWithFrame:(CGRect)frame {
	if ((self = [super initWithFrame:frame])!=nil) {
       
       self.opaque = YES;
       self.clearsContextBeforeDrawing = NO;
       self.multipleTouchEnabled = NO;
	   self.userInteractionEnabled = NO;
              
       sharedInstance = self;				
	}
        	
	return self;
}


- (void)dealloc
{
	//screenbuffer == NULL;
	//[ screenLayer release ];
	
	//sharedInstance = nil;
	
	[ super dealloc ];
}

- (void)drawRect:(CGRect)rect
{
    //printf("Draw rect\n");
    // UIView uses the existence of -drawRect: to determine if should allow its CALayer
    // to be invalidated, which would then lead to the layer creating a backing store and
    // -drawLayer:inContext: being called.
    // By implementing an empty -drawRect: method, we allow UIKit to continue to implement
    // this logic, while doing our real drawing work inside of -drawLayer:inContext:
        
}

@end
