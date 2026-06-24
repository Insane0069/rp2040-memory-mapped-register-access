#include <stdint.h>
#include "register.h"

/*
 * We use an SRAM address only for demonstration.
 * This is NOT a peripheral register.
 */
#define TEST_MEMORY_ADDRESS 0x20000000

int main(void)
{
    /* Write a value */
    REG32(TEST_MEMORY_ADDRESS) = 0x12345678;

    /* Read the value back */
    uint32_t value = REG32(TEST_MEMORY_ADDRESS);

    /* Prevent compiler warning */
    (void)value;

    while (1)
    {
    }
}