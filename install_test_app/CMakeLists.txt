project(include_test_app)

find_package(wpilib REQUIRED)

add_executable(include_test_app main.cpp)
target_link_libraries(include_test_app ntcore cscore wpiutil)
