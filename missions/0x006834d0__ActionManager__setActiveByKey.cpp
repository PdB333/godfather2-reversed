// FUNC_NAME: ActionManager::setActiveByKey
void __thiscall ActionManager::setActiveByKey(int thisPtr, int key) {
    uint count = *(uint *)(thisPtr + 0x88);  // +0x88: number of entries
    int *currentPtr = nullptr;
    if (count != 0) {
        int *entry = (int *)(thisPtr + 8);   // +0x08: start of entry array (key,int* pairs)
        for (uint i = 0; i < count; i++) {
            if (*entry == key) {
                // +0x0c + i*8: pointer field of entry i
                currentPtr = *(int **)(thisPtr + 0x0c + i * 8);
                break;
            }
            entry += 2; // each entry is 8 bytes (key+pointer)
        }
    }
    *(int **)(thisPtr + 4) = currentPtr;     // +0x04: current active pointer
    if (currentPtr != nullptr) {
        // Call virtual function at vtable offset 4 (index 1) with argument 0
        // This is likely an "activate" or "execute" method on the object
        (*(void (*)(int))(*(int *)currentPtr + 4))(0);
    }
}