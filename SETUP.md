# Development Environment

## System
- OS: Ubuntu 24.04
- Architecture: x86_64

## Toolchain
- Compiler: g++ (GCC) — installed via `build-essential`
- Build system: CMake (planned)
- Debugger: GDB
- Editor: VS Code and CLion

## Installation Steps

```bash
sudo apt update
sudo apt install build-essential gdb cmake
```

## Verification

```bash
g++ --version
gdb --version
cmake --version
```

## Standard Compile Flags

For learning and debugging:
```bash
g++ -std=c++20 -Wall -Wextra -Wpedantic -g -O0 file.cpp -o file
```

For release/benchmark builds:
```bash
g++ -std=c++20 -O3 -DNDEBUG file.cpp -o file
```
