// FUNC_NAME: MemoryAllocator::extractNextAllocation
// Address: 0x004b8f10
// This function reads allocation metadata from a sequential buffer managed by the allocator,
// then invokes a callback to process the allocation. It aligns the buffer pointer, extracts
// header fields, and advances the internal pointer past the allocation block.
// The allocator object (this) has at offset +0x18 a pointer to the current position in the buffer.

void __thiscall MemoryAllocator::extractNextAllocation(void* callbackArg) // callbackArg points to a struct whose first element is a function pointer
{
    // +0x18: current buffer pointer (may be misaligned)
    void* currentPtr = *(void**)((int)this + 0x18);

    // Read first 32-bit value from the original pointer (before alignment)
    uint32_t firstValue = *(uint32_t*)currentPtr;

    // Align buffer pointer to next 4-byte boundary (round up to 4)
    uint32_t* alignedHeader = (uint32_t*)(((uint32_t)currentPtr + 7) & 0xFFFFFFFC);
    *(void**)((int)this + 0x18) = alignedHeader;

    // Read the four fields from the aligned header
    uint32_t field0 = alignedHeader[0]; // often a type or another pointer
    uint32_t field1 = alignedHeader[1];
    int32_t size = (int32_t)alignedHeader[2];      // size in dwords? (multiplied by 4 later)
    int32_t alignment = (int32_t)alignedHeader[3]; // alignment requirement (power of 2)

    // Advance the buffer pointer past the 16-byte header (4 uint32)
    *(void**)((int)this + 0x18) = (alignedHeader + 4);

    // Compute the start of the allocated block: aligned to 'alignment' bytes after the header.
    // Align the address of the header plus alignment offset up to the next multiple of alignment.
    uint32_t headerAddr = (uint32_t)alignedHeader;
    uint32_t blockStart = (headerAddr + (uint32_t)alignment + 0x0F) & ~((uint32_t)alignment - 1);
    // Then advance the buffer pointer past the block: block size is size * 4 bytes.
    uint32_t newPtr = (uint32_t)size * 4 + blockStart;
    *(uint32_t*)((int)this + 0x18) = newPtr;

    // Determine the high 32 bits for the 64-bit combined argument.
    // If size != 0, the high part is blockStart; otherwise 0.
    uint32_t highPart = (size != 0) ? blockStart : 0;
    uint64_t combinedArg = ((uint64_t)highPart << 32) | (uint32_t)size;

    // Call the callback function. The callback function pointer is stored as the first element
    // of the struct pointed to by callbackArg.
    typedef void (__cdecl *AllocCallback)(uint32_t, uint32_t, uint32_t, uint64_t, uint32_t);
    AllocCallback callback = *(AllocCallback*)callbackArg;
    callback(firstValue, field0, field1, combinedArg, (uint32_t)alignment);
}