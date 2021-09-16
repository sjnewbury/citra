# - Find SoundTouch library
# This module defines
#  SOUNDTOUCH_INCLUDE_DIR, where to find headers.
#  SOUNDTOUCH_LIBRARIES, the libraries needed to use SoundTouch.
#  SOUNDTOUCH_FOUND, If false, do not try to use SoundTouch.
#
# Copyright (c) 2009, Michal Cihar, <michal@cihar.com>
#
# vim: expandtab sw=4 ts=4 sts=4:

if(ANDROID)
       set(SOUNDTOUCH_FOUND FALSE CACHE INTERNAL "SoundTouch found")
       message(STATUS "SoundTouch not found.")
elseif (NOT SOUNDTOUCH_FOUND)
    pkg_check_modules (SOUNDTOUCH_PKG soundtouch)

    find_path(SOUNDTOUCH_INCLUDE_DIR NAMES SoundTouch.h
       PATHS
       ${SOUNDTOUCH_PKG_INCLUDE_DIRS}
       /usr/include/soundtouch
       /usr/include
       /usr/local/include/soundtouch
       /usr/local/include
    )

    find_library(SOUNDTOUCH_LIBRARIES NAMES libSoundTouch SoundTouch
       PATHS
       ${SOUNDTOUCH_PKG_LIBRARY_DIRS}
       /usr/lib
       /usr/local/lib
    )

    if(SOUNDTOUCH_INCLUDE_DIR AND SOUNDTOUCH_LIBRARIES)
       set(SOUNDTOUCH_FOUND TRUE CACHE INTERNAL "SoundTouch found")
       message(STATUS "Found SoundTouch: ${SOUNDTOUCH_INCLUDE_DIR}, ${SOUNDTOUCH_LIBRARIES}")
    else(SOUNDTOUCH_INCLUDE_DIR AND SOUNDTOUCH_LIBRARIES)
       set(SOUNDTOUCH_FOUND FALSE CACHE INTERNAL "SoundTouch found")
       message(STATUS "SoundTouch not found.")
    endif(SOUNDTOUCH_INCLUDE_DIR AND SOUNDTOUCH_LIBRARIES)

    mark_as_advanced(SOUNDTOUCH_INCLUDE_DIR SOUNDTOUCH_LIBRARIES)
endif ()
