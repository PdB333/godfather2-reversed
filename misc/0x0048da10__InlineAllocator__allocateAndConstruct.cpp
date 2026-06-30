// FUNC_NAME: InlineAllocator::allocateAndConstruct
// Parameters: 
//   param_1: this pointer to InlineAllocator object
//   param_2: pointer to TypeInfo structure whose first member is a constructor function pointer
// Description: 
//   Allocates a 64-byte chunk from the inline buffer (at offset +0x18), copies the 
//   current content to a 64-byte stack buffer, updates the allocation pointer, then 
//   calls the constructor function from the type info. This is used for placement new 
//   or object construction directly within the pre‑allocated pool.
// Memory layout: 
//   InlineAllocator:
//     +0x18: void* bufferPtr (current free pointer inside the allocated memory block)
//   The buffer is managed as a simple pool where each allocation is 64 bytes.
//   After moving the free pointer, it aligns the next allocation appropriately.

void InlineAllocator::allocateAndConstruct(const void* constructorFunc) { // constructorFunc is actually a pointer to a pointer to function? Decompiled says undefined4* param_2, but we use it as a pointer to a function pointer.
    // Align current buffer pointer to the next 4-byte boundary
    void* alignedSrc = reinterpret_cast<void*>((reinterpret_cast<uint32_t>(this->bufferPtr) + 3) & ~3);
    this->bufferPtr = alignedSrc;

    // Save the next 64 bytes from the aligned source to a local stack buffer
    // The stack buffer is 64 bytes (16 uint32)
    uint32_t tempBuffer[16]; // actually local_48[17] but only 16 used; we simplify to 16
    memcpy(tempBuffer, alignedSrc, 64);

    // Advance buffer pointer beyond the copied chunk
    this->bufferPtr = reinterpret_cast<void*>(reinterpret_cast<uint32_t>(alignedSrc) + 64);

    // Read two sizes from the just-copied block (embedded metadata)
    uint32_t size1 = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint32_t>(alignedSrc) + 64);  // offset +0x40
    uint32_t size2 = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint32_t>(alignedSrc) + 68);  // offset +0x44

    // Update buffer pointer to the next free position after the current allocation,
    // accounting for alignment and the two size fields
    this->bufferPtr = reinterpret_cast<void*>(
        (size1 + 3) & ~3 +
        (reinterpret_cast<uint32_t>(alignedSrc) + size2 + 0x47) & ~(size2 - 1)
    );

    // Copy the 64 bytes to yet another stack buffer (auStackY_9c + uStackY_60) 
    uint32_t stackBuffer2[16];
    memcpy(stackBuffer2, tempBuffer, 64);

    // Call the constructor function (pointed by the first word of the type info)
    void (*constructor)() = *reinterpret_cast<void(**)()>(constructorFunc);
    constructor();
}