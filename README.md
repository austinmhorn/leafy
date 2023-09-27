<p align="center">
  <img src="https://github.com/austinmhorn/leafy/blob/c7fa2f7787ac028775d6a416f2514d8458fdee73/resources/images/icon.png" width="160px" height="160px"> 
</p>

<h1>
   <p align="center">
     <b>leafy</b>
   </p>
</h1>

<h3>
  <p align="center">
    <i>Lightweight C++ library of GUI widgets and form components</i>
  </p>
</h3>


### Features

---

- Engine
  - State Machine
  - SmartMouse
  - Resource Manager
    - Fonts | Textures | Sounds

- New Shapes

 • Polygon
 • RoundedRectangleShape
 • Stadium 

- Graphical Control Elements:

 • Buttons
   - Rectangle | Circle | Polygon | RoundedRectangle | Stadium
 • Checkbox
   - Single-Select | Multi-Select
 • Dropdown List
   - Single-Select | Multi-Select
 • Slider
 • Textbox
 • Toggle
 • Vertical Scroll Window

### Dependencies

##### • [CMake](https://cmake.org/download/) : Build Generator System
##### • [SFML](https://www.sfml-dev.org/download.php) : Simple and Fast Multimedia Library

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

### Installing

##### Clone the main branch 

    git clone --branch main --single-branch https://github.com/austinmhorn/leafy.git

##### Generate build files
    
    cmake -S . -B build

##### Install
    
    cmake --build build --target install

By default, the leafy library is built as a **shared library**, but can easily be built using **statically linked** standard/runtime libraries by adding a few flags

    cmake -S . -B build -DBUILD_SHARED_LIBS=OFF -DLEAFY_BUILD_SHARED_LIBS=OFF -DSFML_STATIC_LIBRARIES=ON 

If you're using this library in another project and wish to disable building the examples, you can prevent it with 

    -DLEAFY_BUILD_EXAMPLES=OFF

---

### Troubleshooting


---


##### Widgets to come:

- Progress Bar
A progress bar is a graphical control element used to visualize the progression of an extended computer operation, such as a download, file transfer, or installation. Sometimes, the graphic is accompanied by a textual representation of the progress in a percent format.

- Date Picker
A date picker allows users to select a date and/or time.  By using the picker, the information is consistently formatted and input into the system.

- Pagination	
Pagination divides content up between pages, and allows users to skip between pages or go in order through the content.

- Icons
An icon is a simplified image serving as an intuitive symbol that is used to help users to navigate the system.  Typically, icons are hyperlinked

- Modal Window (pop-up)
A modal window requires users to interact with it in some way before they can return to the system.

- MessageBox
Message Boxes	A message box is a small window that provides information to users and requires them to take an action before they can move forward.
