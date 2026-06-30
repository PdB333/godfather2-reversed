// FUNC_NAME: InputDeviceManager::updateAxisSlots

void __thiscall InputDeviceManager::updateAxisSlots(int thisPtr, char directionFlag)
{
    int *slotBase = (int *)(thisPtr + 0x24);
    int slotIndex = 1;
    int loopCount = 0;

    do {
        // Process 4 consecutive slots per iteration
        // Slot group offset: each slot is 12 ints (48 bytes), groups separated by 0x3c ints (240 bytes)
        // Indices processed: slotIndex, slotIndex+1, slotIndex+2, slotIndex+3
        // Skipped indices: 0, 5, 10, 15

        // --- Slot 1 (index = slotIndex) ---
        if (((unsigned int)(slotIndex - 1) < 0x14) &&
            ((slotBase[4] != 0 || (*(byte *)(thisPtr + 0x3d4) & 1) == 0)) &&
            (slotBase[4] != 3))
        {
            int stepVal = slotBase[1] * 3;
            int newVal;
            if (directionFlag == '\0') {
                // Increase: add step to current, clamp at max
                newVal = stepVal + slotBase[-1];
                if (slotBase[0] <= newVal) {
                    newVal = slotBase[0];
                }
            }
            else {
                // Decrease: subtract step from current, only if no underflow
                if (!__sb_borrow(slotBase[-1], stepVal)) {
                    newVal = stepVal;
                }
                else {
                    newVal = slotBase[-1];
                }
            }
            slotBase[-1] = newVal;
        }

        // --- Slot 2 (index = slotIndex+1) ---
        if (((slotIndex >= 0) && (slotIndex + 1 < 0x14)) &&
            ((slotBase[0x10] != 0 || (*(byte *)(thisPtr + 0x3d4) & 1) == 0)) &&
            (slotBase[0x10] != 3))
        {
            int stepVal = slotBase[0xd] * 3;
            int newVal;
            if (directionFlag == '\0') {
                newVal = stepVal + slotBase[0xb];
                if (slotBase[0xc] <= newVal) {
                    newVal = slotBase[0xc];
                }
            }
            else {
                if (!__sb_borrow(slotBase[0xb], stepVal)) {
                    newVal = stepVal;
                }
                else {
                    newVal = slotBase[0xb];
                }
            }
            slotBase[0xb] = newVal;
        }

        // --- Slot 3 (index = slotIndex+2) ---
        if (((slotIndex >= 0) && (slotIndex + 2 < 0x14)) &&
            ((slotBase[0x1c] != 0 || (*(byte *)(thisPtr + 0x3d4) & 1) == 0)) &&
            (slotBase[0x1c] != 3))
        {
            int stepVal = slotBase[0x19] * 3;
            int newVal;
            if (directionFlag == '\0') {
                newVal = stepVal + slotBase[0x17];
                if (slotBase[0x18] <= newVal) {
                    newVal = slotBase[0x18];
                }
            }
            else {
                if (!__sb_borrow(slotBase[0x17], stepVal)) {
                    newVal = stepVal;
                }
                else {
                    newVal = slotBase[0x17];
                }
            }
            slotBase[0x17] = newVal;
        }

        // --- Slot 4 (index = slotIndex+3) ---
        if (((slotIndex >= 0) && (slotIndex + 3 < 0x14)) &&
            ((slotBase[0x28] != 0 || (*(byte *)(thisPtr + 0x3d4) & 1) == 0)) &&
            (slotBase[0x28] != 3))
        {
            int stepVal = slotBase[0x25] * 3;
            int newVal;
            if (directionFlag == '\0') {
                newVal = stepVal + slotBase[0x23];
                if (slotBase[0x24] <= newVal) {
                    newVal = slotBase[0x24];
                }
            }
            else {
                if (!__sb_borrow(slotBase[0x23], stepVal)) {
                    newVal = stepVal;
                }
                else {
                    newVal = slotBase[0x23];
                }
            }
            slotBase[0x23] = newVal;
        }

        // Advance to next group of 4 slots
        int nextSlotStart = slotIndex + 4;  // Last processed index + 1
        slotBase += 0x3c;                  // Move base pointer by 60 ints (240 bytes)
        slotIndex = slotIndex + 5;         // Jump to next starting index
        if (nextSlotStart > 0x13) {
            break;
        }
    } while (true);
}