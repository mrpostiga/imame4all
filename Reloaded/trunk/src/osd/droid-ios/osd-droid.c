//============================================================
//
//  myosd.c - Implementation of osd stuff
//
//  Copyright (c) 1996-2007, Nicola Salmoria and the MAME Team.
//  Visit http://mamedev.org for licensing and usage restrictions.
//
//  MAME4DROID MAME4iOS by David Valdeita (Seleuco)
//
//============================================================

#include "myosd.h"
#include "opensl_snd.h"

#include "netplay.h"
#include "skt_netplay.h"

#include <unistd.h>
#include <fcntl.h>
#ifdef ANDROID
#include <android/log.h>
#endif
#include <pthread.h>

#include "../../lib/hqx/hqx.h"

//#include "ui.h"
//#include "driver.h"

int  myosd_fps = 1;
int  myosd_showinfo = 1;
int  myosd_sleep = 0;
int  myosd_inGame = 0;
int  myosd_exitGame = 0;
int  myosd_pause = 0;
int  myosd_exitPause = 0;
int  myosd_last_game_selected = 0;
int  myosd_frameskip_value = 2;
int  myosd_sound_value = 48000;
int  myosd_throttle = 1;
int  myosd_cheat = 0;
int  myosd_autosave = 0;
int  myosd_savestate = 0;
int  myosd_loadstate = 0;
int  myosd_video_width = 1;
int  myosd_video_height = 1;
int  myosd_vis_video_width = 1;
int  myosd_vis_video_height = 1;
int  myosd_res_width = 1;
int  myosd_res_height = 1;
int  myosd_in_menu = 0;
int  myosd_auto_res = 1;
int  myosd_res = 1;
int  myosd_force_pxaspect = 0;
int  myosd_waysStick;
int  myosd_pxasp1 = 0;
int  myosd_service = 0;
int  myosd_num_buttons = 0;
int  myosd_light_gun = 0;
int  myosd_fs_counter = 0;
int  myosd_saveload_combo = 1;

int myosd_num_of_joys=1;
int myosd_video_threaded=1;

int myosd_filter_favorites = 0;
int myosd_filter_clones = 0;
int myosd_filter_not_working = 0;

int myosd_filter_manufacturer = -1;
int myosd_filter_gte_year = -1;
int myosd_filter_lte_year = -1;
int myosd_filter_driver_source= -1;
int myosd_filter_category = -1;
char myosd_filter_keyword[MAX_FILTER_KEYWORD] = {'\0'};

int myosd_reset_filter = 0;

int myosd_num_ways = 8;

int myosd_vsync = -1;
int myosd_refresh = -1;
int myosd_dbl_buffer=1;
int myosd_rgb=0;
int myosd_hqx=0;
int myosd_autofire=0;
int myosd_hiscore=0;

int myosd_vector_bean2x = 1;
int myosd_vector_antialias = 1;
int myosd_vector_flicker = 0;

int  myosd_speed = 100;

char myosd_selected_game[MAX_GAME_NAME] = {'\0'};

float joy_analog_x[4];
float joy_analog_y[4];

float lightgun_x[4];
float lightgun_y[4];

float mouse_x[4];
float mouse_y[4];

int myosd_mouse = 0;

static int lib_inited = 0;
static int soundInit = 0;
static int isPause = 0;

unsigned long myosd_pad_status = 0;
unsigned long myosd_joy_status[4];
unsigned short myosd_ext_status = 0;

unsigned short 	*myosd_screen15 = NULL;

char myosd_game[MAX_GAME_NAME] = {'\0'};
char myosd_rompath[MAX_ROM_PATH] = {'\0'};
char myosd_version[16] = {'\0'};
char myosd_bios[16] = {'\0'};

char *myosd_category = NULL;

//////////////////////// android

static unsigned short *screenbuffer1 = NULL;
static unsigned short *screenbuffer2 = NULL;

char globalpath[247]="/sdcard/ROMs/MAME4droid/";

int array_year_count = 0;
int array_main_manufacturers_count = 0;
int array_main_driver_source_count = 0;
int array_categories_count = 0;

static pthread_mutex_t cond_mutex     = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  condition_var   = PTHREAD_COND_INITIALIZER;

