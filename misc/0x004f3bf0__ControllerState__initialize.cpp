// FUNC_NAME: ControllerState::initialize
void __thiscall ControllerState::initialize(int *this) // this is pointer to 12 dword structure (48 bytes)
{
    int globalDefault = DAT_00e2b1a4; // global default value, likely -1 or 0xFFFFFFFF

    // Structure layout (0x00 - 0x2C = 48 bytes)
    // +0x00: int field0;   // header1
    // +0x04: int field1;   // part of zero1[4]
    // +0x08: int field2;
    // +0x0C: int field3;
    // +0x10: int field4;
    // +0x14: int field5;   // header2
    // +0x18: int field6;   // part of zero2[4]
    // +0x1C: int field7;
    // +0x20: int field8;
    // +0x24: int field9;
    // +0x28: int field10;  // header3
    // +0x2C: int field11;  // zero3

    this[0] = globalDefault;  // +0x00
    this[1] = 0;              // +0x04
    this[2] = 0;              // +0x08
    this[3] = 0;              // +0x0C
    this[4] = 0;              // +0x10
    this[5] = globalDefault;  // +0x14
    this[6] = 0;              // +0x18
    this[7] = 0;              // +0x1C
    this[8] = 0;              // +0x20
    this[9] = 0;              // +0x24
    this[10] = globalDefault; // +0x28
    this[11] = 0;             // +0x2C
}