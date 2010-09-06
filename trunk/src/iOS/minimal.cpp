/*

  GP2X minimal library v0.A by rlyeh, (c) 2005. emulnation.info@rlyeh (swap it!)

  Thanks to Squidge, Robster, snaff, Reesy and NK, for the help & previous work! :-)

  License
  =======

  Free for non-commercial projects (it would be nice receiving a mail from you).
  Other cases, ask me first.

  GamePark Holdings is not allowed to use this library and/or use parts from it.

*/


#include "minimal.h"
#include "wiimote.h"

#include <unistd.h>
#include <fcntl.h>

#import <AudioToolbox/AudioQueue.h>
#import <AudioUnit/AudioUnit.h>
#import <AudioToolbox/AudioToolbox.h>
#import <pthread.h>

/* Audio Resources */
#define AUDIO_BUFFERS 12
//12 o 6

extern "C" void app_MuteSound(void);
extern "C" void app_DemuteSound(void);
extern "C" void iphone_UpdateScreen(void);
extern "C" void iphone_Reset_Views(void);

int iOS_video_width = 320;
int iOS_video_height = 240;

typedef struct AQCallbackStruct {
    AudioQueueRef queue;
    UInt32 frameCount;
    AudioQueueBufferRef mBuffers[AUDIO_BUFFERS];
    AudioStreamBasicDescription mDataFormat;
} AQCallbackStruct;

typedef unsigned char byte;
extern unsigned short *screenbuffer;
extern int global_low_latency_sound;

extern int soundcard;

int audioBufferSize = 44100*2;
AQCallbackStruct in;
int soundInit = 0;
struct timeval ptv;
float __audioVolume = 1.0;


unsigned long 			gp2x_dev[3];
static unsigned long 		gp2x_ticks_per_second;
unsigned char 			*gp2x_screen8;
unsigned short 			*gp2x_screen15;
unsigned short 			*gp2x_logvram15[2];
unsigned long 			gp2x_physvram[2];
unsigned int			gp2x_nflip;
unsigned short 	gp2x_palette[512];
int				gp2x_sound_rate=44100;
int				gp2x_sound_stereo=0;
int 				gp2x_pal_50hz=0;
int				gp2x_ram_tweaks=0;
int 				rotate_controls=0;

unsigned char  			*gp2x_dualcore_ram;
unsigned long  			 gp2x_dualcore_ram_size;

unsigned long gp2x_pad_status = 0;

#define MAX_SAMPLE_RATE (44100*2)

void gp2x_video_flip(void)
{
	iphone_UpdateScreen();
}

void gp2x_video_flip_single(void)
{
	iphone_UpdateScreen();
}


void gp2x_video_setpalette(void)
{
}

/*
int master_volume;
*/

unsigned long gp2x_joystick_read(int n)
{
  unsigned long res=0;
	res = gp2x_pad_status;
		
	/* GP2X F200 Push Button */
	if ((res & GP2X_VOL_UP) && (res & GP2X_VOL_DOWN))
	  		res |= GP2X_PUSH;

	if (num_of_joys>n)
	{
	  	/* Check USB Joypad */
		//printf("%d %d\n",num_of_joys,n);
		res |= iOS_wiimote_check(&joys[n]);
	}
  	
	return res;
}

unsigned long gp2x_joystick_press (int n)
{
	unsigned long ExKey=0;
	/*
	while(gp2x_joystick_read(n)&0x8c0ff55) { gp2x_timer_delay(150); }
	while(!(ExKey=gp2x_joystick_read(n)&0x8c0ff55)) { }
	*/
	while(gp2x_joystick_read(n)==0) { gp2x_timer_delay(150); }
	//while(!(ExKey=gp2x_joystick_read(n))) { }


    //while(!(ExKey & (JOY_BUTTON_X|JOY_BUTTON_B))) {nKeys = joystick_read();gp2x_timer_delay(150);} // para quieto!!
    //while(ExKey & (JOY_BUTTON_X|JOY_BUTTON_B)) {nKeys = joystick_read(); gp2x_timer_delay(150);} // para quieto!!

	return ExKey;
}

