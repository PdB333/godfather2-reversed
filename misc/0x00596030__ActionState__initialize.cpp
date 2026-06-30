// FUNC_NAME: ActionState::initialize
void ActionState::initialize(int value, int param) {
    // Range check: value must fit in a short (0 to 0xFFFF)
    if (value > 0xFFFF) {
        // Call error handler from global offset +4 of structure at DAT_01205590
        (*(code **)(*(int*)0x01205590 + 4))();
    }

    // Only set fields if the short-cast value is non-zero
    if ((short)value != 0) {
        this->field_0x7c = 0;           // +0x7c: int (some ID or state)
        this->field_0x80 = 1;           // +0x80: short (mode/type, set to 1)
        this->field_0x82 = (short)value; // +0x82: short (stored value)
        this->field_0x88 = param;       // +0x88: int (parameter)
        this->field_0x84 = 0;           // +0x84: short (counter or flag)
    }

    // Clear bit 3 (0x8) in flags at offset +0x4
    this->flags &= ~0x8;                // +0x04: uint flags
}