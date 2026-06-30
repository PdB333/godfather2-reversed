// FUNC_NAME: ControllerManager::initializeControllerSlots
int __thiscall ControllerManager::initializeControllerSlots(ControllerManager *this)
{
    undefined4 globalValue = DAT_00e2b1a4;  // Global sentinel or default state pointer
    this->field_0x1c = globalValue;         // +0x1c: some pointer
    this->field_0xa8 = 0;                   // +0xa8: flag or counter

    // Initialize 16 controller slots (each 8 bytes: state pointer + flags)
    undefined4 *slotPtr = &this->slotArray[0].state;  // +0x24: start of slot array
    int i = 16;
    do {
        slotPtr[-1] = globalValue;  // +0x20, +0x28, ...: previous slot's flags? Actually writes to offset -4 from current ptr
        *slotPtr = 0;               // +0x24, +0x2c, ...: current slot's state pointer? Actually sets to 0
        slotPtr += 2;               // Advance by 8 bytes (two undefined4)
        i--;
    } while (i != 0);

    // Clear additional fields
    this->field_0xa0 = 0;   // +0xa0
    this->field_0xa4 = 0;   // +0xa4
    this->field_0xbc = 0;   // +0xbc
    this->field_0xc0 = 0;   // +0xc0
    this->field_0xc4 = 0;   // +0xc4
    this->field_0xc8 = 0;   // +0xc8
    this->field_0xcc = 0;   // +0xcc
    this->field_0xd0 = 0;   // +0xd0
    this->field_0xd4 = 0;   // +0xd4
    this->field_0xd8 = 0;   // +0xd8
    this->field_0xdc = 0;   // +0xdc
    this->field_0xe0 = 0;   // +0xe0
    this->field_0xe8 = 0;   // +0xe8

    // Call sub-initializers
    FUN_005ef9a0();  // Likely initializes input device manager or similar
    FUN_005ef890();  // Another initialization
    FUN_005e9fe0();  // Final setup

    return (int)this;
}