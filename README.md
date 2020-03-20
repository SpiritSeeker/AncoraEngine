# Ancora
Ancora Engine

## Cloning the repo
```shell
git clone --recurse-submodules https://github.com/SpiritSeeker/Ancora
```

## Linux

### Dependencies
```shell
sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
```

### Compiling and running
From inside the root Ancora directory, run
```shell
vendor/bin/premake/premake5 gmake
make
./bin/Debug-linux-x86_64/Sandbox/Sandbox
```
## Windows

### Compiling and running
From inside the root Ancora directory, run the ```GenerateProjects.bat``` file by double clicking it.
This should generate a Visual Studio 2017 solution file. Open the solution with Visual Studio.