project(allwpilib)

find_package ( OpenCV REQUIRED )

if (NOT USE_PACKAGE_HAL)

# HAL (Only support sim)

file(GLOB_RECURSE hal_native_sim_src allwpilib/hal/src/main/native/sim/*.cpp)
file(GLOB_RECURSE hal_native_shared_src allwpilib/hal/src/main/native/shared/*.cpp)

add_library (wpiHal ${hal_native_sim_src} ${hal_native_shared_src})
target_link_libraries(wpiHal ntcore wpiutil)

target_include_directories(wpiHal PUBLIC
                 $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/allwpilib/hal/src/main/native/include>
                            $<INSTALL_INTERFACE:${include_dest}/wpiHal>)

set_property(TARGET wpiHal PROPERTY FOLDER "libraries")

install(TARGETS wpiHal EXPORT wpiHal DESTINATION "${main_lib_dest}")
install(DIRECTORY allwpilib/hal/src/main/native/include/ DESTINATION "${include_dest}/wpiHal")

if (MSVC)
    set (hal_config_dir wpilib_dest)
else()
    set (hal_config_dir share/wpiHal)
endif()

install(FILES wpihal-config.cmake DESTINATION ${hal_config_dir})
install(EXPORT wpiHal DESTINATION ${hal_config_dir})

else()
  find_package( wpiHal REQUIRED )
endif()

# wpilibc

file(GLOB_RECURSE wpilibc_native_src allwpilib/wpilibc/src/main/native/cpp/*.cpp)

add_library (wpilibc ${wpilibc_native_src})
target_link_libraries(wpilibc wpiHal cscore ntcore wpiutil ${OpenCV_LIBS})

target_include_directories(wpilibc PUBLIC
                 $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/allwpilib/wpilibc/src/main/native/include>
                            $<INSTALL_INTERFACE:${include_dest}/wpilibc>)

set_property(TARGET wpilibc PROPERTY FOLDER "libraries")

install(TARGETS wpilibc EXPORT wpilibc DESTINATION "${main_lib_dest}")
install(DIRECTORY allwpilib/wpilibc/src/main/native/include/ DESTINATION "${include_dest}/wpilibc")

if (MSVC)
    set (wpilibc_config_dir wpilib_dest)
else()
    set (wpilibc_config_dir share/wpilibc)
endif()

install(FILES wpilibc-config.cmake DESTINATION ${wpilibc_config_dir})
install(EXPORT wpilibc DESTINATION ${wpilibc_config_dir})

# wpilibj

if (NOT WITHOUT_JAVA)
  find_package(Java REQUIRED)
  find_package(JNI REQUIRED)
  include(UseJava)
  set(CMAKE_JAVA_COMPILE_FLAGS "-Xlint:unchecked")

  #find java files, copy them locally

  set(OPENCV_JAVA_INSTALL_DIR ${OpenCV_INSTALL_PATH}/share/OpenCV/java/)

  find_file(OPENCV_JAR_FILE NAMES opencv-${OpenCV_VERSION_MAJOR}${OpenCV_VERSION_MINOR}${OpenCV_VERSION_PATCH}.jar PATHS ${OPENCV_JAVA_INSTALL_DIR} ${OpenCV_INSTALL_PATH}/bin NO_DEFAULT_PATH)
  find_file(OPENCV_JNI_FILE NAMES libopencv_java${OpenCV_VERSION_MAJOR}${OpenCV_VERSION_MINOR}${OpenCV_VERSION_PATCH}.so
                                  libopencv_java${OpenCV_VERSION_MAJOR}${OpenCV_VERSION_MINOR}${OpenCV_VERSION_PATCH}.dylib
                                  opencv_java${OpenCV_VERSION_MAJOR}${OpenCV_VERSION_MINOR}${OpenCV_VERSION_PATCH}.dll
                                  PATHS ${OPENCV_JAVA_INSTALL_DIR} ${OpenCV_INSTALL_PATH}/bin ${OpenCV_INSTALL_PATH}/bin/Release ${OpenCV_INSTALL_PATH}/bin/Debug ${OpenCV_INSTALL_PATH}/lib NO_DEFAULT_PATH)

  file (GLOB_RECURSE wpilibj_native_src allwpilib/wpilibj/src/main/native/cpp/*.cpp)
  file (GLOB_RECURSE wpilibj_java_src allwpilib/wpilibj/src/main/java/*.java)
  set(CMAKE_JNI_TARGET true)
  add_jar(wpilibj_jar ${wpilibj_java_src} WPILibVersion.java INCLUDE_JARS wpiutil_jar ntcore_jar cscore_jar ${OPENCV_JAR_FILE} OUTPUT_NAME wpilibj)

  file (STRINGS WPILibJNIClasses.txt WPILIBJ_JNI_CLASSES)

  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}\\jniheaders)
  create_javah(TARGET wpilibj_jni_headers
              CLASSES ${WPILIBJ_JNI_CLASSES}
              CLASSPATH wpilibj_jar wpiutil_jar ntcore_jar cscore_jar ${OPENCV_JAR_FILE}
              OUTPUT_DIR jniheaders)

  add_library (wpilibJNI ${wpilibj_native_src})
  target_link_libraries (wpilibJNI wpiHal wpiutil)
  target_include_directories(wpilibJNI PRIVATE "${CMAKE_CURRENT_BINARY_DIR}\\jniheaders\\jniheaders" ${JNI_INCLUDE_DIRS})
  add_dependencies(wpilibJNI wpilibj_jni_headers)

  get_property(WPILIBJ_JAR_FILE TARGET wpilibj_jar PROPERTY JAR_FILE)

  install(FILES ${WPILIBJ_JAR_FILE} DESTINATION ${java_lib_dest})
  install(TARGETS wpilibJNI EXPORT wpilibJNI DESTINATION "${main_lib_dest}")

  set_property(TARGET wpilibj_jar PROPERTY FOLDER "java")
  set_property(TARGET wpilibj_jni_headers PROPERTY FOLDER "java")

  set_property(TARGET wpilibJNI PROPERTY FOLDER "libraries")
endif()
