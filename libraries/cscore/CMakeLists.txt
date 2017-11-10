project(cscore)

find_package( OpenCV REQUIRED )

# Java bindings
if (NOT WITHOUT_JAVA)
    find_package(Java)
    find_package(JNI)
    include(UseJava)
    set(CMAKE_JAVA_COMPILE_FLAGS "-Xlint:unchecked")

    include_directories(${JNI_INCLUDE_DIRS})
    file(GLOB
        cscore_jni_src cscore/src/main/native/cpp/jni/CameraServerJNI.cpp)

    file(GLOB_RECURSE JAVA_SOURCES cscore/src/main/java/*.java)
    file(GLOB_RECURSE JAVA_WPIUTIL_SOURCES ../wpiutil/wpiutil/src/main/java/*.java)
    set(CMAKE_JNI_TARGET true)
    add_jar(cscore_jar ${JAVA_SOURCES} ${JAVA_WPIUTIL_SOURCES} OUTPUT_NAME cscore)

    # Generate JNI headers
    add_custom_command(
        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/edu_wpi_cscore_CameraServerJNI.h"
        DEPENDS cscore_jar cscore/src/main/java/edu/wpi/cscore/CameraServerJNI.java
        COMMAND "${Java_JAVAH_EXECUTABLE}"
        -jni
        -o "${CMAKE_CURRENT_BINARY_DIR}/edu_wpi_cscore_CameraServerJNI.h"
        -classpath "${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/cscore_jar.dir/"
        edu.wpi.cscore.CameraServerJNI
        )
    include_directories("${CMAKE_CURRENT_BINARY_DIR}")
    set_source_files_properties(
        cscore/src/main/native/cpp/jni/CameraServerJNI.cpp
        OBJECT_DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/edu_wpi_cscore_CameraServerJNI.h"
        )
endif()

file(GLOB cscore_native_src cscore/src/main/native/cpp/*.cpp)
add_library(cscore ${cscore_native_src})
target_link_libraries(cscore wpiutil ${OpenCV_LIBS})
