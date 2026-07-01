// FUNC_NAME: ControllerSlotData::initialize
// Initializes a controller slot structure at given pointer.
// Structure size: 0x30 bytes (12 DWORD fields)
// All fields zeroed except field at +0x0C which gets a global constant (likely version/ID)
void ControllerSlotData::initialize(ControllerSlotData* slot) {
    slot->field_00 = 0;       // +0x00
    slot->field_04 = 0;       // +0x04
    slot->field_08 = 0;       // +0x08
    slot->field_0C = g_slotVersionID; // +0x0C, global version ID from _DAT_00d5780c
    slot->field_10 = 0;       // +0x10
    slot->field_14 = 0;       // +0x14
    slot->field_18 = 0;       // +0x18
    slot->field_1C = 0;       // +0x1C
    slot->field_20 = 0;       // +0x20
    slot->field_24 = 0;       // +0x24
    slot->field_28 = 0;       // +0x28
    slot->field_2C = 0;       // +0x2C
}