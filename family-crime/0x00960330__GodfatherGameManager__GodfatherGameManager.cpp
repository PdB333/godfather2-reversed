// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
void __thiscall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager *this) {
    // +0x00: vtable pointer
    this->vfptr = (void **)&PTR_FUN_00d8d370;   // GodfatherGameManager vtable
    // +0x04: function pointer / pointer to data
    this->field_0x04 = &PTR_LAB_00d8d348;       // some internal data block
    // +0x4C: another pointer (set twice, last value wins)
    this->field_0x4C = &PTR_LAB_00d8d344;       // overwritten below
    this->field_0x4C = &PTR_LAB_00d8d340;       // final value
    // Global initialization flag
    g_bGodfatherGameManagerInit = 0;            // _DAT_0113087c
    // Call internal initialization routine
    FUN_005c16e0();                             // likely GodfatherGameManager::initSubsystems()
}