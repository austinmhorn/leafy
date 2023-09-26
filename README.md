<p align="center">
  <img src="https://github.com/austinmhorn/leafy/blob/c7fa2f7787ac028775d6a416f2514d8458fdee73/resources/images/icon.png" width="96px" height="96px"> 
</p>

<h1>
   <p align="center">
     leafy<br>
   </p>
</h1>

<h4>
  <p align="center">
    Lightweight C++ library of GUI widgets and form components
  </p>
</h4>

## Dependencies

### • [SFML](https://www.sfml-dev.org/download.php) - Simple and Fast Multimedia Library

SFML depends on a few other libraries, so before starting to compile you must have their development files installed.
On Windows and macOS, all the needed dependencies are provided directly with SFML, so you don't have to download/install anything. Compilation will work out of the box.

On Linux however, nothing is provided and SFML relies on your own installation of the libraries it depends on. Here is a list of what you need to install before compiling SFML:

- pthread
- opengl
- xlib
- udev
- xrandr
- xcursor
- freetype
- openal
- flac
- vorbis

Update existing library versions [if any] and install any missing ones with

    sudo apt-get update && sudo apt-get install libxrandr-dev libxcursor-dev libudev-dev libopenal-dev libflac-dev libvorbis-dev libgl1-mesa-dev libegl1-mesa-dev

### • [CMake](https://cmake.org/download/) - Build Generator System


## Download

Clone the main branch 

    git clone --branch main --single-branch https://github.com/austinmhorn/leafy.git

Generate build files
    
    cmake -S . -B build
  
## Install

    cmake --build build --config Release --target install

## Features

## Troubleshooting


