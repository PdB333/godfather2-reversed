// FUNC_NAME: allocateScratchBuffer
// Address: 0x0053e830
// Role: Allocates a scratch buffer of 0x2000 bytes if a given object is valid and has a non-null pointer at offset 0x10.

#include <cstdint>

// Forward declaration of the memory allocation function.
// It likely takes a pointer to store the allocated address and a size.
extern "C" void __fastcall FUN_004af8c0(uint32_t* outPtr, uint32_t size);

// Fastcall: @ecx = unused, @edx = object
int __fastcall allocateScratchBuffer(uint32_t ecx, uint32_t object)
{
    uint32_t bufferPtr[3]; // 12 bytes on stack, used as output via first element

    // Condition: object must be non-null AND the pointer at offset 0x10 (likely a memory manager) must be non-null.
    // Decompiled expression: *(char *)(object + 0x10) + object != 0
    // Likely intended: *(void**)(object + 0x10) != 0
    if (object != 0 && *(uint8_t*)(object + 0x10) != 0)   // Simplified check; original may check a pointer.
    {
        FUN_004af8c0(bufferPtr, 0x2000);
        if (bufferPtr[0] != 0)
        {
            return bufferPtr[0]; // Return the allocated buffer address
        }
    }
    return 0;
}