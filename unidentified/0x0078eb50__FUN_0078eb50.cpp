// FUNC_NAME: SomeClass::isFlagSet
bool __thiscall SomeClass::isFlagSet(int this, byte flagIndex)
{
    // Check if the flags byte at offset +0x2d is zero (no flags set)
    if (*(byte *)(this + 0x2d) == 0) {
        return true; // If no flags, return true (default behavior)
    }
    // Check if the specific flag bit is set using a bitmask
    // flagIndex is masked to 5 bits (0-31) to avoid overflow
    return ('\x01' << (flagIndex & 0x1f) & *(byte *)(this + 0x2d)) != 0;
}