void gp2x_sound_volume(int l, int r)
{
	//__audioVolume = l;
}


void gp2x_timer_delay(unsigned long ticks)
{
	unsigned long long ini=gp2x_timer_read();
	//printf("ini %ld %ld %d\n",gp2x_timer_read(),ini,(gp2x_timer_read()-ini));
	while (gp2x_timer_read()-ini<ticks){/*nope*/};
}


unsigned long long gp2x_timer_read(void)
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	
	return ((unsigned long long)current_time.tv_sec * 1000LL + (current_time.tv_usec / 1000LL));
}

unsigned long long gp2x_timer_read_real(void)
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	
	return (((unsigned long long)current_time.tv_sec * 1000000LL + current_time.tv_usec));
}

unsigned long gp2x_timer_read_scale(void)
{
 	return gp2x_ticks_per_second;
}

void gp2x_timer_profile(void)
{
}



#if defined(__cplusplus)
extern "C" {
#endif
extern int fcloseall(void);
#if defined(__cplusplus)
}
#endif



void gp2x_set_clock(int mhz)
{
}

void gp2x_set_video_mode(int bpp,int width,int height)
{

	//if(iOS_video_width!=width || iOS_video_height!=height)
	//{
	  iOS_video_width = width;
	  iOS_video_height = height;

	  iphone_Reset_Views();
	//}

	memset(gp2x_screen15, 0, iOS_video_width*iOS_video_height*2);

  	gp2x_video_flip();

  	gp2x_video_flip_single();

	gp2x_pal_50hz=0;
}

void set_ram_tweaks(void)
{
}

