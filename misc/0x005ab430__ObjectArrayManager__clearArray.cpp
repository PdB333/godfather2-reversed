// FUNC_NAME: ObjectArrayManager::clearArray
void __thiscall ObjectArrayManager::clearArray(void)
{
    // +0x50: flag (set to 0)
    *(int *)(this + 0x50) = 0;

    // +0x4c: pointer to array of object pointers
    // +0x54: array size (number of elements)
    int *arrayPtr = *(int **)(this + 0x4c);
    if (arrayPtr != 0) {
        int count = *(int *)(this + 0x54);
        for (int i = 0; i < count; i++) {
            int *objPtr = *(int **)(arrayPtr + i);
            if (objPtr != 0) {
                // Call destructor via global vtable table at DAT_0103aee0
                // The index is the lower 15 bits of the first DWORD (vtable pointer)
                uint vtableIndex = *objPtr & 0x7fff;
                void (*destructor)(void *) = *(void (**)(void *))(&DAT_0103aee0 + vtableIndex * 4);
                destructor(objPtr);
            }
            // Null out the pointer
            *(int **)(arrayPtr + i) = 0;
        }
        // Free the array memory using global function at DAT_0119caf4
        void (*freeFunc)(void *) = *(void (**)(void *))DAT_0119caf4;
        freeFunc(arrayPtr);
        *(int **)(this + 0x4c) = 0;
    }
    // Call additional cleanup function
    FUN_005ba710();
}