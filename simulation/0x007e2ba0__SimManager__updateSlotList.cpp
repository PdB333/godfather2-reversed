// FUNC_NAME: SimManager::updateSlotList
void __thiscall SimManager::updateSlotList()
{
    int slotType;
    int slotIndex;

    slotIndex = *(int *)(this + 0xd8) - 1; // count of slots stored at +0xd8
    if (slotIndex >= 0) {
        do {
            slotType = *(int *)(*(int *)(this + 0xd4) + slotIndex * 8); // array of 8-byte entries at +0xd4
            if ((slotType == 0) || (slotType == 0x48)) {
                // Slot is empty or of a specific type (0x48 = 72, possibly "inactive" or "initialized")
                processSlot(slotIndex);
            }
            else {
                if (shouldSkipSlot() == 0) {
                    // Slot is not empty and we should process it
                    processSlot(slotIndex);
                    *(char *)(this + 0x81) = 1; // set dirty flag at +0x81
                }
            }
            slotIndex = slotIndex - 1;
        } while (slotIndex >= 0);
    }
    return;
}