// FUNC_NAME: SomeClass::areBothFlagsSet
bool __thiscall SomeClass::areBothFlagsSet(void) {
    // Check two byte flags at offsets +0x3c6 and +0x3c8
    // Return true only if both are non-zero
    return (*(char*)((int)this + 0x3c8) != 0) && (*(char*)((int)this + 0x3c6) != 0);
}