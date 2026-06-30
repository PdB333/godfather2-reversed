// FUNC_NAME: WideString::resize
void __thiscall WideString::resize(int thisPtr, unsigned int newLength, unsigned short fillChar)
{
    // struct WideString layout:
    // +0x00: wchar_t* m_data          (pointer to buffer)
    // +0x04: int        m_length       (current character count, not including terminator)
    // +0x08: int        m_capacityBytes (allocated size in bytes)
    // +0x0C: void (*m_dealloc)(void*)  (custom deallocation function)

    int* self = (int*)thisPtr;
    wchar_t* data = (wchar_t*)self[0];
    int curLength = self[1];
    int capacityBytes = self[2];
    unsigned int newByteSize = newLength * 2;

    if (newByteSize < (unsigned int)capacityBytes)
    {
        // Enough capacity: fill newly added elements with fillChar
        for (unsigned int i = curLength; i < newLength; i++)
        {
            data[i] = fillChar;
        }

        // Set null terminator and update length only if shrinking or fillChar is non-zero
        if (newLength < (unsigned int)curLength || fillChar != 0)
        {
            data[newLength] = 0;
            self[1] = newLength;
        }
    }
    else if ((unsigned int)capacityBytes < newByteSize)
    {
        // Need reallocation: compute new byte size with overflow guard
        unsigned int safeNewLength = (newLength & 0x7FFFFFFF) + 1;
        unsigned int newAllocSize = safeNewLength * 2;
        wchar_t* newData = (wchar_t*)heapAllocate(newAllocSize); // FUN_009c8e50

        if (data != 0)
        {
            memcpy(newData, data, curLength * 2);
            if (data != 0)
            {
                ((void (*)(void*))self[3])(data); // custom dealloc
            }
        }

        self[0] = (int)newData;
        self[3] = (int)heapDeallocate; // thunk_FUN_009c8eb0

        // Fill newly allocated elements with fillChar
        memset((unsigned char*)newData + curLength * 2, fillChar, (newLength - curLength) * 2);

        // If fillChar is non-zero, set null terminator and update length
        if (fillChar != 0)
        {
            self[1] = newLength;
            newData[newLength] = 0;
        }

        self[2] = newByteSize; // new capacity in bytes
    }
}