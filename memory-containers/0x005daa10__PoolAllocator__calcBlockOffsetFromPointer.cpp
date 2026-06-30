// FUNC_NAME: PoolAllocator::calcBlockOffsetFromPointer

// Reconstructed from Ghidra decompilation at 0x005daa10
// This function aligns a pointer to a 256-byte boundary, performs a debug validation,
// then computes an offset into a pool of 0x28-byte blocks.
// The caller passes basePtr in EDI and somePtr in EAX (both registers) which are
// likely the pool's base address and an internal pointer (e.g., free list end).

int PoolAllocator::calcBlockOffsetFromPointer(uint pointer, int somePtr, int basePtr)
{
    uint originalPointer = pointer;
    uint alignedPointer = pointer & 0xFFFFFF00; // Align to 256-byte page boundary

    // Debug/validation call – checks the aligned pointer against pool bounds
    FUN_005daaa0(originalPointer, alignedPointer, 0, alignedPointer);

    // Compute number of 0x28-byte blocks between somePtr and originalPointer
    int blockCount = (somePtr - (int)originalPointer) / 0x28;

    // Return base pointer minus the offset of those blocks
    // Equivalent to: basePtr - (blockCount * 0x28)
    return basePtr + blockCount * (-0x28);
}