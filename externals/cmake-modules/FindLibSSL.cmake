# - Find libssl library
# This module defines
#  OPENSSL_INCLUDE_DIR, where to find ssl.h
#  OPENSSL_LIBS, the libraries needed to use libssl.
#  OPENSSL_FOUND, If false, do not try to use libssl.
#
# Copyright (c) 2009, Michal Cihar, <michal@cihar.com>
#
# vim: expandtab sw=4 ts=4 sts=4:

if(ANDROID)
       set(OPENSSL_FOUND FALSE CACHE INTERNAL "libssl found")
       message(STATUS "libssl not found.")
elseif (NOT OPENSSL_FOUND)
    pkg_check_modules (OPENSSL_PKG openssl)

    find_path(OPENSSL_INCLUDE_DIR NAMES ssl.h crypto.h
       PATHS
       ${OPENSSL_PKG_INCLUDE_DIRS}
       /usr/include/openssl
       /usr/include/libressl
       /usr/include/ssl
       /usr/include
       /usr/local/include/openssl
       /usr/local/include/libressl
       /usr/local/include/ssl
       /usr/local/include
    )

    find_library(OPENSSL_SSL_LIBRARIES NAMES ssl
       PATHS
       ${OPENSSL_PKG_LIBRARY_DIRS}
       /usr/lib
       /usr/local/lib
    )

    find_library(OPENSSL_CRYPTO_LIBRARIES NAMES crypto
       PATHS
       ${OPENSSL_PKG_LIBRARY_DIRS}
       /usr/lib
       /usr/local/lib
    )

    list(APPEND OPENSSL_LIBS ${OPENSSL_SSL_LIBRARIES} ${OPENSSL_CRYPTO_LIBRARIES})

    if(OPENSSL_INCLUDE_DIR AND OPENSSL_LIBS)
       set(OPENSSL_FOUND TRUE CACHE INTERNAL "libssl found")
       message(STATUS "Found libssl: ${OPENSSL_INCLUDE_DIR}, ${OPENSSL_LIBS}")
    else(OPENSSL_INCLUDE_DIR AND OPENSSL_LIBS)
       set(OPENSSL_FOUND FALSE CACHE INTERNAL "libssl found")
       message(STATUS "libssl not found.")
    endif(OPENSSL_INCLUDE_DIR AND OPENSSL_LIBS)

    mark_as_advanced(OPENSSL_INCLUDE_DIR OPENSSL_LIBS)
endif ()
