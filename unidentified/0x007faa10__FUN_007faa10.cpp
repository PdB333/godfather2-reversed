// FUNC_NAME: UnknownClass::setFlagAndCallVirtual
void __thiscall UnknownClass::setFlagAndCallVirtual(void) {
    // Check if bit 22 (0x400000) of uint at +0x8e8 is not set
    if ((*(unsigned int *)(this + 0x8e8) >> 0x16 & 1) == 0) {
        // +0x58: pointer to some vtable or function table
        // Call virtual function at offset 0x28 from that table, passing 0x20 as argument
        (**(code **)(*(int *)(this + 0x58) + 0x28))(0x20);
    }
    // Set bit 22 (0x400000) in the flags at +0x8e8
    *(unsigned int *)(this + 0x8e8) |= 0x400000;
}