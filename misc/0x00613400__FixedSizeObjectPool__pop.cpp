// FUNC_NAME: FixedSizeObjectPool::pop
void __fastcall FixedSizeObjectPool::pop(void* destObject, int* elementCount, void* poolBase)
{
    // Decrement the element count and copy the last element (0x40 bytes) to destObject
    if (*elementCount > 0) {
        int lastIndex = *elementCount - 1;
        *elementCount = lastIndex;
        // Copy 64 bytes from poolBase[lastIndex] to destObject
        memcpy(destObject, (char*)poolBase + lastIndex * 0x40, 0x40);
    }
}