static unsigned char fontdata8x8[] =
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x3C,0x42,0x99,0xBD,0xBD,0x99,0x42,0x3C,0x3C,0x42,0x81,0x81,0x81,0x81,0x42,0x3C,
	0xFE,0x82,0x8A,0xD2,0xA2,0x82,0xFE,0x00,0xFE,0x82,0x82,0x82,0x82,0x82,0xFE,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x64,0x74,0x7C,0x38,0x00,0x00,
	0x80,0xC0,0xF0,0xFC,0xF0,0xC0,0x80,0x00,0x01,0x03,0x0F,0x3F,0x0F,0x03,0x01,0x00,
	0x18,0x3C,0x7E,0x18,0x7E,0x3C,0x18,0x00,0xEE,0xEE,0xEE,0xCC,0x00,0xCC,0xCC,0x00,
	0x00,0x00,0x30,0x68,0x78,0x30,0x00,0x00,0x00,0x38,0x64,0x74,0x7C,0x38,0x00,0x00,
	0x3C,0x66,0x7A,0x7A,0x7E,0x7E,0x3C,0x00,0x0E,0x3E,0x3A,0x22,0x26,0x6E,0xE4,0x40,
	0x18,0x3C,0x7E,0x3C,0x3C,0x3C,0x3C,0x00,0x3C,0x3C,0x3C,0x3C,0x7E,0x3C,0x18,0x00,
	0x08,0x7C,0x7E,0x7E,0x7C,0x08,0x00,0x00,0x10,0x3E,0x7E,0x7E,0x3E,0x10,0x00,0x00,
	0x58,0x2A,0xDC,0xC8,0xDC,0x2A,0x58,0x00,0x24,0x66,0xFF,0xFF,0x66,0x24,0x00,0x00,
	0x00,0x10,0x10,0x38,0x38,0x7C,0xFE,0x00,0xFE,0x7C,0x38,0x38,0x10,0x10,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x1C,0x1C,0x18,0x00,0x18,0x18,0x00,
	0x6C,0x6C,0x24,0x00,0x00,0x00,0x00,0x00,0x00,0x28,0x7C,0x28,0x7C,0x28,0x00,0x00,
	0x10,0x38,0x60,0x38,0x0C,0x78,0x10,0x00,0x40,0xA4,0x48,0x10,0x24,0x4A,0x04,0x00,
	0x18,0x34,0x18,0x3A,0x6C,0x66,0x3A,0x00,0x18,0x18,0x20,0x00,0x00,0x00,0x00,0x00,
	0x30,0x60,0x60,0x60,0x60,0x60,0x30,0x00,0x0C,0x06,0x06,0x06,0x06,0x06,0x0C,0x00,
	0x10,0x54,0x38,0x7C,0x38,0x54,0x10,0x00,0x00,0x18,0x18,0x7E,0x18,0x18,0x00,0x00,
	0x00,0x00,0x00,0x00,0x18,0x18,0x30,0x00,0x00,0x00,0x00,0x00,0x3E,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x04,0x08,0x10,0x20,0x40,0x00,0x00,
	0x38,0x4C,0xC6,0xC6,0xC6,0x64,0x38,0x00,0x18,0x38,0x18,0x18,0x18,0x18,0x7E,0x00,
	0x7C,0xC6,0x0E,0x3C,0x78,0xE0,0xFE,0x00,0x7E,0x0C,0x18,0x3C,0x06,0xC6,0x7C,0x00,
	0x1C,0x3C,0x6C,0xCC,0xFE,0x0C,0x0C,0x00,0xFC,0xC0,0xFC,0x06,0x06,0xC6,0x7C,0x00,
	0x3C,0x60,0xC0,0xFC,0xC6,0xC6,0x7C,0x00,0xFE,0xC6,0x0C,0x18,0x30,0x30,0x30,0x00,
	0x78,0xC4,0xE4,0x78,0x86,0x86,0x7C,0x00,0x7C,0xC6,0xC6,0x7E,0x06,0x0C,0x78,0x00,
	0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x18,0x18,0x30,
	0x1C,0x38,0x70,0xE0,0x70,0x38,0x1C,0x00,0x00,0x7C,0x00,0x00,0x7C,0x00,0x00,0x00,
	0x70,0x38,0x1C,0x0E,0x1C,0x38,0x70,0x00,0x7C,0xC6,0xC6,0x1C,0x18,0x00,0x18,0x00,
	0x3C,0x42,0x99,0xA1,0xA5,0x99,0x42,0x3C,0x38,0x6C,0xC6,0xC6,0xFE,0xC6,0xC6,0x00,
	0xFC,0xC6,0xC6,0xFC,0xC6,0xC6,0xFC,0x00,0x3C,0x66,0xC0,0xC0,0xC0,0x66,0x3C,0x00,
	0xF8,0xCC,0xC6,0xC6,0xC6,0xCC,0xF8,0x00,0xFE,0xC0,0xC0,0xFC,0xC0,0xC0,0xFE,0x00,
	0xFE,0xC0,0xC0,0xFC,0xC0,0xC0,0xC0,0x00,0x3E,0x60,0xC0,0xCE,0xC6,0x66,0x3E,0x00,
	0xC6,0xC6,0xC6,0xFE,0xC6,0xC6,0xC6,0x00,0x7E,0x18,0x18,0x18,0x18,0x18,0x7E,0x00,
	0x06,0x06,0x06,0x06,0xC6,0xC6,0x7C,0x00,0xC6,0xCC,0xD8,0xF0,0xF8,0xDC,0xCE,0x00,
	0x60,0x60,0x60,0x60,0x60,0x60,0x7E,0x00,0xC6,0xEE,0xFE,0xFE,0xD6,0xC6,0xC6,0x00,
	0xC6,0xE6,0xF6,0xFE,0xDE,0xCE,0xC6,0x00,0x7C,0xC6,0xC6,0xC6,0xC6,0xC6,0x7C,0x00,
	0xFC,0xC6,0xC6,0xC6,0xFC,0xC0,0xC0,0x00,0x7C,0xC6,0xC6,0xC6,0xDE,0xCC,0x7A,0x00,
	0xFC,0xC6,0xC6,0xCE,0xF8,0xDC,0xCE,0x00,0x78,0xCC,0xC0,0x7C,0x06,0xC6,0x7C,0x00,
	0x7E,0x18,0x18,0x18,0x18,0x18,0x18,0x00,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x7C,0x00,
	0xC6,0xC6,0xC6,0xEE,0x7C,0x38,0x10,0x00,0xC6,0xC6,0xD6,0xFE,0xFE,0xEE,0xC6,0x00,
	0xC6,0xEE,0x3C,0x38,0x7C,0xEE,0xC6,0x00,0x66,0x66,0x66,0x3C,0x18,0x18,0x18,0x00,
	0xFE,0x0E,0x1C,0x38,0x70,0xE0,0xFE,0x00,0x3C,0x30,0x30,0x30,0x30,0x30,0x3C,0x00,
	0x60,0x60,0x30,0x18,0x0C,0x06,0x06,0x00,0x3C,0x0C,0x0C,0x0C,0x0C,0x0C,0x3C,0x00,
	0x18,0x3C,0x66,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
	0x30,0x30,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x06,0x3E,0x66,0x66,0x3C,0x00,
	0x60,0x7C,0x66,0x66,0x66,0x66,0x7C,0x00,0x00,0x3C,0x66,0x60,0x60,0x66,0x3C,0x00,
	0x06,0x3E,0x66,0x66,0x66,0x66,0x3E,0x00,0x00,0x3C,0x66,0x66,0x7E,0x60,0x3C,0x00,
	0x1C,0x30,0x78,0x30,0x30,0x30,0x30,0x00,0x00,0x3E,0x66,0x66,0x66,0x3E,0x06,0x3C,
	0x60,0x7C,0x76,0x66,0x66,0x66,0x66,0x00,0x18,0x00,0x38,0x18,0x18,0x18,0x18,0x00,
	0x0C,0x00,0x1C,0x0C,0x0C,0x0C,0x0C,0x38,0x60,0x60,0x66,0x6C,0x78,0x6C,0x66,0x00,
	0x38,0x18,0x18,0x18,0x18,0x18,0x18,0x00,0x00,0xEC,0xFE,0xFE,0xFE,0xD6,0xC6,0x00,
	0x00,0x7C,0x76,0x66,0x66,0x66,0x66,0x00,0x00,0x3C,0x66,0x66,0x66,0x66,0x3C,0x00,
	0x00,0x7C,0x66,0x66,0x66,0x7C,0x60,0x60,0x00,0x3E,0x66,0x66,0x66,0x3E,0x06,0x06,
	0x00,0x7E,0x70,0x60,0x60,0x60,0x60,0x00,0x00,0x3C,0x60,0x3C,0x06,0x66,0x3C,0x00,
	0x30,0x78,0x30,0x30,0x30,0x30,0x1C,0x00,0x00,0x66,0x66,0x66,0x66,0x6E,0x3E,0x00,
	0x00,0x66,0x66,0x66,0x66,0x3C,0x18,0x00,0x00,0xC6,0xD6,0xFE,0xFE,0x7C,0x6C,0x00,
	0x00,0x66,0x3C,0x18,0x3C,0x66,0x66,0x00,0x00,0x66,0x66,0x66,0x66,0x3E,0x06,0x3C,
	0x00,0x7E,0x0C,0x18,0x30,0x60,0x7E,0x00,0x0E,0x18,0x0C,0x38,0x0C,0x18,0x0E,0x00,
	0x18,0x18,0x18,0x00,0x18,0x18,0x18,0x00,0x70,0x18,0x30,0x1C,0x30,0x18,0x70,0x00,
	0x00,0x00,0x76,0xDC,0x00,0x00,0x00,0x00,0x10,0x28,0x10,0x54,0xAA,0x44,0x00,0x00,
};

