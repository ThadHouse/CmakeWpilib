# WPILIB Cmake Vision Build System

WPILib currently uses a gradle build system. This works great for a preset build on our fully supported sytems, however it has issues when attempting to build libraries for unsupported systems. The biggest issues in OpenCV. Devices such as the NVIDIA Jetson TX1 have their own OpenCV libraries, however the gradle build system has no easy way to use these libraries for CameraServer support. This is a substitute build system designed to use Cmake. It builds the wpiutil, ntcore and cscore libraries, so is great for coprocessors. Note this is not supported by WPI or FIRST directly.

## Downloading
To start, you must download and clone this repo. Because this repo uses git submodules to the official repos, the submodules must be cloned as well. To do this, use the following command.

`git clone --recursive https://github.com/ThadHouse/CmakeWpilib.git`

This will clone the repo, and download the submodules. This will place the repo in a `CmakeWpilib` folder.

If you have just downloaded the repo without the `--recursive` flag, use te following command to clone the submodules manually.

`git submodule update --init --recursive`

## Building

There are multiple different scenarios for building this. For most people, they will want ntcore, cscore and wpiutil with both Java and C++ support. That is the configuration we will start with.

In order to build this configuration, there are 2 major prerequisites that will be required. These are the Java JDK, and OpenCV. For Java JDK, as long as it is installed through your distribution, and the JAVA_HOME environmental variable is set, it should work. For OpenCV, we recommend you build and install the newest release. This build should then see the installed OpenCV.

Once these prerequisites are installed, create a build folder. Then run `cmake path/to/source/code`. This should set up cmake. Then `make` can be ran to actually run the build.




If you don't need Java, you can use the flag `-DWITHOUT_JAVA=ON`. This will skip the Java build and remove the jdk requirement.

If you don't need Cscore, you can use the flag `-DWITHOUT_CSCORE=ON`. This will remove the OpenCV requirement of the build.

In addition, this build system supports building the main wpilib code as well. To enable this (it's disabled by default), use `-DWITHOUT_ALLWPILIB=OFF`. This will build the simulator HAL.
