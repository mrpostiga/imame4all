//============================================================
//
//  minifile.c - Minimal core file access functions
//
//============================================================
//
//  Copyright Aaron Giles
//  All rights reserved.
//
//  Redistribution and use in source and binary forms, with or
//  without modification, are permitted provided that the
//  following conditions are met:
//
//    * Redistributions of source code must retain the above
//      copyright notice, this list of conditions and the
//      following disclaimer.
//    * Redistributions in binary form must reproduce the
//      above copyright notice, this list of conditions and
//      the following disclaimer in the documentation and/or
//      other materials provided with the distribution.
//    * Neither the name 'MAME' nor the names of its
//      contributors may be used to endorse or promote
//      products derived from this software without specific
//      prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY AARON GILES ''AS IS'' AND
//  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
//  FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
//  EVENT SHALL AARON GILES BE LIABLE FOR ANY DIRECT,
//  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  DAMAGE (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
//  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
//  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
//  IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//============================================================

#include "emuopts.h"


#include <android/log.h>

#include "clifront.h"


int SDL_Main(int argc, char *argv[])
{

	// cli_execute does the heavy lifting; if we have osd-specific options, we
	// would pass them as the third parameter here
	__android_log_print(ANDROID_LOG_INFO, "libSDL", "RULA PIRULA!");
	printf("MAIN\n");

	return cli_execute(argc, argv, NULL);
}

#include "osdcore.h"


//============================================================
//  osd_open
//============================================================

file_error osd_open(const char *path, UINT32 openflags, osd_file **file, UINT64 *filesize)
{
	const char *mode;
	FILE *fileptr;

	// based on the flags, choose a mode
	if (openflags & OPEN_FLAG_WRITE)
	{
		if (openflags & OPEN_FLAG_READ)
			mode = (openflags & OPEN_FLAG_CREATE) ? "w+b" : "r+b";
		else
			mode = "wb";
	}
	else if (openflags & OPEN_FLAG_READ)
		mode = "rb";
	else
		return FILERR_INVALID_ACCESS;

	// open the file
	fileptr = fopen(path, mode);
	if (fileptr == NULL)
		return FILERR_NOT_FOUND;

	// store the file pointer directly as an osd_file
	*file = (osd_file *)fileptr;

	// get the size -- note that most fseek/ftell implementations are limited to 32 bits
	fseek(fileptr, 0, SEEK_END);
	*filesize = ftell(fileptr);
	fseek(fileptr, 0, SEEK_SET);

	return FILERR_NONE;
}


//============================================================
//  osd_close
//============================================================

file_error osd_close(osd_file *file)
{
	// close the file handle
	fclose((FILE *)file);
	return FILERR_NONE;
}


//============================================================
//  osd_read
//============================================================

file_error osd_read(osd_file *file, void *buffer, UINT64 offset, UINT32 length, UINT32 *actual)
{
	size_t count;

	// seek to the new location; note that most fseek implementations are limited to 32 bits
	fseek((FILE *)file, offset, SEEK_SET);

	// perform the read
	count = fread(buffer, 1, length, (FILE *)file);
	if (actual != NULL)
		*actual = count;

	return FILERR_NONE;
}


//============================================================
//  osd_write
//============================================================

file_error osd_write(osd_file *file, const void *buffer, UINT64 offset, UINT32 length, UINT32 *actual)
{
	size_t count;

	// seek to the new location; note that most fseek implementations are limited to 32 bits
	fseek((FILE *)file, offset, SEEK_SET);

	// perform the write
	count = fwrite(buffer, 1, length, (FILE *)file);
	if (actual != NULL)
		*actual = count;

	return FILERR_NONE;
}


//============================================================
//  osd_rmfile
//============================================================

file_error osd_rmfile(const char *filename)
{
	return remove(filename) ? FILERR_FAILURE : FILERR_NONE;
}


//============================================================
//  osd_get_physical_drive_geometry
//============================================================

int osd_get_physical_drive_geometry(const char *filename, UINT32 *cylinders, UINT32 *heads, UINT32 *sectors, UINT32 *bps)
{
	// there is no standard way of doing this, so we always return FALSE, indicating
	// that a given path is not a physical drive
	return FALSE;
}


//============================================================
//  osd_uchar_from_osdchar
//============================================================

int osd_uchar_from_osdchar(UINT32 /* unicode_char */ *uchar, const char *osdchar, size_t count)
{
	// we assume a standard 1:1 mapping of characters to the first 256 unicode characters
	*uchar = (UINT8)*osdchar;
	return 1;
}

//============================================================
//  osd_wait_for_debugger
//============================================================
#include "osdepend.h"
#include "render.h"
#include "clifront.h"
#include "mame.h"
void osd_wait_for_debugger(const device_config *device, int firststop)
{
	// we don't have a debugger, so we just return here
}
//============================================================
//  CONSTANTS
//============================================================

