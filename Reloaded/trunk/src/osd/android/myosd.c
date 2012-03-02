//============================================================
//
//  myosd.c - Implementation of osd stuff
//
//  Copyright (c) 1996-2007, Nicola Salmoria and the MAME Team.
//  Visit http://mamedev.org for licensing and usage restrictions.
//
//  MAME4DROID by David Valdeita (Seleuco)
//
//============================================================


#include "myosd.h"
#include "driver.h"

#include <unistd.h>
#include <fcntl.h>
#ifdef ANDROID
#include <android/log.h>
#endif
#include <pthread.h>

#include "ui.h"


int  myosd_fps = 0;
int  myosd_showinfo = 1;
int  myosd_sleep = 0;
int  myosd_inGame = 0;
int  myosd_exitGame = 0;
int  myosd_exitPause = 0;
int  myosd_last_game_selected = 0;
int  myosd_frameskip_value = 2;
int  myosd_sound_value = 48000;
int  myosd_throttle = 1;
int  myosd_cheat = 0;
int  myosd_autosave = 0;
int  myosd_savestate = 0;
int  myosd_loadstate = 0;

int num_of_joys=0;


int m4all_BplusX = 0;
//int m4all_hide_LR = 0;
//int m4all_landscape_buttons = 2;
int m4all_hide_LR = 0;
int m4all_landscape_buttons = 4;
/*extern */int m4all_waysStick;
/*extern */float joy_analog_x[4];
/*extern */float joy_analog_y[4];


static int lib_inited = 0;
static int soundInit = 0;
static int isPause = 0;

unsigned long myosd_pad_status = 0;
unsigned long myosd_joy_status[4];
unsigned short 	*myosd_screen15 = NULL;

//////////////////////// android

unsigned short screenbuffer[1024 * 512];
char globalpath[247]="/sdcard/ROMs/MAME4droid/";

static pthread_mutex_t cond_mutex     = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  condition_var   = PTHREAD_COND_INITIALIZER;

void change_pause(int value);

//android callbacks

int  (*dumpVideo_callback)(int emulating) = NULL;
void (*initVideo_callback)(void *buffer) = NULL;
void (*changeVideo_callback)(int newWidth,int newHeight) = NULL;

void (*openSound_callback)(int rate,int stereo) = NULL;
void (*dumpSound_callback)(void *buffer,int size) = NULL;
void (*closeSound_callback)(void) = NULL;




void setVideoCallbacks(void *init_video_java,void *dump_video_java, void *change_video_java)
{
#ifdef ANDROID
	__android_log_print(ANDROID_LOG_DEBUG, "libMAME4droid.so", "setVideoCallbacks");
#endif
	initVideo_callback = init_video_java;
	dumpVideo_callback = dump_video_java;
	changeVideo_callback = change_video_java;
}

void setAudioCallbacks(void *open_sound_java, void *dump_sound_java, void *close_sound_java)
{
#ifdef ANDROID
	__android_log_print(ANDROID_LOG_DEBUG, "libMAME4droid.so", "setAudioCallbacks");
#endif
    openSound_callback = open_sound_java;
    dumpSound_callback = dump_sound_java;
    closeSound_callback = close_sound_java;
}


void setGlobalPath(const char *path){

	int ret;
	/*
	char *directory = (char *)"/mnt/sdcard/app-data/com.seleuco.mame4droid2/";
	ret = chdir (directory);
    */
#ifdef ANDROID
	__android_log_print(ANDROID_LOG_DEBUG, "libMAME4droid.so", "setGlobalPath %s",path);
#endif

	strcpy(globalpath,path);
	ret = chdir (globalpath);
}

void setPadStatus(int i, unsigned long pad_status)
{
	if(i==0 && num_of_joys==0)
	   myosd_pad_status = pad_status;

	myosd_joy_status[i]=pad_status;

	if(i==1 && pad_status && MYOSD_SELECT && num_of_joys<2)
		num_of_joys = 2;
	else if(i==2 && pad_status && MYOSD_SELECT && num_of_joys<3)
		num_of_joys = 3;
	else if(i==2 && pad_status && MYOSD_SELECT && num_of_joys<4)
		num_of_joys = 4;

	//__android_log_print(ANDROID_LOG_DEBUG, "libMAME4droid.so", "set_pad %ld",pad_status);
}

int isEmulating(void)
{
#ifdef ANDROID
	__android_log_print(ANDROID_LOG_DEBUG, "libMAME4droid.so", "isEmulating  %d",myosd_inGame);
#endif
	return myosd_inGame;
}