static void gp2x_text(unsigned short *screen, int x, int y, char *text, int color)
{
	unsigned int i,l;
	screen=screen+x+y*320;

	for (i=0;i<strlen(text);i++) {
		
		for (l=0;l<8;l++) {
			screen[l*320+0]=(fontdata8x8[((text[i])*8)+l]&0x80)?gp2x_palette[color]:screen[l*320+0];
			screen[l*320+1]=(fontdata8x8[((text[i])*8)+l]&0x40)?gp2x_palette[color]:screen[l*320+1];
			screen[l*320+2]=(fontdata8x8[((text[i])*8)+l]&0x20)?gp2x_palette[color]:screen[l*320+2];
			screen[l*320+3]=(fontdata8x8[((text[i])*8)+l]&0x10)?gp2x_palette[color]:screen[l*320+3];
			screen[l*320+4]=(fontdata8x8[((text[i])*8)+l]&0x08)?gp2x_palette[color]:screen[l*320+4];
			screen[l*320+5]=(fontdata8x8[((text[i])*8)+l]&0x04)?gp2x_palette[color]:screen[l*320+5];
			screen[l*320+6]=(fontdata8x8[((text[i])*8)+l]&0x02)?gp2x_palette[color]:screen[l*320+6];
			screen[l*320+7]=(fontdata8x8[((text[i])*8)+l]&0x01)?gp2x_palette[color]:screen[l*320+7];
		}
		screen+=8;
	} 
}

