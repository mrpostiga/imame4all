//============================================================
//
//  Copyright (c) 1996-2009, Nicola Salmoria and the MAME Team.
//  Visit http://mamedev.org for licensing and usage restrictions.
//
//  MAME4DROID MAME4iOS by David Valdeita (Seleuco)
//
//============================================================

#ifdef ANDROID
#include <android/log.h>
#endif

#include "osdcore.h"
//#include <malloc.h>
#include <unistd.h>
#include "render.h"
#include "emu.h"
#include "osdvideo.h"

#include <pthread.h>
#include "myosd.h"

static int screen_width;
static int screen_height;
static int vis_area_screen_width;
static int vis_area_screen_height;

static int curr_screen_width;
static int curr_screen_height;
static int curr_vis_area_screen_width;
static int curr_vis_area_screen_height;

static int hofs;
static int vofs;

static const render_primitive_list *currlist = NULL;
static int thread_stopping = 0;

static pthread_mutex_t cond_mutex     = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  condition_var   = PTHREAD_COND_INITIALIZER;
#ifdef ANDROID
static void draw_rgb565_draw_primitives(const render_primitive *primlist, void *dstdata, UINT32 width, UINT32 height, UINT32 pitch);
static void draw_bgr888_draw_primitives(const render_primitive *primlist, void *dstdata, UINT32 width, UINT32 height, UINT32 pitch);
#else
static void draw_rgb555_draw_primitives(const render_primitive *primlist, void *dstdata, UINT32 width, UINT32 height, UINT32 pitch);
#endif

static void droid_ios_video_draw(void);
extern "C"
void droid_ios_video_thread(void);

void droid_ios_setup_video()
{

}

//static void droid_video_cleanup(running_machine *machine)
static void droid_ios_video_cleanup(running_machine &machine)
{
   	usleep(150000);
}

void droid_ios_init_video(running_machine *machine)
{
	curr_screen_width = 1;
	curr_screen_height = 1;
	curr_vis_area_screen_width = 1;
	curr_vis_area_screen_height = 1;

	screen_width = 1;
	screen_height = 1;
	vis_area_screen_width = 1;
	vis_area_screen_height = 1;

	//add_exit_callback(machine, droid_video_cleanup);
	machine->add_notifier(MACHINE_NOTIFY_EXIT, droid_ios_video_cleanup);
}


static osd_ticks_t target = -1;

static void my_sync()
{
   while(target!=-1)
   {
       if(osd_ticks() >= target)
          target = -1;
   }
   target = osd_ticks() + ( osd_ticks_per_second() / (double)60);
}

void droid_ios_video_draw()
{
	UINT8 *surfptr;
	INT32 pitch;
	int bpp;

	bpp = 2;
	vofs = hofs = 0;

	if(myosd_video_threaded)
	{
                pthread_mutex_lock( &cond_mutex );
		while(currlist == NULL)
		{
      	  	     pthread_cond_wait( &condition_var, &cond_mutex );
		}
	}

	if(curr_screen_width!= screen_width || curr_screen_height != screen_height ||
	   curr_vis_area_screen_width!= vis_area_screen_width || curr_vis_area_screen_height != vis_area_screen_height)
	{
		screen_width = curr_screen_width;
		screen_height = curr_screen_height;

		vis_area_screen_width = curr_vis_area_screen_width;
		vis_area_screen_height = curr_vis_area_screen_height;

		myosd_set_video_mode(screen_width,screen_height,vis_area_screen_width,vis_area_screen_height);
	}

	if(myosd_video_threaded)
	   pthread_mutex_unlock( &cond_mutex );

	if(myosd_video_threaded)
	   osd_lock_acquire(currlist->lock);

	surfptr = (UINT8 *) myosd_screen15;

        pitch = screen_width * (myosd_rgb==1?4:2);

	surfptr += ((vofs * pitch) + (hofs * bpp));

#ifdef ANDROID
        if(!myosd_rgb)
	  draw_rgb565_draw_primitives(currlist->head, surfptr, screen_width, screen_height, pitch / 2);
        else
          draw_bgr888_draw_primitives(currlist->head, surfptr, screen_width, screen_height, pitch / 4);
#else
	draw_rgb555_draw_primitives(currlist->head, surfptr, screen_width, screen_height, pitch / 2);
#endif

	if(myosd_video_threaded)
        {
	  osd_lock_release(currlist->lock);
          //my_sync();
        }

	myosd_video_flip();

	if(myosd_video_threaded)
	   pthread_mutex_lock( &cond_mutex );

	currlist = NULL;

	if(myosd_video_threaded)
	   pthread_mutex_unlock( &cond_mutex );
}

extern "C"
void droid_ios_video_thread()
{
    while (!thread_stopping && myosd_video_threaded)
    {
	droid_ios_video_draw();
    }
}

