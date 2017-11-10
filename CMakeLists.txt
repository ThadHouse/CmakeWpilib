project(tk1_wpiutil_test)
cmake_minimum_required(VERSION 2.8.0)

# flags and config
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")

add_subdirectory(libraries)

add_executable(tk1_wpiutil_test wpiutil_main.cpp)
target_link_libraries(tk1_wpiutil_test wpiutil)

add_executable(tk1_ntcore_test ntcore_main.cpp)
target_link_libraries(tk1_ntcore_test ntcore)

add_executable(tk1_cscore_test cscore_main.cpp)
target_link_libraries(tk1_cscore_test cscore)
