# rp2040-memory-mapped-register-access
This repository demonstrates the fundamental mechanics of Memory-Mapped I/O (MMIO) on the Raspberry Pi RP2040 microcontroller. Operating completely at the bare-metal level without a Hardware Abstraction Layer (HAL) or standard SDK, this project serves as an educational blueprint for understanding how software directly manipulates hardware.

# RP2040 Register Access

## Project Overview

This repository demonstrates the fundamental concept of **memory-mapped register access** in embedded systems using the RP2040 microcontroller.

Instead of using high-level SDK functions, this project explains how a CPU communicates directly with hardware by reading from and writing to memory-mapped registers. It introduces the core concepts of pointers, pointer casting, the `volatile` keyword, and a reusable register access macro.

This repository serves as the foundation for all future firmware drivers such as GPIO, UART, SPI, I2C, ADC, PWM, DMA, and PIO.

---

# Objectives

After completing this repository, you should be able to:

- Understand Memory-Mapped I/O
- Understand what hardware registers are
- Learn how registers are accessed in Embedded C
- Understand pointer casting
- Understand the purpose of the `volatile` keyword
- Create and use a reusable `REG32()` macro

---

# Prerequisites

Before starting this project, you should know:

- Basic C programming
- Variables
- Functions
- Basic pointers
- Basic understanding of memory

---

# What is a Register?

A **register** is a special memory location inside a microcontroller that is used to control hardware peripherals.

Unlike normal variables stored in RAM, hardware registers interact directly with peripherals.

For example,

- Turning ON an LED
- Reading a push button
- Sending data through UART
- Configuring SPI

All of these operations are performed by reading or writing hardware registers.

---

# Memory-Mapped I/O

In embedded systems, peripherals are assigned fixed memory addresses.

Instead of using special instructions, the CPU accesses peripherals just like normal memory.

```text
           CPU
            │
            ▼
     Memory Address
            │
            ▼
  Peripheral Register
            │
            ▼
         Hardware
```

Example:

```c
*(volatile uint32_t *)0x40014000 = 0x12345678;
```

The CPU writes directly to the register located at address `0x40014000`.

---

# Pointer Basics

A pointer stores the address of another variable.

Example:

```c
uint32_t *ptr;
```

Here,

- `ptr` stores a memory address.
- It does **not** store the actual value.

To access the value stored at that address, we use the dereference operator (`*`).

Example:

```c
uint32_t value = *ptr;
```

---

# Pointer Casting

Memory addresses are just numbers.

Before accessing them, we must tell the compiler what type of data exists at that address.

Example:

```c
(uint32_t *)0x40014000
```

This tells the compiler:

> "Treat address `0x40014000` as a pointer to a 32-bit unsigned integer."

---

# What is `volatile`?

Hardware registers can change at any time without the program modifying them.

Without `volatile`, the compiler may optimize away register accesses.

```text
Without volatile

Compiler Optimization
        │
        ▼
Incorrect Hardware Behaviour
```

With `volatile`

```text
Always Read Memory
Always Write Memory
No Optimization
```

Therefore, hardware registers are always declared as `volatile`.

Example:

```c
volatile uint32_t *ptr;
```

---

# Understanding `REG32()`

The register access macro used in this project is:

```c
#define REG32(addr) (*(volatile uint32_t *)(uintptr_t)(addr))
```

Let's break it down.

### `addr`

The memory address of the register.

Example:

```text
0x40014000
```

---

### `(uintptr_t)`

Converts the address into an integer type capable of safely holding pointer values.

---

### `(uint32_t *)`

Treats the address as a pointer to a 32-bit register.

---

### `volatile`

Prevents compiler optimizations and ensures every read and write accesses the hardware.

---

### `*`

Dereferences the pointer and accesses the register value.

---

# Code Example

```c
REG32(TEST_MEMORY_ADDRESS) = 0x12345678;

uint32_t value = REG32(TEST_MEMORY_ADDRESS);
```

### What happens?

1. `REG32()` converts the address into a pointer.
2. The pointer is dereferenced.
3. The CPU writes the value to that address.
4. The value is read back from the same address.

---

# Folder Structure

```text
rp2040-register-access/
│
├── .gitignore
├── CMakeLists.txt
├── LICENSE
├── README.md
│
├── include/
│   └── register.h
│
└── src/
    └── main.c
```

---

# Build Instructions

## Configure

```bash
mkdir build
cd build
cmake ..
```

## Build

```bash
cmake --build .
```

## Flash

Generate the `.uf2` file and copy it to the Raspberry Pi Pico while it is in BOOTSEL mode.

---

# Interview Questions

Try answering these questions before moving to the next repository.

1. What is a hardware register?

2. What is Memory-Mapped I/O?

3. Why do embedded systems use memory-mapped registers?

4. What is a pointer?

5. What is pointer casting?

6. What does the dereference operator (`*`) do?

7. Why is the `volatile` keyword required?

8. Why use a macro instead of a function for register access?

9. What would happen if `volatile` were removed?

10. Explain the `REG32()` macro line by line.

---

# References

- RP2040 Datasheet
- ARM Cortex-M0+ Technical Reference Manual
- C Standard Library (`stdint.h`)

---

# What I Learned

- I learned how hardware registers are accessed using memory addresses.
- I understood the concept of Memory-Mapped I/O.
- I learned how pointers are used to access hardware.
- I understood why pointer casting is required.
- I learned why the `volatile` keyword is essential for hardware registers.
- I created a reusable register access macro using Embedded C.
- I understood how direct register access forms the foundation of embedded firmware development.

---

# Next Repository

➡️ **RP2040 GPIO Driver**

In the next repository, the `REG32()` macro developed here will be used to access actual RP2040 GPIO registers and build a reusable GPIO driver from scratch.
