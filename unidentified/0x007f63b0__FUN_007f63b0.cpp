//FUNC_NAME: SomeClass::setBit7Flag
// Address: 0x007f63b0
// Role: Sets bit 7 (0x80) of a flags field at +0x970 based on the boolean parameter.
// Additionally, if bit 0 of the byte at +0x8e6 is set, bit 7 is forced on.
void __thiscall SomeClass::setBit7Flag(bool enable)
{
    // +0x970: uint flags (bit 7 used for some state)
    if (enable) {
        *(uint *)(this + 0x970) |= 0x80;
    } else {
        *(uint *)(this + 0x970) &= ~0x80;
    }
    // +0x8e6: byte flags (bit 0 forces bit 7 on)
    if ((*(byte *)(this + 0x8e6) & 1) != 0) {
        *(uint *)(this + 0x970) |= 0x80;
    }
}