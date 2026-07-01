// FUNC_NAME: Player::setBitFlags
// Function at 0x007f4530: Sets or clears two specific bits (bit 10 and bit 11) in a flags field at offset 0x1b94.
// param_2 (set): if non-zero, set the selected bit; if zero, clear it.
// param_3 (selectBit10): if non-zero, operate on bit 10 (0x400); if zero, operate on bit 11 (0x800).
void __thiscall Player::setBitFlags(bool set, bool selectBit10) {
    uint32_t* flags = reinterpret_cast<uint32_t*>(this + 0x1b94); // +0x1b94: flags field

    if (!set) {
        if (selectBit10) {
            *flags &= ~0x400; // Clear bit 10
        } else {
            *flags &= ~0x800; // Clear bit 11
        }
    } else {
        if (selectBit10) {
            *flags |= 0x400;  // Set bit 10
        } else {
            *flags |= 0x800;  // Set bit 11
        }
    }
}