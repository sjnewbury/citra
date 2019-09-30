HAVE_DYNARMIC = 0
HAVE_FFMPEG = 0
HAVE_GLAD = 1
HAVE_SSE = 0

TARGET_NAME    := citra
EXTERNALS_DIR  += ./externals
SRC_DIR        += ./src
LIBS		   = -lm
DEFINES        := -DHAVE_LIBRETRO

STATIC_LINKING := 0
AR             := ar

SPACE :=
SPACE := $(SPACE) $(SPACE)
BACKSLASH :=
BACKSLASH := \$(BACKSLASH)
filter_out1 = $(filter-out $(firstword $1),$1)
filter_out2 = $(call filter_out1,$(call filter_out1,$1))

ifeq ($(platform),)
platform = unix
ifeq ($(shell uname -a),)
   platform = win
else ifneq ($(findstring MINGW,$(shell uname -a)),)
   platform = win
else ifneq ($(findstring Darwin,$(shell uname -a)),)
   platform = osx
else ifneq ($(findstring win,$(shell uname -a)),)
   platform = win
endif
endif

ifeq (,$(ARCH))
	ARCH = $(shell uname -m)
endif

# system platform
system_platform = unix
ifeq ($(shell uname -a),)
	EXE_EXT = .exe
	system_platform = win
else ifneq ($(findstring Darwin,$(shell uname -a)),)
	system_platform = osx
	arch = intel
ifeq ($(shell uname -p),powerpc)
	arch = ppc
endif
else ifneq ($(findstring MINGW,$(shell uname -a)),)
	system_platform = win
endif

ifeq ($(ARCHFLAGS),)
ifeq ($(archs),ppc)
   ARCHFLAGS = -arch ppc -arch ppc64
else
   ARCHFLAGS = -arch i386 -arch x86_64
endif
endif

ifeq ($(platform), osx)
ifndef ($(NOUNIVERSAL))
   CXXFLAGS += $(ARCHFLAGS)
   LFLAGS += $(ARCHFLAGS)
endif
endif

ifeq ($(STATIC_LINKING), 1)
EXT := a
endif

GIT_REV := "$(shell git rev-parse --short HEAD || echo unknown)"
GIT_BRANCH := "$(shell git rev-parse --abbrev-ref HEAD || echo unknown)"
GIT_DESC := "$(shell git describe --always --long --dirty || echo unknown)"
BUILD_DATE := "$(shell date +'%d/%m/%Y %H:%M')"

DEFINES += -DGIT_REV=\"$(GIT_REV)\" \
		   -DGIT_BRANCH=\"$(GIT_BRANCH)\" \
		   -DGIT_DESC=\"$(GIT_DESC)\" \
		   -DBUILD_NAME=\"citra-libretro\" \
		   -DBUILD_DATE=\"$(BUILD_DATE)\" \
		   -DBUILD_VERSION=\"$(GIT_BRANCH)-$(GIT_DESC)\" \
		   -DBUILD_FULLNAME=\"\"

ifeq ($(platform), unix)
	EXT ?= so
   TARGET := $(TARGET_NAME)_libretro.$(EXT)
   fpic := -fPIC
   SHARED := -shared -Wl,--version-script=$(SRC_DIR)/citra_libretro/link.T -Wl,--no-undefined
   LIBS +=-lpthread -lGL -ldl -lavcodec -lavformat -lavutil
   HAVE_FFMPEG = 0
endif

ifneq (,$(findstring msvc,$(platform)))
CFLAGS += -D_CRT_SECURE_NO_WARNINGS
CXXFLAGS += -D_CRT_SECURE_NO_WARNINGS
endif

# x86_64 is expected to support both SSE and Dynarmic
ifeq ($(ARCH), x86_64)
DEFINES += -DARCHITECTURE_x86_64
HAVE_DYNARMIC = 1
HAVE_SSE = 1
endif

ifeq ($(DEBUG), 1)
   CXXFLAGS += -O0 -g
else
   CXXFLAGS += -O3 -ffast-math -ftree-vectorize -DNDEBUG
endif

include Makefile.common

CPPFILES = $(filter %.cpp,$(SOURCES_CXX))
CCFILES = $(filter %.cc,$(SOURCES_CXX))

OBJECTS := $(SOURCES_C:.c=.o) $(CPPFILES:.cpp=.o) $(CCFILES:.cc=.o)

CXXFLAGS += -std=c++17

CFLAGS   	  += -Wall -D__LIBRETRO__ $(fpic) $(INCFLAGS) $(DEFINES) $(INCFLAGS_PLATFORM)
DYNARMICFLAGS += -Wall -D__LIBRETRO__ $(fpic) $(DYNARMICINCFLAGS) $(DEFINES) $(INCFLAGS_PLATFORM) $(CXXFLAGS)
CXXFLAGS 	  += -Wall -D__LIBRETRO__ $(fpic) $(INCFLAGS) $(DEFINES) $(INCFLAGS_PLATFORM)

OBJOUT   = -o
LINKOUT  = -o 

ifneq (,$(findstring msvc,$(platform)))
	OBJOUT = -Fo
	LINKOUT = -out:
ifeq ($(STATIC_LINKING),1)
	LD ?= lib.exe

	ifeq ($(DEBUG), 1)
		CFLAGS += -MTd
		CXXFLAGS += -MTd
	else
		CFLAGS += -MT
		CXXFLAGS += -MT
	endif
else
	LD = link.exe

	ifeq ($(DEBUG), 1)
		CFLAGS += -MDd
		CXXFLAGS += -MDd
	else
		CFLAGS += -MD
		CXXFLAGS += -MD
	endif
endif
else
	LD = $(CXX)
endif

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "** BUILDING $(TARGET) FOR PLATFORM $(platform) **"
ifeq ($(STATIC_LINKING), 1)
	$(AR) rcs $@ $(OBJECTS)
else
	$(LD) $(fpic) $(SHARED) $(INCLUDES) $(LINKOUT)$@ $(OBJECTS) $(LDFLAGS) $(LIBS)
endif
	@echo "** BUILD SUCCESSFUL! GG NO RE **"

%.o: %.c
	$(CC) $(CFLAGS) $(fpic) -c $(OBJOUT)$@ $<

$(foreach p,$(OBJECTS),$(if $(findstring $(EXTERNALS_DIR)/dynarmic/src,$p),$p,)):
	$(CXX) $(DYNARMICFLAGS) $(fpic) -c $(OBJOUT)$@ $(@:.o=.cpp)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(fpic) -c $(OBJOUT)$@ $<

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: clean

