// FUNC_NAME: StreamManager::updateStreamSlot
// Address: 0x005dd3f0
// Role: Updates a stream slot based on state from a stream source object.
// The stream manager has an array of 5 slots (each 0x68 bytes) starting at +0x18.
// The stream source object (unaff_ESI) provides parameters for matching/setting.

void __thiscall updateStreamSlot(void* thisPtr, void* streamSource) {
    int* slotPtr;
    uint slotIndex;
    float floatParam;
    undefined4 unknownValue;
    float paramFloat1, paramFloat2;
    int* emptySlotPtr;

    // Check if the stream source has a pending action (field +0x1c == 0 means no action)
    if (*(int*)((char*)streamSource + 0x1c) == 0) {
        // First loop: search for a matching slot in the manager's array at +0x18
        slotPtr = (int*)((char*)thisPtr + 0x18); // First slot, each stride 0x1a * 4 = 0x68
        for (slotIndex = 0; slotIndex < 5; slotIndex++) {
            // Compare fields: slot[-3] (match ID?), slot[-2] (type?), slot[-1], slot[0], slot[1]
            // with streamSource offsets +0x20, +0x24, +0x28, +0x2c
            if ((((slotPtr[-3] != -1) &&
                  (slotPtr[-2] == *(int*)((char*)streamSource + 0x20))) &&
                 (slotPtr[-1] == *(int*)((char*)streamSource + 0x24))) &&
                ((*slotPtr == *(int*)((char*)streamSource + 0x28) &&
                  (slotPtr[1] == *(int*)((char*)streamSource + 0x2c))))) {
                // If the 'active' flag at offset +10 bytes is zero, slot is already active, return 1
                if (*(char*)((char*)slotPtr + 10) == '\0') {
                    return; // Return 1 implicitly
                }
                // Clear the active flag
                *(char*)((char*)slotPtr + 10) = 0;
                // Update other fields from streamSource
                slotPtr[-5] = *(int*)((char*)streamSource + 0x10); // offset -20
                slotPtr[-6] = *(int*)((char*)streamSource + 0xc);  // offset -24
                slotPtr[0xb] = *(int*)((char*)streamSource + 0x34); // offset +44
                return; // Return 1
            }
            slotPtr += 0x1a; // Next slot (0x1a integers = 0x68 bytes)
        }

        // No matching slot found; find an empty slot (starting at +0xc, same stride)
        slotIndex = 0;
        emptySlotPtr = (int*)((char*)thisPtr + 0xc);
        do {
            if (*emptySlotPtr == -1) break; // Empty slot found
            slotIndex++;
            emptySlotPtr += 0x1a;
        } while (slotIndex < 5);

        if (slotIndex != 5) { // Found an empty slot
            FUN_005dd0d0(0x3f800000, 96000); // Start default stream with volume 1.0, sample rate?
        }
    } else {
        // Stream source has an action (field +0x1c != 0)
        // Use default values from globals or from stream source
        unknownValue = *(undefined4*)0x00e2b1a4; // Global default
        floatParam = 96000.0f;
        if (*(int*)((char*)thisPtr + 0x214) != -1) { // Check if override is valid
            unknownValue = *(undefined4*)((char*)thisPtr + 0x240);
            floatParam = *(float*)((char*)thisPtr + 0x254);
        }
        FUN_005dd0d0(unknownValue, floatParam); // Start stream with these parameters

        // Copy stream source float properties if they are non-negative
        float streamFloat1 = *(float*)((char*)streamSource + 4);
        float streamFloat2 = *(float*)((char*)streamSource + 8);
        if (streamFloat1 >= 0.0f) {
            *(float*)((char*)thisPtr + 0x27c) = streamFloat1;
        }
        if (streamFloat2 >= 0.0f) {
            *(float*)((char*)thisPtr + 0x280) = streamFloat2;
        }
    }
    return; // Return 1
}