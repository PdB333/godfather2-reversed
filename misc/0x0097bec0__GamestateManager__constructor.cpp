// FUNC_NAME: GamestateManager::constructor
// Address: 0x0097bec0
// Role: Constructor for a manager object (likely singleton). Initializes vtable pointers, zeroes many fields, and sets a 4-component default value from a global.

void __fastcall GamestateManager::constructor(GamestateManager* this)
{
    // Store global reference to self
    g_gamestateManager = this;

    // Set vtable pointers (likely base then derived)
    this->vtableBase = (void*)&PTR_FUN_00d8fd70;   // +0x00
    this->vtableDerived = (void*)&PTR_LAB_00d8fd60; // +0x04

    // Zero out various fields at specific offsets
    // Offsets: 0x30, 0x54, 0x78, 0x9C
    this->field_C = 0;
    this->field_15 = 0;
    this->field_1E = 0;
    this->field_27 = 0;

    // Zero a contiguous block from offset 0xA0 to 0xE4 (fields 0x28-0x39)
    // Use pointer arithmetic for clarity
    uint32_t* fields = reinterpret_cast<uint32_t*>(this);
    for (int i = 0x28; i <= 0x39; ++i)
        fields[i] = 0;

    // Two halfword members at offsets 0x100 and 0x102
    *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(this) + 0x100) = 0;
    *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(this) + 0x102) = 0;

    // Initialize a 4-component value (e.g., color/vector) from global DAT_00d5f6f0
    uint32_t defaultVal = DAT_00d5f6f0;
    // Offsets 0xF0, 0xF4, 0xF8, 0xFC
    this->value0 = defaultVal; // +0xF0
    this->value1 = defaultVal; // +0xF4
    this->value2 = defaultVal; // +0xF8
    this->value3 = defaultVal; // +0xFC
}