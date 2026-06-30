// FUNC_NAME: MemoryPoolObject::destructor
void __fastcall MemoryPoolObject::destructor(MemoryPoolObject *this)
{
    int allocIndex = this->m_allocIndex; // offset +0x18

    // Set vtable to a special "destroying" vtable (likely to prevent virtual calls during destruction)
    this->m_vtable = &PTR_LAB_00e397fc;

    // If the allocation index is valid (>= 0), perform TLS-based deallocation
    if (allocIndex >= 0)
    {
        // Retrieve thread-local storage for memory pool manager
        void *tlsValue = TlsGetValue(DAT_01139810);

        // Deallocate the block at m_allocPtr
        // size = (allocIndex & 0x3FFFFFFF) * 0x30, poolTag = 0x17 (23)
        DeallocateFromTlsPool(this->m_allocPtr, // offset +0x10
                              (allocIndex & 0x3FFFFFFF) * 0x30,
                              0x17);
    }

    // Set vtable to the base class vtable (continued destruction chain)
    this->m_vtable = &PTR_LAB_00dc4710;

    return;
}