void setMyValue(int key,int value){


	//__android_log_print(ANDROID_LOG_DEBUG, "libMAME4droid.so", "setMyValue  %d %d",key,value);

	switch(key)
	{
	    case 1:
	    	myosd_fps = value;break;
	    case 2:
	    	myosd_exitGame = value;break;
	    case 8:
	    	myosd_showinfo = value;break;
	    case 9:
	 	    myosd_exitPause = value;break;
	    case 10:
	    	myosd_sleep = value;break;
	    case 11:
	    	change_pause(value);break;
	    case 12:
	    	myosd_frameskip_value = value;break;
	    case 13:
	    	myosd_sound_value = value;break;
	    case 14:
	    	myosd_throttle = value;break;
	    case 15:
	    	myosd_cheat = value;break;
	    case 16:
	    	myosd_autosave = value;break;
	    case 17:
	    	myosd_savestate = value;break;
	    case 18:
	    	myosd_loadstate = value;break;
	}
}

int getMyValue(int key){
	//__android_log_print(ANDROID_LOG_DEBUG, "libMAME4droid.so", "getMyValue  %d",key);

	switch(key)
	{
	    case 1:
	         return myosd_fps;
	    case 2:
	         return myosd_exitGame;
	    case 3:
	    	 return m4all_landscape_buttons;
	    case 4:
	    	 return m4all_hide_LR;
	    case 5:
	    	 return m4all_BplusX;
	    case 6:
	    	 return m4all_waysStick;
	    case 7:
	    	 return 0;
	    case 8:
	    	 return myosd_showinfo;

	    default :
	         return -1;
	}

}

void setMyAnalogData(int i, float v1, float v2){
	joy_analog_x[i]=v1;
	joy_analog_y[i]=v2;
}

static void dump_video(void)
{
#ifdef ANDROID
    // __android_log_print(ANDROID_LOG_DEBUG, "MAME4droid.so", "dump_video");
#endif
	if(dumpVideo_callback!=NULL)
	   dumpVideo_callback(myosd_inGame);
}

/////////////

void myosd_video_flip(void)
{
	dump_video();
}

unsigned long myosd_joystick_read(int n)
{
    unsigned long res=0;
	res = myosd_pad_status;
		
	if ((res & MYOSD_VOL_UP) && (res & MYOSD_VOL_DOWN))
	  		res |= MYOSD_PUSH;

	if (num_of_joys>n)
	{
	  	/* Check USB Joypad */
		//printf("%d %d\n",num_of_joys,n);
		//res |= iOS_wiimote_check(&joys[n]);
		res |= myosd_joy_status[n];
	}
  	
	return res;
}

void myosd_set_video_mode(int width,int height)
{
#ifdef ANDROID
     __android_log_print(ANDROID_LOG_DEBUG, "MAME4droid.so", "set_video_mode: %d %d ",width,height);
#endif

      if(changeVideo_callback!=NULL)
	     changeVideo_callback(width, height);
    if(myosd_screen15!=NULL)
	   memset(myosd_screen15, 0, width*height*2);

  	myosd_video_flip();
}

void myosd_init(void)
{
    if (!lib_inited )
    {
#ifdef ANDROID
		__android_log_print(ANDROID_LOG_DEBUG, "MAME4droid.so", "init");
#endif
	   myosd_screen15=screenbuffer;
	   if(initVideo_callback!=NULL)
          initVideo_callback((void *)&screenbuffer);

	   myosd_set_video_mode(320,240);

   	   lib_inited = 1;
    }
}

void myosd_deinit(void)
{
    if (lib_inited )
    {
#ifdef ANDROID
		__android_log_print(ANDROID_LOG_DEBUG, "MAME4droid.so", "deinit");
#endif
    	lib_inited = 0;
    }
}

void myosd_closeSound(void) {
	if( soundInit == 1 )
	{
#ifdef ANDROID
		__android_log_print(ANDROID_LOG_DEBUG, "MAME4droid.so", "closeSound");
#endif
	   	if(closeSound_callback!=NULL)
		  closeSound_callback();
	   	soundInit = 0;
	}
}

void myosd_openSound(int rate,int stereo) {
	if( soundInit == 0)
	{
#ifdef ANDROID
		__android_log_print(ANDROID_LOG_DEBUG, "MAME4droid.so", "openSound rate:%d stereo:%d",rate,stereo);
#endif
		if(openSound_callback!=NULL)
		  openSound_callback(rate,stereo);
		soundInit = 1;
	}
}

void myosd_sound_play(void *buff, int len)
{
	if(dumpSound_callback!=NULL)
	   dumpSound_callback(buff,len);
}

void change_pause(int value){
	pthread_mutex_lock( &cond_mutex );

	isPause = value;

    if(!isPause)
    {
		pthread_cond_signal( &condition_var );
    }

	pthread_mutex_unlock( &cond_mutex );
}

void myosd_check_pause(void){

	pthread_mutex_lock( &cond_mutex );

	while(isPause)
	{
		pthread_cond_wait( &condition_var, &cond_mutex );
	}

	pthread_mutex_unlock( &cond_mutex );
}

