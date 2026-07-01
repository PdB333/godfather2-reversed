// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager
void __fastcall GodfatherGameManager::~GodfatherGameManager(GodfatherGameManager* this)
{
    // Set vtable pointers to destructor-specific vtables to prevent further virtual calls
    this->vtable = &PTR_FUN_00d89680;          // +0x00: main vtable
    this->field_0x10 = &PTR_LAB_00d8965c;      // +0x10: sub-object vtable
    this->field_0x4C = &PTR_LAB_00d8964c;      // +0x4C: another sub-object vtable
    this->field_0x58 = &PTR_LAB_00d89648;      // +0x58: yet another vtable

    // Initialize sub-object at +0x10 with a function (likely a cleanup or setVtable)
    FUN_005c02f0(&this->field_0x10, &LAB_00930c00, 1);

    // Perform general cleanup (e.g., release resources, stop threads)
    FUN_006a2c00();

    // Destroy sub-objects if they exist, using their destructor function pointers
    if (this->field_0x98 != 0) {
        // Call destructor at +0xA4 on the object at +0x98
        (this->vtable_destructor_0xA4)(this->field_0x98);
    }
    if (this->field_0x84 != 0) {
        // Call destructor at +0x90 on the object at +0x84
        (this->vtable_destructor_0x90)(this->field_0x84);
    }
    if (this->field_0x74 != 0) {
        // Call destructor at +0x80 on the object at +0x74
        (this->vtable_destructor_0x80)(this->field_0x74);
    }

    // Update vtable pointer to final destructor vtable
    this->field_0x58 = &PTR_LAB_00d89644;

    // Clear global singleton flag
    DAT_01129928 = 0;

    // Final cleanup functions
    FUN_004083d0();
    FUN_005c16e0();
}