static OPENSL_SND  *p = NULL;
static int sound_engine = 1;
static int sound_frames = 1024;
//static int sound_fixed_sr = 44100;
static int frame_delay = 0;

void change_pause(int value);

void (*dumpVideo_callback)(void) = NULL;
void (*initVideo_callback)(void *buffer,int width, int height, int pitch) = NULL;
void (*changeVideo_callback)(int newWidth,int newHeight,int newVisWidth,int newVisHeight) = NULL;

void (*openSound_callback)(int rate,int stereo) = NULL;
void (*dumpSound_callback)(void *buffer,int size) = NULL;
void (*closeSound_callback)(void) = NULL;

void (*netplayWarn_callback)(char *) = NULL;

#define PIXEL_PITCH ((myosd_rgb ? 4 : 2))


static void netplay_warn_callback(char *msg)
{
    if(netplayWarn_callback!=NULL)
       netplayWarn_callback(msg);
}

extern "C"
int netplayInit(const char *srv_addr, int port, int join){

   netplay_t *handle = netplay_get_handle();
    
   if(!join)
   {

      if(!skt_netplay_init(handle,srv_addr,port,netplay_warn_callback))
         return -1;

      if(frame_delay == 0)
      {
          handle->is_auto_frameskip = 1;
          handle->frame_skip = 2;
      }
      else
      {
          handle->is_auto_frameskip = 0;            
          handle->frame_skip = frame_delay;
      }

      if(srv_addr==NULL)
         strcpy(handle->game_name,myosd_selected_game);
   }
   else
   {
       if(!netplay_send_join(handle))
          return -1;
   }

   return 0;
}

extern "C" void setVideoCallbacks(void (*init_video_java)(void *, int, int, int),void (*dump_video_java)(void), void (*change_video_java)(int,int,int,int))
{
#ifdef ANDROID
	__android_log_print(ANDROID_LOG_DEBUG, "libMAME4droid.so", "setVideoCallbacks");
#endif
	initVideo_callback = init_video_java;
	dumpVideo_callback = dump_video_java;
	changeVideo_callback = change_video_java;
}

extern "C" void setAudioCallbacks(void (*open_sound_java)(int,int), void (*dump_sound_java)(void *,int), void (*close_sound_java)())
{
#ifdef ANDROID
	__android_log_print(ANDROID_LOG_DEBUG, "libMAME4droid.so", "setAudioCallbacks");
#endif
    openSound_callback = open_sound_java;
    dumpSound_callback = dump_sound_java;
    closeSound_callback = close_sound_java;
}

extern "C" void setNetplayCallbacks(void (*netplay_warn_java)(char *))
{
#ifdef ANDROID
	__android_log_print(ANDROID_LOG_DEBUG, "libMAME4droid.so", "setNetplayCallbacks");
#endif
    netplayWarn_callback = netplay_warn_java;
}

extern "C"
void setPadStatus(int i, unsigned long pad_status)
{
	if(i==0)
	   myosd_pad_status = pad_status;

	myosd_joy_status[i]=pad_status;

	if(i==1 && pad_status && MYOSD_SELECT && myosd_num_of_joys<2)
		myosd_num_of_joys = 2;
	else if(i==2 && pad_status && MYOSD_SELECT && myosd_num_of_joys<3)
		myosd_num_of_joys = 3;
	else if(i==3 && pad_status && MYOSD_SELECT && myosd_num_of_joys<4)
		myosd_num_of_joys = 4;

	//__android_log_print(ANDROID_LOG_DEBUG, "libMAME4droid.so", "set_pad %ld",pad_status);
}

extern "C" void setGlobalPath(const char *path){
    /*
	int ret;
	
	char *directory = (char *)"/mnt/sdcard/app-data/com.seleuco.mame4droid2/";
	ret = chdir (directory);
    */
#ifdef ANDROID
	__android_log_print(ANDROID_LOG_DEBUG, "libMAME4droid.so", "setGlobalPath %s",path);
#endif

	strcpy(globalpath,path);
	/*ret = */chdir (globalpath);
}

