/*
 * This file is part of MAME4droid.
 *
 * Copyright (C) 2011 David Valdeita (Seleuco)
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

#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <android/log.h>

#include <math.h>

#include <pthread.h>

#include "com_seleuco_mame4all_Emulator.h"

#define DEBUG 1

//mame4all funtions
int  (*android_main)(int argc, char **argv)=NULL;
void (*setAudioCallbacks)(void *func1,void *func2,void *func3)= NULL;
void (*setVideoCallbacks)(void *func1,void *func2,void *func3) = NULL;
void (*setPadStatus)(int i, unsigned long pad_status) = NULL;
void (*setGlobalPath)(const char *path) = NULL;

void  (*setMyValue)(int key, int value)=NULL;
int  (*getMyValue)(int key)=NULL;

void  (*setMyAnalogData)(int i, float v1,float v2)=NULL;

/* Callbacks to Android */
jmethodID android_dumpVideo;
jmethodID android_changeVideo;
jmethodID android_openAudio;
jmethodID android_dumpAudio;
jmethodID android_closeAudio;

static JavaVM *jVM = NULL;
static void *libdl = NULL;
static jclass cEmulator = NULL;

static jobject videoBuffer=NULL;//es un ByteBuffer wrappeando el buffer de video en la libreria 

static jbyteArray jbaAudioBuffer = NULL;

static jobject audioBuffer=NULL;
static unsigned char audioByteBuffer[882 * 2 * 2 * 10];

static pthread_t main_tid;


static void load_lib(const char *str)
{

    char str2[256];
    
    strcpy(str2,str);
    strcpy(str2+strlen(str),"/libMAME4all.so");

#ifdef DEBUG
    __android_log_print(ANDROID_LOG_DEBUG, "mame4all-jni", "Attempting to load %s\n", str2);
#endif

    if(libdl!=NULL)
        return;

    libdl = dlopen(str2, RTLD_NOW);
    if(!libdl)
    {
        __android_log_print(ANDROID_LOG_ERROR, "mame4all-jni", "Unable to load libMAME4all.so: %s\n", dlerror());
        return;
    }

    android_main = dlsym(libdl, "android_main");
    setVideoCallbacks = dlsym(libdl, "setVideoCallbacks");
    setAudioCallbacks = dlsym(libdl, "setAudioCallbacks");    
    setPadStatus = dlsym(libdl, "setPadStatus");    
    setGlobalPath = dlsym(libdl, "setGlobalPath"); 

    setMyValue = dlsym(libdl, "setMyValue"); 
    getMyValue = dlsym(libdl, "getMyValue"); 

    setMyAnalogData = dlsym(libdl, "setMyAnalogData"); 
}

void myJNI_initVideo(void *buffer)
{
    JNIEnv *env;
    jobject tmp;
    (*jVM)->GetEnv(jVM, (void**) &env, JNI_VERSION_1_4);
#ifdef DEBUG
    __android_log_print(ANDROID_LOG_DEBUG, "mame4all-jni", "initVideo");
#endif
    tmp = (*env)->NewDirectByteBuffer(env, buffer, 1024 * 512 * 2);//640,480 power 2
    videoBuffer = (jobject)(*env)->NewGlobalRef(env, tmp);

    if(!videoBuffer) __android_log_print(ANDROID_LOG_ERROR, "mame4all-jni", "yikes, unable to initialize video buffer");
}

void myJNI_dumpVideo(int emulating)
{

JNIEnv *env;
    (*jVM)->GetEnv(jVM, (void**) &env, JNI_VERSION_1_4);

#ifdef DEBUG
   // __android_log_print(ANDROID_LOG_DEBUG, "mame4all-jni", "dumpVideo emulating:%d",emulating);
#endif

    (*env)->CallStaticVoidMethod(env, cEmulator, android_dumpVideo, videoBuffer,(jboolean)emulating);
}

void myJNI_changeVideo(int newWidth, int newHeight)
{
    JNIEnv *env;
    (*jVM)->GetEnv(jVM, (void**) &env, JNI_VERSION_1_4);

#ifdef DEBUG
    __android_log_print(ANDROID_LOG_DEBUG, "mame4all-jni", "changeVideo");
#endif


    (*env)->CallStaticVoidMethod(env, cEmulator, android_changeVideo, (jint)newWidth,(jint)newHeight);
}

