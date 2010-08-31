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

#define RADIANS( degrees ) ( degrees * M_PI / 180 )

//unsigned short* screenbuffer = NULL;

static ScreenView *sharedInstance = nil;

static unsigned short img_buffer //[320 * 240 * 4];
                                 [640 * 480 * 4];//max driver res? STANDARD VGA!

extern int safe_render_path;
extern int iOS_video_width;
extern int iOS_video_height;

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

extern crop_border_land;
extern int crop_border_port;
extern crop_state;

extern int isIpad;
extern int __emulation_paused;

extern unsigned char  *gp2x_screen8;
extern unsigned short *gp2x_screen15;


void reset_video(){
   gp2x_screen8 = gp2x_screen15  = img_buffer;
}

void iphone_UpdateScreen()
{
  //return;
  //usleep(100);
  //sched_yield();

  	while(__emulation_paused )
	{
        usleep(100);
    }

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
	   _screenSurface = nil;
	   
	    if(safe_render_path)
	    {
	       	      
	       //screenbuffer = img_buffer;
	       gp2x_screen8 = gp2x_screen15 = img_buffer;
	       	        
	       CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();    
           bitmapContext = CGBitmapContextCreate(
             img_buffer,
             iOS_video_width,//512,//320,
             iOS_video_height,//480,//240,
             /*8*/5, // bitsPerComponent
             2*iOS_video_width,//2*512,///*4*320*/2*320, // bytesPerRow
             colorSpace,
             kCGImageAlphaNoneSkipFirst  | kCGBitmapByteOrder16Little/*kCGImageAlphaNoneSkipLast */);

            CFRelease(colorSpace);
            
        }
        else
        {	   
		    //TODO:
		    CFMutableDictionaryRef dict;
			int w = iOS_video_width;//rEmulatorFrame.size.width;
			int h = iOS_video_height;//rEmulatorFrame.size.height;
			
	    	int pitch = w * 2, allocSize = 2 * w * h;
	    	char *pixelFormat = "565L";
			 
			dict = CFDictionaryCreateMutable(kCFAllocatorDefault, 0,
											 &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
			CFDictionarySetValue(dict, kCoreSurfaceBufferGlobal, kCFBooleanTrue);
			CFDictionarySetValue(dict, kCoreSurfaceBufferMemoryRegion,
								 @"IOSurfaceMemoryRegion");
			CFDictionarySetValue(dict, kCoreSurfaceBufferPitch,
								 CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, &pitch));
			CFDictionarySetValue(dict, kCoreSurfaceBufferWidth,
								 CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, &w));
			CFDictionarySetValue(dict, kCoreSurfaceBufferHeight,
								 CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, &h));
			CFDictionarySetValue(dict, kCoreSurfaceBufferPixelFormat,
								 CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, pixelFormat));
			CFDictionarySetValue(dict, kCoreSurfaceBufferAllocSize,
								 CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, &allocSize));
			
			_screenSurface = CoreSurfaceBufferCreate(dict);
			
			//screenbuffer = CoreSurfaceBufferGetBaseAddress(_screenSurface);	
			gp2x_screen8 = gp2x_screen15  = CoreSurfaceBufferGetBaseAddress(_screenSurface);		 		 		
		 }
		        		
        //rotateTransform = CGAffineTransformMakeRotation(RADIANS(90));
        rotateTransform = CGAffineTransformIdentity;
        self.affineTransform = rotateTransform;
                       		
		if(iphone_smooth_land && iphone_is_landscape || iphone_smooth_port && !iphone_is_landscape)
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
        
    if(safe_render_path)
    {
   
        CGImageRef cgImage = CGBitmapContextCreateImage(bitmapContext);
        
        self.contents = (id)cgImage;
    
        CFRelease(cgImage);
        
    }
    else
    {
	    CoreSurfaceBufferLock(_screenSurface, 3);
	    
	    self.contents = nil;
	    
	    //self.affineTransform = CGAffineTransformIdentity;
	     self.affineTransform = rotateTransform;
	    self.contents = (id)_screenSurface;
	    		
	    CoreSurfaceBufferUnlock(_screenSurface); 
    }   
    
}

- (void)dealloc {
        
                    
    if(bitmapContext!=nil)
    {

       CFRelease(bitmapContext);
       bitmapContext=nil;
    }   
    
    if(_screenSurface!=nil)
    {

      
      //CoreSurfaceBufferLock(_screenSurface, 3);
      CFRelease(_screenSurface);
      //CoreSurfaceBufferUnlock(_screenSurface);
       _screenSurface = nil;
      // self.contents = nil;
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
