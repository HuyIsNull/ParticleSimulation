# ParticleSimulation


ParticleSimulation is a simple particle simulation project written in C++ using SDL, purely for optimization study.

My objective is to run the simulation as fast as possible and with the least amount of memory usage.

Judge my English.


## Compile

``` Bash
cd ParticleSimulation
cmake -S . -B build
cmake --build build
```


## Run

``` Bash
./build/ParticleSimulation
```


## Configuration

You can change number of particles in config.json. If the file doesn't exist, the program will create a default one.



## Controls

* `Escape` - Reload( Don't ask why ).

That's it. More controls will be added in the future.
