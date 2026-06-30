// FUNC_NAME: CElementArray::GetElementData
int __thiscall CElementArray::GetElementData(int index)
{
    int* pEntry;

    // If index is less than 1, use the default entry from a static helper
    if (index < 1) {
        pEntry = FUN_00625430(); // GetDefaultEntry()
    } else {
        // Compute pointer to entry (each entry is 8 bytes)
        // m_pDataArray is at +0x0C, m_nCapacity at +0x08
        pEntry = (int*)(*(int*)(this + 0x0C) - 8 + index * 8);
        // Check bounds: if pEntry >= end of allocated array, return 0
        if (pEntry >= (int*)(*(int*)(this + 0x08))) {
            return 0;
        }
    }

    // If we got a valid entry, interpret its type
    if (pEntry != nullptr) {
        if (*pEntry == 2) {
            // Type 2: return stored value directly
            return pEntry[1];
        }
        if (*pEntry == 7) {
            // Type 7: return stored value + 0x10
            return pEntry[1] + 0x10;
        }
    }
    return 0;
}