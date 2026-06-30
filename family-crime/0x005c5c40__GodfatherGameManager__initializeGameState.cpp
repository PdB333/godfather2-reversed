// FUNC_NAME: GodfatherGameManager::initializeGameState
void GodfatherGameManager::initializeGameState(void)
{
    uint *puVar1;
    int unaff_ESI; // this pointer (likely GodfatherGameManager*)
    
    // +0x01205655: some flag (e.g., m_bInitializing)
    DAT_01205655 = 1;
    
    if (unaff_ESI == 0) {
        // If this is null, call a separate initialization path
        FUN_005c4ac0(); // likely GodfatherGameManager::initNewGame or similar
    }
    else {
        // Stack-based allocation pattern (EASTL or custom allocator)
        puVar1 = (uint *)(DAT_01206880 + 0x14); // +0x14: stack pointer offset
        **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_01126af0; // vtable or allocator
        *puVar1 = *puVar1 + 4;
        *(undefined1 *)*puVar1 = 0; // push 0 (null)
        *puVar1 = *puVar1 + 4 & 0xfffffffc; // align to 4 bytes
    }
    
    // Initialize various game state globals
    DAT_0120569c = 0;  // +0x0120569c: some counter/flag
    _DAT_01205674 = 0; // +0x01205674: game time or tick
    _DAT_0120567c = 0; // +0x0120567c: another timer
    DAT_0119da54 = 0;  // +0x0119da54: mission state
    DAT_0119d0a8 = 0x3e; // +0x0119d0a8: some constant (62 = 0x3E)
    DAT_01205688 = 0;  // +0x01205688: flag
    DAT_01205657 = 0;  // +0x01205657: flag
    DAT_01205684 = 0;  // +0x01205684: flag
    _DAT_01205678 = 0; // +0x01205678: flag
    DAT_00f1765c = 0xfffffffe; // +0x00f1765c: -2 (some sentinel value)
    DAT_00f17658 = 9;  // +0x00f17658: 9 (max family members or similar)
    
    // Call subsystem initializers
    FUN_0059e9b0(); // likely GameplayManager::initialize
    FUN_005d8020(); // likely MissionManager::initialize
    FUN_005c4bf0(); // likely CrimeManager::initialize
    
    // Clear initialization flag
    DAT_01205655 = 0;
    
    if (unaff_ESI != 0) {
        // Pop the stack allocation
        puVar1 = (uint *)(DAT_01206880 + 0x14);
        **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_01126af0;
        *puVar1 = *puVar1 + 4;
        *(undefined1 *)*puVar1 = 1; // push 1 (true)
        *puVar1 = *puVar1 + 4 & 0xfffffffc;
    }
    
    return;
}