# Educational BSOD Experiment

This repository contains a small Windows-focused C/C++ experiment for studying
low-level system error behavior in a controlled lab environment.

The code is intended for educational use only. Run it only on systems you own or
administer, preferably inside a disposable virtual machine. Do not run it on
production systems, shared machines, or any computer where a forced crash could
cause data loss or disruption.

Prebuilt binaries and system DLLs are intentionally not versioned.

## Project layout

- `src/main.cpp`: command-line entry point and safety confirmation gate.
- `include/raise_hard_error.hpp`: Windows native API declarations used by the
  experiment.
- `CMakeLists.txt`: CMake build configuration.

## Build

This project targets Windows and requires a Windows C++ toolchain.

```sh
cmake -S . -B build
cmake --build build
```

## Run

The executable prints usage information unless an explicit confirmation flag is
provided.

```sh
educational_bsod_experiment.exe --i-understand-this-will-crash
```

Only run it inside an isolated lab machine or disposable virtual machine.
