# EEPROM_Database

<versionBadge>![Version 0.0.1](https://img.shields.io/badge/version-0.0.1-blue.svg)</versionBadge>
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![CI/CD Status Badge](https://github.com/Mrunmoy/EEPROM_Database/actions/workflows/ci.yml/badge.svg)](https://github.com/Mrunmoy/EEPROM_Database/actions)

This project provides a small C implementation of a flat-file database stored in EEPROM memory. It is intended for embedded systems that need a simple, structured way to persist device configuration, boot information and sensor data.

## Repository Layout

```
LICENSE   Makefile   README.md
img/      inc/       src/
```

- **`inc/`** – Header files defining the EEPROM layout, data types, and public API.
- **`src/`** – Implementations for EEPROM access, database routines, factory defaults, and a test program.
- **`img/`** – Contains `MydrawingStack.png`, an illustration of the data layout.
- **`Makefile`** – Builds the project (`EEDatabase`).

## Key Components

### Database Layout
Structures in `inc/database.h` describe how data is stored in EEPROM. The main structure, `EEDataLayout_t`, contains product details, shared boot/application information, a database signature and sensor entries. Offset macros let the code compute EEPROM addresses for each field.

### EEPROM Access Layer
`src/EEPROM_Mapping.c` implements helpers for reading and writing EEPROM. It can simulate EEPROM with an array or be adapted to real hardware. The function `EE_ReadWrite` dispatches read or write operations.

### Database Routines
`src/database.c` exposes initialization and read/write helpers for all database sections. Functions handle boot info, application info, product info, the database signature, and sensor data.

### Factory Defaults
`src/factory_defaults.c` resets the database to manufacturing defaults and writes the signature. This is useful to restore a clean database on first boot or after corruption.

### Test Program
`src/test.c` demonstrates basic usage. It initializes the database, updates product and application details, writes sensor data, and then reads them back for display.

## Building

Create a build directory and build with CMake:

```
mkdir build && cd build
cmake ..
cmake --build .
```

The resulting `EEDatabase` binary will be placed in `bin/` inside the build directory. The old Makefile is still provided for compatibility with existing workflows.

## Learning More

- Review `inc/porting.h` to see how data types are defined for portability across compilers.
- Study the offset macros in `database.h` if you need to modify the EEPROM layout.
- `EEPROM_Mapping.c` can be extended with real hardware access if you are integrating with an actual EEPROM device.

This repository is a starting point for managing small databases in embedded applications. Use the code as a reference for structuring and manipulating EEPROM-based data.

