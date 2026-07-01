// FUNC_NAME: SomeClass::getFlagByte
// Address: 0x0090cbe0
// Returns a byte at offset 0x31 (likely a flag/status byte)
unsigned char __thiscall SomeClass::getFlagByte(void) {
    return *(unsigned char *)(this + 0x31);
}