void gp2x_gamelist_text_out(int x, int y, char *eltexto)
{
	char texto[33];
	strncpy(texto,eltexto,32);
	texto[32]=0;
	if (texto[0]!='-')
		gp2x_text(gp2x_screen15,x+1,y+1,texto,0);
	gp2x_text(gp2x_screen15,x,y,texto,255);
}

/* Variadic functions guide found at http://www.unixpapa.com/incnote/variadic.html */
void gp2x_gamelist_text_out_fmt(int x, int y, char* fmt, ...)
{
	char strOut[128];
	va_list marker;
	
	va_start(marker, fmt);
	vsprintf(strOut, fmt, marker);
	va_end(marker);	

	gp2x_gamelist_text_out(x, y, strOut);
}

static int pflog=0;

void gp2x_printf_init(void)
{
	pflog=0;
}

static void gp2x_text_log(char *texto)
{
	if (!pflog)
	{
		memset(gp2x_screen15,0,320*240*2);
	}
	gp2x_text(gp2x_screen15,0,pflog,texto,255);
	pflog+=8;
	if(pflog>239) pflog=0;
}

/* Variadic functions guide found at http://www.unixpapa.com/incnote/variadic.html */
void gp2x_printf(char* fmt, ...)
{
	int i,c;
	char strOut[4096];
	char str[41];
	va_list marker;
	
	va_start(marker, fmt);
	vsprintf(strOut, fmt, marker);
	va_end(marker);	

	fprintf(stderr, "%s\n", strOut);
	
	c=0;
	for (i=0;i<strlen(strOut);i++)
	{
		str[c]=strOut[i];
		if (str[c]=='\n')
		{
			str[c]=0;
			gp2x_text_log(str);
			c=0;
		}
		else if (c==39)
		{
			str[40]=0;
			gp2x_text_log(str);
			c=0;
		}		
		else
		{
			c++;
		}
	}
}


static short gp2x_sound_buffers_total[256*1024];					// Sound buffer


