// FUNC_NAME: ShortArray::ensureCapacity
void __thiscall ShortArray::ensureCapacity(int *thisPtr, uint requiredElements) {
    // thisPtr: [0]=data, [4]=currentSize, [8]=capacity, [12]=deleterFunc
    uint requiredBytes = requiredElements * 2; // each element is 2 bytes
    if ((uint)thisPtr[2] < requiredBytes) {
        void *oldData = (void *)*thisPtr;
        uint newAllocElements = (requiredElements & 0x7fffffff) + 1; // ensure at least 1 extra
        if (oldData == (void *)0x0) {
            // First allocation
            longlong allocSize = (ulonglong)newAllocElements * 2;
            unsigned short *newData = (unsigned short *)FUN_009c8e50(-(uint)((int)((ulonglong)allocSize >> 0x20) != 0) | (uint)allocSize);
            *thisPtr = (int)newData;
            *newData = 0; // null terminate? maybe zero first element
        } else {
            // Reallocate to larger buffer
            longlong allocSize = (ulonglong)newAllocElements * 2;
            unsigned short *newData = (unsigned short *)FUN_009c8e50(-(uint)((int)((ulonglong)allocSize >> 0x20) != 0) | (uint)allocSize);
            *thisPtr = (int)newData;
            _memcpy(newData, oldData, thisPtr[1] * 2); // copy existing elements
            *(unsigned short *)(*thisPtr + thisPtr[1] * 2) = 0; // null terminate after old size
            if (oldData != (void *)0x0) {
                // Free old buffer with stored deleter
                ((void (*)(void *))thisPtr[3])(oldData);
                thisPtr[2] = requiredBytes;
                thisPtr[3] = (int)thunk_FUN_009c8eb0; // set default deleter
                return;
            }
        }
        // Set default deleter and new capacity (only reached for first alloc or if oldData was null in realloc path? but that can't happen)
        thisPtr[3] = (int)thunk_FUN_009c8eb0;
        thisPtr[2] = requiredBytes;
    }
}