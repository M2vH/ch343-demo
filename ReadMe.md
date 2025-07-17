# Comunication on COM Port

We are using Win11 as our host machine.
We are running ubuntu 22.04 on WSL2.
We bound and attached an UART module to USB.

We bound and aatached the USB Port to WSL using `usbipd`

Opening Ubuntu 22.04 on WSL:

    - we can see our UART Module as `/dev/ttyACM0`

## User Story

As a developer i want to test the communication with a simple commandline program.
The program `Test` will write and receive text on COM Port.
To check the integration, we will cross-connect the RX and TX line on themodule with hard wires.
The commandline program must be written in C++
The IDE must be VS Code
The program MUST run on the ubuntu 22.04 WSL2 container

## Clipboard

```cplusplus
# test.cpp
# code goes here
```

```bash
# bash
# build and debug using shell commands

```
