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

#import "ScreenView.h"
#import "Globals.h"

static ScreenView *sharedInstance = nil;

//static
unsigned short img_buffer [1024 * 768 * 4];//max driver res?

void iphone_UpdateScreen()
{
    
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
        
        
        //rotateTransform = CGAffineTransformMakeRotation(DEGREE_TO_RAD(90));
        rotateTransform = CGAffineTransformIdentity;
        self.affineTransform = rotateTransform;
        
		if((g_pref_smooth_land && g_device_is_landscape) || (g_pref_smooth_port && !g_device_is_landscape))
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
        rotateTransform = CGAffineTransformMakeRotation(DEGREE_TO_RAD(90));
    } else if (orientation == UIDeviceOrientationLandscapeRight) {
        rotateTransform = CGAffineTransformMakeRotation(DEGREE_TO_RAD(270));
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
