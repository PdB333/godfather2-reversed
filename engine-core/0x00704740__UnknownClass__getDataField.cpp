// FUNC_NAME: UnknownClass::getDataField
uint32 __thiscall UnknownClass::getDataField(void) {
    // Offset 0xC4: likely an integer field (e.g., ID, index, handle)
    return *(uint32 *)(this + 0xC4);
}