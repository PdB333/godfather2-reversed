// FUNC_NAME: releaseObject

// Global data offset for manager singleton (likely EARS::MemoryManager or similar)
#define DAT_012234ac 0x12234ac

void releaseObject(void* object) {
    // The global at DAT_012234ac contains a pointer to a manager object at offset +4.
    // The manager's vtable's second entry (offset +4) is a function that takes (object, 0).
    // This is commonly used to release engine objects.
    void** managerPtr = *(void***)(DAT_012234ac + 4); // pointer to manager
    void (*releaseFunc)(void*, int) = (void (*)(void*, int))(*(void**)managerPtr + 4);
    releaseFunc(object, 0);
}