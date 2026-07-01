// FUNC_NAME: GodfatherGameManager::constructor
// Address: 0x00915f40
// Role: Initializes the GodfatherGameManager singleton, sets up vtable pointers, cleans up existing child objects, and resets global state.

void __fastcall GodfatherGameManager::constructor(GodfatherGameManager* this)
{
    // Set vtable pointers for multiple inheritance or interface slots
    // +0x00: Primary vtable pointer
    *this = &PTR_FUN_00d85008;
    // +0x10: Secondary vtable pointer
    this[4] = &PTR_LAB_00d84fe0;
    // +0x50: Another vtable pointer
    this[0x14] = &PTR_LAB_00d84fdc;
    // +0x54: Yet another vtable pointer
    this[0x15] = &PTR_LAB_00d84fcc;
    // +0x58: Additional vtable pointer
    this[0x16] = &PTR_LAB_00d84fb4;

    // Check if a child object exists at offset +0x64 (0x19 * 4)
    if (this[0x19] != 0) {
        // Clean up the existing child object (likely a sub-manager or component)
        FUN_009c8f10(this[0x19]);
    }

    // Update vtable pointer at +0x50 to a different one (possibly after cleanup)
    this[0x14] = &PTR_LAB_00d84fb0;

    // Reset global initialization flag
    DAT_01130034 = 0;

    // Call a global initialization routine (e.g., register managers, load config)
    FUN_00957d90();
}