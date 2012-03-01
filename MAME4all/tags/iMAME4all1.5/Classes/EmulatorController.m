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

//http://code.google.com/p/metasyntactic/source/browse/trunk/MetasyntacticShared/Classes/ImageUtilities.m?r=4217

#include "minimal.h"
#import "Helper.h"
#import "ScreenView.h"
#import "EmulatorController.h"
#import "HelpController.h"
#import "OptionsController.h"
#import "DonateController.h"
#import <pthread.h>


#define IPHONE_MENU_DISABLED            0
#define IPHONE_MENU_MAIN                1

#define IPHONE_MENU_HELP                5
#define IPHONE_MENU_OPTIONS             6
#define IPHONE_MENU_DONATE              9
#define IPHONE_MENU_DOWNLOAD           11
#define IPHONE_MENU_WIIMOTE            12

#define IPHONE_MENU_QUIT                7
#define IPHONE_MENU_MAIN_LOAD           8

    
#define MyCGRectContainsPoint(rect, point)						\
	(((point.x >= rect.origin.x) &&								\
		(point.y >= rect.origin.y) &&							\
		(point.x <= rect.origin.x + rect.size.width) &&			\
		(point.y <= rect.origin.y + rect.size.height)) ? 1 : 0)  
		
	

extern unsigned long gp2x_pad_status;
extern int num_of_joys;

extern CGRect drects[100];
extern int ndrects;
//extern btUsed;
unsigned long btUsed = 0;

extern CGRect rEmulatorFrame;
static CGRect rPortraitViewFrame;
static CGRect rPortraitViewFrameNotFull;

static CGRect rPortraitImageBackFrame;
static CGRect rPortraitImageOverlayFrame;

static CGRect rLandscapeViewFrame;
static CGRect rLandscapeViewFrameFull;
static CGRect rLandscapeViewFrameNotFull;
static CGRect rLandscapeImageOverlayFrame;
static CGRect rLandscapeImageBackFrame;

static CGRect rLoopImageMask;
static CGRect rShowKeyboard;

extern CGRect rExternal;

int iphone_menu = IPHONE_MENU_DISABLED;

int iphone_controller_opacity = 50;
int iphone_is_landscape = 0;
int iphone_smooth_land = 0;
int iphone_smooth_port = 0;
int iphone_keep_aspect_ratio = 0;

extern int isIpad;
int safe_render_path = 1;
int enable_dview = 0;

int tv_filter_land = 0;
int tv_filter_port = 0;

int scanline_filter_land = 0;
int scanline_filter_port = 0;

int hide_keyboard = 0;

/////
int global_fps = 0;
int global_low_latency_sound = 0;
int iOS_animated_DPad = 0;
int iOS_4buttonsLand = 0;
int iOS_full_screen_land = 1;
extern int iOS_landscape_buttons;
int iOS_hide_LR=0;
int iOS_skin = 1;
int iOS_deadZoneValue = 2;
int iOS_touchDeadZone = 1;
        
        
enum { DPAD_NONE=0,DPAD_UP=1,DPAD_DOWN=2,DPAD_LEFT=3,DPAD_RIGHT=4,DPAD_UP_LEFT=5,DPAD_UP_RIGHT=6,DPAD_DOWN_LEFT=7,DPAD_DOWN_RIGHT=8};    

enum { BTN_B=0,BTN_X=1,BTN_A=2,BTN_Y=3,BTN_SELECT=4,BTN_START=5,BTN_L1=6,BTN_R1=7,BTN_L2=8,BTN_R2=9};

enum { BUTTON_PRESS=0,BUTTON_NO_PRESS=1};

//states
static int dpad_state;
static int old_dpad_state;

static int btnStates[NUM_BUTTONS];
static int old_btnStates[NUM_BUTTONS];

extern pthread_t main_tid;

extern int iphone_main (int argc, char **argv);
extern int iOS_inGame;
extern int iOS_exitGame;
extern int iOS_exitPause;

int actionPending=0;


//SHARED y GLOBALES!
pthread_t	main_tid;
int			__emulation_run = 0;
int        __emulation_paused = 0;

static EmulatorController *sharedInstance = nil;

extern void reset_video(void);	

void iphone_Reset_Views()
{

   if(sharedInstance==nil) return;
    
   //[sharedInstance changeUI];  
   [sharedInstance performSelectorOnMainThread:@selector(changeUI) withObject:nil waitUntilDone:NO];  
}

void* app_Thread_Start(void* args)
{
	__emulation_run = 1;	
    //app_DemuteSound();
	//iphone_main(ourArgsCnt, ourArgs);
	//mimain(ourArgsCnt, ourArgs);
	mimain(0,NULL);
	__emulation_run = 0;//comento de momento
    //app_MuteSound();
	return NULL;
}

@implementation EmulatorController

@synthesize externalView;

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
	// the user clicked one of the OK/Cancel buttons
	if(__emulation_run)
	{
	  if(iphone_menu == IPHONE_MENU_MAIN)
	  {
        if(buttonIndex == 0)
	    {
           iphone_menu = IPHONE_MENU_HELP;
	    }
	    else if(buttonIndex == 1)
	    {
           iphone_menu = IPHONE_MENU_OPTIONS;
	    }
	    /*
	    else if(buttonIndex == 2)    
	    {
           iphone_menu = IPHONE_MENU_DONATE;
	    }
	    */
	    else if(buttonIndex == 2 )    
	    {
           iphone_menu = IPHONE_MENU_WIIMOTE;
	    }	    
	    else	    
	    {
           iphone_menu = IPHONE_MENU_DISABLED;
	    }
	    	    
	  }
	  
	  //myPool = [[NSAutoreleasePool alloc] init];
	     
	  if(iphone_menu == IPHONE_MENU_HELP)
	  {

           HelpController *addController =[HelpController alloc];
                                   
           [self presentModalViewController:addController animated:YES];

           [addController release];
           
	  }
	  
	  if(iphone_menu == IPHONE_MENU_OPTIONS)
	  {
            
           OptionsController *addController =[OptionsController alloc];
                                   
           [self presentModalViewController:addController animated:YES];

           [addController release];
	  }
	  
	  if(iphone_menu == IPHONE_MENU_DONATE)
	  {
    
           DonateController *addController =[DonateController alloc];
                                   
           [self presentModalViewController:addController animated:YES];

           [addController release];
	  }
	  
	  if(iphone_menu == IPHONE_MENU_WIIMOTE)
	  {
    
           [Helper startwiimote:self]; 
                                                
	  }
	  
	}
}

