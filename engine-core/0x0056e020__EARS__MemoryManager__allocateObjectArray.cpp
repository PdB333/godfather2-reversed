// FUNC_NAME: EARS::MemoryManager::allocateObjectArray

uint* __fastcall EARS::MemoryManager::allocateObjectArray(void* allocatorObject, int count)
{
    // Allocate an array of objects each of size 0x38 bytes.
    // Caller's 'count' is in EDI register (unaff_EDI in decompiler).
    // Allocator object's vtable pointer is in EAX (in_EAX).

    int elementSize = 0x38; // 56 bytes per object

    // Compute total size with overflow check: count * elementSize
    // The masking pattern handles overflow by clamping to 0xFFFFFFFF.
    unsigned long long extended = (unsigned long long)count * elementSize;
    int overflow = (int)(extended >> 32) != 0;
    unsigned int totalSize = overflow ? 0xFFFFFFFF : (unsigned int)(extended & 0xFFFFFFFF);

    // Add space for one extra uint to store the count, with overflow check
    unsigned int allocSize = (totalSize > 0xFFFFFFFB) ? 0xFFFFFFFF : (totalSize + 4);

    // Call the first virtual function of the allocator (likely an allocate method)
    // The allocator's vtable is at *allocatorObject, first entry is the function.
    // Second parameter is a pointer to a three-uint temporary (local_c etc.), possibly a callback or result buffer.
    uint32_t localBuffer[3] = {0, 0, 0};
    uint* allocatedBlock = (*(uint*(__thiscall**)(void*, void*))(*((void**)allocatorObject)))(allocatorObject, &localBuffer);

    if (allocatedBlock != nullptr) {
        // Store the count at the beginning of the allocated block
        *allocatedBlock = count;

        // Construct each object in the array using _vector_constructor_iterator
        // This function is the CRT helper for array construction: pointer, elementSize, count, constructorFunctor
        void* elementStart = allocatedBlock + 1; // skip stored count
        _vector_constructor_iterator(elementStart, elementSize, count, (void*(*)(void*, void*))&objectConstructorFunc);

        // Clear a global variable (possibly debug counter or state flag)
        g_constructFlag = 0;

        // Return pointer to the first constructed object (after the count)
        return (uint*)elementStart;
    }

    g_constructFlag = 0;
    return nullptr;
}