void myJNI_closeAudio()
{
    JNIEnv *env;
    (*jVM)->GetEnv(jVM, (void**) &env, JNI_VERSION_1_4);

#ifdef DEBUG
    __android_log_print(ANDROID_LOG_DEBUG, "mame4all-jni", "closeAudio");
#endif

    (*env)->CallStaticVoidMethod(env, cEmulator, android_closeAudio);
}

void myJNI_openAudio(int rate, int stereo)
{
    JNIEnv *env;
    (*jVM)->GetEnv(jVM, (void**) &env, JNI_VERSION_1_4);

#ifdef DEBUG
    __android_log_print(ANDROID_LOG_DEBUG, "mame4all-jni", "openAudio");
#endif


    (*env)->CallStaticVoidMethod(env, cEmulator, android_openAudio, (jint)rate,(jboolean)stereo);
}


void myJNI_dumpAudio(void *buffer, int size)
{
    JNIEnv *env;
    jobject tmp;
    (*jVM)->GetEnv(jVM, (void**) &env, JNI_VERSION_1_4);

#ifdef DEBUG
    //__android_log_print(ANDROID_LOG_DEBUG, "mame4all-jni", "dumpAudio %ld %d",buffer, size);
#endif

    if(jbaAudioBuffer==NULL)
    {
        jbaAudioBuffer=(*env)->NewByteArray(env, 882*2*2*10);
        tmp = jbaAudioBuffer;
        jbaAudioBuffer=(jbyteArray)(*env)->NewGlobalRef(env, jbaAudioBuffer);
        (*env)->DeleteLocalRef(env, tmp);
    }    

    (*env)->SetByteArrayRegion(env, jbaAudioBuffer, 0, size, (jbyte *)buffer);
   
    (*env)->CallStaticVoidMethod(env, cEmulator, android_dumpAudio,jbaAudioBuffer,(jint)size);
}

void myJNI_dumpAudio2(void *buffer, int size)
{
    JNIEnv *env;
    jobject tmp;
    (*jVM)->GetEnv(jVM, (void**) &env, JNI_VERSION_1_4);

#ifdef DEBUG
    //__android_log_print(ANDROID_LOG_DEBUG, "mame4all-jni", "dumpAudio %ld %d",buffer, size);
#endif

    if(audioBuffer==NULL)
    {
       tmp = (*env)->NewDirectByteBuffer(env, audioByteBuffer, 882*2*2*10);
       audioBuffer = (jobject)(*env)->NewGlobalRef(env, tmp);
    }
    
    memcpy(audioByteBuffer,buffer,size);

    (*env)->CallStaticVoidMethod(env, cEmulator, android_dumpAudio, audioBuffer,(jint)size);

}

int JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv *env;
    jVM = vm;

#ifdef DEBUG
    __android_log_print(ANDROID_LOG_DEBUG, "mame4all-jni", "JNI_OnLoad called");
#endif

    if((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_4) != JNI_OK)
    {
        __android_log_print(ANDROID_LOG_ERROR, "mame4all-jni", "Failed to get the environment using GetEnv()");
        return -1;
    }
    
    cEmulator = (*env)->FindClass (env, "com/seleuco/mame4all/Emulator"); 

    if(cEmulator==NULL)
    {
        __android_log_print(ANDROID_LOG_ERROR, "mame4all-jni", "Failed to find class com.seleuco.mame4all.Emulator");
        return -1;
    } 

    cEmulator = (jclass) (*env)->NewGlobalRef(env,cEmulator );

    android_dumpVideo = (*env)->GetStaticMethodID(env,cEmulator,"bitblt","(Ljava/nio/ByteBuffer;Z)V");
    
    if(android_dumpVideo==NULL)
    {
        __android_log_print(ANDROID_LOG_ERROR, "mame4all-jni", "Failed to find method bitblt");
        return -1;
    }

    android_changeVideo= (*env)->GetStaticMethodID(env,cEmulator,"changeVideo","(II)V");
    
    if(android_changeVideo==NULL)
    {
        __android_log_print(ANDROID_LOG_ERROR, "mame4all-jni", "Failed to find method changeVideo");
        return -1;
    }

    //android_dumpAudio = (*env)->GetStaticMethodID(env,cEmulator,"writeAudio","(Ljava/nio/ByteBuffer;I)V");
    android_dumpAudio = (*env)->GetStaticMethodID(env,cEmulator,"writeAudio","([BI)V");

    if(android_dumpAudio==NULL)
    {
        __android_log_print(ANDROID_LOG_ERROR, "mame4all-jni", "Failed to find method writeAudio");
        return -1;
    }

    android_openAudio = (*env)->GetStaticMethodID(env,cEmulator,"initAudio","(IZ)V");

    if(android_openAudio==NULL)
    {
        __android_log_print(ANDROID_LOG_ERROR, "mame4all-jni", "Failed to find method openAudio");
        return -1;
    }

    android_closeAudio = (*env)->GetStaticMethodID(env,cEmulator,"endAudio","()V");

    if(android_closeAudio==NULL)
    {
        __android_log_print(ANDROID_LOG_ERROR, "mame4all-jni", "Failed to find method closeAudio");
        return -1;
    }
   
    return JNI_VERSION_1_4;
}


