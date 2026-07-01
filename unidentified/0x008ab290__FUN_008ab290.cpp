// FUNC_NAME: SomeClass::assignFrom
void __thiscall SomeClass::assignFrom(const SomeClass* source) {
    // Copy data from source to this+0x10 (likely a struct/array of size 0x20)
    FUN_004bb7d0(source, this + 0x10);
    // Call function with the byte at this+0x30 (e.g., a flag or enum)
    FUN_0064bb50(*(char*)(this + 0x30));
    // Copy data from source to this+0x34 (likely another struct/array)
    FUN_004bc160(source, this + 0x34);
}