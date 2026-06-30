// FUNC_NAME: Serializer::packVehicleStateData

#include <cstdint>

// Global function pointer table (likely vtable for a byte-stream writer type)
// Offset +0x10 contains a memcpy-like function: void (*)(void* dest, const void* src, uint32_t size)
extern void** DAT_01205590;

typedef void (__fastcall *CopyFunc_t)(void* dest, const void* src, uint32_t size);

uint32_t __fastcall packStructWithHeader(void* dest, const void* source)
{
    // Write 2-byte packet type identifier (0x0204) at offset 0
    uint16_t packetType = 0x0204;
    ((CopyFunc_t)(DAT_01205590[0x10 / sizeof(void*)]))(dest, &packetType, 2);

    // Write 2-byte data size (0x001c = 28 bytes) at offset 2
    uint16_t dataSize = 0x001c;
    ((CopyFunc_t)(DAT_01205590[0x10 / sizeof(void*)]))((uint8_t*)dest + 2, &dataSize, 2);

    // Copy 4 bytes from source+0x20 to dest+4
    ((CopyFunc_t)(DAT_01205590[0x10 / sizeof(void*)]))((uint8_t*)dest + 4, (const uint8_t*)source + 0x20, 4);

    // Copy 16 bytes from source+0x10 to dest+8
    ((CopyFunc_t)(DAT_01205590[0x10 / sizeof(void*)]))((uint8_t*)dest + 8, (const uint8_t*)source + 0x10, 16);

    // Copy 4 bytes from source+0x40 to dest+0x18
    ((CopyFunc_t)(DAT_01205590[0x10 / sizeof(void*)]))((uint8_t*)dest + 0x18, (const uint8_t*)source + 0x40, 4);

    return 0x1c; // Total bytes written (2+2+4+16+4)
}