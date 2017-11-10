project(ntcore)


# Java bindings
if (NOT WITHOUT_JAVA)
    find_package(Java)
    find_package(JNI)
    include(UseJava)
    set(CMAKE_JAVA_COMPILE_FLAGS "-Xlint:unchecked")

    include_directories(${JNI_INCLUDE_DIRS})
    file(GLOB
        ntcore_jni_src ntcore/src/main/native/cpp/jni/NetworkTablesJNI.cpp)

    file(GLOB_RECURSE JAVA_SOURCES ntcore/src/main/java/*.java)
    file(GLOB_RECURSE JAVA_WPIUTIL_SOURCES ../wpiutil/wpiutil/src/main/java/*.java)
    set(CMAKE_JNI_TARGET true)
    add_jar(ntcore_jar ${JAVA_SOURCES} ${JAVA_WPIUTIL_SOURCES} OUTPUT_NAME ntcore)

    # Generate JNI headers
    add_custom_command(
        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/edu_wpi_first_networktables_NetworkTablesJNI.h"
        DEPENDS ntcore_jar ntcore/src/main/java/edu/wpi/first/networktables/NetworkTablesJNI.java
        COMMAND "${Java_JAVAH_EXECUTABLE}"
        -jni
        -o "${CMAKE_CURRENT_BINARY_DIR}/edu_wpi_first_networktables_NetworkTablesJNI.h"
        -classpath "${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/ntcore_jar.dir/"
        edu.wpi.first.networktables.NetworkTablesJNI
        )
    include_directories("${CMAKE_CURRENT_BINARY_DIR}")
    set_source_files_properties(
        ntcore/src/main/native/cpp/jni/NetworkTablesJNI.cpp
        OBJECT_DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/edu_wpi_first_networktables_NetworkTablesJNI.h"
        )
endif()

file(GLOB
    ntcore_native_src ntcore/src/main/native/cpp/*.cpp
    ntcore_native_src ntcore/src/main/native/cpp/networktables/*.cpp
    ntcore_native_src ntcore/src/main/native/cpp/tables/*.cpp)
add_library(ntcore ${ntcore_native_src} ${ntcore_jni_src})
target_include_directories(ntcore PUBLIC ntcore/src/main/native/include)
target_link_libraries(ntcore wpiutil)
