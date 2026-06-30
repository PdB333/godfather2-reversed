// FUNC_NAME: BufferSet::setCapacity
// Address: 0x00677de0
// Reconstructed: Sets capacity for two short arrays (Data1 and Data2). Reallocates if new capacity > current.
// Offsets (this-relative):
// +0x00: m_pAllocator (int*) - pointer to custom allocator
// +0x04: m_nAllocRefCount (int) - reference count for allocator
// +0x02: m_nCapacity (short) - current max elements per array
// +0x36: m_nCount (short) - current number of elements stored
// +0x3C: m_pData1 (short*) - pointer to first array
// +0x40: m_pData2 (short*) - pointer to second array
// +0x14: m_staticBuffer (short[?]) - small static buffer used when capacity <= threshold

void __thiscall BufferSet::setCapacity(short newCapacity)
{
    short* thisPtr = reinterpret_cast<short*>(this);

    if (thisPtr[1] >= newCapacity) // m_nCapacity at offset 2 (short) -- (thisPtr[1] is short at offset 2)
        return;

    thisPtr[1] = newCapacity; // update capacity

    // Allocate memory for two arrays: total = newCapacity * 2 shorts = newCapacity * 4 bytes
    // FUN_00673070 returns a pointer to the allocated block (size = newCapacity * 4)
    int* newBlock = (int*)FUN_00673070(); // custom allocation (returns void*, no parameters?)
    short* newData1 = (short*)newBlock;
    short* newData2 = (short*)((int)newBlock + newCapacity * 2);

    short count = *(short*)((int)this + 0x36); // m_nCount

    if (count > 0)
    {
        short* oldData1 = *(short**)((int)this + 0x3C); // m_pData1
        short* oldData2 = *(short**)((int)this + 0x40); // m_pData2
        short i = 0;
        do
        {
            newData1[i] = oldData1[i];
            newData2[i] = oldData2[i];
            i++;
        } while (i < count);
    }

    // Free old Data1 if it was dynamically allocated (not the static buffer at this+0x14)
    short* oldData1 = *(short**)((int)this + 0x3C);
    if (oldData1 != (short*)((int)this + 0x14) && oldData1 != (short*)0)
    {
        int* allocator = *(int**)this; // m_pAllocator
        // Custom deallocation using allocator metadata
        // Clear a reference slot at allocator[0xc] + (oldData1[-2])*4
        *(int*)(*(int*)((int)allocator + 0xc) + (int)((int*)oldData1)[-2] * 4) = 0;
        // Decrement reference count at allocator + 4
        *(int*)((int)allocator + 4) = *(int*)((int)allocator + 4) - 1;
        // Call the actual free function
        ((void (*)(int*))DAT_01206694)((int*)oldData1 - 4);
    }

    // Update the pointers
    *(int**)((int)this + 0x3C) = (int*)newData1;
    *(int**)((int)this + 0x40) = (int*)newData2;
}