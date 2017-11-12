project(wpilib_camera_vision)
cmake_minimum_required(VERSION 2.8.0)

# flags and config

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DNOMINMAX /D_SCL_SECURE_NO_WARNINGS /D_WINSOCK_DEPRECATED_NO_WARNINGS /Zi /FS /Zc:inline /MT")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++11 -Wformat=2 -Wall -Wextra -Werror -pedantic -Wno-unused-parameter -pthread")
endif()

add_subdirectory(libraries)


file(GLOB native_src src/*.cpp)
add_executable(camera_vision ${native_src})
target_link_libraries(camera_vision ntcore wpiutil cscore)
target_include_directories(camera_vision PUBLIC include)
