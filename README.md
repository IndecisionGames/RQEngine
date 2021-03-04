# RQEngine

## Getting started

Follow the steps below to get started.

### Setting up SDL2 and MinGW64 

_Note: this only works on a **Windows** development environment_

Requirement - [7zip](https://www.7-zip.org/)

1) Download:
    - [MinGW64](https://sourceforge.net/projects/mingw-w64/)
    - [SDL2](https://www.libsdl.org/download-2.0.php) - Choose the MinGW 32/64 bit Development library
    - [SDL2_Image](https://www.libsdl.org/projects/SDL_image/) - Choose the MinGW 32/64 bit Development library
2) Unzip all 3 files using 7zip, you may have to unzip some of the files multiple times, into a temporary folder.
3) Move the `mingw64` folder to a more permanent place such as `C:\mingw64` 
4) Add the `/bin` folder to your `PATH`. So if you placed MinGW64 in `C:\mingw64` then you would add `C:\mingw64\bin` in your system environment's PATH variable.
5) Merge the contents of the `x86_64-mingw32` folder inside both of the SDL folder you extracted and move only the merged `x86_64-mingw32` folder to a permanent location such as `C:\x86_64-mingw32` (I recommend renaming this folder to something like `C:\SDL2-w64`)

### Setting up VSCode

1) Download and install VSCode from [here](https://code.visualstudio.com/)
2) Open VSCode and install the **C/C++ extension** by **Microsoft**
3) Open the project folder in VSCode (the root folder for this repo)
4) Make the following changes to the files inside `.vscode`: (assuming you are using the file locations mentioned above)

#### _c_cpp_properties.json_

Replace the following lines: 

```
"F:\\libraries\\SDL2-w64\\include"

"compilerPath": "F:/libraries/mingw64/bin/gcc.exe",
```

With:
```
"C:\\SDL2-w64\\include"

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

#### _tasks.json_

In **both** `command` lines replace the following: 

```
F:/libraries/SDL2-w64/include
F:/libraries/SDL2-w64/lib
```

With:
```
C:/SDL2-w64/include
C:/SDL2-w64/lib
```

If everything has gone well you should be able to build and run the project with **F5**. A window should appear for a few seconds if it has worked.

## Resources

- [Video series by codergopher on YouTube](https://www.youtube.com/watch?v=KsG6dJlLBDw&list=PL2RPjWnJduNmXHRYwdtublIPdlqocBoLS)
- [Game Programming SDL Tutorial by Lazy Foo](https://lazyfoo.net/tutorials/SDL/index.php#Hello%20SDL)