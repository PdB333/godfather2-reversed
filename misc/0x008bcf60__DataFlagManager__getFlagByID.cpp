// FUNC_NAME: DataFlagManager::getFlagByID
uint8_t __thiscall DataFlagManager::getFlagByID(int id) {
    int index = getIndexForID(id); // FUN_008bcb50: maps ID to array index, -1 if not found
    if (index >= 0) {
        // Array pointer at this+0x8, element size 0x2c, flag byte at offset 0x28
        return *(uint8_t*)(*(int*)(this + 8) + index * 0x2c + 0x28);
    }
    return 1; // default: flag true
}