extern "C"
void setMyValue(int key,int i, int value){
	//__android_log_print(ANDROID_LOG_DEBUG, "libMAME4droid.so", "setMyValue  %d,%d:%d",key,i,value);
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
	    case 20:
	    	myosd_res = value;break;
	    case 21:
	    	myosd_force_pxaspect = value;break;
	    case 22:
	    	myosd_video_threaded = value;break;
	    case 23:
	    	myosd_dbl_buffer = value;break;
	    case 24:
	    	myosd_pxasp1 = value;break;
	    case 27:
	    	myosd_filter_favorites = value;break;
	    case 28:
	    	myosd_reset_filter = value;break;
	    case 29:
	    	myosd_last_game_selected = value;break;
	    case 30:
	    	myosd_speed  = value;break;
            case 31:
                myosd_autofire = value;break;
            case 32:
                myosd_vsync = value;break;
            case 33:
                myosd_hiscore = value;break;
            case 34:
                myosd_vector_bean2x = value;break;
            case 35:
                myosd_vector_antialias = value;break;
            case 36:
                myosd_vector_flicker = value;break;
            case 41:
                myosd_filter_clones = value;break;
            case 42:
                myosd_filter_not_working = value;break;
            case 43:
                myosd_filter_manufacturer = value;break;
            case 44:
                myosd_filter_gte_year = value;break;
            case 45:
                myosd_filter_lte_year = value;break;
            case 46:
                myosd_filter_driver_source = value;break;
            case 47:
                myosd_filter_category= value;break;
            case 48:
                sound_frames = value;break;
            case 49:
                {  
                    if(myosd_sound_value!=-1 && sound_engine == 2)
                        myosd_sound_value = value;break;
                }
            case 50:
                sound_engine = value;break;
            case 51:
                myosd_auto_res = value;break;
            case 53:
                 { 
                     netplay_t *handle = netplay_get_handle();
                     handle->has_connection = value;
                     break;
                 }
            case 55:
                 { 
                     
                     netplay_t *handle = netplay_get_handle();
            
                     if(handle->has_joined && value!=frame_delay)
                     {
                         if(value==0)
                         {
                             handle->is_auto_frameskip = 1;
                         }
                         else
                         {
                             handle->is_auto_frameskip = 0;
                             if(handle->frame_skip!=value)
                                handle->new_frameskip_set = value;
                         }
                     }

                     frame_delay = value;

                     break;
                 }
            case 56:
                 myosd_saveload_combo = value;break;        
            case 57:                 
                 myosd_rgb = value;break;                                     
            case 58:                 
                 {
                    myosd_hqx = 0;
                    if(value)
                      myosd_hqx = value+1;
                 }
                 break;
            case 60:                 
                 myosd_mouse = value;break; 
            case 61:                 
                 myosd_refresh = value;break; 
         }
}

extern "C"
int getMyValue(int key,int i){
     //__android_log_print(ANDROID_LOG_DEBUG, "libMAME4droid.so", "getMyValue  %d,%d",key,i);

     if(i==0) 
     {
	switch(key)
	{
	    case 1:
	         return myosd_fps;
	    case 2:
	         return myosd_exitGame;
	    case 6:
	    	 return myosd_waysStick;
	    case 7:
	    	 return 0;
	    case 8:
	    	 return myosd_showinfo;
	    case 19:
	    	 return myosd_in_menu;
	    case 25:
	    	 return myosd_num_buttons;
	    case 26:
	    	 return myosd_num_ways;
            case 37:
            {
                 if(!array_year_count)
                    while(myosd_array_years[array_year_count][0]!='\0')array_year_count++;
                 return array_year_count;
            }
            case 38:
            {
                if(!array_main_manufacturers_count)
                    while(myosd_array_main_manufacturers[array_main_manufacturers_count][0]!='\0')array_main_manufacturers_count++;
                return array_main_manufacturers_count;
            }
            case 39:
            {
                if(!array_main_driver_source_count)
                    while(myosd_array_main_driver_source[array_main_driver_source_count][0]!='\0')array_main_driver_source_count++;
                return array_main_driver_source_count;
            }
            case 40:
            {
                if(!array_categories_count)
                    while(myosd_array_categories[array_categories_count][0]!='\0')array_categories_count++;
                return array_categories_count;
            }
            case 52:
                return myosd_inGame;
            case 53:
            {
                 netplay_t *handle = netplay_get_handle();
                 return handle->has_connection;
            }
            case 54:
            {
                 netplay_t *handle = netplay_get_handle();
                 return handle->has_joined;            
            }
	    case 59:
            {
                  int b = 0;
                  if(myosd_category!=NULL)
                    b = strcmp(myosd_category, "Shooter / Gun")==0;
                  if(!b)
                    b = myosd_light_gun;
        	  return b;
            }
	    default :
	         return -1;
	}
     }
     return -1;
}

