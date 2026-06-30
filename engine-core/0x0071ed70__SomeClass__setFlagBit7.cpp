// FUNC_NAME: SomeClass::setFlagBit7
// Function address: 0x0071ed70
// Sets or clears bit 7 (0x80) of a flags field at offset +0x20.
void __thiscall SomeClass::setFlagBit7(char param_2) {
    uint* flags = (uint*)((char*)this + 0x20);
    if (param_2 != '\0') {
        *flags |= 0x80;
    } else {
        *flags &= 0xffffff7f; // Clear bit 7
    }
}