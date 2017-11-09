project(wpiutil)

file(GLOB_RECURSE wpiutil_native_src wpiutil/src/main/native/cpp/*.cpp)
include_directories(wpiutil/src/main/native/include)
add_library(wpiutil ${wpiutil_native_src})
