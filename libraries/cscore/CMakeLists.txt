project(cscore)

find_package( OpenCV REQUIRED )

file(GLOB cscore_native_src cscore/src/main/native/cpp/*.cpp)
add_library(cscore ${cscore_native_src})
target_link_libraries(cscore wpiutil ${OpenCV_LIBS})
target_include_directories(cscore PUBLIC cscore/src/main/native/include)