-(void)done:(id)sender {

	
    [self dismissModalViewControllerAnimated:YES];

	Options *op = [[Options alloc] init];
		   
    if(iphone_smooth_port != [op smoothedPort] 
        || iphone_smooth_land != [op smoothedLand] 
        || safe_render_path != [op safeRenderPath]
        || iphone_keep_aspect_ratio != [op keepAspectRatio]
        || tv_filter_land != [op tvFilterLand]
        || tv_filter_port != [op tvFilterPort]
        || scanline_filter_land != [op scanlineFilterLand]
        || scanline_filter_port != [op scanlineFilterPort]      
        || global_fps != [op showFPS]
        || global_low_latency_sound  != [op lowlatencySound]
        || iOS_animated_DPad  != [op animatedButtons]
        || iOS_4buttonsLand  != [op fourButtonsLand]
        || iOS_full_screen_land  != [op fullLand]
        || iOS_skin != ([op skin]+1)
        || iOS_deadZoneValue != [op deadZoneValue]
        || iOS_touchDeadZone != [op touchDeadZone]
        )
    {
        iphone_keep_aspect_ratio = [op keepAspectRatio];
        iphone_smooth_land = [op smoothedLand];
        iphone_smooth_port = [op smoothedPort];
        safe_render_path = [op safeRenderPath];
         
        tv_filter_land = [op tvFilterLand];
        tv_filter_port = [op tvFilterPort];
        
        scanline_filter_land = [op scanlineFilterLand];
        scanline_filter_port = [op scanlineFilterPort];
        
       global_fps = [op showFPS];
       global_low_latency_sound  = [op lowlatencySound];
       iOS_animated_DPad  = [op animatedButtons];
       iOS_4buttonsLand  = [op fourButtonsLand];
       iOS_full_screen_land  = [op fullLand];
       
       iOS_skin = [op skin]+1;
       iOS_deadZoneValue = [op deadZoneValue];
       iOS_touchDeadZone = [op touchDeadZone];
       
       [self changeUI];
       
       /*      
       [screenView removeFromSuperview];
       [screenView release];
       
       if(imageBack!=nil)
       {
          [imageBack removeFromSuperview];
          [imageBack release];
          imageBack = nil;
       }
     
       //si tiene overlay
       if(imageOverlay!=nil)
       {
         [imageOverlay removeFromSuperview];
         [imageOverlay release];
         imageOverlay = nil;
       }
 
       if(iphone_is_landscape)
         [self buildLandscape];       
       else
         [self buildPortrait];
       */    
    }
    
    
    [op release];
    
    iphone_menu = IPHONE_MENU_DISABLED;
    
    //[myPool release];
}

- (void)runMenu
{
    
  if(__emulation_paused)return;
  //btUsed = num_of_joys!=0;
  
  app_MuteSound();
  NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
  __emulation_paused = 1;
  iphone_menu = IPHONE_MENU_MAIN_LOAD;
  while(iphone_menu != IPHONE_MENU_DISABLED)
  {
    if(iphone_menu == IPHONE_MENU_MAIN_LOAD)
    {
      iphone_menu = IPHONE_MENU_MAIN;
      [NSThread detachNewThreadSelector:@selector(runMainMenu) toTarget:self withObject:nil];
	}
	else
	{
      usleep(1000000);
    }
  }

   usleep(100000);
   app_DemuteSound();
   iOS_exitPause = 1;
  __emulation_paused = 0;  
  
  int old = btUsed;
  btUsed = num_of_joys!=0;
  actionPending=0;
  
  if(iphone_is_landscape && btUsed && old!=btUsed)
      [self removeDPadView];
  if(iphone_is_landscape && !btUsed && old!=btUsed) 
      [self buildDPadView];
      
  [pool release];
}

- (void)runMainMenu
{

    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	UIActionSheet *alert;
	 alert = [[UIActionSheet alloc] initWithTitle:
	   @"Choose an option from the menu. Press cancel to go back." delegate:self cancelButtonTitle:nil destructiveButtonTitle:nil 
	   otherButtonTitles:@"Help",@"Options",@"WiiMote",@"Cancel", nil];	   
	/*   
	if(isIpad)
	  //[alert showInView:imageBack];
	  [alert showInView:self.view];
	else
	*/
	  [alert showInView:self.view];
	
	[alert release];
	
	[pool release];
    
}


- (void)startEmulation{
    
    sharedInstance = self;
	     		
    //[self buildPortrait];
    				
    pthread_create(&main_tid, NULL, app_Thread_Start, NULL);
		
	struct sched_param param;
 
    //param.sched_priority = 63;
    param.sched_priority = 46;  
    //param.sched_priority = 100;
     
           
    if(pthread_setschedparam(main_tid, /*SCHED_RR*/ SCHED_OTHER, &param) != 0)    
             fprintf(stderr, "Error setting pthread priority\n");
    	
}

- (void)loadView {

	struct CGRect rect = [[UIScreen mainScreen] bounds];
	rect.origin.x = rect.origin.y = 0.0f;
	UIView *view= [[UIView alloc] initWithFrame:rect];
	self.view = view;
	[view release];
     self.view.backgroundColor = [UIColor blackColor];	
    externalView = nil;    
}

