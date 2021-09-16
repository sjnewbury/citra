# - Find ENet library
# This module defines
#  ENET_INCLUDE_DIR, where to find headers.
#  ENET_LIBRARIES, the libraries needed to use ENet.
#  ENET_FOUND, If false, do not try to use ENet.
#
# Copyright (c) 2009, Michal Cihar, <michal@cihar.com>
#
# vim: expandtab sw=4 ts=4 sts=4:

if(ANDROID)
       set(ENET_FOUND FALSE CACHE INTERNAL "ENet found")
       message(STATUS "ENet not found.")
elseif (NOT ENET_FOUND)
    pkg_check_modules (ENET_PKG libenet)

    find_path(ENET_INCLUDE_DIR NAMES enet.h
       PATHS
       ${ENET_PKG_INCLUDE_DIRS}
       /usr/include/enet
       /usr/include
       /usr/local/include/enet
       /usr/local/include
    )

    find_library(ENET_LIBRARIES NAMES libenet enet
       PATHS
       ${ENET_PKG_LIBRARY_DIRS}
       /usr/lib
       /usr/local/lib
    )

    if(ENET_INCLUDE_DIR AND ENET_LIBRARIES)
       set(ENET_FOUND TRUE CACHE INTERNAL "ENet found")
       message(STATUS "Found ENet: ${ENET_INCLUDE_DIR}, ${ENET_LIBRARIES}")
    else(ENET_INCLUDE_DIR AND ENET_LIBRARIES)
       set(ENET_FOUND FALSE CACHE INTERNAL "ENet found")
       message(STATUS "ENet not found.")
    endif(ENET_INCLUDE_DIR AND ENET_LIBRARIES)

    mark_as_advanced(ENET_INCLUDE_DIR ENET_LIBRARIES)
endif ()
