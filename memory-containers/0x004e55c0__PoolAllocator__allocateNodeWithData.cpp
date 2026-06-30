// FUNC_NAME: PoolAllocator::allocateNodeWithData
// Address: 0x004e55c0
// Allocates a node from a pool: writes a vtable pointer (from PTR_LAB_01124ab8),
// a type identifier (param2), and 16 bytes of data (param3) at a 16-byte-aligned offset.
// The pool buffer stores the next free pointer at offset +0x14.

void __thiscall PoolAllocator::allocateNodeWithData(int* thisPtr, uint32_t typeId, const uint64_t* data16)
{
    // 'thisPtr' is a pointer to the first field of the pool object.
    // The pool object's first field (offset 0) is a pointer to its backing buffer.
    uint8_t* poolBuffer = reinterpret_cast<uint8_t*>(*thisPtr);
    
    // At poolBuffer + 0x14 lives a pointer to the next free space in the pool.
    uintptr_t& currentAllocPtr = *reinterpret_cast<uintptr_t*>(poolBuffer + 0x14);
    uintptr_t writePos = currentAllocPtr;           // Current write position
    
    // Write vtable pointer (global table) at the current position
    *reinterpret_cast<void**>(writePos) = reinterpret_cast<void*>(&PTR_LAB_01124ab8);
    writePos += 4;                                  // Advance past vtable pointer
    
    // Write type identifier (param2) next
    *reinterpret_cast<uint32_t*>(writePos) = typeId;
    // writePos now points to the byte after typeId (still at the same address where typeId was written)
    
    // Align writePos to the next 16‑byte boundary (rounding up)
    uintptr_t alignedPos = (writePos + 0x13) & 0xFFFFFFF0;
    
    // Copy the 16 bytes from data16 to the aligned location
    uint64_t* dest = reinterpret_cast<uint64_t*>(alignedPos);
    dest[0] = data16[0];
    dest[1] = data16[1];
    
    // Update the pool's free pointer to the end of the allocated 16‑byte block
    currentAllocPtr = alignedPos + 0x10;
}