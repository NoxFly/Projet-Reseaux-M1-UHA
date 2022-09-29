# Projet Réseaux M1 UHA

## Used Technologies

Outil | Version
------|--------
C++   | 20
SFML  | 2.5
OS    | Linux

# Dependencies

Of course a compiler (gcc or clang), and a bash support.

```sh
sudo apt-get install make libsfml-dev
```


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
