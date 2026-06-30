// FUNC_NAME: getTypeId

// Function at 0x0054a4d0 - Simple getter returning value at this+0x8.
// Likely returns an object type ID, class ID, or handle stored at offset +0x8.
uint32_t __fastcall getTypeId(void* thisPtr)
{
    // Offset +0x8: typically a 4-byte identifier (e.g., type hash, network ID)
    return *(uint32_t*)((uint8_t*)thisPtr + 8);
}