// FUNC_NAME: RemoveSlotEntry
void __fastcall RemoveSlotEntry(int unusedThis, uint slotIndex)
{
    // slotIndex: index of the slot to remove from the global array g_slotArray.
    // g_slotCount holds the number of valid entries.
    // Each slot is two ints (8 bytes). The function shifts later entries forward
    // and zeros the last entry.

    if (slotIndex < g_slotCount) {
        if (slotIndex < g_slotCount - 1) {
            // Shift all subsequent slots down by one
            int* currentSlot = &g_slotArray[slotIndex * 2]; // +0x20 offset relative to base? Actually g_slotArray is at DAT_01206b20
            do {
                currentSlot[0] = currentSlot[2];
                currentSlot[1] = currentSlot[3];
                slotIndex++;
                currentSlot += 2;
            } while (slotIndex < g_slotCount - 1);
        }
        uint newCount = g_slotCount - 1;
        g_slotCount = newCount;
        if (&g_slotArray[newCount * 2] != nullptr) {
            g_slotArray[newCount * 2] = 0;       // zero first int of last slot
            g_slotArray[newCount * 2 + 1] = 0;   // zero second int of last slot
        }
    }
    // unusedThis is ignored – the function operates on global data.
}