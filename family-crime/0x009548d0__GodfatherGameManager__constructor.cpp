// FUNC_NAME: GodfatherGameManager::constructor
void __fastcall GodfatherGameManager::constructor(GodfatherGameManager *this)
{
    // Call base class constructor (likely EARS::Framework::Object or similar)
    FUN_005bf9b0(); // BaseClass::constructor

    // Set vtable pointer at offset 0x00
    this->vtable = (void *)&PTR_FUN_00d85f70;

    // Set pointer at offset 0x10
    this->field_0x10 = (void *)&PTR_LAB_00d85f4c;

    // Set pointer at offset 0x4C
    this->field_0x4C = (void *)&PTR_LAB_00d85f48;

    // Set byte flag at offset 0x14 to 1 (likely an initialization flag)
    *(uint8_t *)((uint8_t *)this + 0x14) = 1;

    // Store this as the global singleton
    g_pGodfatherGameManager = this; // DAT_0113005c
}