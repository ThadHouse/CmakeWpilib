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

add_subdirectory(libraries)

add_executable(test_exe test_main.cpp)
target_link_libraries(test_exe wpiutil ntcore cscore)
