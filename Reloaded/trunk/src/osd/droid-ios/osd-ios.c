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
#include "wiimote.h"

#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

#import <AudioToolbox/AudioQueue.h>
#import <AudioToolbox/AudioToolbox.h>

/* Audio Resources */
//minimum required buffers for iOS AudioQueue

#define AUDIO_BUFFERS 3

int  myosd_fps = 1;
int  myosd_showinfo = 0;
int  myosd_sleep = 1;
int  myosd_inGame = 0;
int  myosd_exitGame = 0;
int  myosd_exitPause = 0;
int  myosd_last_game_selected = 0;
int  myosd_frameskip_value = -1;
int  myosd_sound_value = 44100;
int  myosd_throttle = 1;
int  myosd_cheat = 1;
int  myosd_autosave = 0;
int  myosd_savestate = 0;
int  myosd_loadstate = 0;
int  myosd_waysStick = 8;
int  myosd_video_width = 320;
int  myosd_video_height = 240;
int  myosd_vis_video_width = 320;
int  myosd_vis_video_height = 240;
int  myosd_in_menu = 0;
int  myosd_res = 1;
int  myosd_force_pxaspect = 0;

int num_of_joys=0;

int m4all_BplusX = 0;
int m4all_hide_LR = 0;
int m4all_landscape_buttons = 4;

/*extern */float joy_analog_x[4];
/*extern */float joy_analog_y[4];


static int lib_inited = 0;
static int soundInit = 0;
static int isPause = 0;
static int videot_running = 0;
static int dbl_buff = 1;

unsigned long myosd_pad_status = 0;
unsigned long myosd_joy_status[4];

static unsigned short myosd_screen [1024 * 768 * 4];
unsigned short 	*myosd_screen15 = NULL;

extern unsigned short img_buffer[1024 * 768 * 4];

typedef struct AQCallbackStruct {
    AudioQueueRef queue;
    UInt32 frameCount;
    AudioQueueBufferRef mBuffers[AUDIO_BUFFERS];
    AudioStreamBasicDescription mDataFormat;
} AQCallbackStruct;

AQCallbackStruct in;

static pthread_t main_tid;
static pthread_mutex_t cond_mutex     = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  condition_var   = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t sound_mutex     = PTHREAD_MUTEX_INITIALIZER;

extern int video_thread_priority;
extern int video_thread_priority_type;

extern void iphone_UpdateScreen(void);
extern void iphone_Reset_Views(void);
extern "C" void droid_ios_video_thread(void);

void change_pause(int value);
void* threaded_video(void* args);
int sound_close_AudioQueue(void);
int sound_open_AudioQueue(int rate, int bits, int stereo);
void queue(unsigned char *p,unsigned size);
unsigned short dequeue(unsigned char *p,unsigned size);
inline int emptyQueue(void);


static void dump_video(void)
{


    if(dbl_buff && myosd_screen15!=NULL && img_buffer!=NULL)
	   memcpy(img_buffer,myosd_screen15, myosd_video_width * myosd_video_height * 2);

	iphone_UpdateScreen();
}

/////////////

void myosd_video_flip(void)
{
	dump_video();
}

void myosd_set_video_mode(int width,int height,int vis_width,int vis_height)
{

     printf("myosd_set_video_mode: %d %d \n",width,height);

     myosd_video_width = width;
     myosd_video_height = height;
     myosd_vis_video_width = vis_width;
     myosd_vis_video_height = vis_height;

     iphone_Reset_Views();

     //if(myosd_screen15!=NULL)
	    //memset(myosd_screen15, 0, width*height*2);

  	 myosd_video_flip();
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
		res |= iOS_wiimote_check(&joys[n]);
		res |= myosd_joy_status[n];
	}
  	
	return res;
}

void myosd_init(void)
{
	int res = 0;
	struct sched_param param;

	if (!lib_inited )
    {
	   printf("myosd_init\n");

	   myosd_set_video_mode(320,240,320,240);

	   if(dbl_buff)
	      myosd_screen15 = myosd_screen;
	   else
	      myosd_screen15 = img_buffer;

	   if(videot_running==0)
	   {
		   res = pthread_create(&main_tid, NULL, threaded_video, NULL);
		   if(res!=0)printf("Error setting creating pthread %d \n",res);

		   //param.sched_priority = 67;
		   //param.sched_priority = 50;
		   //param.sched_priority = 46;
		   //param.sched_priority = 100;

		    param.sched_priority = video_thread_priority;
		    int policy;
		    if(video_thread_priority_type == 1)
		      policy = SCHED_OTHER;
		    else if(video_thread_priority_type == 2)
		      policy = SCHED_RR;
		    else
		      policy = SCHED_FIFO;

		   if(pthread_setschedparam(main_tid, policy, &param) != 0)
			  printf("Error setting pthread priority\n");
		   videot_running = 1;
	   }

   	   lib_inited = 1;
    }
}

