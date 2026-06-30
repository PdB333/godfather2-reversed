// FUNC_NAME: initializeNetworkMemoryPool
void initializeNetworkMemoryPool(void)
{
    void *arenaPtr;
    undefined4 local_c;
    undefined4 local_8;
    undefined4 local_4;

    local_c = 0;
    local_8 = 0;
    local_4 = 0;
    // DAT_01205868 is a global pointer to a factory/interface that creates a memory arena.
    // Get 0x28000 bytes of memory from the memory system.
    DAT_012054b0 = (**(code **)*DAT_01205868)(0x28000, &local_c);
    // Allocate a control structure of 0x8024 bytes using a custom allocator.
    void *controlBlock = (void *)FUN_009c8e50(0x8024);
    if (controlBlock != (void *)0x0) {
        // Set the flag at offset 0x8000 to 0 (perhaps end-of-buffer marker).
        *(undefined4 *)((int)controlBlock + 0x8000) = 0;
        // Zero out the first 0x8000 bytes of the control block.
        _memset(controlBlock, 0, 0x8000);
        // Initialize the arena with parameters: arena pointer, size 0x28000, chunk size 0x14, alignment 4.
        FUN_004abe90(DAT_012054b0, 0x28000, 0x14, 4);
        DAT_012054ac = controlBlock;
        return;
    }
    DAT_012054ac = (void *)0x0;
    return;
}