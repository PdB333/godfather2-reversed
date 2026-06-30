// FUNC_NAME: SerializedCallBuffer::readAndInvoke
// Address: 0x004b8a40
// Role: Reads a serialized function call from a nested buffer and executes it.

#include <cstdint>

// Alignment helper (ensures addr is aligned to alignment, alignment must be power of two)
static inline uint32_t alignUp(uint32_t addr, uint32_t alignment) {
    return (addr + alignment - 1) & ~(alignment - 1);
}

class SerializedCallBuffer {
public:
    // The current read pointer is stored at offset 0x18
    uint8_t* currentPtr;
};

// The function pointer is stored as the first DWORD of the passed callable structure.
typedef void (*PackedCallFunc)(uint32_t, uint32_t,
                               uint64_t, uint32_t,
                               uint64_t, uint32_t,
                               uint64_t, uint32_t,
                               uint16_t);

void SerializedCallBuffer::readAndInvoke(void* callable) {
    // Retrieve the function pointer from the callable structure
    PackedCallFunc func = *(PackedCallFunc*)callable;

    // Start reading from the current internal pointer
    uint8_t* ptr = this->currentPtr;

    // Read the first two DWORD arguments
    uint32_t arg0 = *(uint32_t*)ptr; ptr += 4;
    uint32_t arg1 = *(uint32_t*)ptr; ptr += 4;

    // Read count0 and alignment0 for the first sub-array
    int32_t count0 = *(int32_t*)ptr; ptr += 4;
    int32_t alignSize0 = *(int32_t*)ptr; ptr += 4;

    // Align the current position to the next multiple of alignSize0
    uint32_t aligned0 = alignUp((uint32_t)ptr, alignSize0);

    // Compute base pointer for the first sub-array (count0 ints)
    uint32_t* subArray0 = (uint32_t*)(count0 * 4 + aligned0);
    this->currentPtr = (uint8_t*)subArray0; // update internal pointer

    // Read the first two ints from the sub-array: count1 and alignSize1
    int32_t count1 = *(int32_t*)subArray0;
    int32_t alignSize1 = *(int32_t*)(subArray0 + 1);

    // Align after these two ints (subArray0 + alignSize1 + some padding? The formula is unusual)
    uint32_t aligned1 = alignUp((uint32_t)subArray0, alignSize1); // simplified; original used +alignSize1+7
    // Note: The original code used: uVar15 = (int)piVar13 + iVar8 + 7 & ~(iVar8 - 1U);
    // That likely means: add alignSize1, then add 7 more for padding, then align to alignSize1.
    // We'll approximate with alignUp((uint32_t)subArray0 + alignSize1, 8) but unclear.
    // For correctness, we follow the original logic exactly:
    uint32_t aligned1_exact = ((uint32_t)subArray0 + alignSize1 + 7) & ~(alignSize1 - 1U);

    // Compute base pointer for the second sub-array (count1 elements of 12 bytes each)
    uint32_t* subArray1 = (uint32_t*)(count1 * 0xC + aligned1_exact);
    this->currentPtr = (uint8_t*)subArray1;

    // Read the first two ints from the second sub-array: count2 and alignSize2
    int32_t count2 = *(int32_t*)subArray1;
    int32_t alignSize2 = *(int32_t*)(subArray1 + 1);

    // Align after these two ints
    uint32_t aligned2_exact = ((uint32_t)subArray1 + alignSize2 + 7) & ~(alignSize2 - 1U);

    // Compute base pointer for the third sub-array (count2 elements of 8 bytes each)
    uint16_t* subArray2 = (uint16_t*)(count2 * 8 + aligned2_exact);
    this->currentPtr = (uint8_t*)subArray2;

    // Read the first short from the third sub-array
    uint16_t argLast = *subArray2;

    // Advance internal pointer past the last sub-array with 4-byte alignment
    this->currentPtr = (uint8_t*)(((uint32_t)subArray2 + 5) & 0xFFFFFFFC);

    // Assemble the packed 64-bit arguments (pointer + count) using conditional zero
    uint64_t packed0 = (uint64_t)count0 | ((uint64_t)(count0 ? aligned0 : 0) << 32);
    uint64_t packed1 = (uint64_t)count1 | ((uint64_t)(count1 ? aligned1_exact : 0) << 32);
    uint64_t packed2 = (uint64_t)count2 | ((uint64_t)(count2 ? aligned2_exact : 0) << 32);

    // Invoke the packed function
    func(arg0, arg1,
         packed0, alignSize0,
         packed1, alignSize1,
         packed2, alignSize2,
         argLast);
}