extern "C"
void setMyValueStr(int key,int i, const char *value){
     //__android_log_print(ANDROID_LOG_DEBUG, "libMAME4droid.so", "setMyValueStr  %d,%d:%s",key,i,value);
     switch(key)
     {
        case 4:
        {
            if(strlen(value)<MAX_FILTER_KEYWORD)
              strcpy(myosd_filter_keyword,value);
            break;
        }
        case 6:
        {
            if(strlen(value)<MAX_ROM_PATH)
              strcpy(myosd_rompath,value);
            break;
        }
        case 7:
        {
            if(strlen(value)<MAX_GAME_NAME)
              strcpy(myosd_game,value);
            break;
        }
        case 8:
        {
            if(strlen(value)<16)
              strcpy(myosd_version,value);
            break;
        }
        case 9:
        {
            if(strlen(value)<16)
              strcpy(myosd_bios,value);
            break;
        }
        default:;
     }          
}

extern "C"
char *getMyValueStr(int key,int i){
     //__android_log_print(ANDROID_LOG_DEBUG, "libMAME4droid.so", "getMyValueStr  %d,%d",key,i);
     switch(key)
     {
        case 0: return (char *)myosd_array_years[i];
        case 1: return (char *)myosd_array_main_manufacturers[i];
        case 2: return (char *)myosd_array_main_driver_source[i];
        case 3: return (char *)myosd_array_categories[i];
        case 5: return (char *)myosd_selected_game;
        case 6: return (char *)myosd_rompath;
        case 7: return (char *)myosd_game;
        default: return NULL;  
     }
     
   return NULL;
}

extern "C"
void setMyAnalogData(int i, float v1, float v2){
        
        if(i >= 8)
        {
           mouse_x[i-8]=v1;
           mouse_y[i-8]=v2;        
        }
        else if(i>=4 && i<=7)
        {
           lightgun_x[i-4]=v1;
           lightgun_y[i-4]=v2;
        }
        else
        {
	   joy_analog_x[i]=v1;
	   joy_analog_y[i]=v2;
        }
	//__android_log_print(ANDROID_LOG_DEBUG, "MAME4droid.so", "set analog %d %f %f",i,v1,v2);
}

static void dump_video(void)
{
#ifdef ANDROID
     //__android_log_print(ANDROID_LOG_DEBUG, "MAME4droid.so", "dump_video");
#endif
        if(!myosd_hqx)
        {
            if(myosd_dbl_buffer)
               memcpy(screenbuffer1,screenbuffer2,myosd_video_width * myosd_video_height * PIXEL_PITCH);
        }
        else
        {
            if(myosd_rgb)
            {
		    if(myosd_hqx==2)
		      hq2x_32((uint32_t*)screenbuffer2,(uint32_t*)screenbuffer1,myosd_video_width/myosd_hqx,myosd_video_height/myosd_hqx);
		    else if(myosd_hqx==3)
		      hq3x_32((uint32_t*)screenbuffer2,(uint32_t*)screenbuffer1,myosd_video_width/myosd_hqx,myosd_video_height/myosd_hqx);
		    else if(myosd_hqx==4)
		      hq4x_32((uint32_t*)screenbuffer2,(uint32_t*)screenbuffer1,myosd_video_width/myosd_hqx,myosd_video_height/myosd_hqx);

            }
            else
            {
		    if(myosd_hqx==2)
		      hq2x_16((uint16_t*)screenbuffer2,(uint16_t*)screenbuffer1,myosd_video_width/myosd_hqx,myosd_video_height/myosd_hqx);
		    else if(myosd_hqx==3)
		      hq3x_16((uint16_t*)screenbuffer2,(uint16_t*)screenbuffer1,myosd_video_width/myosd_hqx,myosd_video_height/myosd_hqx);
		    else if(myosd_hqx==4)
		      hq4x_16((uint16_t*)screenbuffer2,(uint16_t*)screenbuffer1,myosd_video_width/myosd_hqx,myosd_video_height/myosd_hqx);
            }
        }

	if(dumpVideo_callback!=NULL)
	   dumpVideo_callback();

}

