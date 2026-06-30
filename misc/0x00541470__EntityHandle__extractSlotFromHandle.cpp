// FUNC_NAME: EntityHandle::extractSlotFromHandle
uint __thiscall EntityHandle::extractSlotFromHandle(uint handle)
{
    uint flags = handle & 0xC0000000;
    if (flags == 0)
    {
        // No table lookup: slot directly from low 5 bits
        return handle & 0x1F;
    }
    if (flags == 0x40000000)
    {
        // Use first table at offset 0 from this (array of uint32)
        // handle is used as index into the array (handle*4)
        uint* table1 = (uint*)this; // +0x0
        return table1[handle] & 0x1F;
    }
    if (flags == 0xC0000000)
    {
        // Use second table at offset 0x4C from this (array of uint32)
        uint* table2 = (uint*)((char*)this + 0x4C); // +0x4C
        return table2[handle] & 0x1F;
    }
    // flags == 0x80000000 or invalid: return 0
    return 0;
}