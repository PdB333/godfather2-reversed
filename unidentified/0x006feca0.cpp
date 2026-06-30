// FUN_NAME: GodfatherGameManager::GodfatherGameManager
void __thiscall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager* this)
{
    // Set vtable for GodfatherGameManager
    this->vtable = (void*)0x00d60c30; // +0x00: vtable pointer

    // Additional vtable-like pointers (likely for different interfaces)
    this->field_0x3C = (void*)0x00d60c20; // +0x3C
    this->field_0x48 = (void*)0x00d60c1c; // +0x48
    this->field_0x50 = (void*)0x00d60c18; // +0x50

    // Call internal initializer with a static class descriptor address
    // (the address of this constructor function is used as a key/identifier)
    sub_006fc4c0((void*)0x006fec60, this);

    // If a specific flag (at +0xE8) is set, enable a subsystem
    if (this->field_0xE8 != 0) {
        sub_00474680(1); // enableSomeSystem(true)
    }

    // Perform post-construction initialization
    sub_00474090();
}