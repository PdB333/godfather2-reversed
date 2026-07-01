// FUNC_NAME: SomeManager::getSlotPointer
int SomeManager::getSlotPointer(int index) {
    // Dereference this+0x2c88 to get a base pointer, then add 0x140 (base offset for array start)
    // and index * 0x24 (size of each slot structure, 36 bytes)
    return *(int*)(this + 0x2c88) + 0x140 + index * 0x24;
}