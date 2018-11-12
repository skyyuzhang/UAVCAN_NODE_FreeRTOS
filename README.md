# UAVCAN_NODE_FreeRTOS
NOTE: This program is being complete.
## Documentation 
As an UVACAN node implemented by lincanrd, the FreeRTOS-based program is used which means you could operate more tasks while the lincanard is implemented as long as each task have been allocated for enough memory. as for the hardware I choose the STM32F103C8 and JTA051 CAN, which is ordinary and cheap. the hold program is generate by STM32CubeMX. I choose it beacuse it is simple and easy to use. you can make basic configuration just few more setting.   
## function
the function is simple I port ZUBAX basic tutorial into my projetc meanwhile I will make more my own program 
* Basic tutorial
* Subscriber tutorial
* Publisher tutorial
* Service tutorial
## hardware
working on it!!!!
## Build Instructions
Prerequisites:
* GCC ARM(mine is 6.3.1 the others version should be working)
* Ubuntu
* win10(working on it)
```bash
git submodule update --init --recursive
make
make stlink # compile and download use stlink
```
