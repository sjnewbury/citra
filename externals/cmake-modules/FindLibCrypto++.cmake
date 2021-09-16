# - Find Crypto++ library
# This module defines
#  LIBCRYPTOPP_INCLUDE_DIR, where to find headers.
#  LIBCRYPTOPP_LIBRARIES, the libraries needed to use cryptopp.
#  LIBCRYPTOPP_FOUND, If false, do not try to use cryptopp.
#
# Copyright (c) 2009, Michal Cihar, <michal@cihar.com>
#
# vim: expandtab sw=4 ts=4 sts=4:

if(ANDROID)
       set(LIBCRYPTOPP_FOUND FALSE CACHE INTERNAL "Crypto++ found")
       message(STATUS "Crypto++ not found.")
elseif (NOT LIBCRYPTOPP_FOUND)
    pkg_check_modules (LIBCRYPTOPP_PKG libcryptopp)

    find_path(LIBCRYPTOPP_INCLUDE_DIR NAMES crc.h
       PATHS
       ${LIBCRYPTOPP_PKG_INCLUDE_DIRS}
       /usr/include/cryptopp
       /usr/include
       /usr/local/include/cryptopp
       /usr/local/include
    )

    find_library(LIBCRYPTOPP_LIBRARIES NAMES libcryptopp cryptopp
       PATHS
       ${LIBCRYPTOPP_PKG_LIBRARY_DIRS}
       /usr/lib
       /usr/local/lib
    )

    if(LIBCRYPTOPP_INCLUDE_DIR AND LIBCRYPTOPP_LIBRARIES)
       set(LIBCRYPTOPP_FOUND TRUE CACHE INTERNAL "Crypto++ found")
       message(STATUS "Found libcryptopp: ${LIBCRYPTOPP_INCLUDE_DIR}, ${LIBCRYPTOPP_LIBRARIES}")
    else(LIBCRYPTOPP_INCLUDE_DIR AND LIBCRYPTOPP_LIBRARIES)
       set(LIBCRYPTOPP_FOUND FALSE CACHE INTERNAL "Crypto++ found")
       message(STATUS "Crypto++ not found.")
    endif(LIBCRYPTOPP_INCLUDE_DIR AND LIBCRYPTOPP_LIBRARIES)

    mark_as_advanced(LIBCRYPTOPP_INCLUDE_DIR LIBCRYPTOPP_LIBRARIES)
endif ()
