// FUNC_NAME: MemoryPool::acquireBlock
int MemoryPool::acquireBlock(int param1, int param2) {
    // Allocate a block of 256 bytes (4 * 64 bytes) – likely a node or control structure
    void* allocatedMemory = calloc(4, 0x40);
    if (allocatedMemory == nullptr) {
        return -2; // Allocation failure
    }

    uint64_t magicAndFlags = 0x4000000000;           // Magic constant (maybe a free-list marker or flag)
    uint64_t pointerPacked = (uint64_t)allocatedMemory << 32; // Pack pointer into high 32 bits of a 64-bit field

    // Try to attach the new block to the pool via the internal reference pair (in_EAX points to a 128-bit structure)
    int result = FUN_00665d70(param1, param2, 0, &magicAndFlags); // This function likely atomically swaps or updates a pair of 64-bit values
    if (result == 0) {
        // Check if the low 32 bits of the pointerPacked field indicate a specific state (e.g., “1” means an empty slot or special condition)
        if ((int)pointerPacked == 1) {
            // Special case – process the new block with param2 and finalize
            int specialResult = FUN_006657c0(param2);
            FUN_00665b40(); // Cleanup/finalize
            return specialResult;
        }
        // Otherwise swap the internal reference with our new pair:
        // This replaces the old magic/flags and pointer with the new ones, returning the old values
        uint64_t oldMagic = *in_EAX;         // Assume in_EAX is a pointer to a global/class member pair
        uint64_t oldPointer = in_EAX[1];
        *in_EAX = magicAndFlags;
        in_EAX[1] = pointerPacked;
        magicAndFlags = oldMagic;
        pointerPacked = oldPointer;
        result = 0;
    }
    FUN_00665b40(); // Cleanup/finalize
    return result;
}