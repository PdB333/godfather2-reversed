// FUNC_NAME: MemoryBlockManager::setAllocSize
// Function address: 0x0064e360
// Sets the allocation block size and computes the corresponding shift value for power-of-two alignment.
// The class has fields at offsets +0x1F0 (blockSize) and +0x1F4 (shiftValue).
// Global array at 0x01223170 contains configuration entries of size 0x24 bytes per context.

uint __thiscall MemoryBlockManager::setAllocSize(int param_2) {
    int *piVar1;
    uint (*getContextIndex)(); // virtual function at vtable+0x50
    uint blockSize;
    float fVar4;
    uint contextId;
    int shift;

    // Likely a debug/assert helper – called with size 0x20 and address of param_2
    FUN_0064b9e0(0x20, &param_2);

    // Retrieve the virtual function that returns an index into the global configuration table
    getContextIndex = *(code**)(*(int*)this + 0x50);
    this->blockSize = param_2;  // +0x1F0
    contextId = getContextIndex();

    blockSize = this->blockSize; // re-read stored value
    // Check if blockSize is within the max allowed for the current context
    if (blockSize <= *(uint*)(&DAT_01223170 + contextId * 0x24)) {
        // Second virtual call – possibly to refresh context?
        shift = (**(code**)(*(int*)this + 0x50))();
        contextId = shift * 0x24;

        // Condition: blockSize equals the first value of the context entry,
        // or (blockSize != 0 and pointer list traversal matches)
        if ((blockSize == *(uint*)(&DAT_01223170 + contextId)) ||
            (blockSize != 0 &&
             (piVar1 = (int*)(&DAT_01223178 + contextId), // skip first 8 bytes -> pointer to size array
              contextId = *(uint*)(*piVar1 + blockSize * 4), // dereference pointer
              *(int*)(contextId + 8) !=
              *(int*)(*(int*)(*piVar1 + (blockSize - 1) * 4) + 8)))) {
            // Compute shift value using floating-point log2 approximation
            blockSize = this->blockSize;
            fVar4 = (float)blockSize;
            if ((int)blockSize < 0) {
                fVar4 += DAT_00e44578; // adjustment for negative (likely 2^23 or similar)
            }
            // Classic "highest bit" calculation: ((blockSize-1 & blockSize) != 0) - 127 + exponent
            shift = (((blockSize - 1) & blockSize) != 0) - 0x7f + ((uint)fVar4 >> 0x17);
            this->shiftValue = shift; // +0x1F4
            // Return lower byte set to 1, upper bytes are (shift>>8)
            return CONCAT31((int3)(shift >> 8), 1);
        }
    }
    // Fallback: return contextId with lower byte cleared
    return contextId & 0xffffff00;
}