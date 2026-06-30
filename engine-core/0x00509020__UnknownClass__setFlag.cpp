// FUNC_NAME: UnknownClass::setFlag
// Address: 0x00509020
// Role: Sets or clears bit 0 of flags field at offset +0x8 (used as boolean flag)
void __thiscall UnknownClass::setFlag(bool enable)
{
    if (enable) {
        // Set bit 0
        *(uint *)(this + 8) |= 1;
    } else {
        // Clear bit 0
        *(uint *)(this + 8) &= 0xfffffffe;
    }
}