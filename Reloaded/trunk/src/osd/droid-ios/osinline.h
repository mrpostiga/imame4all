//============================================================
//
//	osinline.h - GNU C inline functions
//
//============================================================

#ifndef __OSINLINE__
#define __OSINLINE__

#include "eminline.h"

INLINE void ATTR_FORCE_INLINE
osd_yield_processor(void)
{
	//__asm__ __volatile__ ( " nop \n nop \n" );
        do {} while (0);
}

#endif /* __OSINLINE__ */
