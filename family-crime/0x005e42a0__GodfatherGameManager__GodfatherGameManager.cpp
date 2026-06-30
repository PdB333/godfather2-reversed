// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
void __thiscall GodfatherGameManager::GodfatherGameManager(void)
{
    // Set vtable pointer at offset 0
    this->vtable = &g_GodfatherGameManagerVTable; // PTR_FUN_00e3f6a4

    // Zero out a large block of fields (indices 0x1804 through 0x1810)
    // These are likely arrays or member variables at high offsets
    for (int i = 0x1804; i <= 0x1810; ++i)
    {
        ((int*)this)[i] = 0;
    }

    // Store singleton pointer globally
    g_pGodfatherGameManager = this; // DAT_012234bc

    // Explicitly zero index 0x1809 (already zeroed in loop)
    ((int*)this)[0x1809] = 0;

    // Release and nullify pointer at index 0x1808
    releasePointer((void*)((int*)this)[0x1808]); // FUN_009c8f10
    ((int*)this)[0x1808] = 0;

    // Zero index 0x180a and 0x180c again (redundant but present in binary)
    ((int*)this)[0x180a] = 0;
    ((int*)this)[0x180c] = 0;

    // Release and nullify pointer at index 0x180b
    releasePointer((void*)((int*)this)[0x180b]); // FUN_009c8f10
    ((int*)this)[0x180b] = 0;

    // Zero index 0x180d (redundant)
    ((int*)this)[0x180d] = 0;

    return;
}