// FUNC_NAME: NetworkPacket::NetworkPacket
NetworkPacket * __thiscall NetworkPacket::NetworkPacket(NetworkPacket *this, int param2, int param3)
{
    // Call base class constructor (likely a more generic packet or object base)
    FUN_0086b060(param2, param3);

    // Initialize vtable pointers for multiple inheritance
    // First vtable pointer at offset 0
    this->vfptr = (void **)&PTR_LAB_00d75f7c;   // +0x00

    // Second vtable pointer at offset 0x60 (this+0x18 in 4-byte units)
    this->second_vfptr = (void **)&PTR_LAB_00d58278; // +0x60

    // Overwrite second vtable pointer with a more derived one
    this->second_vfptr = (void **)&PTR_LAB_00d75f68; // +0x60

    // Initialize data buffer pointer to null
    this->bufferPtr = 0;                        // +0x64 (this[0x19])

    // Set flags / counters to zero
    this->flags = 0;                            // +0x6c low byte? (this[0x1b])
    // Clear other fields (0x1c to 0x2e)
    this->field_1c = 0;                         // +0x70
    this->field_1d = 0;                         // +0x74
    this->field_1e = 0;                         // +0x78
    this->field_20 = 0;                         // +0x80
    this->field_21 = 0;                         // +0x84
    this->field_22 = 0;                         // +0x88
    this->field_23 = 0;                         // +0x8c
    this->field_24 = 0;                         // +0x90
    this->field_25 = 0;                         // +0x94
    this->field_26 = 0;                         // +0x98
    this->field_27 = 0;                         // +0x9c
    this->field_28 = 0;                         // +0xa0
    this->field_29 = 0;                         // +0xa4
    this->field_2a = 0;                         // +0xa8
    this->field_2b = 0;                         // +0xac
    this->field_2c = 0;                         // +0xb0
    this->field_2d = 0;                         // +0xb4
    this->field_2e = 0;                         // +0xb8

    // Copy a global value into field at +0x7c (this[0x1f])
    this->someGlobalRef = DAT_00d5ccf8;         // +0x7c

    // Set the 'initialized' flag (bit 0)
    this->flags |= 1;                           // +0x6c

    // Check if a specific flag is set (field at +0x5c)
    if (this->someFlag != 0) {
        // Check if the global heap manager allows allocation
        int allocOk = FUN_0043b870(DAT_01131018);
        if (allocOk != 0) {
            // Clear the buffer region (32KB size)
            FUN_009aefd0(this->second_vfptr, 0x8000);  // clears from +0x60 for 0x8000 bytes
        }
    }

    return this;
}