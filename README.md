DMA-Based UART Transmission on STM32F401RE (Bare-Metal)
This project demonstrates how to use DMA to transmit data over USART2 on the STM32 Nucleo-F401RE board using pure bare-metal (CMSIS-based) programming — no HAL, no CubeMX, and no abstraction layers.

✅ What This Project Does:
1. Sends "Hello from DMA!\r\n" via USART2 (PA2 TX) every 1 second
2. Uses DMA1 Stream6, Channel 4 in Memory-to-Peripheral mode
3. Toggles the on-board LED (PA5) after each successful transmission
4. Waits for DMA transfer complete flag (TCIF6) and clears it manually
5. Demonstrates non-blocking periodic UART using timer delays

What You’ll Learn:
1. How to configure DMA streams to communicate with peripherals (like USART)
2. Setting up DMA1 Stream6 to point to USART2->DR register (PAR)
3. Assigning buffer address and size using M0AR and NDTR
4. Enabling USART2 for DMA transmission using CR3.DMAT
5. Polling the TCIF6 flag to detect DMA completion
6. How DMA offloads CPU by eliminating byte-wise USART TX management

⚙️ Key Concepts Implemented:
1. DMA-based UART TX (Memory → USART2)
2. CMSIS register-level configuration of DMA and USART
3. LED toggling as a status/debug indicator
4. 1-second delay using SysTick-based delay
5. Idle main loop; no busy-waiting or blocking during transmission
5. Foundation for implementing DMA RX and circular/ring-buffer-based communication

🛠️ Hardware Configuration:
1. Peripheral	USART2 (TX)
2. TX Pin	PA2
3. Baud Rate	115200
4. DMA Stream	DMA1 Stream6
5. DMA Channel	Channel 4
6. DMA Direction	Memory → Peripheral
7. LED Pin	PA5 (on-board LED)
8. Timing	1 second delay loop

🔍 How to View Output:
Option 1: USB-to-UART Module
Connect PA2 (TX) to RX of USB-to-UART converter
Open any serial terminal (PuTTY, TeraTerm, Arduino Serial Monitor)
Set baud rate to 115200
You’ll see repeated prints of:
Hello from DMA!

Option 2: ST-Link Virtual COM Port
Some Nucleo boards expose USART2 via ST-Link USB
If supported, open the detected COM port at 115200 baud

🛠️ How to Build & Flash:
Open STM32CubeIDE
Create a new STM32 project for Nucleo-F401RE
Select “Empty Project”, no HAL, no CubeMX auto-code
Add main.c, startup_stm32f401xe.s, and custom delay.h / delay.c if used
Ensure CMSIS core and device header files are included
Build and flash to the board using CubeIDE debugger
