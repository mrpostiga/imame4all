//============================================================
//
//  Copyright (c) 1996-2009, Nicola Salmoria and the MAME Team.
//  Visit http://mamedev.org for licensing and usage restrictions.
//
//  MAME4DROID by David Valdeita (Seleuco)
//
//============================================================

#ifdef ANDROID
#include <android/log.h>
#endif

#include "osdcore.h"
#include <malloc.h>
#include <unistd.h>
#include "render.h"
#include "mame.h"
#include "droidvideo.h"

#include <pthread.h>
#include "myosd.h"

static int screen_width;
static int screen_height;
static int curr_screen_width;
static int curr_screen_height;
static int hofs;
static int vofs;

static const render_primitive_list *currlist = NULL;
static int thread_stopping = 0;

static pthread_mutex_t cond_mutex     = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  condition_var   = PTHREAD_COND_INITIALIZER;

static void drawsdl_rgb565_draw_primitives(const render_primitive *primlist, void *dstdata, UINT32 width, UINT32 height, UINT32 pitch);

void droid_setup_video()
{
	static int a = 0;
	screen_width = 640;
	screen_height = 480;

	/*
	hofs = (screen_width - screen_width * options_get_float(mame_options(), "safearea")) / 2;
	vofs = (screen_height - screen_height * options_get_float(mame_options(), "safearea")) / 2;
	screen_width -= hofs * 2;
	screen_height -= vofs * 2;
    */
	if(!a)
	{
	myosd_set_video_mode(screen_width,screen_height);
	a=1;
	}
}

static void droid_video_cleanup(running_machine *machine)
{
   	usleep(150000);
}

void droid_init_video(running_machine *machine)
{
	add_exit_callback(machine, droid_video_cleanup);
}

void droid_video_thread()
{
	UINT8 *surfptr;
	INT32 pitch;
	int bpp;

	bpp = 2;
	vofs = hofs = 0;

	while (!thread_stopping)
	{
		pthread_mutex_lock( &cond_mutex );

		while(currlist == NULL)
		{
			pthread_cond_wait( &condition_var, &cond_mutex );
		}

		if(curr_screen_width!= screen_width || curr_screen_height != screen_height)
		{
			screen_width = curr_screen_width;
			screen_height = curr_screen_height;
			myosd_set_video_mode(screen_width,screen_height);
		}

		pthread_mutex_unlock( &cond_mutex );

		osd_lock_acquire(currlist->lock);

		surfptr = (UINT8 *) myosd_screen15;

		pitch = screen_width * 2;

		surfptr += ((vofs * pitch) + (hofs * bpp));

		drawsdl_rgb565_draw_primitives(currlist->head, surfptr, screen_width, screen_height, pitch / 2);

		osd_lock_release(currlist->lock);

		myosd_video_flip();

		pthread_mutex_lock( &cond_mutex );

		currlist = NULL;

		pthread_mutex_unlock( &cond_mutex );
	}

}

void droid_video_render(render_target *our_target)
{
	int minwidth, minheight;

	pthread_mutex_lock( &cond_mutex );

    if(currlist==NULL)
    {
		// get the minimum width/height for the current layout
		render_target_get_minimum_size(our_target, &minwidth, &minheight);

		if(minwidth%2!=0)minwidth++;

		// make that the size of our target
		render_target_set_bounds(our_target, minwidth, minheight, 0);

		currlist = render_target_get_primitives(our_target);

		curr_screen_width = minwidth;
		curr_screen_height = minheight;

		pthread_cond_signal( &condition_var );
    }

	pthread_mutex_unlock( &cond_mutex );
}

#define FUNC_PREFIX(x)		drawsdl_rgb565_##x
#define PIXEL_TYPE			UINT16
#define SRCSHIFT_R			3
#define SRCSHIFT_G			2
#define SRCSHIFT_B			3
#define DSTSHIFT_R			11
#define DSTSHIFT_G			5
#define DSTSHIFT_B			0

#include "rendersw.c"
