// FUNC_NAME: DataManager::getEntry
int __thiscall DataManager::getEntry(int *indexPtr, int *outPointer, uint *outValue) {
    int index = *indexPtr;
    // Array of 12-byte entries starts at this+0x70. Each entry: +0x00 = pointer, +0x08 = value
    int pointer = *(int *)(this + 0x70 + index * 0xC);
    *outPointer = pointer;
    if (pointer != 0) {
        uint value = *(uint *)(this + index * 0xC + 0x78);
        *outValue = value;
        // Return value with high byte set to 1, low byte zeroed from value
        return (value & 0xFFFFFF00) | 0x01000000;
    }
    *outValue = 0;
    return 0;
}