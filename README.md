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


# Features 

---

### Engine

- State Machine
- SmartMouse
- Resource Manager
  - Fonts | Textures | Sounds

### Shapes

- Polygon Shape
- Rounded Rectangle Shape
- Stadium Shape

### UI Elements

- Button
  - Rectangle | Circle | Polygon | RoundedRectangle | Stadium
- Checkbox
  - Single-Select | Multi-Select
- Dropdown
  - Single-Select | Multi-Select
- Slider
- Textbox
- Toggle
- Vertical Scroll Window

# Dependencies

###### - [CMake](https://cmake.org/download/) : Build Generator System
###### - [SFML](https://www.sfml-dev.org/download.php) : Simple and Fast Multimedia Library

#### MacOS | Linux
##### • CMake and SFML are both available formulae for the [Homebrew](https://brew.sh) Package Manager, which can be installed with one simple ruby command:

    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

##### • Then install dependencies

    brew install cmake
    brew install sfml

#### Windows
##### • There are pre-compiled binaries available on the Download page for Windows as MSI packages and ZIP files for both CMake and SFML. 

---

# Installing

#### Clone the main branch 

    git clone --branch main --single-branch https://github.com/austinmhorn/leafy.git

#### Generate **shared library** build files
    
    cmake -S . -B build

###### By default, the leafy library is built as a **shared library**, but can easily be built using **statically linked** standard/runtime libraries instead with a few flags
#### Generate **static library** build files

    cmake -S . -B build -DBUILD_SHARED_LIBS=OFF -DLEAFY_BUILD_SHARED_LIBS=OFF -DSFML_STATIC_LIBRARIES=ON 

#### Install target
    
    cmake --build build --config Release --target install

###### *If you're using this library in another project and wish to disable building the examples, you can prevent it with*

    -DLEAFY_BUILD_EXAMPLES=OFF

---

# Troubleshooting

###### - Missing library? Install all SFML dependencies with

      sudo apt-get update && sudo apt-get install libxrandr-dev libxcursor-dev libudev-dev libopenal-dev libflac-dev libvorbis-dev libgl1-mesa-dev libegl1-mesa-dev

Widgets to come:

### Progress Bar
A progress bar is a graphical control element used to visualize the progression of an extended computer operation, such as a download, file transfer, or installation. Sometimes, the graphic is accompanied by a textual representation of the progress in a percent format.

### Date Picker
A date picker allows users to select a date and/or time.  By using the picker, the information is consistently formatted and input into the system.

### Pagination	
Pagination divides content up between pages, and allows users to skip between pages or go in order through the content.

### Icons
An icon is a simplified image serving as an intuitive symbol that is used to help users to navigate the system.  Typically, icons are hyperlinked

### Modal Window (pop-up)
A modal window requires users to interact with it in some way before they can return to the system.

### MessageBox
Message Boxes	A message box is a small window that provides information to users and requires them to take an action before they can move forward.
