// FUNC_NAME: extractIndexFromHandle
#include <cstdint>

// Function: 0x008a6370
// Calls FUN_008a6270 to process a 32-bit handle/ID and then returns its lower 16 bits.
// The sub-function at 0x008a6270 likely performs some extraction or validation,
// storing an intermediate result in the local buffer and possibly modifying the handle via pointer.
uint32_t extractIndexFromHandle(uint32_t handle)
{
    uint8_t localBuffer[4]; // Intermediate result buffer (unused in this function)
    FUN_008a6270(handle, localBuffer, &handle); // Pass handle by value, pointer to handle, and buffer
    return handle & 0xFFFF; // Return low 16 bits (presumably the index)
}