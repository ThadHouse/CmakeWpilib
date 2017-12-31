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
    set(CMAKE_JNI_TARGET true)
    add_jar(ntcore_jar ${JAVA_SOURCES} INCLUDE_JARS wpiutil_jar OUTPUT_NAME ntcore)

    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}\\jniheaders)
    create_javah(TARGET ntcore_jni_headers
                CLASSES edu.wpi.first.networktables.NetworkTablesJNI
                CLASSPATH ntcore_jar wpiutil_jar
                OUTPUT_DIR jniheaders)
    include_directories("${CMAKE_CURRENT_BINARY_DIR}\\jniheaders\\jniheaders")
    get_property(NTCORE_JAR_FILE TARGET ntcore_jar PROPERTY JAR_FILE)
    add_custom_command(
        TARGET ntcore_jar
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${NTCORE_JAR_FILE} ${CMAKE_BINARY_DIR}/outputs/java/ntcore.jar
    )
endif()

file(GLOB
    ntcore_native_src ntcore/src/main/native/cpp/*.cpp
    ntcore_native_src ntcore/src/main/native/cpp/networktables/*.cpp
    ntcore_native_src ntcore/src/main/native/cpp/tables/*.cpp)
add_library(ntcore SHARED ${ntcore_native_src} ${ntcore_jni_src})
target_include_directories(ntcore PUBLIC ntcore/src/main/native/include)
target_link_libraries(ntcore wpiutil)

if (NOT WIHTOUT_JAVA)
    add_dependencies(ntcore ntcore_jni_headers)
endif()

add_custom_command(
    TARGET ntcore
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ntcore> ${CMAKE_BINARY_DIR}/outputs/native/$<TARGET_FILE_NAME:ntcore>
)

file(COPY ntcore/src/main/native/include DESTINATION ${CMAKE_BINARY_DIR}/outputs)
