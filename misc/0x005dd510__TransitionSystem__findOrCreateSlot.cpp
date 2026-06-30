// FUNC_NAME: TransitionSystem::findOrCreateSlot
uint TransitionSystem::findOrCreateSlot(void) {
    uint result = 0;
    uint retVal = in_EAX & 0xffffff00;
    // Check if key is not set
    if (*(int*)(unaff_ESI + 0x1c) == 0) {
        int* slotData = (int*)(unaff_EDI + 0x18);
        // Search for a matching slot (up to 5 slots, stride 0x68)
        while (true) {
            if (slotData[-3] == -1 ||
                slotData[-2] != *(int*)(unaff_ESI + 0x20) ||
                slotData[-1] != *(int*)(unaff_ESI + 0x24) ||
                *slotData != *(int*)(unaff_ESI + 0x28) ||
                slotData[1] != *(int*)(unaff_ESI + 0x2c)) {
                result++;
                slotData += 0x1a; // 0x68 bytes stride
                if (result > 4) {
                    return retVal; // no match found, return original value
                }
            } else {
                break;
            }
        }
        int slotIndex = result * 0x68 + unaff_EDI;
        int someValue = *(int*)(slotIndex + 0x4c);
        // Set slot data
        *(undefined4*)(slotIndex + 8) = *(undefined4*)(unaff_ESI + 0x18);
        bool greaterOrEqual = DAT_00e44598 <= *(float*)(slotIndex + 8);
        // Mirror previous blend weights
        *(float*)(slotIndex + 0x28) = *(float*)(slotIndex + 0x38);
        *(float*)(slotIndex + 0x2c) = *(float*)(slotIndex + 0x3c);
        *(int*)(slotIndex + 0x40) = someValue;
        *(undefined4*)(slotIndex + 0x24) = 0;
        if (greaterOrEqual) {
            float timeScale = DAT_00e2b1a4 / *(float*)(slotIndex + 8);
            float deltaY = DAT_00e2b1a4 - *(float*)(slotIndex + 0x3c);
            float floatVal = (float)someValue;
            *(float*)(slotIndex + 0x30) = (DAT_00e2b1a4 - *(float*)(slotIndex + 0x38)) * timeScale;
            *(float*)(slotIndex + 0x34) = deltaY * timeScale;
            if (someValue < 0) {
                floatVal += DAT_00e44578;
            }
            floatVal = DAT_00e4459c - floatVal;
            *(undefined1*)(slotIndex + 0x23) = 0;
            *(undefined1*)(slotIndex + 0x22) = 1;
            *(float*)(slotIndex + 0x48) = floatVal * timeScale;
            return CONCAT31((undefined3)(slotIndex >> 8), 1);
        }
        *(undefined4*)(slotIndex + 0x30) = 0;
        *(undefined4*)(slotIndex + 0x34) = 0;
        *(undefined4*)(slotIndex + 0x48) = 0;
        *(undefined1*)(slotIndex + 0x23) = 0;
        *(undefined1*)(slotIndex + 0x22) = 1;
        retVal = CONCAT31((undefined3)(slotIndex >> 8), 1);
    }
    return retVal;
}