/////////////

void myosd_video_flip(void)
{
	dump_video();
}

unsigned long myosd_joystick_read(int n)
{
    unsigned long res=0;

	if(myosd_num_of_joys==1)
	{
        if(myosd_pxasp1 || n==0)
		   res = myosd_pad_status;
	}
	else
	{
	   if (n<myosd_num_of_joys)
	   {
		  //res |= iOS_wiimote_check(&joys[n]);
		  res |= myosd_joy_status[n];
	   }
	}
  	
	return res;
}

float myosd_joystick_read_analog(int n, char axis)
{
	float res = 0.0;

	if(myosd_num_of_joys==1)
	{
		if(myosd_pxasp1 || n==0)
		{
			if(axis=='x')
				res = joy_analog_x[0];
			else if (axis=='y')
				res = joy_analog_y[0];
		}
	}
	else
	{
	    if (n<myosd_num_of_joys)
		{
		    if(axis=='x')
				res = joy_analog_x[n];
			else if (axis=='y')
				res = joy_analog_y[n];
		}
	}
    return res;
}


void myosd_set_video_mode(int width,int height,int vis_width, int vis_height)
{
#ifdef ANDROID
     __android_log_print(ANDROID_LOG_DEBUG, "MAME4droid.so", "set_video_mode: %d %d ",width,height);
#endif
    if(width==0)width=1;
    if(height==0)height=1;
    if(vis_width==0)vis_width=1;
    if(vis_height==0)vis_height=1;

    if(!myosd_hqx)
    {
       myosd_vis_video_width = vis_width;
       myosd_vis_video_height = vis_height;
              
       myosd_video_width = width;
       myosd_video_height = height;
    }
    else
    {
       myosd_vis_video_width = vis_width * myosd_hqx;
       myosd_vis_video_height = vis_height * myosd_hqx;
              
       myosd_video_width = width * myosd_hqx;
       myosd_video_height = height * myosd_hqx;
    }

    if(changeVideo_callback!=NULL)
       changeVideo_callback(myosd_video_width,myosd_video_height,myosd_vis_video_width ,myosd_vis_video_height);

    myosd_video_flip();
}


