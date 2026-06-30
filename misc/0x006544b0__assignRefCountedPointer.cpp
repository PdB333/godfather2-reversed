// FUNC_NAME: assignRefCountedPointer

void assignRefCountedPointer(void* dstObj, void* srcObj) {
    // Dest: pointer to the destination smart pointer object (internal raw pointer is at offset 0)
    // Src: pointer to the source smart pointer object (internal raw pointer is at offset 0)
    // Objects expected to have vtable at offset 0 and refcount at offset 8

    int* oldPtr = *reinterpret_cast<int**>(dstObj);   // destination's current raw pointer
    int* newPtr = *reinterpret_cast<int**>(srcObj);   // source's raw pointer

    // Release old reference
    if (oldPtr != nullptr) {
        int* refCountPtr = oldPtr + 2;   // refcount at offset 8 (2 ints after start)
        (*refCountPtr)--;
        if (*refCountPtr == 0) {
            // Call destructor via vtable (third entry at vtable+8)
            void (*destructor)(void) = *reinterpret_cast<void (**)(void)>(*oldPtr + 8);
            destructor();
        }
    }

    // Assign new pointer
    *reinterpret_cast<int**>(dstObj) = newPtr;

    // Add reference to new object
    if (newPtr != nullptr) {
        int* refCountPtr = newPtr + 2;   // refcount at offset 8
        (*refCountPtr)++;
    }
}