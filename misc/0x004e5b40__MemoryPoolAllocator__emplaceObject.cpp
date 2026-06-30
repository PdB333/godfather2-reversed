// FUNC_NAME: MemoryPoolAllocator::emplaceObject
void __thiscall MemoryPoolAllocator::emplaceObject(int *this, uint headerSize, void *source)
{
    // this points to a structure where the first DWORD is a pointer to a descriptor block (allocator context)
    int *context = (int *)*this; // +0x00: pointer to allocator context
    // context[0x14] is a "current allocation pointer" that tracks where to write next
    int *currentPtr = (int *)(context + 0x14); // offset 0x14 = current write pointer (as an int pointer)

    // Step 1: Write a vtable pointer from a global constant (PTR_LAB_01124b30)
    // This is likely the vtable for the object being placed.
    **(int **)(context + 0x14) = (int)&PTR_LAB_01124b30; // write vtable address at current location
    // Advance the current pointer by 4 bytes (size of a pointer)
    *currentPtr += 4;

    // Step 2: Write the headerSize (param_2) after the vtable (maybe a type tag or size)
    context = (int *)*this; // re-read context pointer (necessary because previous call might have invalidated?)
    **(int **)(context + 0x14) = headerSize;
    // Get the address to copy source data to, aligned to 16 bytes
    // Alignment: (current pointer + 0x13) & ~0xF (arithmetic shift? but uses >>
    // Actually the code does: (*(int *)(iVar2+0x14) + 0x13U) & 0xfffffff0
    int alignedAddr = (*(int *)(context + 0x14) + 0x13) & 0xfffffff0;
    *(int **)(context + 0x14) = (int *)alignedAddr; // update current pointer to aligned address

    // Copy 0x30 bytes from source into the aligned location
    _memcpy((void *)alignedAddr, source, 0x30);

    // Advance current pointer by 0x30 past the copied data
    *(int *)(context + 0x14) += 0x30;
}