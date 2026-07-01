// FUNC_NAME: GameManager::reset
void __fastcall GameManager::reset(GameManager *this)
{
    // Set vtable to base class (PTR_FUN_00d80f30)
    this->vtable = &PTR_FUN_00d80f30;
    // Clear field at +0x08 (e.g., some flag or counter)
    this->field_0x08 = 0;
    // Release sub-object at +0x04 (e.g., a sub-manager or resource handle)
    FUN_009c8f10(this->field_0x04);
    // Null out the sub-object pointer
    this->field_0x04 = 0;
    // Clear field at +0x0C (e.g., another state variable)
    this->field_0x0C = 0;
    // Set vtable to derived class (PTR_LAB_00d80f2c)
    this->vtable = &PTR_LAB_00d80f2c;
    // Reset global singleton pointer (DAT_011299b8) to null
    g_pGameManager = 0;
    return;
}