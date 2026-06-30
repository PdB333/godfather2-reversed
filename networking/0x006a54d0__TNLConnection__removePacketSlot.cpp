// FUNC_NAME: TNLConnection::removePacketSlot
void __thiscall TNLConnection::removePacketSlot(int thisPtr, int slotId)
{
    int slotIndex;
    int *slotPtr;
    int local_c;
    int local_8;
    char local_4;

    slotIndex = 0;
    slotPtr = (int *)(thisPtr + 0x48); // Pointer to second slot's ID field? Actually used for grouped checks
    do {
        // Check four consecutive slots' ID fields (offsets: -0x28, 0, +0x28, +0x50 from slotPtr)
        if (*(int *)(thisPtr + 0x20 + slotIndex * 0x28) == slotId) { // slotIndex * 0x28 + 0x20
            goto foundSlot;
        }
        if (*slotPtr == slotId) {
            slotIndex += 1;
            goto foundSlot;
        }
        if (slotPtr[10] == slotId) {
            slotIndex += 2;
            goto foundSlot;
        }
        if (slotPtr[0x14] == slotId) {
            slotIndex += 3;
            goto foundSlot;
        }
        slotIndex += 4;
        slotPtr += 0x28; // Move to next group of 4 slots (overlapping by one slot)
    } while (slotIndex < 0x20); // 32 slots total

    // If not found in the main array, check the "current" slot at +0x534
    if (*(int *)(thisPtr + 0x534) == slotId) {
        if (*(int **)(thisPtr + 0x530) != (int *)0x0) {
            local_c = **(int **)(thisPtr + 0x530);
            local_8 = 0;
            local_4 = 0;
            FUN_00408a00(&local_c, 0); // Likely memset or bzero
        }
        *(int *)(thisPtr + 0x530) = 0;
        *(int *)(thisPtr + 0x52c) = 0;
        *(int *)(thisPtr + 0x534) = 0;
    }
    return;

foundSlot:
    if (slotIndex < 0x20) {
        int slotBase = thisPtr + slotIndex * 0x28; // Slot base address (stride 0x28)
        if (*(int *)(slotBase + 0x24) != 0) {
            FUN_004daf90((undefined4 *)(slotBase + 0x24)); // Release/destructor
            *(int *)(slotBase + 0x24) = 0;
        }
        *(int *)(slotBase + 0x20) = 0; // Clear ID field
        *(int *)(slotBase + 0x40) = 0; // Clear some other field
        *(int *)(slotBase + 0x44) = 0; // Clear another field
        *(int *)(thisPtr + 0x520) = *(int *)(thisPtr + 0x520) - 1; // Decrement active slot count
    }
    return;
}