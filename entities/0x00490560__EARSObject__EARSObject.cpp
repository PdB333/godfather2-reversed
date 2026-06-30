// FUNC_NAME: EARSObject::EARSObject
void __thiscall EARSObject::EARSObject(EARSObject* this) {
    // Call base class constructor (FUN_006126d0)
    BaseClass::BaseClass();

    // Set vtable pointer (global table at 0x00e343d0)
    this->vtable = &gVTable_00e343d0; // +0x00

    // Zero out various state fields (offsets are from start of this)
    this->field_0x29 = 0; // +0xA4
    this->field_0x2A = 0; // +0xA8
    this->field_0x2B = 0; // +0xAC
    this->field_0x30 = 0; // +0xC0
    this->field_0x38 = 0; // +0xE0
    this->field_0x40 = 0; // +0x100
    this->field_0x54 = 0; // +0x150
    this->field_0x68 = 0; // +0x1A0
    this->field_0x6B = 0; // +0x1AC
    this->field_0x6C = 0; // +0x1B0
    this->flag_0x6E = 0;  // +0x1B8 (byte)

    // Clear buffers (each 16 bytes) at +0xB0 and +0xF0, and 8 bytes at +0x1A4
    memset(this->buf_B0, 0, 16); // +0xB0
    memset(this->buf_F0, 0, 16); // +0xF0
    memset(this->buf_1A4, 0, 8); // +0x1A4

    // Initialize an array of 8 packet slots (each 5 integers = 20 bytes)
    // Slot layout: first int = sentinel/sequence, next 4 ints = data
    // The sentinel value is loaded from a global constant (DAT_00e2b1a4)
    int sentinel = g_Sentinel_00e2b1a4; // Likely 0xFFFFFFFF or 0
    for (int i = 0; i < 8; i++) {
        // Each slot starts at offset 0x44 + i*5 (dwords) = 0x110 + i*20 (bytes)
        this->packetSlots[i].sentinel = sentinel;
        // Remaining 4 ints are already zeroed by earlier memset or default
    }
}