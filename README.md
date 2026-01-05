# STM32-Bare-Metal-LED-Blinking-No-HAL-
Bare-metal STM32 LED blinking example using direct register access (no HAL). Demonstrates RCC clock setup, GPIO configuration, and SysTick-based delay for stable timing and understanding low-level STM32 hardware behavior.

📌 Overview

This project demonstrates bare-metal programming on an STM32 microcontroller without using the HAL library.
It configures the system clock, GPIO, and SysTick timer directly using registers to blink an LED connected to GPIOB Pin 7.

The purpose of this repository is to:

Understand STM32 hardware registers
Learn clock configuration without HAL
Implement accurate delays using SysTick
Debug common bare-metal pitfalls (clock instability, SysTick misuse)

🧠 Key Concepts Covered

Direct RCC register programming
Switching system clock to HSI (16 MHz)
GPIO configuration using MODER, OTYPER, OSPEEDR, PUPDR
LED control using BSRR / BRR
Delay generation using SysTick COUNTFLAG
Differences between HAL-based and bare-metal execution

🛠️ Hardware Requirements

STM32 microcontroller (tested with STM32 L4/G4 family – addresses match RCC base 0x40021000)
LED connected to PB7 (with current-limiting resistor)
ST-Link or equivalent debugger

🧩 Software Requirements

STM32CubeIDE / GCC ARM toolchain
CMSIS startup files (default CubeIDE project)
No HAL drivers required

⚙️ How It Works

1️⃣ Clock Configuration

MCU starts on MSI by default
Code explicitly enables HSI (16 MHz) for stable timing
SysTick reload value is calculated based on HSI frequency

2️⃣ GPIO Configuration

GPIOB clock enabled via RCC_AHB2ENR
PB7 configured as:
Output mode
Push-pull
Low speed
Pull-up enabled

3️⃣ SysTick Timer

SysTick configured for 1 ms tick
Delay implemented by polling COUNTFLAG in SysTick CTRL register

4️⃣ LED Blinking Logic


🎯 Learning Outcome

Writing HAL-free STM32 code
Understanding the reset clock behavior
Using SysTick at register level
Debugging timing issues in bare-metal systems

⚠️ Pin mapping may vary depending on the board. Check your schematic.
