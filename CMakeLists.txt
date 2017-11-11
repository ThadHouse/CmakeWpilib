project(tk1_wpiutil_test)
cmake_minimum_required(VERSION 2.8.0)

# flags and config

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DNOMINMAX /D_SCL_SECURE_NO_WARNINGS /D_WINSOCK_DEPRECATED_NO_WARNINGS /Zi /FS /Zc:inline /MT")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++11 -Wformat=2 -Wall -Wextra -Werror -pedantic -Wno-unused-parameter -pthread")
endif()

add_subdirectory(libraries)

add_executable(tk1_wpiutil_test wpiutil_main.cpp)
target_link_libraries(tk1_wpiutil_test wpiutil)

add_executable(tk1_ntcore_test ntcore_main.cpp)
target_link_libraries(tk1_ntcore_test ntcore)
