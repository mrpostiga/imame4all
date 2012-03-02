###########################################################################
#
#   makefile
#
#   Core makefile for building MAME and derivatives
#
#   Copyright (c) Nicola Salmoria and the MAME Team.
#   Visit http://mamedev.org for licensing and usage restrictions.
#
###########################################################################

#BASE_DEV=/home/david/Projects/android/android-ndk-r6/platforms/android-8/arch-arm
#BASE_DEV=/home/david/Projects/android/android-ndk-r6/platforms/android-5/arch-arm
#MYPREFIX=/home/david/Projects/android/android-ndk-r6/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin/arm-linux-androideabi-
#MYPREFIX=/home/david/Projects/android/android-ndk-r6/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/arm-linux-androideabi/bin/

ANDROID = 1

ifdef ANDROID
MYPREFIX=/home/david/Projects/android/my-android-toolchain/bin/arm-linux-androideabi-
BASE_DEV=/home/david/Projects/android/my-android-toolchain/sysroot
endif

#MYPREFIX=/home/david/Projects/iphone/toolchain/toolchain/pre/bin/arm-apple-darwin9-
#BASE_DEV=/home/david/Projects/iphone/toolchain/sdks/iPhoneOS2.0.sdk

#CROSS_BUILD = 1

###########################################################################
#################   BEGIN USER-CONFIGURABLE OPTIONS   #####################
###########################################################################


#-------------------------------------------------
# specify core target: mame, mess, etc.
# specify subtarget: mame, mess, tiny, etc.
# build rules will be included from 
# src/$(TARGET)/$(SUBTARGET).mak
#-------------------------------------------------

ifndef TARGET
TARGET = mame
endif

ifndef SUBTARGET
#SUBTARGET = $(TARGET)
SUBTARGET = tiny
endif

#-------------------------------------------------
# specify OSD layer: windows, sdl, etc.
# build rules will be included from 
# src/osd/$(OSD)/$(OSD).mak
#-------------------------------------------------

ifndef OSD
OSD = android
endif

ifndef CROSS_BUILD_OSD
CROSS_BUILD_OSD = $(OSD)
endif



#-------------------------------------------------
# specify OS target, which further differentiates
# the underlying OS; supported values are:
# win32, unix, macosx, os2
#-------------------------------------------------

ifndef TARGETOS
ifeq ($(OSD),windows)
TARGETOS = win32
else
TARGETOS = unix
endif
endif



#-------------------------------------------------
# configure name of final executable
#-------------------------------------------------

# uncomment and specify prefix to be added to the name
# PREFIX =

# uncomment and specify suffix to be added to the name
# SUFFIX =



#-------------------------------------------------
# specify architecture-specific optimizations
#-------------------------------------------------

# uncomment and specify architecture-specific optimizations here
# some examples:
#   optimize for I686:   ARCHOPTS = -march=pentiumpro
#   optimize for Core 2: ARCHOPTS = -march=pentium-m -msse3
#   optimize for G4:     ARCHOPTS = -mcpu=G4
# note that we leave this commented by default so that you can
# configure this in your environment and never have to think about it
# ARCHOPTS =



#-------------------------------------------------
# specify program options; see each option below 
# for details
#-------------------------------------------------

# uncomment next line to build a debug version
# DEBUG = 1

# uncomment next line to include the internal profiler
# PROFILER = 1

# uncomment the force the universal DRC to always use the C backend
# you may need to do this if your target architecture does not have
# a native backend
FORCE_DRC_C_BACKEND = 1

# uncomment next line to build using unix-style libsdl on Mac OS X
# (vs. the native framework port).  Normal users should not enable this.
# MACOSX_USE_LIBSDL = 1


#-------------------------------------------------
# specify build options; see each option below 
# for details
#-------------------------------------------------

# uncomment next line if you are building for a 64-bit target
# PTR64 = 1

#android es little endian
# uncomment next line if you are building for a big-endian target
#BIGENDIAN = 1

# uncomment next line to build expat as part of MAME build
BUILD_EXPAT = 1

# uncomment next line to build zlib as part of MAME build
BUILD_ZLIB = 1

