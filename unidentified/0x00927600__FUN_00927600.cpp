// FUNC_NAME: SomeClass::isSpecialStateActive
// Address: 0x00927600
// Role: Checks two state flags at offsets +0x3c8 and +0x3c6.
// Returns true if flag at +0x3c8 is zero and flag at +0x3c6 is non-zero.
bool __thiscall SomeClass::isSpecialStateActive() {
    // +0x3c8: likely a boolean flag (e.g., "isDisabled" or "isInactive")
    // +0x3c6: another boolean flag (e.g., "isInSpecialMode")
    if (*(char *)(this + 0x3c8) == '\0' && *(char *)(this + 0x3c6) != '\0') {
        return true;
    }
    return false;
}