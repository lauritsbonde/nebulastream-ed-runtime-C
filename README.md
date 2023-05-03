<img alt="License" src="https://img.shields.io/badge/license-MIT-brightgreen.svg"/>

# NebulaStream End Device Runtime
An implementation of: [NebulaStream End Device Runtime]( https://github.com/FlapKap/nebulastream-ed-runtime) in C

## How to Build
The project is written as a [RIOT OS](https://github.com/RIOT-OS/RIOT/blob/master/examples/lorawan/main.c) application and uses the RIOT build system. Building requires a copy of the RIOT codebase either locally (linux only), in a docker container or on a virtual machine.

To build you must set the following variables in the `Makefile`
- `RIOTBASE` The path to you RIOT code base
- `BOARD` The specific board that riot should build for. [List of boards support by RIOT](https://doc.riot-os.org/group__boards.html).
- `DEVEUI`, `APPEUI`and `APPKEY`. Settings for your specific LoRaWAN connection

To build the application, flash to a device, and open a terminal to the flashed device, run:

`$ make flash term`

## Contributors
Laurits og Markus for Bachelor Thesis @ ITU
