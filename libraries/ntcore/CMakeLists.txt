project(ntcore)


# Java bindings
if (NOT WITHOUT_JAVA)
    find_package(Java REQUIRED)
    find_package(JNI REQUIRED)
    include(UseJava)
    set(CMAKE_JAVA_COMPILE_FLAGS "-Xlint:unchecked")

    include_directories(${JNI_INCLUDE_DIRS})
    file(GLOB
        ntcore_jni_src ntcore/src/main/native/cpp/jni/NetworkTablesJNI.cpp)

    file(GLOB_RECURSE JAVA_SOURCES ntcore/src/main/java/*.java)
    set(CMAKE_JNI_TARGET true)

    if(${CMAKE_VERSION} VERSION_LESS "3.11.0")
        add_jar(ntcore_jar ${JAVA_SOURCES} INCLUDE_JARS wpiutil_jar OUTPUT_NAME ntcore)
        file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}\\jniheaders)
        create_javah(TARGET ntcore_jni_headers
                    CLASSES edu.wpi.first.networktables.NetworkTablesJNI
                    CLASSPATH ntcore_jar wpiutil_jar
                    OUTPUT_DIR jniheaders)
        set_property(TARGET ntcore_jni_headers PROPERTY FOLDER "java")
    else()
        add_jar(ntcore_jar ${JAVA_SOURCES} INCLUDE_JARS wpiutil_jar OUTPUT_NAME ntcore GENERATE_NATIVE_HEADERS ntcore_jni_headers)
    endif()

    get_property(NTCORE_JAR_FILE TARGET ntcore_jar PROPERTY JAR_FILE)
    install(FILES ${NTCORE_JAR_FILE} DESTINATION "${java_lib_dest}")

    set_property(TARGET ntcore_jar PROPERTY FOLDER "java")

endif()

file(GLOB
    ntcore_native_src ntcore/src/main/native/cpp/*.cpp
    ntcore_native_src ntcore/src/main/native/cpp/networktables/*.cpp
    ntcore_native_src ntcore/src/main/native/cpp/tables/*.cpp)
add_library(ntcore ${ntcore_native_src} ${ntcore_jni_src})
target_include_directories(ntcore PUBLIC
                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ntcore/src/main/native/include>
                            $<INSTALL_INTERFACE:${include_dest}/ntcore>)
target_link_libraries(ntcore PUBLIC wpiutil)

set_property(TARGET ntcore PROPERTY FOLDER "libraries")

if (NOT WITHOUT_JAVA)
    target_link_libraries(ntcore PRIVATE ntcore_jni_headers)
endif()

install(TARGETS ntcore EXPORT ntcore DESTINATION "${main_lib_dest}")
install(DIRECTORY ntcore/src/main/native/include/ DESTINATION "${include_dest}/ntcore")

if (MSVC)
    set (ntcore_config_dir ${wpilib_dest})
else()
    set (ntcore_config_dir share/ntcore)
endif()

install(FILES ntcore-config.cmake DESTINATION ${ntcore_config_dir})
install(EXPORT ntcore DESTINATION ${ntcore_config_dir})
