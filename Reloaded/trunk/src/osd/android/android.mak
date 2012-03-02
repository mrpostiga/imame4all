SDLSRC = $(SRC)/osd/$(OSD)
SDLOBJ = $(OBJ)/osd/$(OSD)

OBJDIRS += $(SDLOBJ)

#-------------------------------------------------
# OSD core library
#-------------------------------------------------

OSDCOREOBJS = \
	$(SDLOBJ)/droiddir.o	\
	$(SDLOBJ)/droidfile.o  	\
	$(SDLOBJ)/droidos.o	\
	$(SDLOBJ)/droidsync.o     \
	$(SDLOBJ)/droidwork.o	

OSDOBJS =  $(SDLOBJ)/droidmain.o \
	$(SDLOBJ)/droidinput.o \
	$(SDLOBJ)/droidsound.o  $(SDLOBJ)/droidvideo.o \
	$(SDLOBJ)/myosd.o \


DEFS += -D_BSD_SETJMP_H

$(LIBOCORE): $(OSDCOREOBJS)
$(LIBOSD): $(OSDOBJS)

	