void myosd_deinit(void)
{
    if (lib_inited )
    {
		printf("myosd_deinit\n");

    	lib_inited = 0;
    }
}

void myosd_closeSound(void) {
	if( soundInit == 1 )
	{
		printf("myosd_closeSound\n");

		sound_close_AudioQueue();

	   	soundInit = 0;
	}
}

void myosd_openSound(int rate,int stereo) {
	if( soundInit == 0)
	{
		printf("myosd_openSound rate:%d stereo:%d \n",rate,stereo);

		sound_open_AudioQueue(rate, 16, stereo);

		soundInit = 1;
	}
}

void myosd_sound_play(void *buff, int len)
{
	queue((unsigned char *)buff,len);
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

void* threaded_video(void* args)
{
	droid_ios_video_thread();
	return 0;
}

/////////////

//SQ buffers for sound between MAME and iOS AudioQueue. AudioQueue
//SQ callback reads from these.
//SQ Size: (44100/30fps) * bytesize * stereo * (3 buffers)
#define TAM (1470 * 2 * 2 * 3)
unsigned char ptr_buf[TAM];
unsigned head = 0;
unsigned tail = 0;

inline int fullQueue(unsigned short size){

    if(head < tail)
	{
		return head + size >= tail;
	}
	else if(head > tail)
	{
		return (head + size) >= TAM ? (head + size)- TAM >= tail : false;
	}
	else return false;
}

inline int emptyQueue(){
	return head == tail;
}

void queue(unsigned char *p,unsigned size){
        unsigned newhead;
		if(head + size < TAM)
		{
			memcpy(ptr_buf+head,p,size);
			newhead = head + size;
		}
		else
		{
			memcpy(ptr_buf+head,p, TAM -head);
			memcpy(ptr_buf,p + (TAM-head), size - (TAM-head));
			newhead = (head + size) - TAM;
		}
		pthread_mutex_lock(&sound_mutex);

		head = newhead;

		pthread_mutex_unlock(&sound_mutex);
}

unsigned short dequeue(unsigned char *p,unsigned size){

    	unsigned real;
    	unsigned datasize;

		if(emptyQueue())
		{
	    	memset(p,0,size);//TODO ver si quito para que no petardee
			return size;
		}

		pthread_mutex_lock(&sound_mutex);

		datasize = head > tail ? head - tail : (TAM - tail) + head ;
		real = datasize > size ? size : datasize;

		if(tail + real < TAM)
		{
			memcpy(p,ptr_buf+tail,real);
			tail+=real;
		}
		else
		{
			memcpy(p,ptr_buf + tail, TAM - tail);
			memcpy(p+ (TAM-tail),ptr_buf , real - (TAM-tail));
			tail = (tail + real) - TAM;
		}

		pthread_mutex_unlock(&sound_mutex);

        return real;
}

void checkStatus(OSStatus status){}

/*
int audioBufferSize = 480000*2;

#define BUF (audioBufferSize )

static void AQBufferCallback(
							 void *userdata,
							 AudioQueueRef outQ,
							 AudioQueueBufferRef outQB)
{
	unsigned char *coreAudioBuffer;
	int res;
	coreAudioBuffer = (unsigned char*) outQB->mAudioData;

	res = dequeue(coreAudioBuffer,BUF);
	outQB->mAudioDataByteSize = res;

	AudioQueueEnqueueBuffer(outQ, outQB, 0, NULL);
}
*/


static void AQBufferCallback(void *userdata,
							 AudioQueueRef outQ,
							 AudioQueueBufferRef outQB)
{
	unsigned char *coreAudioBuffer;
	coreAudioBuffer = (unsigned char*) outQB->mAudioData;

	dequeue(coreAudioBuffer, in.mDataFormat.mBytesPerFrame * in.frameCount);
	outQB->mAudioDataByteSize = in.mDataFormat.mBytesPerFrame * in.frameCount;

	AudioQueueEnqueueBuffer(outQ, outQB, 0, NULL);
}


int sound_close_AudioQueue(){

	if( soundInit == 1 )
	{
		AudioQueueDispose(in.queue, true);
		soundInit = 0;
        head = 0;
        tail = 0;
	}
	return 0;
}

/*
int sound_open_AudioQueue(int rate, int bits, int stereo){

    Float64 sampleRate = 48000.0;
    int i;
    UInt32 err;

    if(rate==44100)
    	sampleRate = 44100.0;
    if(rate==32000)
    	sampleRate = 32000.0;
    else if(rate==22050)
    	sampleRate = 22050.0;
    else if(rate==11025)
    	sampleRate = 11025.0;

    audioBufferSize =  (rate / 60) * 2 * (stereo==1 ? 2 : 1) ;

    //audioBufferSize = 882 * 2 * 2;
    //printf("%d %d %d %f\n",rate,bits,stereo,sampleRate);
    //printf("audio buffer size %d\n",audioBufferSize);

    if( soundInit == 1 )
    {
    	sound_close_AudioQueue();
    }


    soundInit = 0;
    memset (&in.mDataFormat, 0, sizeof (in.mDataFormat));
    in.mDataFormat.mSampleRate = sampleRate;
    in.mDataFormat.mFormatID = kAudioFormatLinearPCM;
    in.mDataFormat.mFormatFlags = kLinearPCMFormatFlagIsSignedInteger  | kAudioFormatFlagIsPacked;
    in.mDataFormat.mBytesPerPacket =  (stereo == 1 ? 4 : 2 );
    in.mDataFormat.mFramesPerPacket = 1;
    in.mDataFormat.mBytesPerFrame = (stereo ==  1? 4 : 2);
    in.mDataFormat.mChannelsPerFrame = (stereo == 1 ? 2 : 1);
    in.mDataFormat.mBitsPerChannel = 16;

    err = AudioQueueNewOutput(&in.mDataFormat,
							  AQBufferCallback,
							  NULL,
							  NULL,
							  kCFRunLoopCommonModes,
							  0,
							  &in.queue);

    //printf("res %ld",err);


	for (i=0; i<AUDIO_BUFFERS; i++)
	{
		err = AudioQueueAllocateBuffer(in.queue, BUF, &in.mBuffers[i]);
		//printf("res %ld",err);
		in.mBuffers[i]->mAudioDataByteSize = BUF;
		AudioQueueEnqueueBuffer(in.queue, in.mBuffers[i], 0, NULL);
	}

	soundInit = 1;
	err = AudioQueueStart(in.queue, NULL);

	return 0;

}
*/


int sound_open_AudioQueue(int rate, int bits, int stereo){

    Float64 sampleRate = 48000.0;
    int i;
    UInt32 err;
    int fps;
    int bufferSize;

    if(rate==44100)
    	sampleRate = 44100.0;
    if(rate==32000)
    	sampleRate = 32000.0;
    else if(rate==22050)
    	sampleRate = 22050.0;
    else if(rate==11025)
    	sampleRate = 11025.0;

	//SQ Roundup for games like Galaxians
    //fps = ceil(Machine->drv->frames_per_second);
    fps = 60;//TODO

    if( soundInit == 1 )
    {
    	sound_close_AudioQueue();
    }

    soundInit = 0;
    memset (&in.mDataFormat, 0, sizeof (in.mDataFormat));
    in.mDataFormat.mSampleRate = sampleRate;
    in.mDataFormat.mFormatID = kAudioFormatLinearPCM;
    in.mDataFormat.mFormatFlags = kLinearPCMFormatFlagIsSignedInteger  | kAudioFormatFlagIsPacked;
    in.mDataFormat.mBytesPerPacket =  (stereo == 1 ? 4 : 2 );
    in.mDataFormat.mFramesPerPacket = 1;
    in.mDataFormat.mBytesPerFrame = (stereo ==  1? 4 : 2);
    in.mDataFormat.mChannelsPerFrame = (stereo == 1 ? 2 : 1);
    in.mDataFormat.mBitsPerChannel = 16;
	in.frameCount = rate / fps;

    err = AudioQueueNewOutput(&in.mDataFormat,
							  AQBufferCallback,
							  NULL,
							  NULL,
							  kCFRunLoopCommonModes,
							  0,
							  &in.queue);

    //printf("res %ld",err);

    bufferSize = in.frameCount * in.mDataFormat.mBytesPerFrame;

	for (i=0; i<AUDIO_BUFFERS; i++)
	{
		err = AudioQueueAllocateBuffer(in.queue, bufferSize, &in.mBuffers[i]);
		in.mBuffers[i]->mAudioDataByteSize = bufferSize;
		AudioQueueEnqueueBuffer(in.queue, in.mBuffers[i], 0, NULL);
	}

	soundInit = 1;
	err = AudioQueueStart(in.queue, NULL);

	return 0;

}