void gp2x_sound_thread_mute(void)
{
	memset(gp2x_sound_buffers_total,0,audioBufferSize);
}
/////
/*
void gp2x_sound_play(void *buff, int len)
{
	memcpy(gp2x_sound_buffers_total,buff,len);					// Write the sound buffer
}


static void gp2x_sound_thread_play(void *buffer, int size)
{
	memcpy(buffer, gp2x_sound_buffers_total, size);
}

static void AQBufferCallback(
							 void *userdata,
							 AudioQueueRef outQ,
							 AudioQueueBufferRef outQB)
{
	unsigned char *coreAudioBuffer;
	coreAudioBuffer = (unsigned char*) outQB->mAudioData;
	
	outQB->mAudioDataByteSize = audioBufferSize;
	AudioQueueSetParameter(outQ, kAudioQueueParam_Volume, __audioVolume);	
	gp2x_sound_thread_play(coreAudioBuffer, audioBufferSize);
	AudioQueueEnqueueBuffer(outQ, outQB, 0, NULL);
}


int app_OpenSound(int samples_per_sync, int sample_rate) {
    Float64 sampleRate = 44100.0;
    int i;
    UInt32 bufferBytes;
	
    app_MuteSound();
	
    soundInit = 0;
	
    in.mDataFormat.mSampleRate = sampleRate;
    in.mDataFormat.mFormatID = kAudioFormatLinearPCM;
    in.mDataFormat.mFormatFlags = kLinearPCMFormatFlagIsSignedInteger
	| kAudioFormatFlagIsPacked;
    in.mDataFormat.mBytesPerPacket = 4;
    in.mDataFormat.mFramesPerPacket = 2;
    in.mDataFormat.mBytesPerFrame = 2;
    in.mDataFormat.mChannelsPerFrame = 1;
    in.mDataFormat.mBitsPerChannel = 16;
	
    // Pre-buffer before we turn on audio
    UInt32 err;
    err = AudioQueueNewOutput(&in.mDataFormat,
							  AQBufferCallback,
							  NULL,
							  NULL,
							  kCFRunLoopCommonModes,
							  0,
							  &in.queue);
	
	bufferBytes = audioBufferSize;
	
	for (i=0; i<AUDIO_BUFFERS; i++) 
	{
		err = AudioQueueAllocateBuffer(in.queue, bufferBytes, &in.mBuffers[i]);
		//"Prime" by calling the callback once per buffer
		//AQBufferCallback (&in, in.queue, in.mBuffers[i]);
		in.mBuffers[i]->mAudioDataByteSize = audioBufferSize; //samples_per_frame * 2; //inData->mDataFormat.mBytesPerFrame; //(inData->frameCount * 4 < (sndOutLen) ? inData->frameCount * 4 : (sndOutLen));
		AudioQueueEnqueueBuffer(in.queue, in.mBuffers[i], 0, NULL);
	}
	
	soundInit = 1;
	err = AudioQueueStart(in.queue, NULL);
	
	return 0;
}

void app_CloseSound(void) {
	if( soundInit == 1 )
	{
		AudioQueueDispose(in.queue, true);
		soundInit = 0;
	}
}

extern "C" void app_MuteSound(void) {
	if( soundInit == 1 )
	{
		app_CloseSound();
	}
}

extern "C" void app_DemuteSound(void) {
	if( soundInit == 0 )
	{
		app_OpenSound(1, 44100);
	}
}
*/
////
void gp2x_sound_thread_start(int len)
{
	audioBufferSize = len;
	//fprintf(stderr,"audio buffer size %d \n", audioBufferSize);
	gp2x_sound_thread_mute();
}

void gp2x_sound_thread_stop(void)
{
}

void gp2x_sound_set_rate(int rate)
{
}

void gp2x_sound_set_stereo(int stereo)
{
}

void gp2x_video_wait_vsync()
{
}

extern "C" void set_save_state()
{
}


////////////////////////////////////

static int lib_inited = 0;

pthread_mutex_t mut;

void gp2x_init(int ticks_per_second, int bpp, int rate, int bits, int stereo, int Hz)
{

    if (!lib_inited )
    {

       gp2x_ticks_per_second=1000;

	   //gp2x_screen15=screenbuffer;
	   //gp2x_screen8=(unsigned char *)screenbuffer;
	   gp2x_nflip=0;

	   gp2x_set_video_mode(bpp,320,240);

	   gp2x_video_color8(0,0,0,0);
	   gp2x_video_color8(255,255,255,255);
	   gp2x_video_setpalette();

	   /* atexit(gp2x_deinit); */
	   //app_DemuteSound();

	   pthread_mutex_init (&mut,NULL);
   	   lib_inited = 1;
    }
}

void gp2x_deinit(void)
{
    if (lib_inited )
    {
	   //memset(gp2x_screen15, 0, 320*240*2); gp2x_video_flip();

    	pthread_mutex_destroy(&mut);
        lib_inited = 0;
    }
}

/// QUEUE
//TODO quidado.. que va a 60hz no a 50
//#define TAM (882 * 2 * 2 * 6)
#define TAM (256*1024)
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
/*
		if(fullQueue(size))
		{

			do
		    {
		    	usleep(100);
		    }
		    while (fullQueue(size));
		}
*/
/*
	   if(fullQueue(size))
	   {
		    if(head < tail)
			{
				//return head + size >= tail;
		    	size = (tail - head) - 1;
			}
			else if(head > tail)
			{
				//return (head + size) >= TAM ? (head + size)- TAM >= tail : false;
				size = (TAM - head) + tail -1;
			}
	    }
*/
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
		pthread_mutex_lock(&mut);

		head = newhead;

		pthread_mutex_unlock(&mut);
}