# uncomment next line to include the symbols
#SYMBOLS = 1

# uncomment next line to include profiling information from the compiler
# PROFILE = 1

# uncomment next line to generate a link map for exception handling in windows
# MAP = 1

# uncomment next line to generate verbose build information
#VERBOSE = 1

# specify optimization level or leave commented to use the default
# (default is OPTIMIZE = 3 normally, or OPTIMIZE = 0 with symbols)
#OPTIMIZE = 3

# experimental: uncomment to compile everything as C++ for stricter type checking
#CPP_COMPILE = 1


###########################################################################
##################   END USER-CONFIGURABLE OPTIONS   ######################
###########################################################################


#-------------------------------------------------
# sanity check the configuration
#-------------------------------------------------

# specify a default optimization level if none explicitly stated
ifndef OPTIMIZE
ifndef SYMBOLS
OPTIMIZE = 3
else
OPTIMIZE = 0
endif
endif

# profiler defaults to on for DEBUG builds
ifdef DEBUG
ifndef PROFILER
PROFILER = 1
endif
endif



#-------------------------------------------------
# platform-specific definitions
#-------------------------------------------------

# extension for executables
EXE = 

ifeq ($(TARGETOS),win32)
EXE = .exe
endif
ifeq ($(TARGETOS),os2)
EXE = .exe
endif

ifndef BUILD_EXE
BUILD_EXE = $(EXE)
endif

CCEXE = .exe
#CCEXE = 

# compiler, linker and utilities
#AR = @$(PREFIX)ar
#CC = @$(PREFIX)gcc
#LD = $(CC)

MD = -mkdir$(EXE)
RM = @rm -f

AR = @$(MYPREFIX)ar
CC = @$(MYPREFIX)gcc
#CPP = $(MYPREFIX)gcc
LD =  $(MYPREFIX)g++
#ASM = $(MYPREFIX)gcc



#-------------------------------------------------
# form the name of the executable
#-------------------------------------------------

# debug builds just get the 'd' suffix and nothing more
ifdef DEBUG
DEBUGSUFFIX = d
endif

# cpp builds get a 'pp' suffix
ifdef CPP_COMPILE
CPPSUFFIX = pp
endif

# the name is just 'target' if no subtarget; otherwise it is
# the concatenation of the two (e.g., mametiny)
ifeq ($(TARGET),$(SUBTARGET))
NAME = $(TARGET)
else
NAME = $(TARGET)$(SUBTARGET)
endif

# fullname is prefix+name+suffix+debugsuffix
FULLNAME = $(PREFIX)$(NAME)$(CPPSUFFIX)$(SUFFIX)$(DEBUGSUFFIX)

# add an EXE suffix to get the final emulator name
EMULATOR = $(FULLNAME)$(EXE)



#-------------------------------------------------
# source and object locations
#-------------------------------------------------

# all sources are under the src/ directory
SRC = src

# build the targets in different object dirs, so they can co-exist
OBJ = obj/$(OSD)/$(FULLNAME)



#-------------------------------------------------
# compile-time definitions
#-------------------------------------------------

# CR/LF setup: use both on win32/os2, CR only on everything else
DEFS = -DCRLF=2

ifeq ($(TARGETOS),win32)
DEFS = -DCRLF=3
endif
ifeq ($(TARGETOS),os2)
DEFS = -DCRLF=3
endif

# map the INLINE to something digestible by GCC
DEFS += -DINLINE="static __inline__"

# define LSB_FIRST if we are a little-endian target
ifndef BIGENDIAN
DEFS += -DLSB_FIRST
endif

# define PTR64 if we are a 64-bit target
ifdef PTR64
DEFS += -DPTR64
endif

# define MAME_DEBUG if we are a debugging build
ifdef DEBUG
DEFS += -DMAME_DEBUG
else
DEFS += -DNDEBUG 
endif

# define MAME_PROFILER if we are a profiling build
ifdef PROFILER
DEFS += -DMAME_PROFILER
endif



#-------------------------------------------------
# compile flags
# CCOMFLAGS are common flags
# CONLYFLAGS are flags only used when compiling for C
# CPPONLYFLAGS are flags only used when compiling for C++
#-------------------------------------------------

