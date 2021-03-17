# RQEngine 
[![Build Status](https://travis-ci.com/IndecisionGames/RQEngine.svg?branch=main)](https://travis-ci.com/IndecisionGames/RQEngine)

<!-- ## Current output

![Output](./res/result.gif) -->

## Getting started

Follow the steps below to get started.


### Setting up MinGW64 for Windows Development

Requirement - [7zip](https://www.7-zip.org/)

1) Download:
    - [MinGW64](https://sourceforge.net/projects/mingw-w64/)

2) Unzip using 7zip into a temporary folder, you may have to unzip multiple times.
3) Move the `mingw64` folder to a more permanent location such as `C:\mingw64` 
4) Add the `/bin` folder inside this folder to your `PATH`. So if you placed MinGW64 in `C:\mingw64` then you would add `C:\mingw64\bin` to your system environment's PATH variable.

### Setting up SDL2 in Xcode for Mac Development

1) In a terminal run: `brew install sdl2 sdl2_image sdl2_ttf`
2) Create a new Xcode command line project and add the repo's contents to the project folder within Xcode
3) Open the target settings by clicking on the xcodeproj file
4) General -> Add Frameworks and Libraries -> add `libSDL2-2.0.0.dylib`, `libSDL2_image-2.0.0.dylib` and `libSDL2_ttf-2.0.0.dylib`
5) Build Settings -> Search Paths -> Header Search Paths -> add `/usr/local/include`

### Using make in Windows

You need to use a bash terminal, such as [Git BASH](https://gitforwindows.org/) from the root directory.

To build the project use: 
```
mingw32-make.exe
```

To build **and** run the project use:
```
mingw32-make.exe run
```

### Setting up VSCode for Windows

1) Download and install VSCode from [here](https://code.visualstudio.com/)
2) Open VSCode and install the **C/C++ extension** by **Microsoft**
3) Open the project folder in VSCode (the root folder for this repo)
4) Make the following changes to the files inside `.vscode`: (assuming you are using the file locations mentioned above)

#### _c_cpp_properties.json_

Replace the following line: 

```
"compilerPath": "F:/libraries/mingw64/bin/gcc.exe",
```

with:
```
"compilerPath": "C:/mingw64/bin/gcc.exe",
```

#### _launch.json_

Replace the following line: 

```
"miDebuggerPath": "F:/libraries/mingw64/bin/gdb.exe",
```

With:
```
"miDebuggerPath": "C:/mingw64/bin/gdb.exe",
```

If everything has gone well you should be able to build and run the project with **Terminal > Run Build Task**. A window should appear for a few seconds if it has worked.

## Resources

- [Video series by codergopher on YouTube](https://www.youtube.com/watch?v=KsG6dJlLBDw&list=PL2RPjWnJduNmXHRYwdtublIPdlqocBoLS)
- [Game Programming SDL Tutorial by Lazy Foo](https://lazyfoo.net/tutorials/SDL/index.php#Hello%20SDL)