void myosd_init(void)
{
    if (!lib_inited )
    {
#ifdef ANDROID
	   __android_log_print(ANDROID_LOG_DEBUG, "MAME4droid.so", "init");
#endif
      int reswidth = 640,resheight=480; 	

      if(myosd_hqx )
         hqxInit();   

      switch (myosd_res)
      {
            case 1:{reswidth = 320;resheight = 200;break;}//320x200 (16/10)
            case 2:{reswidth = 320;resheight = 240;break;}//320x240 (4/3)
            case 3:{reswidth = 401;resheight = 301;break;}//400x300 (4/3)
            case 4:{reswidth = 480;resheight = 300;break;}//480x300 (16/10)
            case 5:{reswidth = 512;resheight = 384;break;}//512x384 (4/3)
            case 6:{reswidth = 640;resheight = 360;break;}//640x360 (16/9)  
            case 7:{reswidth = 640;resheight = 400;break;}//640x400 (16/10)
            case 8:{reswidth = 640;resheight = 480;break;}//640x480 (4/3)
            case 9:{reswidth = 800;resheight = 600;break;}//800x600 (4/3)    
            case 10:{reswidth = 848-(16*2);resheight = 477-(9*2);break;}//854x480 (16/9)  
            case 11:{reswidth = 1024;resheight = 576;break;}//1024×576 (16/9) 
            case 12:{reswidth = 1024;resheight = 768;break;}//1024x768 (4/3)   
            case 13:{reswidth = 960;resheight = 720;break;}//960x720 (4/3)  
	    case 14:{reswidth = 1280;resheight = 720;break;}//1280x720 (16/9) 
	    case 15:{reswidth = 1440;resheight = 1080;break;}//1440x1080 (4/3) 
	    case 16:{reswidth = 1920;resheight = 1080;break;}//1920x1080 (16/9) 
       } 
       
       if(!myosd_hqx)
       {
          myosd_res_width = reswidth;
          myosd_res_height = resheight;

          if(reswidth<640)reswidth=640;
          if(resheight<480)resheight=480;

          if(screenbuffer1 == NULL)
             screenbuffer1 = (unsigned short *)malloc(reswidth * resheight * PIXEL_PITCH);
      
          if(myosd_dbl_buffer && screenbuffer2==NULL)
             screenbuffer2 = (unsigned short *)malloc(reswidth * resheight * PIXEL_PITCH);

          myosd_screen15 = myosd_dbl_buffer ? screenbuffer2 : screenbuffer1;

          if(initVideo_callback!=NULL)    
             initVideo_callback((void *)screenbuffer1,reswidth,resheight,PIXEL_PITCH);

          myosd_set_video_mode(myosd_res_width,myosd_res_height,myosd_res_width,myosd_res_height);
       }
       else
       {
          myosd_res_width = reswidth;
          myosd_res_height = resheight;

          if(reswidth<640)reswidth=640;
          if(resheight<480)resheight=480;

          if(screenbuffer1 == NULL)
             screenbuffer1 = (unsigned short *)malloc(reswidth * resheight * PIXEL_PITCH  * (myosd_hqx * myosd_hqx));
      
          if(screenbuffer2==NULL)
             screenbuffer2 = (unsigned short *)malloc(reswidth * resheight * PIXEL_PITCH);       
          
          myosd_screen15 = screenbuffer2;

          if(initVideo_callback!=NULL)    
             initVideo_callback((void *)screenbuffer1,reswidth * myosd_hqx,resheight * myosd_hqx,PIXEL_PITCH);

          myosd_set_video_mode(myosd_res_width,myosd_res_height,myosd_res_width,myosd_res_height);
       }

               


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
        if(screenbuffer1!=NULL)
           free(screenbuffer1);
        if(screenbuffer2!=NULL)
           free(screenbuffer2);
    	lib_inited = 0;
    }
}

void myosd_closeSound(void) {
	if( soundInit == 1 )
	{
#ifdef ANDROID
		__android_log_print(ANDROID_LOG_DEBUG, "MAME4droid.so", "closeSound");
#endif
                if(sound_engine==1)
                {
	   	   if(closeSound_callback!=NULL)
		     closeSound_callback();
                }
                else 
                {
                   if(p!=NULL)
                     opensl_close(p);
                }

	   	soundInit = 0;
	}
}

void myosd_openSound(int rate,int stereo) {
	if( soundInit == 0 &&  myosd_sound_value!=-1)
	{
#ifdef ANDROID
		__android_log_print(ANDROID_LOG_DEBUG, "MAME4droid.so", "openSound rate:%d stereo:%d",rate,stereo);
#endif
	        if(sound_engine==1)
                {
 	           __android_log_print(ANDROID_LOG_DEBUG, "SOUND", "Open audioTrack");
                   if(openSound_callback!=NULL)
		     openSound_callback(rate,stereo);
                }
                else
                {
 	           __android_log_print(ANDROID_LOG_DEBUG, "SOUND", "Open openSL %d %d",myosd_sound_value,sound_frames);
                   p = opensl_open(myosd_sound_value,2,sound_frames);
                }

		soundInit = 1;
	}
}

void myosd_sound_play(void *buff, int len)
{
       //__android_log_print(ANDROID_LOG_DEBUG, "PIS", "BUF %d",len);
       if(sound_engine==1)
       {
          if(dumpSound_callback!=NULL)
	    dumpSound_callback(buff,len);
       }
       else
       {
          if(p!=NULL)       
            opensl_write(p,(short *)buff, len / 2);
       }
}

void change_pause(int value){
	pthread_mutex_lock( &cond_mutex );

	isPause = value;

        if(!isPause)
           pthread_cond_signal( &condition_var );


	pthread_mutex_unlock( &cond_mutex );
}

void myosd_check_pause(void){

	pthread_mutex_lock( &cond_mutex );

	while(isPause)
	{
	     myosd_pause = 1;
             pthread_cond_wait( &condition_var, &cond_mutex );
	}
        myosd_pause = 0;
	pthread_mutex_unlock( &cond_mutex );
}