# start with empties for everything
CCOMFLAGS = 
CONLYFLAGS =
CPPONLYFLAGS =

# CFLAGS is defined based on C or C++ targets
# (remember, expansion only happens when used, so doing it here is ok)
ifdef CPP_COMPILE
CFLAGS = $(CCOMFLAGS) $(CPPONLYFLAGS)
else
CFLAGS = $(CCOMFLAGS) $(CONLYFLAGS)
endif

# we compile C-only to C89 standard with GNU extensions
# we compile C++ code to C++98 standard with GNU extensions
#CONLYFLAGS += -std=gnu89 
CPPONLYFLAGS += -x c++ -std=gnu++98

# this speeds it up a bit by piping between the preprocessor/compiler/assembler
#CCOMFLAGS += -pipe

# add -g if we need symbols, and ensure we have frame pointers
ifdef SYMBOLS
CCOMFLAGS += -g -fno-omit-frame-pointer
endif

# add -v if we need verbose build information
ifdef VERBOSE
CCOMFLAGS += -v
endif

# add profiling information for the compiler
ifdef PROFILE
CCOMFLAGS += -pg
endif

# add the optimization flag
CCOMFLAGS += -O$(OPTIMIZE)

# if we are optimizing, include optimization options
# and make all errors into warnings
ifneq ($(OPTIMIZE),0)
ifneq ($(TARGETOS),os2)
ifndef IA64
#CCOMFLAGS += -Werror -fno-strict-aliasing $(ARCHOPTS)
CCOMFLAGS +=  -fno-strict-aliasing $(ARCHOPTS)
#CCOMFLAGS += -fno-strict-aliasing $(ARCHOPTS)
else
endif
else
CCOMFLAGS += -fno-strict-aliasing $(ARCHOPTS)
endif
endif

# add a basic set of warnings
CCOMFLAGS += \
	-Wall \
	-Wundef \
	-Wformat-security \
	-Wwrite-strings \
	-Wno-sign-compare
#	-Wcast-align \
	
# warnings only applicable to C compiles
CONLYFLAGS += \
	-Wpointer-arith \
	-Wbad-function-cast \
	-Wstrict-prototypes

# this warning is not supported on the os2 compilers
ifneq ($(TARGETOS),os2)
CONLYFLAGS += -Wdeclaration-after-statement
endif


#-------------------------------------------------
# include paths
#-------------------------------------------------


# add core include paths
CCOMFLAGS += \
	-I$(SRC)/include-SDL-1.2 \
	-I$(SRC)/$(TARGET) \
	-I$(SRC)/$(TARGET)/includes \
	-I$(OBJ)/$(TARGET)/layout \
	-I$(SRC)/emu \
	-I$(OBJ)/emu \
	-I$(OBJ)/emu/layout \
	-I$(SRC)/lib/util \
	-I$(SRC)/osd \
	-I$(SRC)/osd/$(OSD) \

		
#-I/home/david/Projects/android/android-ndk-r3/build/platforms/android-5/arch-arm/usr/include \
#-I/home/david/Projects/iphone/toolchain/sdks/iPhoneOS3.1.2.sdk/usr/include \

#-------------------------------------------------
# linking flags
#-------------------------------------------------

# LDFLAGS are used generally; LDFLAGSEMULATOR are additional
# flags only used when linking the core emulator
LDFLAGS =
ifneq ($(TARGETOS),macosx)
ifneq ($(TARGETOS),os2)
ifneq ($(TARGETOS),solaris)
LDFLAGS = -Wl,--warn-common
endif
endif
endif
LDFLAGSEMULATOR =

# add profiling information for the linker
ifdef PROFILE
LDFLAGS += -pg
endif

# strip symbols and other metadata in non-symbols and non profiling builds
ifndef SYMBOLS
ifndef PROFILE
ifneq ($(TARGETOS),macosx)
LDFLAGS += -s
endif
endif
endif

# output a map file (emulator only)
ifdef MAP
LDFLAGSEMULATOR += -Wl,-Map,$(FULLNAME).map
endif



