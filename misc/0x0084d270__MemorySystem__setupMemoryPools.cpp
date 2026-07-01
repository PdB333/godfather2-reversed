// FUNC_NAME: MemorySystem::setupMemoryPools
void MemorySystem::setupMemoryPools(void)
{
    // Check if the memory system instance exists (global at DAT_01223480 +0x54)
    if (*(int *)(DAT_01223480 + 0x54) != 0) {
        // Set allocation flags for various pool sizes
        FUN_00a67930(0x200000, 2);      // 2MB pool, type 2
        FUN_00a679d0(0x1000,  0x20000); // 4KB alignment, flag 0x20000
        FUN_00a679d0(0x800,   0x20000); // 2KB alignment, flag 0x20000
        FUN_00a679d0(0x800,   0x200);   // 2KB alignment, flag 0x200
        FUN_00a67930(0x800,   2);       // 2KB pool, type 2
        FUN_00a679d0(0x80,    0x100);   // 128B alignment, flag 0x100
        FUN_00a679d0(0x80,    0x20000); // 128B alignment, flag 0x20000
        FUN_00a67930(0x10000, 0x100);   // 64KB pool, flag 0x100
        FUN_00a67930(0x10000, 0x10000); // 64KB pool, flag 0x10000
        FUN_00a67930(0x10000, 0x4000);  // 64KB pool, flag 0x4000
    }
    return;
}