-(void)viewDidLoad{	

   nameImgButton_NotPress[BTN_B] = @"button_NotPress_B.png";
   nameImgButton_NotPress[BTN_X] = @"button_NotPress_X.png";
   nameImgButton_NotPress[BTN_A] = @"button_NotPress_A.png";
   nameImgButton_NotPress[BTN_Y] = @"button_NotPress_Y.png";
   nameImgButton_NotPress[BTN_START] = @"button_NotPress_start.png";
   nameImgButton_NotPress[BTN_SELECT] = @"button_NotPress_select.png";
   nameImgButton_NotPress[BTN_L1] = @"button_NotPress_R_L1.png";
   nameImgButton_NotPress[BTN_R1] = @"button_NotPress_R_R1.png";
   nameImgButton_NotPress[BTN_L2] = @"button_NotPress_R_L2.png";
   nameImgButton_NotPress[BTN_R2] = @"button_NotPress_R_R2.png";
   
   nameImgButton_Press[BTN_B] = @"button_Press_B.png";
   nameImgButton_Press[BTN_X] = @"button_Press_X.png";
   nameImgButton_Press[BTN_A] = @"button_Press_A.png";
   nameImgButton_Press[BTN_Y] = @"button_Press_Y.png";
   nameImgButton_Press[BTN_START] = @"button_Press_start.png";
   nameImgButton_Press[BTN_SELECT] = @"button_Press_select.png";
   nameImgButton_Press[BTN_L1] = @"button_Press_R_L1.png";
   nameImgButton_Press[BTN_R1] = @"button_Press_R_R1.png";
   nameImgButton_Press[BTN_L2] = @"button_Press_R_L2.png";
   nameImgButton_Press[BTN_R2] = @"button_Press_R_R2.png";
         
   nameImgDPad[DPAD_NONE]=@"DPad_NotPressed.png";
   nameImgDPad[DPAD_UP]= @"DPad_U.png";
   nameImgDPad[DPAD_DOWN]= @"DPad_D.png";
   nameImgDPad[DPAD_LEFT]= @"DPad_L.png";
   nameImgDPad[DPAD_RIGHT]= @"DPad_R.png";
   nameImgDPad[DPAD_UP_LEFT]= @"DPad_UL.png";
   nameImgDPad[DPAD_UP_RIGHT]= @"DPad_UR.png";
   nameImgDPad[DPAD_DOWN_LEFT]= @"DPad_DL.png";
   nameImgDPad[DPAD_DOWN_RIGHT]= @"DPad_DR.png";
      
   dpadView=nil;
   
   int i;
   for(i=0; i<NUM_BUTTONS;i++)
      buttonViews[i]!=nil;
      
   screenView=nil;
   imageBack=nil;   			
   dview = nil;
   
   [ self getConf];

	//[self.view addSubview:self.imageBack];
 	
	//[ self getControllerCoords:0 ];
	
	//self.navigationItem.hidesBackButton = YES;
	
	
    self.view.opaque = YES;
	self.view.clearsContextBeforeDrawing = NO; //Performance?
	self.view.userInteractionEnabled = YES;
	
	self.view.multipleTouchEnabled = YES;
	self.view.exclusiveTouch = YES;
	
    //self.view.multipleTouchEnabled = NO; investigar porque se queda
	//self.view.contentMode = UIViewContentModeTopLeft;
	
	//[[self.view layer] setMagnificationFilter:kCAFilterNearest];
	//[[self.view layer] setMinificationFilter:kCAFilterNearest];

	//kito
	[NSThread setThreadPriority:1.0];
	
	iphone_menu = IPHONE_MENU_DISABLED;
		
	//self.view.frame = [[UIScreen mainScreen] bounds];//rMainViewFrame;
		
	Options *op = [[Options alloc] init];
	        
    iphone_keep_aspect_ratio = [op keepAspectRatio];
    iphone_smooth_land = [op smoothedLand];
    iphone_smooth_port = [op smoothedPort];
    safe_render_path = [op safeRenderPath];
                    
    tv_filter_land = [op tvFilterLand];
    tv_filter_port = [op tvFilterPort];
        
    scanline_filter_land = [op scanlineFilterLand];
    scanline_filter_port = [op scanlineFilterPort];
    
    global_fps = [op showFPS];
    global_low_latency_sound  = [op lowlatencySound];
    iOS_animated_DPad  = [op animatedButtons];
    iOS_4buttonsLand  = [op fourButtonsLand];
    iOS_full_screen_land  = [op fullLand];
    
    iOS_skin = [op skin]+1;
    iOS_deadZoneValue = [op deadZoneValue];
    iOS_touchDeadZone = [op touchDeadZone];
        
    [op release];
    
    [self changeUI];
	
}

- (void)drawRect:(CGRect)rect
{
            
}

-(BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
	//return (interfaceOrientation == UIInterfaceOrientationPortrait);
	return YES;
}



