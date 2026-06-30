// FUNC_NAME: SmallFixedArray::SmallFixedArray
void __thiscall SmallFixedArray::SmallFixedArray(void *thisPointer)
{
    int *thisPtr = (int *)thisPointer;  // this as int pointer

    // +0x00: DWORD field0 – set to 0
    thisPtr[0] = 0;
    // +0x04: DWORD field4 – set to 0
    thisPtr[1] = 0;
    // +0x08: pointer to embedded array data (offset +0x0C)
    thisPtr[2] = (int)(thisPtr + 3);  // points to the first 8-byte element

    // +0x0C: first 8-byte element (QWORD1)
    *(unsigned long long *)(thisPtr + 3) = 0ULL;
    // +0x14: second 8-byte element (QWORD2)
    *(unsigned long long *)(thisPtr + 5) = 0ULL;
}