unsigned short dequeue(unsigned char *p,unsigned size){

    	unsigned real;

		if(emptyQueue())
		{
	    	memset(p,0,size);//TODO ver si quito para que no petardee
			return size;
		}

		pthread_mutex_lock(&mut);

		unsigned datasize = head > tail ? head - tail : (TAM - tail) + head ;
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

		pthread_mutex_unlock(&mut);

        return real;
}

///////

#define kOutputBus 0
static AudioComponentInstance audioUnit;
int stereo_cached = 0;
int bits_cached = 16;
int rate_cached = 44100;


void checkStatus(OSStatus status){}

static OSStatus playbackCallback(void *inRefCon,
                                  AudioUnitRenderActionFlags *ioActionFlags,
                                  const AudioTimeStamp *inTimeStamp,
                                  UInt32 inBusNumber,
                                  UInt32 inNumberFrames,
                                  AudioBufferList *ioData) {
    // Notes: ioData contains buffers (may be more than one!)
    // Fill them up as much as you can. Remember to set the size value in each buffer to match how
    // much data is in the buffer.

	unsigned  char *coreAudioBuffer;

    int i;
    for (i = 0 ; i < ioData->mNumberBuffers; i++)
    {
      coreAudioBuffer = (unsigned char*) ioData->mBuffers[i].mData;
      ioData->mBuffers[i].mDataByteSize = dequeue(coreAudioBuffer,/*BUF*/stereo_cached ? inNumberFrames * 4: inNumberFrames * 2);
    }

    return noErr;
}

int sound_close_AudioUnit(){

	if( soundInit == 1 )
	{
		OSStatus status = AudioOutputUnitStop(audioUnit);
		checkStatus(status);

		AudioUnitUninitialize(audioUnit);
		soundInit = 0;
	}

	return 1;
}

int sound_open_AudioUnit(int rate, int bits, int stereo){
	    Float64 sampleRate = 44100.0;

	    stereo_cached = stereo;
	    rate_cached = rate;
	    bits_cached = bits;

	    if( soundInit == 1 )
	    {
	    	sound_close_AudioUnit();
	    }

	    if(rate==32000)
	    	sampleRate = 32000.0;
	    else if(rate==22050)
	    	sampleRate = 22050.0;
	    else if(rate==11025)
	    	sampleRate = 11025.0;

	    audioBufferSize =  (rate / 50) * 2 * (stereo==1 ? 2 : 1) ;

	    OSStatus status;

	    // Describe audio component
	    AudioComponentDescription desc;
	    desc.componentType = kAudioUnitType_Output;
	    desc.componentSubType = kAudioUnitSubType_RemoteIO;

	    desc.componentFlags = 0;
	    desc.componentFlagsMask = 0;
	    desc.componentManufacturer = kAudioUnitManufacturer_Apple;

	    // Get component
	    AudioComponent inputComponent = AudioComponentFindNext(NULL, &desc);

	    // Get audio units
	    status = AudioComponentInstanceNew(inputComponent, &audioUnit);
	    checkStatus(status);

	    UInt32 flag = 1;
	    // Enable IO for playback
	    status = AudioUnitSetProperty(audioUnit,
	                                  kAudioOutputUnitProperty_EnableIO,
	                                  kAudioUnitScope_Output,
	                                  kOutputBus,
	                                  &flag,
	                                  sizeof(flag));
	    checkStatus(status);

	    AudioStreamBasicDescription audioFormat;

	    memset (&audioFormat, 0, sizeof (audioFormat));

	    audioFormat.mSampleRate = sampleRate;
	    audioFormat.mFormatID = kAudioFormatLinearPCM;
	    audioFormat.mFormatFlags = kLinearPCMFormatFlagIsSignedInteger  | kAudioFormatFlagIsPacked;
	    audioFormat.mBytesPerPacket =  (stereo == 1 ? 4 : 2 );
	    audioFormat.mFramesPerPacket = 1;
	    audioFormat.mBytesPerFrame = (stereo ==  1? 4 : 2);
	    audioFormat.mChannelsPerFrame = (stereo == 1 ? 2 : 1);
	    audioFormat.mBitsPerChannel = 16;

	    status = AudioUnitSetProperty(audioUnit,
	                                  kAudioUnitProperty_StreamFormat,
	                                  kAudioUnitScope_Input,
	                                  kOutputBus,
	                                  &audioFormat,
	                                  sizeof(audioFormat));
	    checkStatus(status);

		struct AURenderCallbackStruct callbackStruct;
	    // Set output callback
	    callbackStruct.inputProc = playbackCallback;
	    callbackStruct.inputProcRefCon = NULL;
	    status = AudioUnitSetProperty(audioUnit,
	                                  kAudioUnitProperty_SetRenderCallback,
	                                  kAudioUnitScope_Global,
	                                  kOutputBus,
	                                  &callbackStruct,
	                                  sizeof(callbackStruct));
	    checkStatus(status);

	    status = AudioUnitInitialize(audioUnit);
	    checkStatus(status);

	    //ARANCAR
		soundInit = 1;
	    status = AudioOutputUnitStart(audioUnit);
	    checkStatus(status);

	    return 1;
}

