# Disable in-source builds to prevent source tree corruption.
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "
FATAL: In-source builds are not allowed.
       You should create a separate directory for build files.
")
endif()

project(wpilib_vision)
cmake_minimum_required(VERSION 3.3.0)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/wpilib/lib")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


# the RPATH to be used when installing, but only if it's not a system directory
LIST(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/wpilib/lib" isSystemDir)
IF("${isSystemDir}" STREQUAL "-1")
   SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/wpilib/lib")
ENDIF("${isSystemDir}" STREQUAL "-1")

# flags and config

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DNOMINMAX /D_SCL_SECURE_NO_WARNINGS /D_WINSOCK_DEPRECATED_NO_WARNINGS /Zi /FS /Zc:inline /MT")
elseif(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wformat=2 -Wall -Wextra -Werror -pedantic -Wno-unused-parameter")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wformat=2 -Wall -Wextra -Werror -pedantic -Wno-unused-parameter -pthread")
endif()

option(WITHOUT_JAVA "don't include java and JNI in the build" OFF)



set( wpilib_dest wpilib)
set( include_dest wpilib/include )
set( main_lib_dest wpilib/lib )
set( java_lib_dest wpilib/java )

if (MSVC)
    set (wpilib_config_dir ${wpilib_dest})
else()
    set (wpilib_config_dir share/wpilib)
endif()

add_subdirectory(libraries)
add_subdirectory(vision_app)

install(FILES wpilib-config.cmake DESTINATION ${wpilib_config_dir})
