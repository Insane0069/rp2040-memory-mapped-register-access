#ifndef REGISTER_H
#define REGISTER_H

/******************************************************************************
 * @file    register.h
 * @brief   Generic register access macros for RP2040.
 *
 * @author  BALA
 * @date    2026
 ******************************************************************************/

#include <stdint.h>

/*
 * Access a 32-bit memory-mapped register.
 *
 * Example:
 * REG32(0x40014000) = 0x12345678;
 * uint32_t value = REG32(0x40014000);
 */
#define REG32(addr) (*(volatile uint32_t *)(addr))

#endif /* REGISTER_H */