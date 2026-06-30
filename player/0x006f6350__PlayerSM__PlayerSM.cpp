// FUNC_NAME: PlayerSM::PlayerSM
// Function address: 0x006f6350
// Role: Constructor for PlayerSM singleton. Initializes base class, vtable pointers, and zeroes most fields.

void __thiscall PlayerSM::PlayerSM(PlayerSM* this, void* arg)
{
    // Call base class constructor (likely PlayerStateMachineBase or similar)
    FUN_006f2cd0(arg);

    // Set vtable pointers (multiple inheritance interfaces)
    this->vtable1 = &PTR_LAB_00d60740;   // +0x90 (0x24*4)
    this->vtable2 = &PTR_LAB_00d6074c;   // +0x3C (0xf*4)
    this->vtable3 = &PTR_LAB_00d60748;   // +0x48 (0x12*4)
    this->vtable4 = &PTR_LAB_00d60744;   // +0x90 (same as vtable1? likely different)
    // Note: vtable1 and vtable4 are at same offset; might be a mistake in decompiler.

    // Store singleton instance globally
    s_PlayerSMInstance = this;

    // Set the primary vtable (first entry in object)
    this->primaryVtable = &PTR_FUN_00d6075c;   // +0x00

    // Initialize fields with debug pattern (0xBADBADBA) then clear to zero.
    // This was a common pattern to detect uninitialized usage.
    this->field_0x94 = 0xBADBADBA;  // +0x94
    this->field_0xA4 = 0xBADBADBA;  // +0xA4
    this->field_0xB4 = 0xBADBADBA;  // +0xB4

    // Zero all remaining fields (offsets 0xB4 to 0xF4)
    this->field_0xB4 = 0;
    this->field_0xB8 = 0;
    this->field_0xBC = 0;
    this->field_0xC0 = 0;
    this->field_0xC4 = 0;
    this->field_0xC8 = 0;
    this->field_0xCC = 0;
    this->field_0xD0 = 0;
    this->field_0xD4 = 0;
    this->field_0xE4 = 0;
    this->field_0xE8 = 0;
    this->field_0xF0 = 0;

    // Additional zeroing (offsets 0xD4 and 0xD8)
    this->field_0xD4 = 0;
    this->field_0xD8 = 0;
    this->field_0xDC = 0;
    this->field_0xE0 = 0;

    // Zero fields set earlier (0x94, 0xA4, 0xB4) - final initialization to 0
    this->field_0x94 = 0;
    this->field_0xA0 = 0;
    this->field_0xA8 = 0;
    this->field_0xB0 = 0;  // +0xB0 (offset 0x2C*4)
    this->field_0xAC = 0;  // +0xAC (offset 0x2B*4)
    this->field_0xA8 = 0;  // +0xA8 (offset 0x2A*4)
    this->field_0xA4 = 0;  // +0xA4 (offset 0x29*4)
    this->field_0xA0 = 0;  // +0xA0 (offset 0x28*4)
    this->field_0x9C = 0;  // +0x9C (offset 0x27*4)
    this->field_0x98 = 0;  // +0x98 (offset 0x26*4)
    this->field_0x94 = 0;  // +0x94 (offset 0x25*4)
}