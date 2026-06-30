// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
undefined4* __fastcall GodfatherGameManager::GodfatherGameManager(undefined4* this) {
    int* pSomeBuffer;

    this[1] = 1;                       // +0x04: m_bInitialized (or enabled flag)
    this[2] = 0;                       // +0x08: m_nCounter
    this[3] = &PTR_LAB_00d5d898;       // +0x0C: base vtable (first base class)
    g_pGodfatherGameManager = this;    // store singleton instance
    *this = &PTR_FUN_00d5d8b8;         // +0x00: main vtable pointer
    this[3] = &PTR_LAB_00d5d8b4;       // +0x0C: overwrite with derived vtable (likely second base)
    *(byte*)(this + 4) = 0;            // +0x10: m_bSomeFlag
    pSomeBuffer = this + 5;            // +0x14: m_pAllocation (pointer to a buffer)
    *pSomeBuffer = 0;                  // null it out
    this[6] = 0;                       // +0x18: m_nSomeCount
    this[7] = 0;                       // +0x1C: m_nSomeIndex
    *(byte*)(this + 8) = 0;            // +0x20: m_bAnotherFlag
    if (*pSomeBuffer != 0) {
        FUN_004daf90(pSomeBuffer);     // deallocate if non-null
        *pSomeBuffer = 0;
    }
    this[7] = 0;                       // redundant zero
    return this;
}