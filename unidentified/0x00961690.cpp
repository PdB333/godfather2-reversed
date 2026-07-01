// FUN_NAME: GodfatherGameManager::initialize
void __fastcall GodfatherGameManager::initialize(GodfatherGameManager* this)
{
    // Set vtable pointer (index 0)
    this[0] = &PTR_FUN_00d8d740;

    // Set pointer at offset +0x10 (index 4)
    this[4] = &PTR_LAB_00d8d718;

    // Set pointer at offset +0x4C (index 19) to some label
    this[0x13] = &PTR_LAB_00d8d714;

    // Call sub-initializer with parameter stored at offset +0x84 (index 33)
    FUN_009c8eb0(this[0x21]);

    // Update pointer at offset +0x4C to another label
    this[0x13] = &PTR_LAB_00d8d710;

    // Global flag indicating initialization status
    DAT_011305a0 = 0;

    // Call finalization/registration routine
    FUN_005c16e0();
}