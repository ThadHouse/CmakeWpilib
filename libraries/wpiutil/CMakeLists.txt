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
  add_custom_command(
      TARGET wpiutil_jar
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy ${WPIUTIL_JAR_FILE} ${CMAKE_BINARY_DIR}/outputs/java/wpiutil.jar
  )

endif()

file(GLOB_RECURSE wpiutil_native_src wpiutil/src/main/native/cpp/*.cpp)
add_library(wpiutil SHARED ${wpiutil_native_src})
target_include_directories(wpiutil PUBLIC wpiutil/src/main/native/include)

add_custom_command(
    TARGET wpiutil
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:wpiutil> ${CMAKE_BINARY_DIR}/outputs/native/$<TARGET_FILE_NAME:wpiutil>
)

file(COPY wpiutil/src/main/native/include DESTINATION ${CMAKE_BINARY_DIR}/outputs)