#-------------------------------------------------
# define the standard object directory; other
# projects can add their object directories to
# this variable
#-------------------------------------------------

OBJDIRS = $(OBJ)



#-------------------------------------------------
# define standard libarires for CPU and sounds
#-------------------------------------------------

#LIBEMU = $(OBJ)/libemu.a
#LIBCPU = $(OBJ)/libcpu.a
#LIBDASM = $(OBJ)/libdasm.a
#LIBSOUND = $(OBJ)/libsound.a
#LIBUTIL = $(OBJ)/libutil.a
#LIBOCORE = $(OBJ)/libocore.a
#LIBOSD = $(OBJ)/libosd.a

VERSIONOBJ = $(OBJ)/version.o



#-------------------------------------------------
# either build or link against the included 
# libraries
#-------------------------------------------------

# start with an empty set of libs
LIBS = 

# add expat XML library
ifdef BUILD_EXPAT
CCOMFLAGS += -I$(SRC)/lib/expat
EXPAT = $(OBJ)/libexpat.a
else
LIBS += -lexpat
EXPAT =
endif

# add ZLIB compression library
ifdef BUILD_ZLIB
CCOMFLAGS += -I$(SRC)/lib/zlib
ZLIB = $(OBJ)/libz.a
else
LIBS += -lz
ZLIB =
endif

ifdef ANDROID
CFLAGS += --sysroot $(BASE_DEV)
CFLAGS += -DANDROID
LDFLAGS += -Wl,--fix-cortex-a8
LDFLAGS += -llog -lgcc
CFLAGS += -fpic
#CFLAGS +=  -fPIC
LDFLAGS += -Wl,-soname,libapplication.so -shared
#CFLAGS += -isysroot $(BASE_DEV)/usr/include
#CFLAGS += --with-sysroot $(BASE_DEV)
CFLAGS += -march=armv7-a -mfloat-abi=softfp -DARMV7
endif

LDFLAGS += -lc -lm

#CFLAGS += -c -save-temps
#DEFS += -DLSB_FIRST
#CFLAGS +=  -I/home/david/Projects/iphone/toolchain/sdks/iPhoneOS3.1.2.sdk/usr/include
#CFLAGS +=  -I/home/david/Projects/android/android-ndk-r3/build/platforms/android-5/arch-arm/usr/include
#LDFLAGS += -F$(BASE_DEV)/usr/lib
#CFLAGS += -iprefix /home/david/Projects/android/android-ndk-r6/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin/../lib/gcc/arm-linux-androideabi/4.4.3/ 
#CFLAGS += -isysroot /home/david/Projects/android/android-ndk-r6/platforms/android-5/arch-arm



LDFLAGS += -Wl,-export-dynamic  
#LDFLAGS += -rdynamic

#CFLAGS += -fsigned-char -finline  -fno-common -fno-builtin
#CFLAGS += -Wno-sign-compare -Wunused -Wpointer-arith -Wcast-align -Waggregate-return -Wshadow
#CFLAGS += -O3 -ffast-math -fweb -frename-registers -falign-functions=16 -fsingle-precision-constant
#CFLAGS += -mstructure-size-boundary=32 -mthumb-interwork
CFLAGS += -fpic


LDFLAGS += -lc -lm 

   
###########


###########

#-------------------------------------------------
# 'all' target needs to go here, before the 
# include files which define additional targets
#-------------------------------------------------

all: maketree buildtools emulator




#-------------------------------------------------
# defines needed by multiple make files
#-------------------------------------------------

BUILDSRC = $(SRC)/build
BUILDOBJ = $(OBJ)/build
BUILDOUT = $(BUILDOBJ)


#-------------------------------------------------
# include the various .mak files
#-------------------------------------------------

# include OSD-specific rules first
include $(SRC)/osd/$(OSD)/$(OSD).mak

# then the various core pieces
include $(SRC)/$(TARGET)/$(SUBTARGET).mak
include $(SRC)/emu/emu.mak
include $(SRC)/lib/lib.mak
include $(SRC)/build/build.mak
-include $(SRC)/osd/$(CROSS_BUILD_OSD)/build.mak
include $(SRC)/tools/tools.mak

