// FUNC_NAME: memoryPoolDeallocateWithDestructor
void memoryPoolDeallocateWithDestructor(void* objectPtr) {
    if (objectPtr != nullptr) {
        callDestructor();
        // Global deallocation function for size 0x30 (48 bytes)
        extern void (*pFreeFunc)(void*, unsigned int);
        pFreeFunc(objectPtr, 0x30);
    }
}