// FUNC_NAME: GodfatherGameManager::clearRegisteredObjects
void __thiscall GodfatherGameManager::clearRegisteredObjects() {
    int count = *(int *)((uintptr_t)this + 0x654);   // number of registered objects
    if (count > 0) {
        int* objectPtr = (int*)((uintptr_t)this + 0x658); // start of 8-byte entries
        do {
            FUN_00459280(objectPtr);                     // release/destroy entry
            objectPtr += 2;                              // advance 8 bytes (2 ints)
            count--;
        } while (count > 0);
        *(int *)((uintptr_t)this + 0x654) = 0;         // reset count
    } else {
        *(int *)((uintptr_t)this + 0x654) = 0;         // ensure zero
    }
}