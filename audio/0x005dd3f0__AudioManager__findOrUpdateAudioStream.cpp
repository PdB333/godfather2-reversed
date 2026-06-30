// FUNC_NAME: AudioManager::findOrUpdateAudioStream
int AudioManager::findOrUpdateAudioStream(void* thisManager, void* audioEvent) {
    // thisManager assumed in unaff_EDI (EDI)
    // audioEvent assumed in unaff_ESI (ESI)
    // AudioEvent field offsets:
    // +0x04 : float volume
    // +0x08 : float pan
    // +0x0C : instance ID
    // +0x10 : something ID
    // +0x1C : flags (0 = use slot list, non-zero = use default)
    // +0x20 : compare ID0
    // +0x24 : compare ID1
    // +0x28 : compare ID2
    // +0x2C : compare ID3
    // +0x34 : slot update value

    // Manager (thisManager) holds:
    // +0x0C : free slot indicator array? (first ID of each slot, -1 if free)
    // +0x18 : start of 5 audio slots (each 0x68 bytes)
    // +0x214 : flags for default values
    // +0x240 : default volume override
    // +0x254 : default sample rate override
    // +0x27C : output volume
    // +0x280 : output pan

    uint slotIndex = 0;

    if (*(int*)((char*)audioEvent + 0x1c) == 0) {
        // No special flags, search for matching slot
        int* slotPtr = (int*)((char*)thisManager + 0x18);
        do {
            // Check if slot is occupied and matches audio event IDs
            if ((slotPtr[-3] != -1) &&                   // slot ID0 (offset +0x0C)
                (slotPtr[-2] == *(int*)((char*)audioEvent + 0x20)) &&  // compare ID0
                (slotPtr[-1] == *(int*)((char*)audioEvent + 0x24)) &&  // compare ID1
                (slotPtr[0] == *(int*)((char*)audioEvent + 0x28)) &&   // compare ID2
                (slotPtr[1] == *(int*)((char*)audioEvent + 0x2c))) {   // compare ID3
                // Matching slot found
                if (*(char*)(slotPtr + 10) == '\0') {
                    // Slot already active? Return success
                    return 1;
                }
                // Update slot state
                *(char*)(slotPtr + 10) = 0;                 // Clear active/playing flag
                slotPtr[-5] = *(int*)((char*)audioEvent + 0x10); // Set some ID from event
                slotPtr[-6] = *(int*)((char*)audioEvent + 0xc);  // Set another ID
                slotPtr[0xb] = *(int*)((char*)audioEvent + 0x34);// Set additional value
                return 1;
            }
            slotIndex++;
            slotPtr += 0x1a; // Advance to next slot (26 ints = 0x68 bytes)
        } while (slotIndex < 5);

        // No match found, look for first free slot
        slotIndex = 0;
        slotPtr = (int*)((char*)thisManager + 0x0C);
        do {
            if (*slotPtr == -1) break; // Free slot found
            slotIndex++;
            slotPtr += 0x1a;
        } while (slotIndex < 5);

        if (slotIndex != 5) {
            // Initialize free slot with default values
            FUN_005dd0d0(0x3f800000, 96000); // volume=1.0f, sampleRate=96000
        }
    } else {
        // Use default parameters
        float volume = *(float*)DAT_00e2b1a4; // Global default volume
        int sampleRate = 96000;
        if (*(int*)((char*)thisManager + 0x214) != -1) {
            volume = *(float*)((char*)thisManager + 0x240);
            sampleRate = *(int*)((char*)thisManager + 0x254);
        }
        FUN_005dd0d0(volume, sampleRate);
        // Update output volume/pan from audio event if positive
        if (*(float*)((char*)audioEvent + 4) >= 0.0f) {
            *(float*)((char*)thisManager + 0x27c) = *(float*)((char*)audioEvent + 4);
        }
        if (*(float*)((char*)audioEvent + 8) >= 0.0f) {
            *(float*)((char*)thisManager + 0x280) = *(float*)((char*)audioEvent + 8);
            return 1;
        }
    }
    return 1;
}