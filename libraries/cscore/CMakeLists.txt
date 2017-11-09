project(cscore)

find_package( OpenCV REQUIRED )

file(GLOB cscore_native_src cscore/src/main/native/cpp/*.cpp)
add_library(cscore ${cscore_native_src})
target_link_libraries(cscore ntcore wpiutil ${OpenCV_LIBS})
