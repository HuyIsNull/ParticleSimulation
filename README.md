# ParticleSimulation


ParticleSimulation is a simple particle simulation project written in C++ using SDL, purely for optimization study.

My objective is to run the simulation as fast as possible and with the least amount of memory usage.

Judge my English.


## Compile

``` Bash
cd ParticleSimulation
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

For maximum performance, add:

```
-DCMAKE_CXX_FLAGS="-O3 -march=native -flto"
```

If you don't have require packages by default, you can add:


## Run

``` Bash
./build/Particle
```


## Configuration

You can change number of particles in config.json. If the file doesn't exist, the program will create a default one.

> [!WARNING]
> Currently, there are no safe load on wrong configuration, the program will crash.


## Controls

* `Escape` - Quit.
* `R` - Reload.
