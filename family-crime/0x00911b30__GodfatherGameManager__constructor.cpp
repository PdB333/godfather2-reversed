// FUNC_NAME: GodfatherGameManager::constructor
undefined4* __fastcall GodfatherGameManager::constructor(undefined4* this) {
    // Call base class constructor (likely EARSObject or similar)
    FUN_005bf9b0();

    // Set vtable pointer at offset 0x4C (this[0x13]) to a global table
    this[0x13] = &PTR_LAB_00d83fec;

    // Store this instance globally (singleton)
    DAT_0112fe08 = this;

    // Zero out specific bytes at offsets 0x50 and 0x5C
    *(undefined1*)(this + 0x14) = 0;  // offset 0x50
    *(undefined1*)(this + 0x17) = 0;  // offset 0x5C

    // Set primary vtable at offset 0
    *this = &PTR_FUN_00d84018;

    // Set secondary vtable at offset 0x10 (this[4])
    this[4] = &PTR_LAB_00d83ff4;

    // Overwrite vtable at offset 0x4C with another table
    this[0x13] = &PTR_LAB_00d83ff0;

    // Initialize fields at offsets 0x54 and 0x58 to 0
    this[0x15] = 0;
    this[0x16] = 0;

    return this;
}