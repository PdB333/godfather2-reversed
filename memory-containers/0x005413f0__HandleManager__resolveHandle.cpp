// FUNC_NAME: HandleManager::resolveHandle
// Function at 0x005413f0: Resolves a handle to a pointer based on the handle's type bits.
// Handles are 32-bit values where the top two bits indicate the type:
//   0x00 - invalid (returns 0xFFFFFFFF)
//   0x80 - Type A: direct pointer stored at (handle * 4 + 4) in a global table
//   0xC0 - Type B: indirect pointer via a secondary table at (handle * 4 + 0x60)
uint32_t HandleManager::resolveHandle(uint32_t handle)
{
    uint32_t result = 0xFFFFFFFFu; // -1 indicates invalid handle

    // Check handle type via top two bits
    if ((handle & 0xC0000000) == 0x80000000u)
    {
        // Type A: direct access into primary table
        if (handle * 4 != 0)
        {
            // Primary table is at absolute offset (handle * 4 + 4)
            // In reality, there is a global base pointer added; the decompiled output omitted it.
            result = *(uint32_t *)(handle * 4 + 4);
        }
    }
    else if ((handle & 0xC0000000) == 0xC0000000u)
    {
        // Type B: indirect via secondary table
        // First, read a pointer from offset (handle * 4 + 0x60)
        int *primaryPointer = *(int **)(handle * 4 + 0x60);
        if (primaryPointer != nullptr)
        {
            // Then dereference that pointer + 4 bytes to get the result
            result = *(uint32_t *)((uint8_t *)primaryPointer + 4);
        }
    }

    return result;
}