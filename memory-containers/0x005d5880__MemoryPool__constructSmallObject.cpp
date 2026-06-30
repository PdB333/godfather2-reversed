// FUNC_NAME: MemoryPool::constructSmallObject
// Function at 0x005d5880: Constructs a small object (vtable + 3 DWORDs) from a memory pool.
// Uses a global pointer (g_pMemoryPool) with a free list at offset 0x14.
// The object layout: [vtable_ptr (4 bytes)] [data0 (4)] [data1 (4)] [data2 (4)]
// Parameters: param1 (ecx) unused, param2 (edx) first data value, param3 (stack) second, param4 (stack) third
// Cached vtable pointer from a static location (PTR_LAB_01126c58).

void __fastcall MemoryPool::constructSmallObject(uint32_t param1, uint32_t param2, uint32_t param3, uint32_t param4)
{
    // Global memory pool structure, offset 0x14 holds pointer to next free block
    uint32_t** poolPtr = reinterpret_cast<uint32_t**>(g_pMemoryPool + 0x14);
    uint32_t* currentBlock = *poolPtr;

    // Set the first field (vtable pointer) to a static vtable
    *currentBlock = reinterpret_cast<uint32_t>(&PTR_LAB_01126c58);

    // Advance past vtable pointer to data area
    uint32_t* dataPtr = currentBlock + 1;
    // Align to 4-byte boundary (already aligned, but for safety)
    dataPtr = reinterpret_cast<uint32_t*>((reinterpret_cast<uint32_t>(dataPtr) + 3) & 0xFFFFFFFC);

    // Store three data values sequentially
    *dataPtr = param2;
    ++dataPtr;
    *dataPtr = param3;
    ++dataPtr;
    *dataPtr = param4;

    // Update pool free pointer to the next available slot (after the object)
    *poolPtr = dataPtr + 1;
}