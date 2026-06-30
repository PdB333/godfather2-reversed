// FUNC_NAME: resolveGameHandle
// Address: 0x005413f0
// Role: Resolves a game handle using top 2 bits as type selector.
// Type 0x80000000: handle*4 -> index into 4-byte table, read uint32 at offset +4.
// Type 0xC0000000: handle*4 -> pointer table at offset +0x60, then dereference +4.
// Other or invalid returns 0xFFFFFFFF.

#include <cstdint>

uint32_t resolveGameHandle(uint32_t handle)
{
    uint32_t result = 0xFFFFFFFF;

    uint32_t typeBits = handle & 0xC0000000; // Extract bits 30-31

    if (typeBits == 0x80000000) // Type 2: direct index
    {
        uint32_t rawOffset = handle * 4;
        if (rawOffset != 0) // guard against handle==0
        {
            result = *(uint32_t*)(rawOffset + 4); // Read from table at offset+0x4
        }
    }
    else if (typeBits == 0xC0000000) // Type 3: indirect via pointer table
    {
        uint32_t rawOffset = handle * 4;
        int* ptrTableEntry = *(int**)(rawOffset + 0x60); // +0x60: base of pointer array 
        if (ptrTableEntry != nullptr)
        {
            result = *(uint32_t*)(ptrTableEntry + 4); // Offset +4 in the pointed struct
        }
    }
    // Types 0x00000000 and 0x40000000 fall through to default 0xFFFFFFFF

    return result;
}