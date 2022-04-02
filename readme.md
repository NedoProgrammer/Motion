## WARNING
Please, only use this project in CMake with `FetchContent()`. The CSFML and SFML.NET bindings were removed, since I don't use them 😅.

## Usage
```cmake
include(FetchContent)
FetchContent_Declare(
        motion
        GIT_REPOSITORY https://github.com/NedoProgrammer/MotionPP
        GIT_TAG fc3723db02256469d2fdabf87842a1bbb72a6847
)
message(STATUS "Fetching Motion..")
set(FFMPEG_ROOT "YOUR_FFMPEG_DIRECTORY")
FetchContent_MakeAvailable(motion)
```

## Where can I find FFMPEG?
For Windows, install it from [here](https://github.com/GyanD/codexffmpeg/releases/tag/4.3.1-2020-11-19), unpack it somewhere and set `FFMPEG_ROOT` to the unpacked folder. That's it! 😁

## Motion Project

### License
This software is provided 'as-is' without any express or implied warranty. Read the full license agreement in "license.txt".


### Author
Motion was created by Zachariah Brown (zsbzsb). Motion is written in C++ with duel C style functions so that it can be utilized by C++ or CLR/CLI programs. It provides an easy way to add video or audio playback to any SFML program. FFMPEG is used for decoding the files and then the data played back using SFML.


### Examples
Check the included example folders for a quick code example to get up and running. Remember MotionNET depends on Motion while the Motion project can be used independently of MotionNET.

### Linking
When using MotionNET ensure that SFML is compiled dynamically and CSFML is linked to the dynamic version of SFML. Also ensure that you do not link to static std libs. Failure to link everything dynamically will cause issues.

### Custom Backends
As of the latest version there is not support for custom backends other than SFML. To implement your own video or audio backend inherit from one of the playback base classes and override the required functions.

### Dependencies
* SFML (latest master or 2.5+)
* FFMPEG
* Motion (only required for MotionNET)
* CSFML
