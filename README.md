# WPILIB Cmake Vision Build System

WPILib currently uses a gradle build system. This works great for a preset build on our fully supported sytems, however it has issues when attempting to build libraries for unsupported systems. The biggest issues in OpenCV. Devices such as the NVIDIA Jetson TX1 have their own OpenCV libraries, however the gradle build system has no easy way to use these libraries for CameraServer support. This is a substitute build system designed to use Cmake. It builds the wpiutil, ntcore and cscore libraries, so is great for coprocessors. Note this is not supported by WPI or FIRST directly.

## Downloading
To start, you must download and clone this repo. Because this repo uses git submodules to the official repos, the submodules must be cloned as well. To do this, use the following command.

`git clone --recursive https://github.com/ThadHouse/CmakeWpilib.git`

This will clone the repo, and download the submodules. This will place the repo in a `CmakeWpilib` folder.

If you have just downloaded the repo without the `--recursive` flag, use te following command to clone the submodules manually.

`git submodule update --init --recursive`

## Building
