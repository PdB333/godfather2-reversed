// FUNC_NAME: BaseObject::release
void BaseObject::release(int allocationSize, int param3) // 0x005a2400
{
    // Check if allocationSize is zero: just decrement refCount and possibly free
    if (allocationSize == 0) {
        if (this == nullptr) return;
    } else {
        // State must be 2 (active) before we start destroying
        if (this->m_state != 2) {
            assertFailed(); // FUN_0059bf00
        }
        this->m_state = 3; // Mark as deleting

        // Validate allocator info
        if (g_allocator->m_freeListSize > 0xffffe) {
            assertFailed(); // FUN_0059bf00
        }
        if (g_allocator->m_freeList != nullptr) {
            g_allocator->m_freeList += allocationSize; // Adjust pointer? (likely for tracking)
        }

        // Call allocator-specific free (e.g., pool deallocator)
        allocatorFree((char*)g_allocator->m_freeList + 8, allocationSize, param3); // FUN_005a5490

        // Save allocation metadata (for debug/tracking)
        int oldFreeList = g_allocator->m_freeList;
        this->m_allocSize = allocationSize;     // param_1[9]
        this->m_oldFreeList = oldFreeList;      // param_1[10]
        this->m_allocParam3 = param3;           // param_1[0xb]

        if (g_allocator->m_freeList != nullptr) {
            g_allocator->m_freeList -= allocationSize; // Restore pointer
        }

        // Call virtual function at vtable[0] (likely post-destruction hook)
        g_vtableHook(); // (*DAT_0119cb18)()
    }

    // Decrement reference count
    this->m_refCount--;
    if (this->m_refCount == 0) {
        // Run actual destructor and deallocate memory
        this->vtableDestructor(); // FUN_005a1b40
        g_memoryFree(this, sizeof(BaseObject)); // FUN_0119caf8, size 0x30 (48 bytes)
    }
}