void* app_Thread_Start(void* args)
{
    android_main(0, NULL); 
    return NULL;
}

JNIEXPORT void JNICALL Java_com_seleuco_mame4all_Emulator_init
  (JNIEnv *env, jclass c,  jstring s1, jstring s2)
{
    __android_log_print(ANDROID_LOG_INFO, "mame4all-jni", "init");

    const char *str1 = (*env)->GetStringUTFChars(env, s1, 0);

    load_lib(str1);

    (*env)->ReleaseStringUTFChars(env, s1, str1);
    
    setVideoCallbacks(&myJNI_initVideo,&myJNI_dumpVideo,&myJNI_changeVideo);   

    setAudioCallbacks(&myJNI_openAudio,&myJNI_dumpAudio,&myJNI_closeAudio);

    const char *str2 = (*env)->GetStringUTFChars(env, s2, 0);

    __android_log_print(ANDROID_LOG_INFO, "mame4all-jni", "path %s",str2);

    setGlobalPath(str2);

    (*env)->ReleaseStringUTFChars(env, s2, str2);

    //int i = pthread_create(&main_tid, NULL, app_Thread_Start, NULL);

    //if(i!=0)__android_log_print(ANDROID_LOG_ERROR, "mame4all-jni", "Error setting creating pthread %d",i);	
    //struct sched_param    param;
    //param.sched_priority = 63;
    //param.sched_priority = 46;
    //param.sched_priority = 100;
    /*  
    if(pthread_setschedparam(main_tid, SCHED_RR, &param) != 0)
    {
        __android_log_print(ANDROID_LOG_ERROR, "mame4all-jni", "Error setting pthread priority");
        return;
    }
    */
    
    android_main(0, NULL);    
}

JNIEXPORT void JNICALL Java_com_seleuco_mame4all_Emulator_setPadData
  (JNIEnv *env, jclass c, jint i,  jlong jl)
{
    //long 	jlong 	signed 64 bits ??? valdria con un jint
    //__android_log_print(ANDROID_LOG_INFO, "mame4all-jni", "setPadData");

    unsigned long l = (unsigned long)jl;

    if(setPadStatus!=NULL)
       setPadStatus(i,l);
}

JNIEXPORT void JNICALL Java_com_seleuco_mame4all_Emulator_setAnalogData
  (JNIEnv *env, jclass c, jint i, jfloat v1, jfloat v2)
{
    if(setMyAnalogData!=NULL)
       setMyAnalogData(i,v1,v2);
}

JNIEXPORT jint JNICALL Java_com_seleuco_mame4all_Emulator_getValue
  (JNIEnv *env, jclass c, jint key)
{
#ifdef DEBUG
   // __android_log_print(ANDROID_LOG_DEBUG, "mame4all-jni", "getValue %d",key);
#endif
      if(getMyValue!=NULL)
         return getMyValue(key);
      else 
         return -1;
}

JNIEXPORT void JNICALL Java_com_seleuco_mame4all_Emulator_setValue
  (JNIEnv *env, jclass c, jint key, jint value)
{
#ifdef DEBUG
    __android_log_print(ANDROID_LOG_DEBUG, "mame4all-jni", "setValue %d=%d",key,value);
#endif
    if(setMyValue!=NULL)
      setMyValue(key,value);
}




