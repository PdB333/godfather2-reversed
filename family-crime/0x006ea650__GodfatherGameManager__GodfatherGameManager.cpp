// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Address: 0x006ea650 - Constructor for the game manager singleton
__fastcall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager *this)
{
    // Initialize member fields
    this->field_0x04 = 1;                                 // offset +0x04: some flag/count
    this->field_0x08 = 0;                                 // offset +0x08
    this->field_0x0C = &PTR_LAB_00d5fd38;                 // offset +0x0C: initial data pointer
    this->vtable = &PTR_FUN_00d5fd40;                     // offset +0x00: virtual function table
    this->field_0x0C = &PTR_LAB_00d5fd3c;                 // offset +0x0C: overwritten with another pointer

    // Zero out the rest of the members (indices 4 through 0xE)
    this->field_0x10 = 0;                                 // offset +0x10
    this->field_0x14 = 0;                                 // offset +0x14
    this->field_0x18 = 0;                                 // offset +0x18
    this->field_0x1C = 0;                                 // offset +0x1C
    this->field_0x20 = 0;                                 // offset +0x20
    this->field_0x24 = 0;                                 // offset +0x24
    this->field_0x28 = 0;                                 // offset +0x28
    this->field_0x2C = 0;                                 // offset +0x2C
    this->field_0x30 = 0;                                 // offset +0x30
    this->field_0x34 = 0;                                 // offset +0x34
    this->field_0x38 = 0;                                 // offset +0x38

    // Assign this instance to the global singleton pointer
    g_gameManager = this;                                 // DAT_01129880

    // If static initialization data exists (0x8000 bytes), copy it into the manager
    if (g_staticData != nullptr) {                        // DAT_01206a20
        memcpy(this, g_staticData, 0x8000);              // FUN_00408900: likely memcpy or similar
    }

    return this;
}