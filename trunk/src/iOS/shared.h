#ifndef __SHARED_H__
#define __SHARED_H__

#if defined(__cplusplus)
extern "C" {
#endif

extern const char* get_resource_path(char* file);
extern const char* get_documents_path(char* file);
    
#define IMAMEBASEPATH "/var/mobile/Media/ROMs/iMAME4all"
    
#ifdef MYDEBUG
#define IMAMEBASEPATH "/var/mobile/Applications/2CC608BB-8BD1-46F6-993C-738EDFE375F6/iMAME4all.app/ROMS"
#endif
    
#if defined(__cplusplus)
}
#endif

#endif
