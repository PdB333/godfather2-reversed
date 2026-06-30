// FUNC_NAME: MemoryAllocator::allocateObject
// Address: 0x005d4420
// Purpose: Reads allocation parameters (constructor, size, alignment) from a memory stream,
// advances the stream pointer, aligns the allocation address, and calls the constructor.
// The memory stream is stored at offset +0x18 in the allocator object.

void __thiscall MemoryAllocator::allocateObject(void *thisPtr, undefined4 *pConstructorFunc)
{
    uint32_t *pCurrent;       // current pointer in memory stream (at +0x18)
    uint32_t constructorAddr; // address of constructor to invoke (first field read)
    uint32_t objectSize;      // size of object (second field)
    uint32_t alignment;       // alignment requirement (third field)
    uint32_t alignedAddr;     // aligned start address for the object

    // Read current stream pointer from this+0x18
    pCurrent = *(uint32_t **)((int)thisPtr + 0x18);

    // Read three fields sequentially, advancing the stream pointer after each read
    constructorAddr = pCurrent[0];
    *(uint32_t **)((int)thisPtr + 0x18) = pCurrent + 1; // skip first field

    objectSize = pCurrent[1];
    *(uint32_t **)((int)thisPtr + 0x18) = pCurrent + 2; // skip second field

    alignment = pCurrent[2];
    *(uint32_t **)((int)thisPtr + 0x18) = pCurrent + 3; // skip third field

    // Compute aligned address: align (base + alignment + 0x0b) down to multiple of alignment
    // This ensures the object data starts at a properly aligned offset past the header
    alignedAddr = ((int)pCurrent + alignment + 0x0b) & ~(alignment - 1U);

    // Update the stream pointer to the end of this allocated block
    // Block size = aligned object size (rounded up to 4) + alignedAddr
    *(uint32_t *)((int)thisPtr + 0x18) = (objectSize + 3U & 0xfffffffc) + alignedAddr;

    // Call the constructor function stored in pConstructorFunc (or via a pointer)
    // Arguments: constructorAddr, a 64-bit value composed of (objectSize << 32) | (alignedAddr if objectSize>0 else 0), alignment
    // The low 32 bits of the second argument come from -(objectSize != 0) & alignedAddr
    (*(code *)*pConstructorFunc)(constructorAddr,
                                 CONCAT44(objectSize, -(uint)(objectSize != 0) & alignedAddr),
                                 alignment);
}