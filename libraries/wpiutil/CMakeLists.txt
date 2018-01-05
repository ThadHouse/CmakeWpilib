project(wpiutil)

# Java bindings
if (NOT WITHOUT_JAVA)
  find_package(Java)
  include(UseJava)
  set(CMAKE_JAVA_COMPILE_FLAGS "-Xlint:unchecked")

  set(CMAKE_JAVA_INCLUDE_PATH wpiutil.jar)

  file(GLOB_RECURSE JAVA_SOURCES wpiutil/src/main/java/*.java)
  add_jar(wpiutil_jar ${JAVA_SOURCES} OUTPUT_NAME wpiutil)

  get_property(WPIUTIL_JAR_FILE TARGET wpiutil_jar PROPERTY JAR_FILE)
  install(FILES ${WPIUTIL_JAR_FILE} DESTINATION "${java_lib_dest}")

endif()

file(GLOB_RECURSE wpiutil_native_src wpiutil/src/main/native/cpp/*.cpp)
add_library(wpiutil SHARED ${wpiutil_native_src})
target_include_directories(wpiutil PUBLIC
                            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/wpiutil/src/main/native/include>
                            $<INSTALL_INTERFACE:${include_dest}/wpiutil>)

install(TARGETS wpiutil EXPORT wpiutil DESTINATION "${main_lib_dest}")
install(DIRECTORY wpiutil/src/main/native/include/ DESTINATION "${include_dest}/wpiutil")

if (MSVC)
    set (wpiutil_config_dir ${wpilib_dest})
else()
    set (wpiutil_config_dir share/wpiutil)
endif()

install(FILES wpiutil-config.cmake DESTINATION ${wpiutil_config_dir})
install(EXPORT wpiutil DESTINATION ${wpiutil_config_dir})
