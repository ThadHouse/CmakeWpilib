add_subdirectory(wpiutil)
add_subdirectory(ntcore)

if (NOT WITHOUT_CSCORE)
add_subdirectory(cscore)
endif()

if (NOT WITHOUT_ALLWPILIB)
add_subdirectory(allwpilib)
endif()
