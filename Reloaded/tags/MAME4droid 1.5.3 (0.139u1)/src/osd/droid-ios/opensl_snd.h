//============================================================
//
//  opensl_snd.c - Implementation of osd stuff
//
//  Copyright (c) 1996-2007, Nicola Salmoria and the MAME Team.
//  Visit http://mamedev.org for licensing and usage restrictions.
//
//  MAME4DROID MAME4iOS by David Valdeita (Seleuco)
//
//============================================================

#ifndef OPENSL_SOUND
#define OPENSL_SOUND

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct opensl_snd {
  SLObjectItf engineObject;
  SLEngineItf engineEngine;
  SLObjectItf outputMixObject;
  SLObjectItf bqPlayerObject;
  SLPlayItf bqPlayerPlay;
  SLAndroidSimpleBufferQueueItf bqPlayerBufferQueue;
  short *outputBuffer;
  short *playBuffer[2];
  int outBufSamples;
  int outchannels;
  int   sr;
  short currPlayBuffer;
} OPENSL_SND;

OPENSL_SND* opensl_open(int sr, int outchannels, int bufferframes);
void opensl_close(OPENSL_SND *p);
int opensl_write(OPENSL_SND *p, short *buffer,int size);
  
#ifdef __cplusplus
};
#endif

#endif
