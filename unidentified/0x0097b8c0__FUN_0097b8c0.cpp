// FUNC_NAME: SomeClass::setValueAndMarkDirty
void __thiscall SomeClass::setValueAndMarkDirty(int value) {
    // Store the value at offset +0xA4 (possibly a pointer or ID)
    *(int*)(this + 0xA4) = value;
    // Set bit 1 (value 2) of the flags field at offset +0x102 to mark dirty/needs update
    *(uint16*)(this + 0x102) |= 2;
}