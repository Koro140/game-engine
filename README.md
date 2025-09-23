# Game Engine in C
A cross-platform game engine written in C, using the GLFW/GLad library.

## Requirements
Before building, make sure you have the following installed:

- **CMake** (version 3.10 or newer)
- **C compiler**
  - GCC or Clang on Linux/macOS
  - MSVC (Visual Studio) on Windows
- **Git** (to fetch this repository and submodules)

## Installation
to clone this repository with the dependancies you should:

```
git clone --recursive https://github.com/Koro140/game-engine.git
```

## Building
  This project uses CMake , making it portable across Windows, Linux, and macOS.

Build from the command line (Windows / Linux / macOS):

```
  mkdir build
  cd build
  cmake ..
  cmake --build .
```
The compiled executable will be inside the build folder.

### On Windows using Visual Studio
 
 1. Open the project folder in Visual Studio.

 2. Let CMake configure automatically.

 3. Select the App target and build/run it.
