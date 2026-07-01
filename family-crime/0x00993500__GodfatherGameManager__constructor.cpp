// FUNC_NAME: GodfatherGameManager::constructor
undefined4* __thiscall GodfatherGameManager::constructor(GodfatherGameManager* this)
{
    // Call base class constructor (likely EARS::Framework::Object or similar)
    FUN_005bf9b0();

    // Set vtable pointer at offset 0x4C (param_1[0x13]) to a data pointer
    this->field_0x4C = &PTR_LAB_00d92148; // +0x4C

    // Store this instance in global singleton pointer
    DAT_0113000c = this;

    // Initialize fields at offsets 0x50, 0x54, 0x58 to zero
    this->field_0x50 = 0; // +0x50
    this->field_0x54 = 0; // +0x54
    this->field_0x58 = 0; // +0x58

    // Set primary vtable pointer at offset 0x00
    this->vtable = &PTR_FUN_00d92178; // +0x00

    // Set secondary vtable pointer at offset 0x10 (param_1[4])
    this->baseVtable = &PTR_LAB_00d92150; // +0x10

    // Overwrite field at offset 0x4C with another vtable pointer
    this->field_0x4C = &PTR_LAB_00d9214c; // +0x4C

    return this;
}