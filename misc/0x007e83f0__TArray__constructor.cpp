// FUNC_NAME: TArray::constructor
// Reconstructed constructor for a dynamic uint32 array (EA EARS engine).
// Allocates a contiguous block of uint32 elements with given capacity.
// Stores a flags byte at offset +0x14.

uint32* __thiscall TArray::constructor(uint32* this, uint32 capacity, uint8 flags)
{
    // Set flags byte at offset +0x14 (size: 1 byte)
    *(uint8*)(this + 5) = flags;

    // Set capacity at offset +0x04
    this[1] = capacity;

    // Initialize data pointer and other internal fields to 0
    this[0] = 0;  // m_pData (pointer to allocated elements)
    this[2] = 0;  // m_count (current element count)
    this[3] = 0;  // m_maxCount (or similar)
    this[4] = 0;  // m_growSize (or similar)

    // Allocate memory: capacity * 4 bytes, with overflow guard.
    // The original code computes: size = (uint64)capacity * 4;
    // if high 32 bits non-zero, use 0xFFFFFFFF; else low 32 bits.
    // Simplified here: assume safe heap allocation.
    void* pData = allocateMemory(capacity * sizeof(uint32));

    // Store allocated pointer
    this[0] = (uint32*)pData;

    // Zero-initialize the allocated memory
    memset(pData, 0, this[1] * sizeof(uint32));

    return this;
}