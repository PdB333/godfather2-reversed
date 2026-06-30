// FUNC_NAME: SomeClass::isObjectEnabled
byte __thiscall SomeClass::isObjectEnabled(void) {
    // Read flags byte at offset 0xA from this
    byte flags = *(byte *)((int)this + 10); // +0x0A: flags field
    // Check bit 3 (0x08): if set, return true (enabled)
    if ((flags & 0x08) != 0) {
        return 1;
    }
    // Check bit 4 (0x10): if set, return false (disabled)
    if ((flags & 0x10) != 0) {
        return 0;
    }
    // Otherwise, return the inverse of bit 2 (0x04) - default enabled/disabled
    return (~(flags >> 2) & 1);
}