# Definitions for all external bundled libraries

# Suppress warnings from external libraries
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/W0)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/CMakeModules)
include(DownloadExternals)
include(ExternalProject)

# Boost
set(BOOST_ROOT "${CMAKE_SOURCE_DIR}/externals/boost")
set(Boost_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/externals/boost")
set(Boost_NO_SYSTEM_PATHS ON)
add_library(boost INTERFACE)
target_include_directories(boost SYSTEM INTERFACE ${Boost_INCLUDE_DIR})

# Boost::serialization
if (NOT USE_SYSTEM_BOOST)
    file(GLOB boost_serialization_SRC "${CMAKE_SOURCE_DIR}/externals/boost/libs/serialization/src/*.cpp")
    add_library(boost_serialization STATIC ${boost_serialization_SRC})
    target_link_libraries(boost_serialization PUBLIC boost)
endif()

# Add additional boost libs here; remember to ALIAS them in the root CMakeLists!

# Catch
add_library(catch-single-include INTERFACE)
target_include_directories(catch-single-include INTERFACE catch/single_include)

# Xbyak
if (ARCHITECTURE_x86_64)
    add_library(xbyak INTERFACE)
    if (USE_SYSTEM_XBYAK)
        target_include_directories(xbyak SYSTEM INTERFACE /usr/include/xbyak)
    else()
        target_include_directories(xbyak INTERFACE ./xbyak/xbyak)
    endif()
    target_compile_definitions(xbyak INTERFACE XBYAK_NO_OP_NAMES)
endif()

# Dynarmic
if (ARCHITECTURE_x86_64 OR ARCHITECTURE_ARM64)
    set(DYNARMIC_TESTS OFF)
    set(DYNARMIC_NO_BUNDLED_FMT ON)
    set(DYNARMIC_FRONTENDS "A32")
    add_subdirectory(dynarmic)
endif()

# libfmt
if (NOT USE_SYSTEM_FMT)
    add_subdirectory(fmt)
    add_library(fmt::fmt ALIAS fmt)
else()
    set(DYNARMIC_NO_BUNDLED_FMT ON)
endif()

# getopt
if (MSVC)
    add_subdirectory(getopt)
endif()

# Glad
add_subdirectory(glad)

# inih
add_subdirectory(inih)

# MicroProfile
add_library(microprofile INTERFACE)
target_include_directories(microprofile INTERFACE ./microprofile)

# Nihstro
add_library(nihstro-headers INTERFACE)
target_include_directories(nihstro-headers INTERFACE ./nihstro/include)

# Open Source Archives
add_subdirectory(open_source_archives)

# Teakra
add_subdirectory(teakra EXCLUDE_FROM_ALL)

# Cubeb
if (ENABLE_CUBEB)
    set(BUILD_TESTS OFF CACHE BOOL "")
    add_subdirectory(cubeb EXCLUDE_FROM_ALL)
endif()

# DiscordRPC
if (USE_DISCORD_PRESENCE)
    add_subdirectory(discord-rpc EXCLUDE_FROM_ALL)
    target_include_directories(discord-rpc INTERFACE ./discord-rpc/include)
endif()

# LibRetro
add_library(libretro INTERFACE)
target_include_directories(libretro INTERFACE ./libretro)

if (ENABLE_WEB_SERVICE)
    # LibreSSL
    if (NOT USE_SYSTEM_SSL)
        set(LIBRESSL_SKIP_INSTALL ON CACHE BOOL "")
        add_subdirectory(libressl EXCLUDE_FROM_ALL)
        target_include_directories(ssl INTERFACE ./libressl/include)
        target_compile_definitions(ssl PRIVATE -DHAVE_INET_NTOP)
    endif()
    # JSON
    add_library(json-headers INTERFACE)
    target_include_directories(json-headers INTERFACE ./json)

    # lurlparser
    add_subdirectory(lurlparser EXCLUDE_FROM_ALL)

    if(ANDROID)
        add_subdirectory(android-ifaddrs)
    endif()

    # httplib
    add_library(httplib INTERFACE)
    target_include_directories(httplib INTERFACE ./httplib)
    target_compile_options(httplib INTERFACE -DCPPHTTPLIB_OPENSSL_SUPPORT)

    # cpp-jwt
    add_library(cpp-jwt INTERFACE)
    target_include_directories(cpp-jwt INTERFACE ./cpp-jwt/include)
endif()

# lodepng
add_subdirectory(lodepng)
