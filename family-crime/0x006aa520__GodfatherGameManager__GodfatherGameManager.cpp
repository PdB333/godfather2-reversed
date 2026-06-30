// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
void __thiscall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager* this) {
    // +0x04: set to 1 (likely a flag or version)
    this->field_0x04 = 1;
    // +0x08: set to 0
    this->field_0x08 = 0;
    // +0x0C: temporary base vtable pointer (later overwritten)
    this->dataPtr = &PTR_LAB_00d5d9ac;
    // Store this singleton globally
    DAT_011299ac = this;
    // +0x00: set vtable pointer for the class
    this->vtable = &PTR_FUN_00d5d9b8;
    // +0x0C: final derived vtable pointer (overwrites previous)
    this->dataPtr = &PTR_LAB_00d5d9b4;
    // +0x10: init to 0
    this->field_0x10 = 0;
    // +0x14: init to 0
    this->field_0x14 = 0;
    // +0x18: init to 0
    this->field_0x18 = 0;
    // +0x1C: init to -1 (0xFFFFFFFF)
    this->field_0x1C = -1;
    // +0x20: init to 0
    this->field_0x20 = 0;
}