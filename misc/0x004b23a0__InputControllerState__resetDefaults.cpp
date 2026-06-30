// FUNC_NAME: InputControllerState::resetDefaults
void __fastcall InputControllerState::resetDefaults(InputControllerState* this)
{
    uint32_t defaultHandle = g_defaultControllerHandle; // DAT_00e2b1a4

    // Clear entire structure - offsets relative to this (size ~0x5C)
    this->field_00 = 0;      // +0x00
    this->field_04 = 0;      // +0x04
    this->field_08 = 0;      // +0x08
    this->field_0C = 0;      // +0x0C
    this->field_10 = 0;      // +0x10
    this->field_14 = 0;      // +0x14
    this->someByte = 0;      // +0x18 (byte)
    this->slotHandles[0] = defaultHandle; // +0x1C
    this->slotReserved0[0] = 0; // +0x20
    this->slotReserved0[1] = 0; // +0x24
    this->slotReserved0[2] = 0; // +0x28
    this->slotReserved0[3] = 0; // +0x2C
    this->slotHandles[1] = defaultHandle; // +0x30
    this->slotReserved1[0] = 0; // +0x34
    this->slotReserved1[1] = 0; // +0x38
    this->slotReserved1[2] = 0; // +0x3C
    this->slotReserved1[3] = 0; // +0x40
    this->slotHandles[2] = defaultHandle; // +0x44
    this->slotReserved2[0] = 0; // +0x48
    this->slotReserved2[1] = 0; // +0x4C
    this->slotReserved2[2] = 0; // +0x50
    this->slotReserved2[3] = 0; // +0x54
    this->slotHandles[3] = defaultHandle; // +0x58
}
```