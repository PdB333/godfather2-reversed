// FUNC_NAME: SlotManager::processSlotUpdate
uint __thiscall SlotManager::processSlotUpdate(int this, int param2, int targetId) // targetId is likely passed in EAX before call
{
    float fVar1;
    int index;
    uint matchedSlotIndex;
    int* idPtr;
    int slotBase;

    matchedSlotIndex = randomOrIdGenerator(); // FUN_005dbc10, possibly generates unique ID or returns current frame number?
    if ((*(char*)(this + 0x1744) != '\0') && (targetId != 0)) {
        matchedSlotIndex = 0;
        idPtr = (int*)(this + 0x490); // array of 5 slot IDs, each 0x4A4 bytes apart
        do {
            if (targetId == *idPtr) {
                // Found the slot matching targetId
                // Rebase 'this' to point to the slot's internal data structure (offset +4 from slot base?)
                slotBase = this + 4 + matchedSlotIndex * 0x4a4;
                // Perform some update
                slotUpdate(); // FUN_005e9440, likely handles actual update logic
                fVar1 = *(float*)(param2 + 4); // input float at offset 4
                // Build flags based on comparison with global threshold
                // Bits: 0x02 = fVar1 < DAT, 0x04 = NaN condition, 0x40 = equality
                uint flags = (fVar1 == DAT_00e2b05c) << 6 | (isNaN(fVar1) || isNaN(DAT_00e2b05c)) << 2 | 2U | (fVar1 < DAT_00e2b05c);
                if (fVar1 == DAT_00e2b05c) {
                    // Reset two fields at slotBase + 0x1fc and slotBase + 0x200
                    resetSomething(); // FUN_005e86e0 (called twice)
                    resetSomething();
                    *(int*)(slotBase + 0x1fc) = 0;
                    *(int*)(slotBase + 0x200) = 0;
                }
                return (flags << 8) | 1; // CONCAT31(flags, 1) - low byte set to 1 (success)
            }
            matchedSlotIndex++;
            idPtr = (int*)((char*)idPtr + 0x129 * 4); // each slot is 0x4A4 bytes, pointer adjustment
        } while ((int)matchedSlotIndex < 5);
    }
    return matchedSlotIndex & 0xffffff00; // return 0 if matchedSlotIndex < 256 (likely no match)
}