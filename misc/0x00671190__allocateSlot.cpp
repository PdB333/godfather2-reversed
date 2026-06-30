// FUNC_NAME: allocateSlot
// Function at 0x00671190: Allocates a slot from a fixed pool of 2 slots. Returns the associated data (e.g., handle) if a free slot is found, else 0.
// Global arrays:
// sSlotUsedFlags[2] (DAT_012066ac) - byte flags indicating slot usage (0=free, 1=used)
// sSlotData[2] (DAT_012066a4) - 32-bit data values (e.g., handles, pointers) for each slot

uint32_t allocateSlot(void)
{
    uint32_t slotIndex;
    
    slotIndex = 0;
    do {
        if (sSlotUsedFlags[slotIndex] == '\0') {
            sSlotUsedFlags[slotIndex] = 1;
            return sSlotData[slotIndex];
        }
        slotIndex = slotIndex + 1;
    } while (slotIndex < 2);
    
    return 0; // No free slot available
}