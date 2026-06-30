// FUNC_NAME: copyRefCountedArray
// Function at 0x005a3780: Helper to copy an array of reference-counted pointers.
// Handles refcount increment/decrement, and releases objects when refcount reaches zero.
// Parameters:
//   dst - destination array of pointers (to ref-counted objects)
//   srcEnd - pointer to one-past-the-end of source array
//   srcStart - pointer to start of source array (passed in EAX via __thiscall convention)
// Returns: dst (dest array pointer, for chaining)
void** __thiscall copyRefCountedArray(void** dst, void** srcStart, void** srcEnd)
{
    void** dstCur = dst;
    void** srcCur = srcStart;

    if (srcCur != srcEnd) {
        do {
            void* newObj = *srcCur;
            // Release old object if present
            if (newObj != nullptr) {
                int* refCount = (int*)*srcCur; // ref count at offset 0
                *refCount = *refCount - 1;
                if (*refCount == 0) {
                    releaseRefCountedObject(*srcCur); // FUN_005a3270
                }
            }
            // Assign new pointer
            *dstCur = newObj;
            // Increment ref count of new object (if not null)
            if (newObj != nullptr) {
                int* refCount = (int*)*dstCur;
                *refCount = *refCount + 1;
            }
            srcCur++;
            dstCur++;
        } while (srcCur != srcEnd);
    }
    return dst;
}