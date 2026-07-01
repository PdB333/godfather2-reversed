// FUNC_NAME: GodfatherGameManager::constructor
void __fastcall GodfatherGameManager::constructor(GodfatherGameManager *this)
{
    // Set vtable pointer to class-specific vtable
    this->vtable = &PTR_FUN_00d74270;

    // Initialize function pointers at various offsets (likely virtual method table entries or callbacks)
    this->field_0x3C = &PTR_LAB_00d74260;   // +0x3C
    this->field_0x48 = &PTR_LAB_00d7425c;   // +0x48
    this->field_0x148 = &PTR_LAB_00d74258;  // +0x148
    this->field_0x148 = &PTR_LAB_00d74254;  // +0x148 (overwrites previous assignment)

    // Reset global initialization flag
    g_gameManagerInitialized = 0; // DAT_0112a678

    // Call secondary initialization routine
    FUN_0083f0e0();
}