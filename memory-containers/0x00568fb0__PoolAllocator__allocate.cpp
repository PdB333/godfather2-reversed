// FUNC_NAME: PoolAllocator::allocate
// Address: 0x00568fb0
// Role: Allocates a slot from a static pool. Returns pointer to the slot data, or nullptr if full.
// The pool has 64 slots (0x5400/0x150). Each slot's data block is 0x54 bytes? But offsets used
// (0x00,0x04,0x108,0x10C,0x120) exceed 0x54, so data likely consists of separate arrays.
// In-use flags are stored in a separate array with stride 0x150.

static void* allocate() {
    for (int slotIndex = 0; slotIndex < 64; ++slotIndex) {
        // Check if slot is free (flag at g_inUse + slotIndex*0x150)
        if (*(char*)(g_inUse + slotIndex * 0x150) == 0) {
            // Zero out various fields of the slot data
            *(int*)(g_dataBlock1 + slotIndex * 0x54) = 0;          // +0x00
            *(int*)(g_dataBlock2 + slotIndex * 0x54) = 0;          // +0x04
            *(int*)(g_dataBlock3 + slotIndex * 0x54) = 0;          // +0x108
            *(int*)(g_dataBlock4 + slotIndex * 0x54) = 0;          // +0x10C
            *(int*)(g_dataBlock5 + slotIndex * 0x54) = 0;          // +0x120
            // Mark slot as in-use
            *(char*)(g_inUse + slotIndex * 0x150) = 1;
            // Return pointer to the start of slot data (g_dataBlock1 + slotIndex*0x54)
            return (void*)(g_dataBlock1 + slotIndex * 0x54);
        }
    }
    return nullptr;
}