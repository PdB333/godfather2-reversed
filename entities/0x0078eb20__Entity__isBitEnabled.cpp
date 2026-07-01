// FUNC_NAME: Entity::isBitEnabled
bool __thiscall Entity::isBitEnabled(unsigned char bitIndex) {
    // Byte at +0x2c holds a bitmask of flags.
    unsigned char flags = *(unsigned char*)(this + 0x2c);
    // If no flags are set, consider the feature enabled by default.
    if (flags == 0) {
        return true;
    }
    // Test the specific bit.
    return (1 << (bitIndex & 0x1f) & flags) != 0;
}