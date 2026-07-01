// FUNC_NAME: DataManager::getDataByIndex
int __thiscall DataManager::getDataByIndex(int this, byte index) {
    // Check if data is initialized (field at +0x148)
    if (*(int*)(this + 0x148) != 0) {
        // Return value from array at offset 0xb0 within the data block pointed by +0x80
        return *(int*)(*(int*)(this + 0x80) + 0xb0 + (uint)index * 4);
    }
    return 0;
}