// Function at 0x006d6b50 - NPC constructor
// FUNC_NAME: NPC::constructor
NPC * __thiscall NPC::NPC(int creationFlags) {
    // Call base class constructor with creation flags
    FUN_00473840(creationFlags);
    // Set vtable pointers for multiple inheritance / interfaces
    this->vtable = &PTR_FUN_00d5f4d4;            // +0x00: main vtable
    this->vtable_0x3C = &PTR_LAB_00d5f4c4;      // +0x3C: interface vtable 1
    this->vtable_0x48 = &PTR_LAB_00d5f4c0;      // +0x48: interface vtable 2
    this->vtable_0x50 = &PTR_LAB_00d5f4bc;      // +0x50: interface vtable 3
    // Initialize fields to zero
    this->field_0x58 = 0;
    this->field_0x5C = 0;
    this->field_0x60 = 0;
    this->field_0x64 = 0;
    // Post-construction initialization
    FUN_006d69c0();
    return this;
}