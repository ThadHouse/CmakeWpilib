project(ntcore)


file(GLOB
    ntcore_native_src ntcore/src/main/native/cpp/*.cpp
    ntcore_native_src ntcore/src/main/native/cpp/networktables/*.cpp
    ntcore_native_src ntcore/src/main/native/cpp/tables/*.cpp)
add_library(ntcore ${ntcore_native_src})
target_include_directories(ntcore PUBLIC ntcore/src/main/native/include)
target_link_libraries(ntcore wpiutil)
