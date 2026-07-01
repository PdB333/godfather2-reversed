// FUNC_NAME: SlotManager::clearSlots
void __thiscall SlotManager::clearSlots(int* thisObj)
{
    // Iterate over 4 slots stored at +0xA4C
    int* slotPtrArray = (int*)(thisObj + 0xA4C);
    int slotIndex = 4;
    do {
        int* pSlot = (int*)*slotPtrArray;
        if (pSlot != 0) {
            // Notify of release (argument 0 means all?)
            FUN_00790110(0);
            // Clear bit 20 (0x00100000) in slot's flags at +0x5C
            pSlot[0x5C / 4] &= 0xFFEFFFFF;
            // Check if slot is still active
            char isActive = FUN_00791230();
            if (isActive != '\0') {
                // Perform full release
                FUN_00792d80(pSlot);
            }
            // Mark slot as empty
            *slotPtrArray = 0;
        }
        slotPtrArray++;
        slotIndex--;
    } while (slotIndex != 0);
}