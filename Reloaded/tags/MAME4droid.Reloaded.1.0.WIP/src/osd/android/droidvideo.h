//============================================================
//
//  Copyright (c) 1996-2009, Nicola Salmoria and the MAME Team.
//  Visit http://mamedev.org for licensing and usage restrictions.
//
//  MAME4DROID by David Valdeita (Seleuco)
//
//============================================================

#ifndef _DROIDVIDEO_H_
#define _DROIDVIDEO_H_

#include "render.h"

void droid_init_video(running_machine *machine);
void droid_setup_video(void);
void droid_video_render(render_target *);
void droid_video_thread(void);

#endif
