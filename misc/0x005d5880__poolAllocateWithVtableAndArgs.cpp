// FUNC_NAME: poolAllocateWithVtableAndArgs
void __fastcall poolAllocateWithVtableAndArgs(uint param_2, uint param_3, uint param_4) // param_1 (ecx) unused
{
    // Global memory manager singleton at 0x01206880. Offset +0x14 holds a pointer to the next free block.
    uint* pNextFree = *reinterpret_cast<uint**>(0x01206880 + 0x14);

    // Write fixed vtable pointer (address 0x01126c58) into the block
    *reinterpret_cast<uint*>(*pNextFree) = 0x01126c58; // PTR_LAB_01126c58

    // Advance allocation pointer by 4 bytes (size of vtable pointer)
    *pNextFree += 4;

    // Align next address to 4-byte boundary (round up to next multiple of 4)
    uint alignedAddr = (*pNextFree + 3) & 0xFFFFFFFC;
    *pNextFree = alignedAddr;

    // Store the three parameters sequentially
    *reinterpret_cast<uint*>(*pNextFree) = param_2;
    *pNextFree += 4;
    *reinterpret_cast<uint*>(*pNextFree) = param_3;
    *pNextFree += 4;
    *reinterpret_cast<uint*>(*pNextFree) = param_4;
    *pNextFree += 4;
    // Total allocated: 16 bytes (4 vtable + aligned 12 for three args)
}