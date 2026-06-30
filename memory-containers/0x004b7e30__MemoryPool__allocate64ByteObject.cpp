// FUNC_NAME: MemoryPool::allocate64ByteObject
void __thiscall MemoryPool::allocate64ByteObject(uint headerValue, void* sourceData)
{
    // this->blockBase points to the beginning of the memory pool block
    int* block = *this; // Dereference this to get the base pointer (offset 0 from this)
    
    // Free pointer is stored at block + 0x14
    int** freePtrSlot = (int**)(block + 0x14);
    
    // Write vtable pointer from global constant at current free position
    **freePtrSlot = (int)&PTR_LAB_0112467c;
    // Advance free pointer by 4 bytes (size of vtable pointer)
    *freePtrSlot = *freePtrSlot + 4;
    
    // Write the header value (e.g., object type or size) after the vtable
    **freePtrSlot = headerValue;
    
    // Align next data to 16-byte boundary (common for SIMD optimizations)
    void* alignedDst = (void*)((int)(*freePtrSlot) + 0x13U & 0xFFFFFFF0);
    *freePtrSlot = (int*)alignedDst;
    
    // Copy the 64-byte payload from sourceData to the aligned destination
    memcpy(alignedDst, sourceData, 0x40);
    
    // Advance free pointer past the copied data
    *freePtrSlot = (int*)((int)*freePtrSlot + 0x40);
}