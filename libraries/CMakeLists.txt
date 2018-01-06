add_subdirectory(wpiutil)
add_subdirectory(ntcore)

if (NOT WITHOUT_CSCORE)
add_subdirectory(cscore)
endif()