#define BUF (audioBufferSize )

static void AQBufferCallback(
							 void *userdata,
							 AudioQueueRef outQ,
							 AudioQueueBufferRef outQB)
{
	unsigned char *coreAudioBuffer;
	coreAudioBuffer = (unsigned char*) outQB->mAudioData;

	//outQB->mAudioDataByteSize = BUF;
	//AudioQueueSetParameter(outQ, kAudioQueueParam_Volume, __audioVolume);

	int res = dequeue(coreAudioBuffer,BUF);
	outQB->mAudioDataByteSize = res;

	AudioQueueEnqueueBuffer(outQ, outQB, 0, NULL);
}


int sound_close_AudioQueue(){

	if( soundInit == 1 )
	{

		AudioQueueDispose(in.queue, true);
		soundInit = 0;
	}
}

int sound_open_AudioQueue(int rate, int bits, int stereo){

    Float64 sampleRate = 44100.0;
    int i;

    stereo_cached = stereo;
    rate_cached = rate;
    bits_cached = bits;

    if(rate==32000)
    	sampleRate = 32000.0;
    else if(rate==22050)
    	sampleRate = 22050.0;
    else if(rate==11025)
    	sampleRate = 11025.0;

    audioBufferSize =  (rate / 50) * 2 * (stereo==1 ? 2 : 1) ;

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


    printf("format %f %d %d %d %d %d\n",in.mDataFormat.mSampleRate,
    		in.mDataFormat.mBytesPerPacket,
    		in.mDataFormat.mFramesPerPacket,
    		in.mDataFormat.mBytesPerFrame,
    		in.mDataFormat.mChannelsPerFrame,
    		in.mDataFormat.mBitsPerChannel);

    /* Pre-buffer before we turn on audio */
    UInt32 err;
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

extern "C" void app_MuteSound(void) {
	if( soundInit == 1 )
	{
		if(global_low_latency_sound)
		   sound_close_AudioUnit();
		else
		   sound_close_AudioQueue();

	}
}

extern "C" void app_DemuteSound(void) {
	if( soundInit == 0 && soundcard!=0)
	{
		if(global_low_latency_sound)
	      sound_open_AudioUnit(gp2x_sound_rate/*rate_cached*/, bits_cached, gp2x_sound_stereo/*stereo_cached*/);
		else
		  sound_open_AudioQueue(gp2x_sound_rate/*rate_cached*/, bits_cached,gp2x_sound_stereo/* stereo_cached*/);

	}
}

void gp2x_sound_play(void *buff, int len)
{
	queue((unsigned char *)buff,len);
}

///END QUEUE
