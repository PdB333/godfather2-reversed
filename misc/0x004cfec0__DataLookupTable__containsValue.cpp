// FUNC_NAME: DataLookupTable::containsValue
// Address: 0x004cfec0
// This function checks if a given 16-bit value exists in a specific sub-table identified by index.
// The object has a 2-level lookup: first level indexed by high byte of index, second level by low byte.
// Each sub-table has a count of entries and an offset into a global data array of 3-byte records.
// The first two bytes of each record are compared to the value's low and high bytes.

void __thiscall DataLookupTable::containsValue(ushort value, ushort index)
{
    // Offsets relative to this:
    // +0x448: short m_totalCount (must be non-zero)
    // +0x44: array of pointers to sub-tables (indexed by high byte of index)
    // +0x450: pointer to base of data array (byte*)
    // Sub-table entry structure (pointed to by entries in the array):
    //   +0x14: ushort m_entryCount
    //   +0x16: ushort m_dataOffset (multiplied by 3 to get offset into base data)

    if (*(short*)((char*)this + 0x448) != 0 && value != 0)
    {
        int* subTableArray = *(int**)((char*)this + 0x44);
        int subTableIndex = (index >> 8) & 0xFF;
        int* subTable = subTableArray[subTableIndex];
        if (subTable != 0)
        {
            int entryIndex = index & 0xFF;
            int* entry = (int*)((char*)subTable + entryIndex * 4);
            if (entry != 0)
            {
                ushort entryCount = *(ushort*)((char*)entry + 0x14);
                if (entryCount != 0)
                {
                    ushort dataOffset = *(ushort*)((char*)entry + 0x16);
                    byte* dataPtr = (byte*)((uint)dataOffset * 3 + *(int*)((char*)this + 0x450));
                    for (ushort i = 0; i < entryCount; i++)
                    {
                        if (dataPtr[0] == (value & 0xFF) && dataPtr[1] == ((value >> 8) & 0xFF))
                        {
                            // Found – function does nothing further
                            return;
                        }
                        dataPtr += 3;
                    }
                }
            }
        }
    }
    // Not found or any condition failed – just return
}