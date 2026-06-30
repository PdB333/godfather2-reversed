// FUNC_NAME: RefCountManager::lockAndExtractPointer
uint __thiscall RefCountManager::lockAndExtractPointer(void* manager, void* objectPtr) {
    // manager+0x4e8: pointer to a CRITICAL_SECTION used for thread-safe ref counting
    LPCRITICAL_SECTION cs = *(LPCRITICAL_SECTION*)((char*)manager + 0x4e8);

    if (cs != nullptr) {
        EnterCriticalSection(cs);

        // The reference count is stored immediately after the CRITICAL_SECTION (offset 0x18)
        volatile int* refCount = (volatile int*)((char*)cs + sizeof(CRITICAL_SECTION));
        (*refCount)++;          // AddRef – prevent deletion during read

        // Read the tagged pointer from the object's reference count field
        // (stored at 4 bytes before the object's user data: objectPtr[-1])
        uint taggedPtr = *(uint*)((char*)objectPtr - 4);

        (*refCount)--;          // Release – balance the temporary increment
        LeaveCriticalSection(cs);

        // Mask out the lower 3 bits (flags) to extract the real pointer
        return taggedPtr & 0x7ffffff8;
    } else {
        // No lock available; direct read
        uint taggedPtr = *(uint*)((char*)objectPtr - 4);
        return taggedPtr & 0x7ffffff8;
    }
}