-(void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation {
   
    [self changeUI];
    
}

- (void)changeUI{
   NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
   
  int prev_emulation_paused = __emulation_paused;
   
  __emulation_paused = 1;
  
  //reset_video(); 
  
  //if(!safe_render_path)
      usleep(150000);//ensure some frames displayed
        
  [screenView removeFromSuperview];
  [screenView release];

  if(imageBack!=nil)
  {
     [imageBack removeFromSuperview];
     [imageBack release];
     imageBack = nil;
  }
   
  //si tiene overlay
  if(imageOverlay!=nil)
  {
     [imageOverlay removeFromSuperview];
     [imageOverlay release];
     imageOverlay = nil;
  }
  
  if((self.interfaceOrientation ==  UIDeviceOrientationLandscapeLeft) || (self.interfaceOrientation == UIDeviceOrientationLandscapeRight)){
	  [self buildLandscape];	        
	
   } else	if((self.interfaceOrientation == UIDeviceOrientationPortrait) || (self.interfaceOrientation == UIDeviceOrientationPortraitUpsideDown)){	
      [self buildPortrait];
   }
	
	iOS_exitPause = 1;
	
	if(prev_emulation_paused!=1)
	   __emulation_paused = 0;
		
	[pool release];
}

- (void)removeDPadView{
   
   int i;
   
   if(dpadView!=nil)
   {
      [dpadView removeFromSuperview];
      [dpadView release];
      dpadView=nil;
   }
   
   for(i=0; i<NUM_BUTTONS;i++)
   {
      if(buttonViews[i]!=nil)
      {
         [buttonViews[i] removeFromSuperview];
         [buttonViews[i] release];     
         buttonViews[i] = nil; 
      }
   }
}

- (void)buildDPadView {

   int i;
   
   
   [self removeDPadView];
   
   btUsed = num_of_joys!=0; 
   
   if(btUsed && iphone_is_landscape)
     return;
   
   //dpad
   NSString *name = [NSString stringWithFormat:@"./SKIN_%d/%@",iOS_skin,nameImgDPad[DPAD_NONE]];
   dpadView = [ [ UIImageView alloc ] initWithImage:[UIImage imageNamed:name]];
   dpadView.frame = rDPad_image;
   if(iphone_is_landscape && iOS_full_screen_land)
         [dpadView setAlpha:((float)iphone_controller_opacity / 100.0f)];  
   [self.view addSubview: dpadView];
   dpad_state = old_dpad_state = DPAD_NONE;
   
   for(i=0; i<NUM_BUTTONS;i++)
   {

      if(iphone_is_landscape)
      {
          if(i==BTN_Y && iOS_landscape_buttons < 4)continue;
          if(i==BTN_A && iOS_landscape_buttons < 3)continue;
          if(i==BTN_X && iOS_landscape_buttons < 2)continue;      
          
          if(i==BTN_L1 && iOS_hide_LR)continue;
          if(i==BTN_R1 && iOS_hide_LR)continue;
      }
   
      //if((i==BTN_Y || i==BTN_A) && !iOS_4buttonsLand && iphone_is_landscape)
         //continue;
      name = [NSString stringWithFormat:@"./SKIN_%d/%@",iOS_skin,nameImgButton_NotPress[i]];   
      buttonViews[i] = [ [ UIImageView alloc ] initWithImage:[UIImage imageNamed:name]];
      buttonViews[i].frame = rButton_image[i];
      if(iphone_is_landscape && (iOS_full_screen_land || i==BTN_Y || i==BTN_A))      
         [buttonViews[i] setAlpha:((float)iphone_controller_opacity / 100.0f)];   
      [self.view addSubview: buttonViews[i]];
      btnStates[i] = old_btnStates[i] = BUTTON_NO_PRESS; 
   }
       
}

- (void)buildPortraitImageBack {
  /*
   [UIView beginAnimations:@"foo2" context:nil];
   [UIView setAnimationCurve:UIViewAnimationCurveEaseOut];
   [UIView setAnimationDuration:0.50];
   */

   if(isIpad)
     imageBack = [ [ UIImageView alloc ] initWithImage:[UIImage imageNamed:[NSString stringWithFormat:@"./SKIN_%d/back_portrait_iPad.png",iOS_skin]]];
   else
     imageBack = [ [ UIImageView alloc ] initWithImage:[UIImage imageNamed:[NSString stringWithFormat:@"./SKIN_%d/back_portrait_iPhone.png",iOS_skin]]];
   
   imageBack.frame = rPortraitImageBackFrame; // Set the frame in which the UIImage should be drawn in.
   
   imageBack.userInteractionEnabled = NO;
   imageBack.multipleTouchEnabled = NO;
   imageBack.clearsContextBeforeDrawing = NO;
   //[imageBack setOpaque:YES];

   [self.view addSubview: imageBack]; // Draw the image in self.view.
   //[UIView commitAnimations];
   
}

- (void)buildPortraitImageOverlay {
   
   if(safe_render_path || scanline_filter_port || tv_filter_port)
   {
                                                                                                                                                       
       UIGraphicsBeginImageContext(rPortraitImageOverlayFrame.size);  
       
       //[image1 drawInRect: rPortraitImageOverlayFrame];
       
       CGContextRef uiContext = UIGraphicsGetCurrentContext();
             
       CGContextTranslateCTM(uiContext, 0, rPortraitImageOverlayFrame.size.height);
	
       CGContextScaleCTM(uiContext, 1.0, -1.0);

       if(scanline_filter_port)
       {       
            
          UIImage *image2 = [UIImage imageNamed:[NSString stringWithFormat: @"scanline-1.png"]];
                        
          CGImageRef tile = CGImageRetain(image2.CGImage);
                   
          CGContextSetAlpha(uiContext,((float)22 / 100.0f));   
              
          CGContextDrawTiledImage(uiContext, CGRectMake(0, 0, image2.size.width, image2.size.height), tile);
       
          CGImageRelease(tile);       
       }

       if(tv_filter_port)
       {              
          
          UIImage *image3 = [UIImage imageNamed:[NSString stringWithFormat: @"crt-1.png"]];              
          
          CGImageRef tile = CGImageRetain(image3.CGImage);
              
          CGContextSetAlpha(uiContext,((float)19 / 100.0f));     
          
          CGContextDrawTiledImage(uiContext, CGRectMake(0, 0, image3.size.width, image3.size.height), tile);
       
          CGImageRelease(tile);       
       }
     
       if(isIpad && externalView==nil /*|| 1*/)
       {
          UIImage *image1;
          if(isIpad)          
            image1 = [UIImage imageNamed:[NSString stringWithFormat:@"border-iPad.png"]];
          else
            image1 = [UIImage imageNamed:[NSString stringWithFormat:@"border-iPhone.png"]];
         
          CGImageRef img = CGImageRetain(image1.CGImage);
       
          CGContextSetAlpha(uiContext,((float)100 / 100.0f));  
   
          CGContextDrawImage(uiContext,rPortraitImageOverlayFrame , img);
   
          CGImageRelease(img);  
       }
             
       UIImage *finishedImage = UIGraphicsGetImageFromCurrentImageContext();
                                                            
       UIGraphicsEndImageContext();
       
       imageOverlay = [ [ UIImageView alloc ] initWithImage: finishedImage];
         
       imageOverlay.frame = rPortraitImageOverlayFrame;
       
       if(externalView==nil)
       {             		    			
           [self.view addSubview: imageOverlay];
       }  
       else
       {   
           screenView.frame = rExternal;
           [externalView addSubview: imageOverlay];
       } 
                                    
   }  

  //DPAD---   
  [self buildDPadView];   
  /////
   
  /////////////////
  if(enable_dview)
  {
	  if(dview!=nil)
	  {
	    [dview removeFromSuperview];
	    [dview release];
	  }  	 
	
	  dview = [[DView alloc] initWithFrame:self.view.bounds];
	  
	  [self.view addSubview:dview];   
	
	  [self filldrectsController];
	  
	  [dview setNeedsDisplay];
  }
  ////////////////
}

- (void)buildPortrait {

   iphone_is_landscape = 0;
   [ self getControllerCoords:0 ];
     

	   //HACK
	   if(safe_render_path &&  rPortraitViewFrame.size.width==319)//HACK
	   {
	       rPortraitViewFrame = CGRectMake(0,0,320,240);
	   }
	   /*
	   else
	   {
	       rPortraitViewFrame = CGRectMake(0,0,319,240);
	   }*/  
   
   [self buildPortraitImageBack];
   
   if(!iphone_keep_aspect_ratio && isIpad)
		screenView = [ [ScreenView alloc] initWithFrame: rPortraitViewFrameNotFull];	  
   else
        screenView = [ [ScreenView alloc] initWithFrame: rPortraitViewFrame];
               
   if(externalView==nil)
   {             		    			
      [self.view addSubview: screenView];
   }  
   else
   {   
      screenView.frame = rExternal;
      [externalView addSubview: screenView];
   }  
   
   [self buildPortraitImageOverlay];
     
}

- (void)buildLandscapeImageBack {
  /*
   [UIView beginAnimations:@"foo2" context:nil];
   [UIView setAnimationCurve:UIViewAnimationCurveEaseOut];
   [UIView setAnimationDuration:0.50];
   */

   if(!iOS_full_screen_land)
   {
	   if(isIpad)
	     imageBack = [ [ UIImageView alloc ] initWithImage:[UIImage imageNamed:[NSString stringWithFormat:@"./SKIN_%d/back_landscape_iPad.png",iOS_skin]]];
	   else
	     imageBack = [ [ UIImageView alloc ] initWithImage:[UIImage imageNamed:[NSString stringWithFormat:@"./SKIN_%d/back_landscape_iPhone.png",iOS_skin]]];
	   
	   imageBack.frame = rLandscapeImageBackFrame; // Set the frame in which the UIImage should be drawn in.
	   
	   imageBack.userInteractionEnabled = NO;
	   imageBack.multipleTouchEnabled = NO;
	   imageBack.clearsContextBeforeDrawing = NO;
	   //[imageBack setOpaque:YES];
	
	   [self.view addSubview: imageBack]; // Draw the image in self.view.
   }
   //[UIView commitAnimations];
   
}

- (void)buildLandscapeImageOverlay{
/*
   [UIView beginAnimations:@"foo2" context:nil];
   [UIView setAnimationCurve:UIViewAnimationCurveEaseOut];
   [UIView setAnimationDuration:0.50];
*/
    
   if(scanline_filter_land || tv_filter_land)
   {                                                                                                                                              
	   CGRect r;
   
       if(!iphone_keep_aspect_ratio && !isIpad && iOS_full_screen_land)
		  r = rLandscapeViewFrameFull;	  
       else if(iOS_full_screen_land)
          r = rLandscapeViewFrame;
       else
          r = rLandscapeImageOverlayFrame;
	
	   UIGraphicsBeginImageContext(r.size);
	
	   CGContextRef uiContext = UIGraphicsGetCurrentContext();  
	   
	   CGContextTranslateCTM(uiContext, 0, r.size.height);
		
	   CGContextScaleCTM(uiContext, 1.0, -1.0);
	   
	   if(scanline_filter_land)
	   {       	       
	      UIImage *image2;
	      
	      if(isIpad)
	        image2 =  [UIImage imageNamed:[NSString stringWithFormat: @"scanline-2.png"]];
	      else
	        image2 =  [UIImage imageNamed:[NSString stringWithFormat: @"scanline-1.png"]];
	                        
	      CGImageRef tile = CGImageRetain(image2.CGImage);
	      
	      if(isIpad)             
	         CGContextSetAlpha(uiContext,((float)10 / 100.0f));
	      else
	         CGContextSetAlpha(uiContext,((float)22 / 100.0f));
	              
	      CGContextDrawTiledImage(uiContext, CGRectMake(0, 0, image2.size.width, image2.size.height), tile);
	       
	      CGImageRelease(tile);       
	    }
	
	    if(tv_filter_land)
	    {              
	       UIImage *image3 = [UIImage imageNamed:[NSString stringWithFormat: @"crt-1.png"]];              
	          
	       CGImageRef tile = CGImageRetain(image3.CGImage);
	              
	       CGContextSetAlpha(uiContext,((float)20 / 100.0f));     
	          
	       CGContextDrawTiledImage(uiContext, CGRectMake(0, 0, image3.size.width, image3.size.height), tile);
	       
	       CGImageRelease(tile);       
	    }

	       
	    UIImage *finishedImage = UIGraphicsGetImageFromCurrentImageContext();
	                  
	    UIGraphicsEndImageContext();
	    
	    imageOverlay = [ [ UIImageView alloc ] initWithImage: finishedImage];
	    
	    imageOverlay.frame = r; // Set the frame in which the UIImage should be drawn in.
      
        imageOverlay.userInteractionEnabled = NO;
        imageOverlay.multipleTouchEnabled = NO;
        imageOverlay.clearsContextBeforeDrawing = NO;
   
        //[imageBack setOpaque:YES];
         
         if(externalView==nil)
		 {             		    			
		      [self.view addSubview: imageOverlay];
		 }  
		 else
		 {   
		      screenView.frame = rExternal;
		      [externalView addSubview: imageOverlay];
		 }  
         //[UIView commitAnimations];	    
    }
   
    //DPAD---   
    [self buildDPadView];   
    /////
  
   //////////////////
   if(enable_dview)
   {
	  if(dview!=nil)
	  {
        [dview removeFromSuperview];
        [dview release];
      }	 	  
	  
	  dview = [[DView alloc] initWithFrame:self.view.bounds];
		 	  
	  [self filldrectsController];
	  
	  [self.view addSubview:dview];   
	  [dview setNeedsDisplay];
	  
	 
  }
  /////////////////	
}

- (void)buildLandscape{
	
   iphone_is_landscape = 1;
   
   [self getControllerCoords:1 ];

   [self buildLandscapeImageBack];
         
   if(!iphone_keep_aspect_ratio && !isIpad && iOS_full_screen_land) 
		screenView = [ [ScreenView alloc] initWithFrame: rLandscapeViewFrameFull];	 
   else if(iOS_full_screen_land)
        screenView = [ [ScreenView alloc] initWithFrame: rLandscapeViewFrame];
   else
        screenView = [ [ScreenView alloc] initWithFrame: rLandscapeViewFrameNotFull];
        
   if(externalView==nil)
   {             		    			
      [self.view addSubview: screenView];
   }  
   else
   {               
      screenView.frame = rExternal;
      [externalView addSubview: screenView];
   }   
      
   [self buildLandscapeImageOverlay];
	
}

////////////////

- (void)handle_DPAD{

    if(!iOS_animated_DPad)return;

    if(dpad_state!=old_dpad_state)
    {
        
       //printf("cambia depad %d %d\n",old_dpad_state,dpad_state);
       NSString *imgName; 
       imgName = nameImgDPad[dpad_state];
       if(imgName!=nil)
       {  
         NSString *name = [NSString stringWithFormat:@"./SKIN_%d/%@",iOS_skin,imgName];   
         //printf("%s\n",[name UTF8String]);
         UIImage *img = [UIImage imageNamed:name]; 
         [dpadView setImage:img];
         [dpadView setNeedsDisplay];
       }           
       old_dpad_state = dpad_state;
    }
    
    int i = 0;
    for(i=0; i< NUM_BUTTONS;i++)
    {
        if(btnStates[i] != old_btnStates[i])
        {
           NSString *imgName;
           if(btnStates[i] == BUTTON_PRESS)
           {
               imgName = nameImgButton_Press[i];
           }
           else
           {
               imgName = nameImgButton_NotPress[i];
           } 
           if(imgName!=nil)
           {  
              NSString *name = [NSString stringWithFormat:@"./SKIN_%d/%@",iOS_skin,imgName];
              UIImage *img = [UIImage imageNamed:name]; 
              [buttonViews[i] setImage:img];
              [buttonViews[i] setNeedsDisplay];              
           }
           old_btnStates[i] = btnStates[i]; 
        }
    }
    
}


////////////////

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{	       
    if(btUsed && iphone_is_landscape)
    {
        NSSet *allTouches = [event allTouches];
        UITouch *touch = [[allTouches allObjects] objectAtIndex:0];
        
        if(touch.phase == UITouchPhaseBegan || touch.phase == UITouchPhaseStationary)
		{
			if(__emulation_run)
		    {
                [NSThread detachNewThreadSelector:@selector(runMenu) toTarget:self withObject:nil];
			}					
	    }
    }
    else
      [self touchesController:touches withEvent:event];
}


  
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
  iOS_exitPause = 1;
  __emulation_paused = 0;
  if(buttonIndex == 0 )
  {
     iOS_exitGame = 1;
  }
  actionPending=0;
}

