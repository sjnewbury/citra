# - Find Zstd library
# This module defines
#  ZSTD_INCLUDE_DIR, where to find headers.
#  ZSTD_LIBRARIES, the libraries needed to use cryptopp.
#  ZSTD_FOUND, If false, do not try to use libzstd.
#
# Copyright (c) 2009, Michal Cihar, <michal@cihar.com>
#
# vim: expandtab sw=4 ts=4 sts=4:

if(ANDROID)
       set(ZSTD_FOUND FALSE CACHE INTERNAL "Zstd found")
       message(STATUS "Zstd not found.")
elseif (NOT ZSTD_FOUND)
    pkg_check_modules (ZSTD_PKG libzstd)

    find_path(ZSTD_INCLUDE_DIR NAMES zstd.h
       PATHS
       ${ZSTD_PKG_INCLUDE_DIRS}
       /usr/include/cryptopp
       /usr/include
       /usr/local/include/cryptopp
       /usr/local/include
    )

    find_library(ZSTD_LIBRARIES NAMES libzstd zstd
       PATHS
       ${ZSTD_PKG_LIBRARY_DIRS}
       /usr/lib
       /usr/local/lib
    )

    if(ZSTD_INCLUDE_DIR AND ZSTD_LIBRARIES)
       set(ZSTD_FOUND TRUE CACHE INTERNAL "Zstd found")
       message(STATUS "Found libzstd: ${ZSTD_INCLUDE_DIR}, ${ZSTD_LIBRARIES}")
    else(ZSTD_INCLUDE_DIR AND ZSTD_LIBRARIES)
       set(ZSTD_FOUND FALSE CACHE INTERNAL "Zstd found")
       message(STATUS "Zstd not found.")
    endif(ZSTD_INCLUDE_DIR AND ZSTD_LIBRARIES)

    mark_as_advanced(ZSTD_INCLUDE_DIR ZSTD_LIBRARIES)
endif ()
