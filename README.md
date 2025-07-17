DMA-Based UART Transmission on STM32F401RE (Bare-Metal):-
This project demonstrates how to use DMA to transmit data over USART2 on the STM32 Nucleo-F401RE board using pure bare-metal (register-level) programming via CMSIS. No HAL, no CubeMX, no abstraction layers.

What This Project Does:
1. Sends "Hello from DMA!\r\n" via USART2 (PA2 TX)
2. Uses DMA1 Stream6, Channel 4 to transmit data
3. Frees the CPU from busy-wait or interrupt handling
4. Ideal for high-speed or background UART transfers

Key Concepts Implemented:
1. DMA configuration in memory-to-peripheral mode
2. CMSIS-level configuration of USART2 and DMA1
3. Direct register access for DMA and USART
4. Blocking-free UART transmission using TC flag
5. Lays the foundation for interrupt-based and circular DMA

Hardware Configuration:
Peripheral: USART2 TX
Pin: PA2
Baud Rate: 115200
DMA Stream: DMA1 Stream6
DMA Channel: Channel 4
Direction: Memory to Peripheral

How to View Output:
Option 1: Use a USB-to-UART module
Connect PA2 (TX) from Nucleo to RX of USB-UART
Open a serial terminal (TeraTerm, PuTTY, Arduino Serial Monitor)
Set baud rate to 115200
Output should display:
Hello from DMA!

Option 2: Use ST-Link Virtual COM Port
Check if your Nucleo board exposes USART2 via USB
If yes, open the detected COM port at 115200 baud


How to Build:
Option 1: Using STM32CubeIDE
Open STM32CubeIDE and create a new STM32 project for Nucleo-F401RE
Choose "Empty" project without HAL or CubeMX code generation
Add the provided main.c, startup_stm32f401xe.s, and any custom headers into the project under Core/Src and Core/Inc folders
Make sure your project includes CMSIS core and device header files (they are usually included automatically)
Build and flash the project to your board using the IDE’s built-in debugger

Option 2: Using Makefile + arm-none-eabi toolchain
Create a basic Makefile-based project structure
Include the following in your project directory:
main.c (your application logic)
startup_stm32f401xe.s (startup vector table)
stm32f4xx.h and CMSIS core files (from STM32CubeF4 package)
STM32F401RE_FLASH.ld linker script (or use default from STM32CubeIDE)
Use the arm-none-eabi-gcc toolchain to compile and link

Flash the .elf or .bin file using ST-Link CLI or open-source tools like st-flash or OpenOCD


