// FUNC_NAME: EAWideString::ConstructFromTwo
void __thiscall EAWideString::ConstructFromTwo(int *thisPtr, void *string1, uint len1, void *string2, uint len2)
{
    uint totalLen;
    longlong allocSize;
    void *buffer;
    
    if (len1 != 0) {
        if (len2 == 0) {
            // Only first string provided
            thisPtr[1] = len1;                                      // +0x04: length (in wchar_t units)
            thisPtr[2] = len1 * 2;                                   // +0x08: capacity in bytes
            // Allocate (len1+1)*2 bytes (round up to avoid zero)
            allocSize = (longlong)((len1 & 0x7fffffff) + 1) * 2;
            buffer = (void *)EAAlloc((uint)((int)((ulonglong)allocSize >> 32) != 0) | (uint)allocSize);
            *thisPtr = (int)buffer;                                 // +0x00: pointer to wide string data
            _memcpy(buffer, string1, len1 * 2);                     // copy wchar_t* content
        }
        else {
            // Both strings provided – concatenate
            totalLen = len1 + len2;
            thisPtr[1] = totalLen;                                  // length
            thisPtr[2] = totalLen * 2;                              // capacity bytes
            allocSize = (longlong)((totalLen & 0x7fffffff) + 1) * 2;
            buffer = (void *)EAAlloc((uint)((int)((ulonglong)allocSize >> 32) != 0) | (uint)allocSize);
            *thisPtr = (int)buffer;
            _memcpy(buffer, string1, len1 * 2);                     // copy first part
            _memcpy((void *)(*thisPtr + len1 * 2), string2, len2 * 2); // copy second part
        }
        // Null-terminate the wide string
        *(wchar_t *)(*thisPtr + thisPtr[1] * 2) = L'\0';
        thisPtr[3] = (int)&EADealloc;                              // +0x0C: deallocator function pointer
        return;
    }
    if (len2 != 0) {
        // Only second string provided
        thisPtr[1] = len2;
        thisPtr[2] = len2 * 2;
        allocSize = (longlong)((len2 & 0x7fffffff) + 1) * 2;
        buffer = (void *)EAAlloc((uint)((int)((ulonglong)allocSize >> 32) != 0) | (uint)allocSize);
        *thisPtr = (int)buffer;
        _memcpy(buffer, string2, len2 * 2);
        *(wchar_t *)(*thisPtr + thisPtr[1] * 2) = L'\0';
        thisPtr[3] = (int)&EADealloc;
        return;
    }
    // Both strings empty – zero-initialize
    *thisPtr = 0;                      // +0x00: null pointer
    thisPtr[2] = 0;                    // +0x08: capacity 0
    thisPtr[1] = 0;                    // +0x04: length 0
    return;
}