// FUNC_NAME: RefCountedObject::release
// Function at 0x004e88c0: Releases a reference-counted object. Decrements counter, calls destructor if zero.
// Structure layout: 
//   +0x00 : vtbl* (vtable pointer, implicitly used by virtual calls)
//   +0x04 : int refCount

int* __thiscall RefCountedObject::release(int thisPtr, int arg) {
    int* refCountPtr;
    char canDelete;

    if (thisPtr != 0) {
        // Call virtual method at index 2 (vtable+8) to check if object is allowed to be deleted
        canDelete = (*(int (__thiscall**)(int))(*thisPtr + 8))(arg);
        if (canDelete != 0) {
            // Decrement reference count
            refCountPtr = (int*)(thisPtr + 4);  // +0x04 refCount
            (*refCountPtr)--;
            if (*refCountPtr == 0) {
                // Call virtual destructor (vtable+4)
                (*(void (__thiscall**)(int))(*thisPtr + 4))();
            }
            // Return a non-null dummy pointer (stack address, used as success indicator)
            return (int*)&arg; // Actually local_4, but returned pointer value is irrelevant
        }
        // Even if deletion is not allowed, still decrement and possibly destroy
        refCountPtr = (int*)(thisPtr + 4);
        (*refCountPtr)--;
        if (*refCountPtr == 0) {
            (*(void (__thiscall**)(int))(*thisPtr + 4))();
        }
    }
    return 0;
}