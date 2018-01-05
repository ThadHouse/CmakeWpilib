project(include_test_app)

find_package(wpilib REQUIRED)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DNOMINMAX /D_SCL_SECURE_NO_WARNINGS /D_WINSOCK_DEPRECATED_NO_WARNINGS /Zi /FS /Zc:inline /MT")
elseif(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wformat=2 -Wall -Wextra -Werror -pedantic -Wno-unused-parameter")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wformat=2 -Wall -Wextra -Werror -pedantic -Wno-unused-parameter -pthread")
endif()

add_executable(include_test_app main.cpp)
target_link_libraries(include_test_app ntcore cscore wpiutil)
