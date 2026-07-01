//FUNC_NAME: SomeManager::getSlot
int* __thiscall SomeManager::getSlot(int index) {
    // +0x1c0c: array of slots, each 0xC bytes
    return reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x1c0c + index * 0xC);
}