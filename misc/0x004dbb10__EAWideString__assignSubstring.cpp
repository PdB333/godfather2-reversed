// FUNC_NAME: EAWideString::assignSubstring
int* __thiscall EAWideString::assignSubstring(int* thisPtr, const wchar_t* source, int startIndex, uint count)
{
    uint newSizeBytes;
    int allocResult;
    longlong allocSize;

    newSizeBytes = count * 2; // wide char size = 2 bytes
    if (count != 0) {
        if ((uint)thisPtr[2] <= newSizeBytes) {
            // Need to reallocate
            if (thisPtr[0] != 0) {
                // Call deallocator function stored at offset +0xC
                ((void (*)(void*))thisPtr[3])((void*)thisPtr[0]);
            }
            // Calculate new allocation size: (count | 0x80000000) + 1, then *2
            allocSize = (longlong)((count & 0x7fffffff) + 1) * 2;
            thisPtr[2] = newSizeBytes; // update capacity
            allocResult = FUN_009c8e50(-(uint)((int)((ulonglong)allocSize >> 0x20) != 0) | (uint)allocSize);
            thisPtr[0] = allocResult;
            thisPtr[3] = (int)thunk_FUN_009c8eb0; // store deallocator function
        }
        // Copy the substring
        _memcpy((void*)thisPtr[0], (void*)(source + startIndex), newSizeBytes);
        // Null-terminate
        *(wchar_t*)(newSizeBytes + thisPtr[0]) = 0;
        thisPtr[1] = count; // update length
        return thisPtr;
    }
    // count == 0: set to empty string
    if ((wchar_t*)thisPtr[0] != (wchar_t*)0x0) {
        *(wchar_t*)thisPtr[0] = 0;
    }
    thisPtr[1] = 0;
    return thisPtr;
}