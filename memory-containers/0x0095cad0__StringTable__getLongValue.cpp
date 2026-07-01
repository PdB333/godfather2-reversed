// FUNC_NAME: StringTable::getLongValue
void __thiscall StringTable::getLongValue(int thisPtr) {
    // +0x28: index into string table (array of structs, size 0x10)
    int index = *(int*)(thisPtr + 0x28);
    // DAT_01130828: pointer to array of 0x10-byte entries, first member is char*
    char* str = *(char**)(index * 0x10 + DAT_01130828);
    if (str == nullptr) {
        // DAT_0120546e: default string (likely "0" or empty)
        str = (char*)&DAT_0120546e;
    }
    // _atol: convert string to long, result discarded (likely debug/utility function)
    _atol(str);
    return;
}