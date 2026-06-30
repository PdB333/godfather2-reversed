// FUNC_NAME: EAString::assign

int* __thiscall EAString::assign(int* pThis, const wchar_t* source, int offset, unsigned int count)
{
    // pThis layout:
    // [0] = wchar_t* buffer        // pointer to character data
    // [1] = int length             // number of characters (wchar_t units)
    // [2] = int capacity           // capacity in bytes (2 * max_chars)
    // [3] = void* deallocator      // function pointer to free buffer

    unsigned int neededSize = count * 2; // bytes needed for the new characters
    if (count != 0) {
        if ((unsigned int)pThis[2] <= neededSize) {
            // Need to reallocate: free old buffer, allocate larger one
            if (pThis[0] != 0) {
                ((void (*)(void*))pThis[3])((void*)pThis[0]); // call custom deallocator
            }
            // Compute new allocation size: (count+1) * 2, but mask with 0x7fffffff to avoid overflow
            unsigned long long newSize = (unsigned long long)((count & 0x7fffffff) + 1) * 2;
            pThis[2] = neededSize; // update capacity (note: not the actual allocated size, but the requested)
            int* newBuffer = (int*)FUN_009c8e50((unsigned int)(long long)newSize); // custom alloc
            pThis[0] = (int)newBuffer;
            pThis[3] = (int)thunk_FUN_009c8eb0; // set default deallocator
        }
        // Copy the requested substring from source+offset
        _memcpy((void*)pThis[0], (void*)(source + offset), neededSize);
        // Null-terminate
        *(wchar_t*)(neededSize + pThis[0]) = 0;
        // Update length
        pThis[1] = count;
        return pThis;
    }
    // count == 0: set to empty string
    if ((wchar_t*)pThis[0] != (wchar_t*)0x0) {
        *(wchar_t*)pThis[0] = 0; // set first character to null
    }
    pThis[1] = 0; // length = 0
    return pThis;
}