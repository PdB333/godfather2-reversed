// FUNC_NAME: ClearSlotArray
void __fastcall ClearSlotArray(int thisPtr, int slotManager) {
    // slotManager points to an object containing a slot array at offset +0 and a slot count at offset +0x300
    int slotCount = *(int*)(slotManager + 0x300);
    if (slotCount != 0 && slotCount != 1) {
        // Iterate from slot index 1 to slotCount - 1, leaving slot 0 untouched
        for (int slotIndex = 1; slotIndex < slotCount; slotIndex++) {
            // Each slot is 24 bytes (6 DWORDs)
            int slotBase = slotIndex * 24; // relative offset from slotManager
            // Clear the entire slot
            *(int*)(slotManager + slotBase + 0)  = 0; // field at offset +0
            *(int*)(slotManager + slotBase + 4)  = 0; // field at offset +4
            *(int*)(slotManager + slotBase + 8)  = 0; // field at offset +8
            *(int*)(slotManager + slotBase + 12) = 0; // field at offset +12
            *(int*)(slotManager + slotBase + 16) = 0; // field at offset +16
            *(int*)(slotManager + slotBase + 20) = 0; // field at offset +20
        }
    }
    *(int*)(slotManager + 0x300) = 0; // Reset slot count to 0
}