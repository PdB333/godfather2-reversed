// FUNC_NAME: DynamicArray32::reserve

// +0x00: m_pData (pointer to array of elements, each 32 bytes)
// +0x04: m_nSize (number of elements currently used)
// +0x08: m_nCapacity (allocated capacity in elements)
// +0x0C: m_pAllocator (pointer to allocator object, or null for default)
// +0x10: m_pAllocatorVtbl (pointer to allocator vtable pointer? unclear, but used to call allocate/deallocate)
void __thiscall DynamicArray32::reserve(uint newCapacity) {
    // Check if new capacity exceeds current capacity
    if (newCapacity > this->m_nCapacity) {
        // Allocator context: use custom if set, else fallback to a global default allocator
        void* allocCtx = this->m_pAllocator;
        if (allocCtx == 0) {
            allocCtx = &DAT_01218a14; // Global default allocator instance
        }
        // Allocate new block: newCapacity * 32 bytes
        // vtable at m_pAllocatorVtbl: first entry is allocate(size, allocCtx)
        AllocVtbl* vtbl = *(AllocVtbl**)this->m_pAllocatorVtbl;
        char* newData = reinterpret_cast<char*>(vtbl->allocate(newCapacity << 5, allocCtx));

        // Copy existing elements if any
        if (this->m_pData != 0) {
            if (this->m_nSize != 0) {
                unsigned int idx = 0;
                unsigned int count = 0;
                unsigned char* src = reinterpret_cast<unsigned char*>(this->m_pData);
                unsigned char* dst = newData;
                do {
                    // Copy 32 bytes (4 qwords) per element
                    *(unsigned long long*)dst = *(unsigned long long*)src;
                    *(unsigned long long*)(dst + 8) = *(unsigned long long*)(src + 8);
                    *(unsigned long long*)(dst + 16) = *(unsigned long long*)(src + 16);
                    *(unsigned long long*)(dst + 24) = *(unsigned long long*)(src + 24);
                    count++;
                    src += 0x20;
                    dst += 0x20;
                } while (count < this->m_nSize);
            }
            // Free old data using allocator's deallocate (second vtable entry, offset 4)
            // deallocate(pointer, 0)
            vtbl->deallocate(this->m_pData, 0);
        }
        // Update members
        this->m_pData = reinterpret_cast<char*>(newData);
        this->m_nCapacity = newCapacity;
    }
}