// we fake a keyboard with the following keys
enum
{
	KEY_ESCAPE,
	KEY_P1_START,
	KEY_BUTTON_1,
	KEY_BUTTON_2,
	KEY_BUTTON_3,
	KEY_JOYSTICK_U,
	KEY_JOYSTICK_D,
	KEY_JOYSTICK_L,
	KEY_JOYSTICK_R,
	KEY_TOTAL
};


//============================================================
//  GLOBALS
//============================================================

// a single rendering target
static render_target *our_target;

// a single input device
static input_device *keyboard_device;

// the state of each key
static UINT8 keyboard_state[KEY_TOTAL];


//============================================================
//  FUNCTION PROTOTYPES
//============================================================

static INT32 keyboard_get_state(void *device_internal, void *item_internal);



//============================================================
//  keyboard_get_state
//============================================================

static INT32 keyboard_get_state(void *device_internal, void *item_internal)
{
	// this function is called by the input system to get the current key
	// state; it is specified as a callback when adding items to input
	// devices
	UINT8 *keystate = (UINT8 *)item_internal;
	return *keystate;
}
//============================================================
//  osd_init
//============================================================

void osd_init(running_machine *machine)
{
	printf("OSD init\n");
	// initialize the video system by allocating a rendering target
	our_target = render_target_alloc(machine, NULL, 0);
	if (our_target == NULL)
		fatalerror("Error creating render target");

	// nothing yet to do to initialize sound, since we don't have any
	// sound updates are handled by osd_update_audio_stream() below

	// initialize the input system by adding devices
	// let's pretend like we have a keyboard device
	keyboard_device = input_device_add(machine, DEVICE_CLASS_KEYBOARD, "Keyboard", NULL);
	if (keyboard_device == NULL)
		fatalerror("Error creating keyboard device");

	// our faux keyboard only has a couple of keys (corresponding to the
	// common defaults)
	input_device_item_add(keyboard_device, "Esc", &keyboard_state[KEY_ESCAPE], ITEM_ID_ESC, keyboard_get_state);
	input_device_item_add(keyboard_device, "P1", &keyboard_state[KEY_P1_START], ITEM_ID_1, keyboard_get_state);
	input_device_item_add(keyboard_device, "B1", &keyboard_state[KEY_BUTTON_1], ITEM_ID_LCONTROL, keyboard_get_state);
	input_device_item_add(keyboard_device, "B2", &keyboard_state[KEY_BUTTON_2], ITEM_ID_LALT, keyboard_get_state);
	input_device_item_add(keyboard_device, "B3", &keyboard_state[KEY_BUTTON_3], ITEM_ID_SPACE, keyboard_get_state);
	input_device_item_add(keyboard_device, "JoyU", &keyboard_state[KEY_JOYSTICK_U], ITEM_ID_UP, keyboard_get_state);
	input_device_item_add(keyboard_device, "JoyD", &keyboard_state[KEY_JOYSTICK_D], ITEM_ID_DOWN, keyboard_get_state);
	input_device_item_add(keyboard_device, "JoyL", &keyboard_state[KEY_JOYSTICK_L], ITEM_ID_LEFT, keyboard_get_state);
	input_device_item_add(keyboard_device, "JoyR", &keyboard_state[KEY_JOYSTICK_R], ITEM_ID_RIGHT, keyboard_get_state);

	// hook up the debugger log
//  add_logerror_callback(machine, output_oslog);
}





//============================================================
//  osd_update
//============================================================

void osd_update(running_machine *machine, int skip_redraw)
{
	const render_primitive_list *primlist;
	int minwidth, minheight;

	// get the minimum width/height for the current layout
	render_target_get_minimum_size(our_target, &minwidth, &minheight);

	// make that the size of our target
	render_target_set_bounds(our_target, minwidth, minheight, 0);

	// get the list of primitives for the target at the current size
	primlist = render_target_get_primitives(our_target);

	// lock them, and then render them
	osd_lock_acquire(primlist->lock);
	printf("dibujando\n");
	// do the drawing here
	osd_lock_release(primlist->lock);

	// after 5 seconds, exit
	if (attotime_compare(timer_get_time(machine), attotime_make(5, 0)) > 0)
		mame_schedule_exit(machine);
	printf("fin\n");
}


//============================================================
//  osd_update_audio_stream
//============================================================

void osd_update_audio_stream(running_machine *machine, INT16 *buffer, int samples_this_frame)
{
	// if we had actual sound output, we would copy the
	// interleaved stereo samples to our sound stream
}


//============================================================
//  osd_set_mastervolume
//============================================================

void osd_set_mastervolume(int attenuation)
{
	// if we had actual sound output, we would adjust the global
	// volume in response to this function
}


//============================================================
//  osd_customize_input_type_list
//============================================================

void osd_customize_input_type_list(input_type_desc *typelist)
{
	// This function is called on startup, before reading the
	// configuration from disk. Scan the list, and change the
	// default control mappings you want. It is quite possible
	// you won't need to change a thing.
}
