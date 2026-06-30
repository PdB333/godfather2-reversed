// FUNC_NAME: threadLocalReadIndexedValue
#include <cstdint>

uint32_t __cdecl threadLocalReadIndexedValue(int32_t index)
{
    // On x86 Windows, FS:[0x2C] holds a pointer to the Thread Local Storage array
    // (an array of pointers to each thread's TLS block).
    void* tlsArrayPtr = (void*)__readfsdword(0x2C);  // Read FS:[0x2C] as a pointer

    // The first element of the TLS array points to the TLS block for the current thread.
    void* tlsBlock = *(void**)tlsArrayPtr;

    // Read a 16-bit value from the TLS block at offset 0xC + index*2
    uint16_t lowWord = *(uint16_t*)((uint8_t*)tlsBlock + 0xC + index * 2);

    // High 16 bits are taken from the upper half of the TLS array pointer's address.
    uint16_t highWord = (uint16_t)((uint32_t)tlsArrayPtr >> 16);

    return ((uint32_t)highWord << 16) | lowWord;
}