# combine the various definitions to one
CDEFS = $(DEFS) $(COREDEFS) $(SOUNDDEFS)



#-------------------------------------------------
# primary targets
#-------------------------------------------------

emulator: maketree $(BUILD) $(EMULATOR)

buildtools: maketree $(BUILD)

tools: maketree $(TOOLS)

maketree: $(sort $(OBJDIRS))

clean: $(OSDCLEAN)
	@echo Deleting object tree $(OBJ)...
	$(RM) -r $(OBJ)
	@echo Deleting $(EMULATOR)...
	$(RM) $(EMULATOR)
	@echo Deleting $(TOOLS)...
	$(RM) $(TOOLS)
ifdef MAP
	@echo Deleting $(FULLNAME).map...
	$(RM) $(FULLNAME).map
endif



#-------------------------------------------------
# directory targets
#-------------------------------------------------

$(sort $(OBJDIRS)):
	$(MD) -p $@

$(OBJ)/build/file2str$(CCEXE):
	mkdir -p $(OBJ)/build
	cp -t $(OBJ)/build prec-build/file2str$(CCEXE)

$(OBJ)/build/m68kmake$(CCEXE):
	cp -t $(OBJ)/build prec-build/m68kmake$(CCEXE)

$(OBJ)/build/png2bdc$(CCEXE):
	cp -t $(OBJ)/build prec-build/png2bdc$(CCEXE)

$(OBJ)/build/tmsmake$(CCEXE):
	cp -t $(OBJ)/build prec-build/tmsmake$(CCEXE)

$(OBJ)/build/verinfo$(CCEXE):
	cp -t $(OBJ)/build prec-build/verinfo$(CCEXE)

#-------------------------------------------------
# executable targets and dependencies
#-------------------------------------------------

ifndef EXECUTABLE_DEFINED

# always recompile the version string
$(VERSIONOBJ): $(DRVLIBS) $(LIBOSD) $(LIBEMU) $(LIBCPU) $(LIBSOUND) $(LIBUTIL) $(EXPAT) $(ZLIB) $(LIBOCORE) $(RESFILE)

$(EMULATOR): $(VERSIONOBJ)  $(DRVLIBS) $(OSDOBJS) $(EMUOBJS) $(EMUSOUNDOBJS) $(EMUAUDIOOBJS) $(EMUDRIVEROBJS) $(EMUMACHINEOBJS) $(EMUVIDEOOBJS) $(CPUOBJS)  $(DASMOBJS) $(SOUNDOBJS) $(UTILOBJS) $(EXPAT) $(ZLIB) $(OSDCOREOBJS) $(RESFILE)
	$(LD) $(LDFLAGS) $(LDFLAGSEMULATOR) $(LIBS) $^ $(LIBS) -o $@

endif

#-------------------------------------------------
# generic rules
#-------------------------------------------------

$(OBJ)/%.o: $(SRC)/%.c | $(OSPREBUILD)
	@echo Compiling $<...
	$(CC) $(CDEFS) $(CFLAGS) -c $< -o $@

$(OBJ)/%.pp: $(SRC)/%.c | $(OSPREBUILD)
	@echo Compiling $<...
	$(CC) $(CDEFS) $(CFLAGS) -E $< -o $@

$(OBJ)/%.s: $(SRC)/%.c | $(OSPREBUILD)
	@echo Compiling $<...
	$(CC) $(CDEFS) $(CFLAGS) -S $< -o $@

$(OBJ)/%.lh: $(SRC)/%.lay $(FILE2STR)
	@echo Converting $<...
	@$(FILE2STR) $< $@ layout_$(basename $(notdir $<))

$(OBJ)/%.fh: $(SRC)/%.png $(PNG2BDC) $(FILE2STR)
	@echo Converting $<...
	@$(PNG2BDC) $< $(OBJ)/temp.bdc
	@$(FILE2STR) $(OBJ)/temp.bdc $@ font_$(basename $(notdir $<)) UINT8

$(OBJ)/%.a:
	@echo Archiving $@...
	$(RM) $@
	$(AR) -cr -v $@ $^
