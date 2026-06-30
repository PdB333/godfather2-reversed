// FUNC_NAME: SlotManager::resetSlots
// Address: 0x00561950
// Role: Resets all slots in the pool: sets active flag, reinitializes global pool, then initializes each slot.

// Slot structure assumed from code: +0x00 = active flag (set to 1), size 0x30 bytes.
// SlotManager layout: +0x04 = m_count (number of slots), +0x20 = m_slots[] start.
void __thiscall SlotManager::resetSlots(void)
{
    // Set all slots' active flag to 1
    for (int i = 0; i < m_count; i++) {
        Slot* slot = &m_slots[i];
        slot->active = 1; // +0x00 within slot
    }

    // Reset global memory/pool associated with the slot count
    resetSlotMemory(m_count); // callee at 0x00aad120

    // Initialize each slot (likely sets up default state)
    for (int i = 0; i < m_count; i++) {
        initSlot(&m_slots[i]); // callee at 0x00aad110
    }
}