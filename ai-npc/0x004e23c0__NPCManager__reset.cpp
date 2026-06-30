// FUNC_NAME: NPCManager::reset
void NPCManager::reset(void)
{
    uint offset;
    
    // Call base class destructor or initialization
    FUN_004e1c40();
    
    // Reset global state variables
    g_ManagerData.m_iSomeFlag1 = 0;   // +0x102? Actually DAT_01218e42 is a byte? It's set to 0, but it's a uint? The decompiled shows DAT_01218e42 = 0; likely a byte or short. We'll treat as int.
    g_ManagerData.m_iSomeFlag2 = 0;   // +0x100
    g_ManagerData.m_iSomeFlag3 = 0;   // +0x108
    g_ManagerData.m_iSomeFlag4 = 0;   // +0x104
    g_ManagerData.m_iSomeFlag5 = 0;   // +0x10c (underscore indicates overlapping)
    
    // Free and clear an array of 20 pointers (each 8 bytes) starting at offset 0x110
    offset = 0x110;
    do {
        // Check if pointer at current offset is non-null
        if (*(int *)((int)&g_ManagerData + offset) != 0) {
            // Free the allocated memory (second parameter 0 might be size or flag)
            FUN_006065a0(*(int *)((int)&g_ManagerData + offset), 0);
        }
        // Clear the pointer (and possibly the next 4 bytes? But only pointer is cleared)
        *(undefined4 *)((int)&g_ManagerData + offset) = 0;
        offset += 8;
    } while (offset < 0x1b0);
    
    return;
}