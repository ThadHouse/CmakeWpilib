project(wpiutil)

file(GLOB_RECURSE wpiutil_native_src wpiutil/src/main/native/cpp/*.cpp)
add_library(wpiutil ${wpiutil_native_src})
target_include_directories(wpiutil PUBLIC wpiutil/src/main/native/include)
