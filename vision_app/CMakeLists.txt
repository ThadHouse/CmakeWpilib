project(vision_app)

if (NOT WITHOUT_CSCORE)
file(GLOB app_src src/*.cpp)
else()
file(GLOB app_src src_no_cscore/*.cpp)
endif()

add_executable(vision_app ${app_src})
#add_executable(vision_app ${app_src})
target_link_libraries(vision_app wpiutil ntcore)

if (NOT WITHOUT_CSCORE)
  target_link_libraries(vision_app cscore)
endif()
