project(tk1_wpiutil_test)
cmake_minimum_required(VERSION 3.9.0)

# flags and config
set (CMAKE_CXX_STANDARD 11)

# includes and building the other stuff
add_subdirectory(libraries)

include_directories(libraries/wpiutil/wpiutil/src/main/native/include)

add_executable(tk1_wpiutil_test main.cpp)

target_link_libraries(tk1_wpiutil_test wpiutil)
