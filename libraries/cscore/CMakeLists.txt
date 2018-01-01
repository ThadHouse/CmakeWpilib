project(cscore)

find_package( OpenCV REQUIRED )

# Java bindings
if (NOT WITHOUT_JAVA)
    find_package(Java)
    find_package(JNI)
    include(UseJava)
    set(CMAKE_JAVA_COMPILE_FLAGS "-Xlint:unchecked")

    #find java files, copy them locally

    set(OPENCV_JAVA_INSTALL_DIR ${OpenCV_INSTALL_PATH}/share/OpenCV/java/)

    find_file(OPENCV_JAR_FILE NAMES opencv-${OpenCV_VERSION_MAJOR}${OpenCV_VERSION_MINOR}${OpenCV_VERSION_PATCH}.jar PATHS ${OPENCV_JAVA_INSTALL_DIR} ${OpenCV_INSTALL_PATH}/bin NO_DEFAULT_PATH)
    find_file(OPENCV_JNI_FILE NAMES libopencv_java${OpenCV_VERSION_MAJOR}${OpenCV_VERSION_MINOR}${OpenCV_VERSION_PATCH}.so
                                    libopencv_java${OpenCV_VERSION_MAJOR}${OpenCV_VERSION_MINOR}${OpenCV_VERSION_PATCH}.dylib
                                    opencv_java${OpenCV_VERSION_MAJOR}${OpenCV_VERSION_MINOR}${OpenCV_VERSION_PATCH}.dll
                                    PATHS ${OPENCV_JAVA_INSTALL_DIR} ${OpenCV_INSTALL_PATH}/bin ${OpenCV_INSTALL_PATH}/bin/Release ${OpenCV_INSTALL_PATH}/bin/Debug ${OpenCV_INSTALL_PATH}/lib NO_DEFAULT_PATH)

    include_directories(${JNI_INCLUDE_DIRS})
    file(GLOB
        cscore_jni_src cscore/src/main/native/cpp/jni/CameraServerJNI.cpp)

    file(GLOB_RECURSE JAVA_SOURCES cscore/src/main/java/*.java)
    set(CMAKE_JNI_TARGET true)
    add_jar(cscore_jar ${JAVA_SOURCES} INCLUDE_JARS wpiutil_jar ${OPENCV_JAR_FILE} OUTPUT_NAME cscore)

    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}\\jniheaders)
    create_javah(TARGET cscore_jni_headers
                CLASSES edu.wpi.cscore.CameraServerJNI
                CLASSPATH cscore_jar wpiutil_jar ${OPENCV_JAR_FILE}
                OUTPUT_DIR jniheaders)
    include_directories("${CMAKE_CURRENT_BINARY_DIR}\\jniheaders\\jniheaders")
    get_property(CSCORE_JAR_FILE TARGET cscore_jar PROPERTY JAR_FILE)

    install(FILES ${CSCORE_JAR_FILE} DESTINATION "${java_lib_dest}")
    install(FILES ${OPENCV_JAR_FILE} DESTINATION "${java_lib_dest}")
    install(FILES ${OPENCV_JNI_FILE} DESTINATION "${java_lib_dest}/jni")
endif()

file(GLOB cscore_native_src cscore/src/main/native/cpp/*.cpp)
add_library(cscore SHARED ${cscore_native_src} ${cscore_native_src} ${cscore_jni_src})
target_link_libraries(cscore wpiutil ${OpenCV_LIBS})
target_include_directories(cscore PUBLIC
                 $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cscore/src/main/native/include>
                            $<INSTALL_INTERFACE:${include_dest}/cscore>)

if (NOT WIHTOUT_JAVA)
    add_dependencies(cscore cscore_jni_headers)
    install(TARGETS cscore DESTINATION "${java_lib_dest}/jni")
endif()

install(TARGETS cscore EXPORT cscore DESTINATION "${main_lib_dest}")
install(DIRECTORY cscore/src/main/native/include/ DESTINATION "${include_dest}/cscore")
install(FILES cscore-config.cmake DESTINATION "${wpilib_dest}")
install(EXPORT cscore DESTINATION "${wpilib_dest}")
