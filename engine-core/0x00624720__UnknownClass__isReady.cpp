// FUNC_NAME: UnknownClass::isReady
// Address: 0x00624720
// Returns 1 if the object is not ready (either sub-object pointer at +0x18 or +0x20 is null,
// or the flag at +0x14 has bit 2 set). Returns 0 when both pointers are valid and the flag bit is clear.
int __thiscall UnknownClass::isReady(void) {
    // Check if first sub-object (offset 0x18) and second sub-object (offset 0x20) are non-null,
    // and the flag byte at offset 0x14 does not have bit 2 set (e.g., FLAG_DISABLED).
    if ( (*(int*)(this + 0x18) != 0) &&
         (*(int*)(this + 0x20) != 0) &&
         ((*(byte*)(this + 0x14) & 4) == 0) ) {
        return 0;  // Ready
    }
    return 1;  // Not ready
}