- (void)touchesController:(NSSet *)touches withEvent:(UIEvent *)event {	
	int i;
	//Get all the touches.
	NSSet *allTouches = [event allTouches];
	int touchcount = [allTouches count];
	
	gp2x_pad_status = 0;
	
	dpad_state = DPAD_NONE;
	
	for(i=0; i<NUM_BUTTONS;i++)
    {
       btnStates[i] = BUTTON_NO_PRESS; 
    }
						
	for (i = 0; i < touchcount; i++) 
	{
		UITouch *touch = [[allTouches allObjects] objectAtIndex:i];
		
		if(touch == nil)
		{
			return;
		}
		
		/*if(touch.phase == UITouchPhaseBegan)
		{
			NSLog([NSString stringWithFormat:@"%s", test_print_buffer]);
		}*/
		if( touch.phase == UITouchPhaseBegan		||
			touch.phase == UITouchPhaseMoved		||
			touch.phase == UITouchPhaseStationary	)
		{
			struct CGPoint point;
			point = [touch locationInView:self.view];
			
			if (MyCGRectContainsPoint(ButtonUp, point)) {
				gp2x_pad_status |= GP2X_Y;
				btnStates[BTN_Y] = BUTTON_PRESS; 
				//NSLog(@"GP2X_Y");
			}
			else if (MyCGRectContainsPoint(ButtonDown, point)) {
				gp2x_pad_status |= GP2X_X;
				btnStates[BTN_X] = BUTTON_PRESS;
				//NSLog(@"GP2X_X");
			}
			else if (MyCGRectContainsPoint(ButtonLeft, point)) {
				gp2x_pad_status |= GP2X_A;
				btnStates[BTN_A] = BUTTON_PRESS;
				//NSLog(@"GP2X_A");
			}
			else if (MyCGRectContainsPoint(ButtonRight, point)) {
				gp2x_pad_status |= GP2X_B;
				btnStates[BTN_B] = BUTTON_PRESS;
				//NSLog(@"GP2X_B");
			}
			else if (MyCGRectContainsPoint(ButtonUpLeft, point)) {
				gp2x_pad_status |= GP2X_Y | GP2X_A;
				btnStates[BTN_Y] = BUTTON_PRESS;
				btnStates[BTN_A] = BUTTON_PRESS;
				//NSLog(@"GP2X_Y | GP2X_A");
			}
			else if (MyCGRectContainsPoint(ButtonDownLeft, point)) {

				gp2x_pad_status |= GP2X_X | GP2X_A;
                btnStates[BTN_A] = BUTTON_PRESS;
                btnStates[BTN_X] = BUTTON_PRESS;							
				//NSLog(@"GP2X_X | GP2X_A");
			}
			else if (MyCGRectContainsPoint(ButtonUpRight, point)) {
				gp2x_pad_status |= GP2X_Y | GP2X_B;
                btnStates[BTN_B] = BUTTON_PRESS;
                btnStates[BTN_Y] = BUTTON_PRESS;				
				//NSLog(@"GP2X_Y | GP2X_B");
			}			
			else if (MyCGRectContainsPoint(ButtonDownRight, point)) {
				gp2x_pad_status |= GP2X_X | GP2X_B;
                btnStates[BTN_B] = BUTTON_PRESS;
                btnStates[BTN_X] = BUTTON_PRESS;
				//NSLog(@"GP2X_X | GP2X_B");
			} 
			else if (MyCGRectContainsPoint(Select, point)) {
			    //NSLog(@"GP2X_SELECT");
				gp2x_pad_status |= GP2X_SELECT;				
                btnStates[BTN_SELECT] = BUTTON_PRESS;
			}
			else if (MyCGRectContainsPoint(Start, point)) {
				//NSLog(@"GP2X_START");
				gp2x_pad_status |= GP2X_START;
			    btnStates[BTN_START] = BUTTON_PRESS;
			}						
			else if (MyCGRectContainsPoint(Up, point)) {
				//NSLog(@"GP2X_UP");
				gp2x_pad_status |= GP2X_UP;
				dpad_state = DPAD_UP;
			}			
			else if (MyCGRectContainsPoint(Down, point)) {
				//NSLog(@"GP2X_DOWN");
				gp2x_pad_status |= GP2X_DOWN;
				dpad_state = DPAD_DOWN;
			}			
			else if (MyCGRectContainsPoint(Left, point)) {
				//NSLog(@"GP2X_LEFT");
				gp2x_pad_status |= GP2X_LEFT;
				dpad_state = DPAD_LEFT;
			}			
			else if (MyCGRectContainsPoint(Right, point)) {
				//NSLog(@"GP2X_RIGHT");
				gp2x_pad_status |= GP2X_RIGHT;
				dpad_state = DPAD_RIGHT;
			}			
			else if (MyCGRectContainsPoint(UpLeft, point)) {
				//NSLog(@"GP2X_UP | GP2X_LEFT");
				gp2x_pad_status |= GP2X_UP | GP2X_LEFT;
				dpad_state = DPAD_UP_LEFT;
			}			
			else if (MyCGRectContainsPoint(UpRight, point)) {
				//NSLog(@"GP2X_UP | GP2X_RIGHT");
				gp2x_pad_status |= GP2X_UP | GP2X_RIGHT;
				dpad_state = DPAD_UP_RIGHT;
			}			
			else if (MyCGRectContainsPoint(DownLeft, point)) {
				//NSLog(@"GP2X_DOWN | GP2X_LEFT");
				gp2x_pad_status |= GP2X_DOWN | GP2X_LEFT;
				dpad_state = DPAD_DOWN_LEFT;
			}			
			else if (MyCGRectContainsPoint(DownRight, point)) {
				//NSLog(@"GP2X_DOWN | GP2X_RIGHT");
				gp2x_pad_status |= GP2X_DOWN | GP2X_RIGHT;
				dpad_state = DPAD_DOWN_RIGHT;
			}
			else if (MyCGRectContainsPoint(LPad, point)) {
				//NSLog(@"GP2X_L");
				gp2x_pad_status |= GP2X_L;
			    btnStates[BTN_L1] = BUTTON_PRESS;
			}
			else if (MyCGRectContainsPoint(RPad, point)) {
				//NSLog(@"GP2X_R");
				gp2x_pad_status |= GP2X_R;
				btnStates[BTN_R1] = BUTTON_PRESS;
			}			
			else if (MyCGRectContainsPoint(LPad2, point)) {
				//NSLog(@"GP2X_VOL_DOWN");
				//gp2x_pad_status |= GP2X_VOL_DOWN;
				btnStates[BTN_L2] = BUTTON_PRESS;
				
				if(iOS_inGame && !actionPending)
				{				  				
		            
		            actionPending=1;
		            iOS_exitGame = 0;	
		            usleep(100000);	            
		            __emulation_paused = 1;
		            UIAlertView* downloadAlertView=[[UIAlertView alloc] initWithTitle:nil
	                     message:@"are you sure you want to exit the game?"
					     delegate:self cancelButtonTitle:nil
	                     otherButtonTitles:@"Yes",@"No",nil];
		            [downloadAlertView show];
		            [downloadAlertView release];
	            } 
							
			}
			else if (MyCGRectContainsPoint(RPad2, point)) {
				//NSLog(@"GP2X_VOL_UP");
				//gp2x_pad_status |= GP2X_VOL_UP;
				btnStates[BTN_R2] = BUTTON_PRESS;
				
				//if(touch.phase == UITouchPhaseBegan || touch.phase == UITouchPhaseStationary)
				//{
					if(__emulation_run && !actionPending)
					{
                        actionPending=1;
                        [NSThread detachNewThreadSelector:@selector(runMenu) toTarget:self withObject:nil];
					}					
				//}
				
			}			
			else if (MyCGRectContainsPoint(Menu, point)) {
				gp2x_pad_status |= GP2X_SELECT;				
                btnStates[BTN_SELECT] = BUTTON_PRESS;
				gp2x_pad_status |= GP2X_START;
			    btnStates[BTN_START] = BUTTON_PRESS;
			}
			else if (MyCGRectContainsPoint(rShowKeyboard, point)) {
  
			}	
			
		}
	}
	
	[self handle_DPAD];
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


- (void)getControllerCoords:(int)orientation {
    char string[256];
    FILE *fp;
	
	if(!orientation)
	{
		if(isIpad)
		  fp = fopen([[NSString stringWithFormat:@"%s/SKIN_%d/controller_portrait_iPad.txt",  get_resource_path("/"), iOS_skin] UTF8String], "r");
		else
		  fp = fopen([[NSString stringWithFormat:@"%s/SKIN_%d/controller_portrait_iPhone.txt", get_resource_path("/"),  iOS_skin] UTF8String], "r");
    }
	else
	{
		if(isIpad)
		   fp = fopen([[NSString stringWithFormat:@"%s/SKIN_%d/controller_landscape_iPad.txt", get_resource_path("/"), iOS_skin ] UTF8String], "r");
		else
		   fp = fopen([[NSString stringWithFormat:@"%s/SKIN_%d/controller_landscape_iPhone.txt", get_resource_path("/"), iOS_skin] UTF8String], "r");
	}
	
	if (fp) 
	{

		int i = 0;
        while(fgets(string, 256, fp) != NULL && i < 36) 
       {
			char* result = strtok(string, ",");
			int coords[4];
			int i2 = 1;
			while( result != NULL && i2 < 5 )
			{
				coords[i2 - 1] = atoi(result);
				result = strtok(NULL, ",");
				i2++;
			}
			
			/*
			if(isIpad && orientation==1)
			{
			     coords[1] =  coords[1] - 100;
			}*/
			
			switch(i)
			{
    		case 0:    DownLeft   	= CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
    		case 1:    Down   	= CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
    		case 2:    DownRight    = CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
    		case 3:    Left  	= CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
    		case 4:    Right  	= CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
    		case 5:    UpLeft     	= CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
    		case 6:    Up     	= CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
    		case 7:    UpRight  	= CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
    		case 8:    Select = CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
    		case 9:    Start  = CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
    		case 10:   LPad   = CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
    		case 11:   RPad   = CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
    		case 12:   Menu   = CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
    		case 13:   ButtonDownLeft   	= CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
    		case 14:   ButtonDown   	= CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
    		case 15:   ButtonDownRight    	= CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
    		case 16:   ButtonLeft  		= CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
    		case 17:   ButtonRight  	= CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
    		case 18:   ButtonUpLeft     	= CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
    		case 19:   ButtonUp     	= CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
    		case 20:   ButtonUpRight  	= CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
    		case 21:   LPad2   = CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
    		case 22:   RPad2   = CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
    		case 23:   rShowKeyboard  = CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
    		
    		case 24:   rButton_image[BTN_B] = CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
            case 25:   rButton_image[BTN_X]  = CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
            case 26:   rButton_image[BTN_A]  = CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
            case 27:   rButton_image[BTN_Y]  = CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
            case 28:   rDPad_image  = CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
            case 29:   rButton_image[BTN_SELECT]  = CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
            case 30:   rButton_image[BTN_START]  = CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
            case 31:   rButton_image[BTN_L1] = CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
            case 32:   rButton_image[BTN_R1] = CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
            case 33:   rButton_image[BTN_L2] = CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
            case 34:   rButton_image[BTN_R2] = CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
            case 35:   iphone_controller_opacity= coords[0]; break;
			}
      i++;
    }
    fclose(fp);
    
    if(iOS_touchDeadZone)
    {
        //ajustamos
        if(!isIpad)
        {
           if(!orientation)
           {
             Left.size.width -= 17;//Left.size.width * 0.2;
             Right.origin.x += 17;//Right.size.width * 0.2;
             Right.size.width -= 17;//Right.size.width * 0.2;
           }
           else
           {
             Left.size.width -= 14;
             Right.origin.x += 20;
             Right.size.width -= 20;
           }
        }
        else
        {
           if(!orientation)
           {
             Left.size.width -= 22;//Left.size.width * 0.2;
             Right.origin.x += 22;//Right.size.width * 0.2;
             Right.size.width -= 22;//Right.size.width * 0.2;
           }
           else
           {
             Left.size.width -= 22;
             Right.origin.x += 22;
             Right.size.width -= 22;
           }
        }    
    }
  }
}


- (void)getConf{
    char string[256];
    FILE *fp;
	
	if(isIpad)
	   fp = fopen([[NSString stringWithFormat:@"%sconfig_iPad.txt", get_resource_path("/")] UTF8String], "r");
	else
	   fp = fopen([[NSString stringWithFormat:@"%sconfig_iPhone.txt", get_resource_path("/")] UTF8String], "r");
	   	
	if (fp) 
	{

		int i = 0;
        while(fgets(string, 256, fp) != NULL && i < 12) 
       {
			char* result = strtok(string, ",");
			int coords[4];
			int i2 = 1;
			while( result != NULL && i2 < 5 )
			{
				coords[i2 - 1] = atoi(result);
				result = strtok(NULL, ",");
				i2++;
			}
			
			
			switch(i)
			{
    		case 0:    rEmulatorFrame   	= CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
    		case 1:    rPortraitViewFrame     	= CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
    		case 2:    rPortraitViewFrameNotFull = CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;    		
    		case 3:    rPortraitImageBackFrame     	= CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
    		case 4:    rPortraitImageOverlayFrame     	= CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;    		    		
    		case 5:    rLandscapeViewFrame = CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;
    		case 6:    rLandscapeViewFrameFull = CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;      		    		    		
    		case 7:    rLandscapeViewFrameNotFull = CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;    		
    		case 8:    rLandscapeImageBackFrame  	= CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;  
    		case 9:    rLandscapeImageOverlayFrame     	= CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;      		  		
            case 10:    rLoopImageMask = CGRectMake( coords[0], coords[1], coords[2], coords[3] ); break;    	
            case 11:   enable_dview = coords[0]; break;
			}
      i++;
    }
    fclose(fp);
  }
}

- (void)didReceiveMemoryWarning {
	//[super didReceiveMemoryWarning]; // Releases the view if it doesn't have a superview
	// Release anything that's not essential, such as cached data
}


- (void)dealloc {

    [self removeDPadView];

    if(screenView!=nil)
      [screenView release];
       
    if(imageBack!=nil)
      [imageBack release];
      
    if(imageOverlay!=nil)
      [imageOverlay release];
 
    if(dview!=nil)
	   [dview release];	   

	[super dealloc];
}

- (void)filldrectsController {

    		drects[0]=DownLeft;
    		drects[1]=Down;
    		drects[2]=DownRight;
    		drects[3]=Left;
    		drects[4]=Right;
    		drects[5]=UpLeft;
    		drects[6]=Up;
    		drects[7]=UpRight;
    		drects[8]=Select;
    		drects[9]=Start;
    		drects[10]=LPad;
    		drects[11]=RPad;
    		drects[12]=Menu;
    		drects[13]=ButtonDownLeft;
    		drects[14]=ButtonDown;
    		drects[15]=ButtonDownRight;
    		drects[16]=ButtonLeft;
    		drects[17]=ButtonRight;
    		drects[18]=ButtonUpLeft;
    		drects[19]=ButtonUp;
    		drects[20]=ButtonUpRight;
    		drects[21]=LPad2;
    		drects[22]=RPad2;
    		drects[23]=rShowKeyboard;
            ndrects = 24;        
}

@end
