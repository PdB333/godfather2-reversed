// FUNC_NAME: HandleTable::getSlotData
int __thiscall HandleTable::getSlotData(int thisPtr, int slotIndex)
{
    int diff;
    
    // Get the table info structure (offset +0x04)
    TableInfo* tableInfo = *(TableInfo**)(thisPtr + 4);
    
    // Compute slot index difference relative to the known count (offset +0x04 of TableInfo)
    diff = slotIndex - tableInfo->m_nCount;
    
    if (diff < 0)
    {
        // Slot index is within the primary table range
        // Primary table base pointer is at TableInfo+0, stride 0x70, member offset 0x48
        return tableInfo->m_pPrimaryBase[0] + 0x48 + slotIndex * 0x70;
    }
    
    // Slot index is beyond primary count – use overflow handling
    if (*(int*)(thisPtr + 0x1c) != 0)
    {
        // Overflow info exists: use triple-indirect pointer chain
        // thisPtr+0x1c -> overflow structure -> +0x10 -> secondary table info -> +0x30 -> base pointer -> dereference for actual data
        OverflowInfo* overflow = *(OverflowInfo**)(thisPtr + 0x1c);
        SecondaryTableInfo* secondaryTable = *(SecondaryTableInfo**)(overflow->field_0x10);
        int* overflowBase = *(int**)secondaryTable[0x30];
        return overflowBase + 0x48 + diff * 0x70;
    }
    
    // No overflow info – fallback to a global base pointer (likely a shared resource pool)
    return *g_pGlobalBase + 0x48 + diff * 0x70;
}