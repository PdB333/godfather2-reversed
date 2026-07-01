// FUNC_NAME: SomeClass::clearBuffers (or initializer)
// Function address: 0x008230e0
// Purpose: Zeroes three 64-byte buffers at offsets 0x50, 0x90, 0xD0 within the object.
// Likely part of a constructor or reset function for a class that holds three arrays.
// The caller at 0x00830ce0 is probably a constructor.

void __thiscall clearBuffers(void* thisPtr)
{
    // Clear buffer 1 at offset 0x50 (64 bytes)
    _memset((void*)((unsigned int)thisPtr + 0x50), 0, 0x40);
    
    // Clear buffer 2 at offset 0x90 (64 bytes)
    _memset((void*)((unsigned int)thisPtr + 0x90), 0, 0x40);
    
    // Clear buffer 3 at offset 0xD0 (64 bytes)
    _memset((void*)((unsigned int)thisPtr + 0xD0), 0, 0x40);
    
    return;
}