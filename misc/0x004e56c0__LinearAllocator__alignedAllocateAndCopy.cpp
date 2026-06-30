// FUNC_NAME: LinearAllocator::alignedAllocateAndCopy
void __thiscall LinearAllocator::alignedAllocateAndCopy(int* thisPtr, int typePtr, const long long* data128)
{
    // this->m_pPool is at offset 0, points to a pool descriptor
    int* pool = (int*)*thisPtr;
    // Pool descriptor has a bump allocation pointer at offset 0x14
    int** currentAlloc = (int**)(pool + 0x14);

    // Allocate and write base vtable pointer (global table)
    *(void**)(*currentAlloc) = (void*)&PTR_LAB_01124acc;
    *currentAlloc += 1; // advance by 4 bytes

    // Allocate and write derived vtable / type pointer
    *(int*)(*currentAlloc) = typePtr;
    *currentAlloc += 1; // advance by 4 bytes

    // Align to 16-byte boundary for the 128-bit data
    char* alignedData = (char*)(((uint)*currentAlloc + 0x13) & 0xfffffff0);
    *currentAlloc = (int*)alignedData;

    // Copy the 128-bit data (16 bytes) into the aligned slot
    *(long long*)alignedData = data128[0];
    *(long long*)(alignedData + 8) = data128[1];
    // Advance past the data block
    *currentAlloc += 4; // 16 bytes = 4 ints
}