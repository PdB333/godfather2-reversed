// FUNC_NAME: eastl::allocator::allocateAndCopy
void* __cdecl eastl::allocator::allocateAndCopy(int elementCount, void* sourceStart, int sourceEnd)
{
    void* dest;

    // If elementCount is zero, no allocation is needed; dest is set to nullptr.
    if (elementCount == 0) {
        dest = nullptr;
    }
    else {
        // Allocate space for elementCount elements (each 4 bytes)
        dest = (void*)FUN_0068ab90(elementCount * 4, "EASTL", 0, 0,
                                   "c:\\packages001_pc\\EASTL\\1.09.02\\include\\EASTL/allocator.h",
                                   0xe9);
    }

    // Copy the source range (from sourceStart to sourceEnd) into dest
    // sourceEnd is a pointer (as int) representing one past the last element
    // Note: This memmove is safe even if dest is nullptr (range copy size must be zero)
    _memmove(dest, sourceStart, sourceEnd - (int)sourceStart);

    return dest;
}