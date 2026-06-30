// FUNC_NAME: ManagedList::addItemWithRefCheck
void __thiscall ManagedList::addItemWithRefCheck(int* item) {  // item is param_2
    // Unknown helper functions
    void copyString(void* src, int maxLen, void* dest);        // FUN_004035f0
    int checkReferenceCount(void* ptr, int zero);              // FUN_006fb2b0
    void debugLog();                                           // FUN_006bccd0
    void resizeArray(int newCapacity);                         // FUN_006f9120

    // Copy some data from item into this (probably name/owner)
    copyString(*(void**)(item + 0x0c), 0x1ff, this);
    copyString(*(void**)(item + 0x0c), 0x1ff, item);

    // Decrement total weight/sum by item's value
    *(int*)((int)this + 0x34) = *(int*)((int)this + 0x34) - *(int*)(item + 0x30);

    int refCount = checkReferenceCount(*(void**)(item + 0x0c), 0);
    if (refCount == 0) {
        // Item is no longer referenced, release it
        debugLog();
        *(int*)(item + 0x0c) = 0;  // clear reference
        *(int*)(item + 0x2c) = 0;
        if (*(int*)(item + 0x10) != 0) {
            // Call destructor/callback stored at +0x1c
            (*(void (**)(int))(item + 0x1c))(*(int*)(item + 0x10));
        }
        *(int*)(item + 0x10) = 0;
        *(int*)(item + 0x18) = 0;
        *(int*)(item + 0x14) = 0;
        *(int*)(item + 0x30) = 0;
        *(char*)(item + 0x34) = 1;  // mark as released
        *(char*)(item + 0x35) = 0;
    } else {
        // Item is still referenced, add to list
        debugLog();
        *(char*)(item + 0x35) = 0;

        int currentSize = *(int*)((int)this + 0x2c);
        int currentCapacity = *(int*)((int)this + 0x30);
        if (currentSize == currentCapacity) {
            // Need to grow the array
            int newCapacity = (currentCapacity == 0) ? 1 : (currentCapacity * 2);
            resizeArray(newCapacity);
        }
        int* slot = (int*)(*(int*)((int)this + 0x28) + currentSize * 4);
        *(int*)((int)this + 0x2c) = currentSize + 1;  // increment size after use
        if (slot != nullptr) {
            *slot = (int)item;
        }
    }
}