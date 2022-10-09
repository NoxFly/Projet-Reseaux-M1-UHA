# Projet Réseaux M1 UHA

## Used Technologies

Outil | Version
------|--------
C++   | 17
SFML  | 2.5
OS    | Linux or Windows with MingW

# Dependencies

Of course a compiler (gcc or clang), and a bash support.

## Linux

Install dependencies :

```sh
sudo apt-get install make libsfml-dev
```

The `libs/` folder is only for Windows's users.

## Windows

You only need to have a [MingW](https://www.msys2.org/) compiler with a `make` command.<br>
Usually, this is located in `C:\\msys64\\mingw64\\bin\\mingw32-make.exe`.<br>
You have to create a soft link of it in the same folder :
```sh
# on a terminal
# mklink src dest
mklink /d C:\\msys64\\mingw64\\bin\\mingw32-make.exe C:\\msys64\\mingw64\\bin\\make
```
Don't forget to add this folder in the PATH environment variable.

You don't have to install any libraries, these already are part of the project :
- The `.dll` are in the `bin/` folder
- The `.h[pp]` and `.lib` are in the `libs/` folder.


# Run

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

On Visual Studio Code :
- Press F5, or launch the debugguer.<br>It will run custom task, executing the run script.

# Authors

- Dorian Thivolle
- Farouk Brahimi
- Yanis Guezi
- Amir Sali
