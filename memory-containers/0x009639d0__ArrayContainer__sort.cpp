// FUNC_NAME: ArrayContainer::sort
void __thiscall ArrayContainer::sort(void* thisPtr, int (*comparisonFunc)(const void*, const void*))
{
    // Offset +0x00: pointer to array of 4-byte elements
    void* array = *(void**)thisPtr;
    // Offset +0x04: number of elements in the array
    uint32_t count = *(uint32_t*)((char*)thisPtr + 4);

    if (count > 1)
    {
        // Sort using C library qsort, element size = 4 bytes
        qsort(array, count, 4, comparisonFunc);
    }
}