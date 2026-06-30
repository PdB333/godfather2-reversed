// FUNC_NAME: UpgradeManager::getEffectiveValue
// Address: 0x005f5230
// This function retrieves an upgrade property value by ID, optionally scaling it based on a ratio.
// It searches an internal ID-to-index mapping (10 slots, 0x5c bytes each) starting at this+0x82b0.
// Then accesses a data block (10 entries, 0x170 bytes each) at this+0x8210.
// The property at offset +0x100 is returned via outValue, and may be scaled if state (offset +0xa4) != 1
// and the ratio of count2 (offset +0x8c) / count1 (offset +0x88) is negative.

int __thiscall UpgradeManager::getEffectiveValue(int thisPtr, int upgradeId, int* outValue)
{
    int index;
    int* idMapPtr;
    int count1;
    int count2;
    int state;
    float ratio;
    float valueFloat;
    int scaledValue;

    // Search the ID mapping array (10 entries, each 0x5c bytes, starting at this+0x82b0)
    idMapPtr = (int*)(thisPtr + 0x82b0);
    index = 0;
    while (true) {
        if (*idMapPtr < 0 || *idMapPtr != upgradeId) {
            index++;
            idMapPtr = idMapPtr + 0x5c / 4; // Advance by 0x5c bytes (23 ints)
            if (index > 9) {
                return 0; // Not found
            }
        } else {
            break; // Found matching non-negative ID
        }
    }

    if (index < 0) {
        return 0; // Safety check (should not happen)
    }

    // Compute pointer to the data slot for this index (slot size 0x170 bytes, base at this+0x8210)
    int slotPtr = thisPtr + 0x8210 + index * 0x170;

    // Lock global mutex (DAT_00e2aea0)
    FUN_00ab4db0(&DAT_00e2aea0);

    // Read the property value (offset +0x100)
    *outValue = *(int*)(slotPtr + 0x100);

    // Read counts (offsets +0x88 and +0x8c)
    count1 = *(int*)(slotPtr + 0x88);
    count2 = *(int*)(slotPtr + 0x8c);

    // Read state (offset +0xa4)
    state = *(int*)(slotPtr + 0xa4);

    // Unlock global mutex
    FUN_00ab4e70();

    // If state is not 1, we may adjust the output value
    if (state != 1) {
        if (count1 > 0) {
            // Compute ratio using floating point with a global scale factor (DAT_00e2af48) which cancels
            ratio = ((float)count2 * DAT_00e2af48) / ((float)count1 * DAT_00e2af48);
            if (ratio < 0.0f) {
                valueFloat = (float)*outValue;
                // Handle potential negative integer by adding a large constant (DAT_00e44578) to make it positive for rounding
                if (*outValue < 0) {
                    valueFloat = valueFloat + DAT_00e44578;
                }
                scaledValue = (int)(long long)round(valueFloat * ratio);
                *outValue = scaledValue;
            }
        }
        return 1;
    } else {
        // State == 1 indicates an invalid or empty slot; set output to -1 and fail
        *outValue = -1;
        return 0;
    }
}