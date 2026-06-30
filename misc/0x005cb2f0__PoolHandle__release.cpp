// FUNC_NAME: PoolHandle::release
// Function at 0x005cb2f0: Destroys a pooled handle object, cleaning up its internal resources and returning the handle itself to the free list.

void PoolHandle::release()
{
    // this->field0 (offset +0x00) is a pointer to an internal resource object
    int *resourcePtr = reinterpret_cast<int*>(this->m_resource);
    if (resourcePtr != nullptr) {
        // Set a flag at offset 0x0C of the resource (e.g., 0x200000 = some destruction flag)
        resourcePtr[0x03] |= 0x200000;   // *(resourcePtr + 0x0C) |= 0x200000

        // Call a cleanup helper (likely virtual or static)
        InternalCleanup();

        // Clear a back-pointer at offset +0x08 of the resource, if present
        if (*(int**)(resourcePtr + 0x02) != nullptr) {   // +0x08
            **(int**)(resourcePtr + 0x02) = 0;
            *(int**)(resourcePtr + 0x02) = nullptr;
        }
    }

    // this->field1 (offset +0x04) is a reference-counted object
    int *refCounted = reinterpret_cast<int*>(this->m_refObject);
    if (refCounted != nullptr) {
        int *refCountPtr = refCounted + 1;   // ref count at offset +0x04
        *refCountPtr = *refCountPtr - 1;
        if (*refCountPtr == 0) {
            // Call virtual destructor of the reference-counted object
            (*(void(__thiscall**)(int*))(*refCounted + 4))(refCounted);
        }
    }

    // Return this handle to the global free list
    // gMemoryManager + 0x14 points to the current free list head (a pointer into a preallocated buffer)
    int **freeListPtr = reinterpret_cast<int**>(reinterpret_cast<char*>(gMemoryManager) + 0x14);
    // Write the free node vtable at the current head position
    *(*freeListPtr) = reinterpret_cast<int>(&HANDLE_FREE_VTABLE);   // 0x01126260
    *freeListPtr = *freeListPtr + 1;   // advance head past vtable slot
    // Write this handle pointer into the next slot
    *reinterpret_cast<int*>(*freeListPtr) = reinterpret_cast<int>(this);
    *freeListPtr = *freeListPtr + 1;   // advance head past handle pointer

    // Final cleanup on the original resource pointer
    if (this->m_resource != nullptr) {
        // Zero out the back-pointer at +0x08 and clear the resource pointer
        *(int**)(this->m_resource + 2) = nullptr;   // +0x08
        this->m_resource = nullptr;
    }
}