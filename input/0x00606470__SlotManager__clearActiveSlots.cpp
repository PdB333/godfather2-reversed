// FUNC_NAME: SlotManager::clearActiveSlots
// Iterates over a global array of 20 active slots (e.g., network packet slots, NPC slots, or input device slots).
// For each non‑null slot, it calls the release function (FUN_00618d40) and marks the slot as free.
void __cdecl SlotManager::clearActiveSlots(void)
{
    uint32_t slotIndex;
    
    slotIndex = 0;
    do {
        // Check if slot is occupied (non‑zero)
        if (g_activeSlots[slotIndex] != 0) {
            // Destroy/release the resource associated with this slot
            g_destroySlot();
            // Mark slot as free
            g_activeSlots[slotIndex] = 0;
        }
        slotIndex = slotIndex + 1;
    } while (slotIndex < 20); // 0x14 slots
}