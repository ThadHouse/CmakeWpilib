project(wpilib_vision)
cmake_minimum_required(VERSION 3.3.0)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

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

add_subdirectory(libraries)
add_subdirectory(vision_app)
