# Projet Réseaux M1 UHA

## Used Technologies

Outil | Version
------|--------
C++   | 17
SFML  | 2.5
TGUI  | 0.9
OS    | Linux or Windows with MingW

## Execute release

The released executable is in the `bin/` folder.


## Dev Dependencies

Of course a compiler (gcc or clang), and a bash support.

## Linux

Install dependencies :

```sh
sudo apt-get install make libsfml-dev
```


To install TGUI :

```
./install/tgui.sh
```


The `libs/` folder is only for Windows's users.

## Windows

### Visual Studio

/         | /
----------|---------
Version   | 2019
Mode      | Release
Platform  | x64

* The Win32 platform is not supported, because we loaded TGUI from sources with platform target x64 only.

* The Debug mode is for now unabled to use, but we will fix it in the future.

* Libraries are provided directly in the repository, and the solution has already be setup. It means that you can directly launch the solution.

### MingW

The project worked with MingW until we added TGUI library (loaded from sources).

Now we have setup the project so it works on Visual Studio 2019.

Required setup :

* MingW - with GCC and Make : `pacman -S mingw-w64-x86_65-make mingw-w64-x86_64-toolchain`,
* A symlink of the mingw-make : `mklink /d C:\\msys64\\mingw64\\bin\\mingw32-make.exe C:\\msys64\\mingw64\\bin\\make`,
* The `C:\\msys64\\mingw64\\bin` folder in the PATH environment variables.

On Git Bash, you can now execute the code like a Unix environment do from CLI.


# Run

Run.sh manual :
```sh
# give rights to execute the script manager
chmod 755 ./run.sh

# help
./run.sh -h

# to build then run in dev mode (default)
./run.sh
# to build then run with verbose
./run.sh -v
# to rebuild the entire solution then run
./run.sh -v -f
# to build without run
./run.sh -v --no-run
# to build then run in release mode
./run.sh -v -r
# to build then run in debug mode. Starts the debugger.
./run.sh -v -d
```

The run script compiles and runs if it succeed. It places the PWD in the `bin/` folder on the program execution, it's why resources are inside.

The command to compile/run the application:
```sh
./run.sh -v res/config.ini res/sample1.txt
```

On Visual Studio Code :
- Press F5, or launch the debugguer.<br>It will run custom task, executing the run script.

# Authors

- Dorian Thivolle
- Farouk Brahimi
- Yanis Guezi
- Amir Sali
