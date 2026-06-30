// FUNC_NAME: SlotEntry::checkAndHandleSlot
void __fastcall SlotEntry::checkAndHandleSlot(SlotEntry* thisPtr)
{
    // Short index into the manager's slot array
    int16_t slotIndex;
    // Pointer to the manager that owns this slot
    SlotManager* manager;
    
    // Check if bit 12 of flags is clear (e.g., "not destroyed" or "active")
    // +0x10: uint32_t m_flags (bit12 = 0 means valid)
    if ((*(uint32_t*)(thisPtr + 0x10) >> 12 & 1) == 0 &&
        // +0x70: SlotManager* m_pManager
        (manager = *(SlotManager**)(thisPtr + 0x70), manager != nullptr) &&
        // +0x18 (manager): int32_t m_slotCount
        *(int32_t*)(manager + 0x18) > 0 &&
        // +0x1c (manager): Slot* m_pSlots (array of 0x18-byte entries)
        *(void**)(manager + 0x1c) != nullptr &&
        // +0x76: int16_t m_slotIndex
        (slotIndex = *(int16_t*)(thisPtr + 0x76), slotIndex >= 0) &&
        // Validate index within bounds
        (int32_t)slotIndex < *(int32_t*)(manager + 0x18) &&
        // Check that the specific slot pointer is non-null (array + index * 0x18)
        *(void**)(*(int32_t*)(manager + 0x1c) + slotIndex * 0x18) != 0)
    {
        // All conditions met – invoke the global handler
        FUN_00577a50();
    }
    // Otherwise, do nothing
    return;
}