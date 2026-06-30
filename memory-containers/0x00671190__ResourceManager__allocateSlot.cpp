// FUNC_NAME: ResourceManager::allocateSlot
// Allocates a slot from a fixed-size pool (2 slots) and returns an associated resource handle.
// DAT_012066ac is a boolean array tracking slot usage (size 2).
// DAT_012066a4 is a resource handle array (size 2) corresponding to each slot.
// Returns the handle of the allocated slot, or 0 if no slots are free.
undefined4 ResourceManager::allocateSlot(void)
{
    uint slotIndex;
    
    slotIndex = 0;
    do {
        if (slotUsage[slotIndex] == '\0') {  // Check if slot is free (0 = free, 1 = used)
            slotUsage[slotIndex] = 1;         // Mark slot as used
            return slotHandles[slotIndex];     // Return the handle associated with this slot
        }
        slotIndex = slotIndex + 1;
    } while (slotIndex < 2);  // Only 2 slots available
    return 0;  // No free slots
}