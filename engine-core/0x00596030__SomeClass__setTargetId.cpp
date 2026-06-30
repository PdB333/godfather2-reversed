// FUNC_NAME: SomeClass::setTargetId
void SomeClass::setTargetId(int id, int param) {
    // Check if id is out of valid range (greater than 0xffff)
    if (id > 0xffff) {
        // Call error handler from global vtable (offset 4)
        (*(void (**)(void))(*DAT_01205590 + 4))();
    }

    // If the lower 16 bits of id are non-zero, set target state
    if ((short)id != 0) {
        this->field_0x7c = 0;          // +0x7c: some state flag
        this->field_0x80 = 1;          // +0x80: active flag
        this->field_0x82 = (short)id;  // +0x82: target ID (16-bit)
        this->field_0x88 = param;      // +0x88: parameter
        this->field_0x84 = 0;          // +0x84: another state
    }

    // Clear bit 3 (0x8) of flags at +0x4
    this->flags &= ~0x8;
}