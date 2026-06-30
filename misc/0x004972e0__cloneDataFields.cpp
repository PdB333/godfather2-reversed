// FUNC_NAME: cloneDataFields
void cloneDataFields(void *source)
{
    // Call allocator that returns a pointer via out parameter (stored at stack)
    void *newObj;
    EngineAlloc::Allocate(&newObj); // FUN_004986e0 - custom memory allocator

    if (newObj)
    {
        // Copy the first four DWORDs (16 bytes) from source into the new object at offsets +8, +0xC, +0x10, +0x14
        *(uint32_t *)((uint8_t *)newObj + 8)  = *(uint32_t *)source;                // source[0]
        *(uint32_t *)((uint8_t *)newObj + 0xC) = *(uint32_t *)((uint8_t *)source + 4); // source[1]
        *(uint32_t *)((uint8_t *)newObj + 0x10) = *(uint32_t *)((uint8_t *)source + 8); // source[2]
        *(uint32_t *)((uint8_t *)newObj + 0x14) = *(uint32_t *)((uint8_t *)source + 0xC); // source[3]
    }
}