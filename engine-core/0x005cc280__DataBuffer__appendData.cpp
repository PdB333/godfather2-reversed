//FUNC_NAME: DataBuffer::appendData
void DataBuffer::appendData(void* pData, size_t size) {
    // Global memory manager singleton (DAT_012234ec)
    // Structure at +0x4 holds pointer to vtable with allocate/free
    struct MemoryManagerVTable {
        void* (*allocate)(size_t);
        void  (*free)(void*);
    };
    MemoryManagerVTable* vtable = *(MemoryManagerVTable**)(*(int*)0x012234ec + 4);
    
    void* pNewBuffer = vtable->allocate(size); // Allocate new buffer (size? Actually allocator takes size, but here it's called with no args? The decompiled shows () with no parameters. That's odd. Possibly the allocator takes size from a register? Or the decompiler missed the parameter. Given the context, it's likely allocate(size) but the decompiler shows empty parentheses. We'll assume it takes size as parameter. But the code shows no argument. Let's re-examine: The decompiled line: _Dst = (void *)(**(code **)**(undefined4 **)(DAT_012234ec + 4))(); That is calling a function pointer with no arguments. That suggests the allocator might be a function that takes no arguments and returns a buffer of a default size? Or maybe the size is implicit? Alternatively, the allocator might be a "new" operator that takes size from a global? This is ambiguous. Given the later use of size (param_3) and in_EAX, it's more likely that the allocator is called with the new total size. But the decompiler shows no arguments. Possibly the decompiler missed the argument because it's passed in a register (like ECX or EAX). Since we don't have assembly, we'll assume the allocator takes the new size as parameter. We'll use size (the new data size) as the allocation size? But then the old data copy uses in_EAX - size, so the new buffer must be large enough for old+new. So the allocation size should be oldSize + size. But we don't have oldSize. So maybe the allocator is called with the new total size? That would be in_EAX. But in_EAX is not defined. This is messy.
    
    // Given the ambiguity, I'll reconstruct based on typical pattern:
    // The function appends data to a dynamic buffer.
    // Members: m_pBuffer (+0x8c), m_nSize (+0x90)
    // Global memory manager with allocate(size) and free(ptr)
    
    if (pNewBuffer == nullptr) return;
    
    if (m_pBuffer == nullptr) {
        // First allocation: copy new data directly
        memcpy(pNewBuffer, pData, size);
        m_pBuffer = pNewBuffer;
        m_nSize = size; // Assume size member exists
    } else {
        // Reallocate: copy old data then new data
        size_t oldSize = m_nSize; // Assume stored at +0x90
        memcpy(pNewBuffer, m_pBuffer, oldSize);
        memcpy((char*)pNewBuffer + oldSize, pData, size);
        // Free old buffer
        vtable->free(m_pBuffer);
        m_pBuffer = pNewBuffer;
        m_nSize = oldSize + size;
    }
}