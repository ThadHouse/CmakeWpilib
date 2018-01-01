project(vision_app)

file(GLOB app_src src/*.cpp)

add_executable(vision_app ${app_src})
#add_executable(vision_app ${app_src})
target_link_libraries(vision_app wpiutil ntcore cscore)
