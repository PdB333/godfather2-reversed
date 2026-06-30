// FUNC_NAME: ComponentState::reset (0x005e3260)
// Initializes a 13-byte component state structure: sets active flag to 1, zeros other fields.
void __thiscall ComponentState::reset(uint32_t *this) {
    this[0] = 1;          // +0x00: active (bool/int)
    this[1] = 0;          // +0x04: some count/flag
    this[2] = 0;          // +0x08: some count/flag
    *(uint8_t *)(this + 3) = 0; // +0x0C: pending flag (byte)
}