void droid_ios_video_render(render_target *our_target)
{
	int width, height;
        int minwidth, minheight;
	int viswidth, visheight;
        int aspect;

	if(myosd_video_threaded)
	   pthread_mutex_lock( &cond_mutex );

        if(currlist==NULL)
        {		                                 
                if(!myosd_inGame) 
                {
                    width  = viswidth = myosd_res_width;
                    height = visheight = myosd_res_height;
                    aspect = 0;
                }
		else if(myosd_force_pxaspect == 1)
		{                   
		    render_target_get_minimum_size(our_target, &minwidth, &minheight);   
                   
                    width = minwidth;
                    height = minheight;
		    viswidth = minwidth;
		    visheight = minheight;

                    aspect = 0;
 	        }
                else if(myosd_force_pxaspect==2)
		{
		   render_target_get_minimum_size(our_target, &minwidth, &minheight);
                   
                   width = minwidth;
                   height = minheight;

		   viswidth = minwidth;
		   visheight = minheight;
			   
                   int w,h;
		   render_target_compute_visible_area(our_target,minwidth,minheight,1,render_target_get_orientation(our_target),&w, &h);

		   if(visheight > h &&  abs((float)w/(float)h - 4.0f/3.0f) < 0.001)// 4/3 minimum
		   {
		       viswidth = w;
	  	       visheight = h;
		   }

		   if(viswidth > h * 16.0f/9.0f &&  abs((float)w/(float)h - 4.0f/3.0f) < 0.001)// 16/9 maximun
		   {
		       viswidth = h * 16.0f/9.0f;
	  	       visheight = h;
		   }

		   if(viswidth < w &&  abs((float)w/(float)h - 3.0f/4.0f) < 0.001)// 3/4 minimum
		   {
		       viswidth = w;
	  	       visheight = h;
		   }
		        
		   if(visheight > h && abs((float)w/(float)h - 3.0f/4.0f) < 0.001)// 3/4 maximun
		   {
		       viswidth = w ;
	  	       visheight = h;
		   }  
                  
                   aspect = 0;              
#ifdef ANDROID
//	__android_log_print(ANDROID_LOG_DEBUG, "VIS","FIN %d, %d",viswidth,visheight);
#endif
		}
		else //MAME standard
                {
                   if(myosd_auto_res==1)
                   {
		      render_target_get_minimum_size(our_target, &width, &height);

                      if(width > 640)
                      {
                         if(myosd_res_width > 640)
                            width = myosd_res_width;
                         else
                            width = 640;
                      }

                      if(height > 480) 
                      {
                          if(myosd_res_height > 480)
                             height = myosd_res_height;
                          else
                             height = 480;
                      }
                       
                      //calculate vis area to pass to GPU scaler instead MAME scaler. Performace and accurate!
		      render_target_compute_visible_area(our_target,width,height,1,render_target_get_orientation(our_target),&viswidth, &visheight);
                      aspect = 0;
		   }
		   else
		   {
                      width = myosd_res_width;
                      height = myosd_res_height; 			
                      viswidth = width ;
	              visheight = height;
                      aspect = width  / height;
		   }
                }

		if(width%2!=0)width++;

		// make that the size of our target
		render_target_set_bounds(our_target, width, height, aspect);

		currlist = render_target_get_primitives(our_target);

		curr_screen_width = width;
		curr_screen_height = height;
		curr_vis_area_screen_width = viswidth;
		curr_vis_area_screen_height = visheight;

		if(myosd_video_threaded)
		    pthread_cond_signal( &condition_var );
		else
	            droid_ios_video_draw();
    }


    if(myosd_video_threaded)
	   pthread_mutex_unlock( &cond_mutex );
}

#define FUNC_PREFIX(x)		draw_rgb565_##x
#define PIXEL_TYPE			UINT16
#define SRCSHIFT_R			3
#define SRCSHIFT_G			2
#define SRCSHIFT_B			3
#define DSTSHIFT_R			11
#define DSTSHIFT_G			5
#define DSTSHIFT_B			0

#include "rendersw.c"

#define FUNC_PREFIX(x)		draw_rgb555_##x
#define PIXEL_TYPE			UINT16
#define SRCSHIFT_R			3
#define SRCSHIFT_G			3
#define SRCSHIFT_B			3
#define DSTSHIFT_R			10
#define DSTSHIFT_G			5
#define DSTSHIFT_B			0

#include "rendersw.c"

#define FUNC_PREFIX(x)		draw_bgr888_##x
#define PIXEL_TYPE			UINT32
#define SRCSHIFT_R			0
#define SRCSHIFT_G			0
#define SRCSHIFT_B			0
#define DSTSHIFT_R			0
#define DSTSHIFT_G			8
#define DSTSHIFT_B			16

#include "rendersw.c"
