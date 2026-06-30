//FUNC_NAME: SlotManager::clearActiveSlots
void SlotManager::clearActiveSlots()
{
    uint id;
    int basePtr;
    char isValid;
    int dataEntry;
    uint* slotPtr;

    basePtr = this;
    slotPtr = (uint*)(this + 0x24); // +0x24: array of slot structures (0x30 bytes each, 0x200 entries)
    int slotCount = 0x200; // 512 slots

    do {
        // slotPtr[0] = ID, slotPtr[1] = active flag
        if (slotPtr[1] != 0) {
            id = slotPtr[0];
            isValid = isIdValid(id); // FUN_005e63e0: checks if ID is still valid
            if (isValid != '\0') {
                dataEntry = 0;
                if (id < 0x200) {
                    // data array starts at this + 0x10, each entry 0x30 bytes
                    dataEntry = id * 0x30 + 0x10 + basePtr;
                }
                // Clear four fields in the data entry
                *(int*)(dataEntry + 0x20) = 0; // +0x20
                *(int*)(dataEntry + 0x18) = 0; // +0x18
                *(int*)(dataEntry + 0x2c) = 0; // +0x2c
                *(int*)(dataEntry + 0x10) = 0; // +0x10
            }
        }
        int globalVal = DAT_01223504; // global singleton or flag
        slotPtr = slotPtr + 0xc; // advance by 0x30 bytes (0xc * 4)
        slotCount = slotCount - 1;
    } while (slotCount != 0);

    // Clear a flag in the global structure
    *(char*)(DAT_01223504 + 0x1d) = 0;
    // Clear the 0x18 field of the last processed data entry (likely intended for the global)
    *(int*)(globalVal + 0x18) = 0;
    return;
}