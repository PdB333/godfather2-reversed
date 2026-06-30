// FUNC_NAME: DonControlManager::findAvailableSlot
// Address: 0x005e26a0
// Role: Finds an available slot for a new crew member or action. Iterates 5 slots (0x4A4 bytes each) to find an inactive slot or the best candidate based on timestamps.

int DonControlManager::findAvailableSlot(int requestInfo) { // this +0x230 base of slot array, each slot 0x4A4 bytes, structure includes float at +0x230, char flag at +0x264, int time at +0x268, int id at +0x26C, int state at +0x488
    int bestSlot = -1;
    if (*(char *)(requestInfo + 5) != '\0') { // requestInfo +5 is a flag (e.g., priority)
        // First pass: check for existing slot matching requestInfo+0x58, but abort if timestamp is too old
        for (int i = 0; i < 5; ++i) {
            int *slotIdPtr = (int *)(this + 0x26C + i * 0x4A4); // pointer to slot's ID at +0x26C
            int slotId = *slotIdPtr;
            if (slotId != 0 && *(int *)(slotIdPtr + 0x87) != 3) { // state at +0x488: 3 = active/occupied?
                if (slotId == *(int *)(requestInfo + 0x58)) { // matching ID
                    int slotTime = *(int *)(slotIdPtr - 1); // time at +0x268
                    int requestTime = *(int *)(requestInfo + 0x54);
                    if (requestTime < slotTime) { // request timestamp is earlier than slot timestamp
                        // Conflict: request too old, abort and log
                        logSlotConflict(*(int *)(requestInfo + 0x58));
                        return -1;
                    }
                }
            }
        }
        // If no conflict, process matching slots
        for (int i = 0; i < 5; ++i) {
            float *slotFloatPtr = (float *)(this + 0x230 + i * 0x4A4);
            if (slotFloatPtr[0xF] == *(int *)(requestInfo + 0x58)) { // slot ID matches (at +0x260? Actually slotFloatPtr+0xF = offset 0x3C from float base, which is 0x230+0x3C=0x26C)
                processSlotData(requestInfo, i, slotFloatPtr[0xF]); // log something
                // Prepare some data for processing later
                int local_c = 0;
                float local_10 = *slotFloatPtr; // float at +0x230
                int local_14 = 1;
                char local_8 = 0;
                processSlotStruct(local_14, local_c, local_8, local_10); // calls FUN_005e9440
                if (local_10 == someGlobalFloat) { // DAT_00e2b05c
                    resetSlot(slotFloatPtr); // calls FUN_005e86e0 twice and clears two ints at +0x200 and +0x204
                }
            }
        }
    }
    // Determine first inactive slot and count active slots
    int activeCount = *(char *)(this + 0x494) != '\0' ? 1 : 0; // slot 0 flag
    if (*(char *)(this + 0x494) == '\0' && bestSlot == -1) bestSlot = 0;
    activeCount += *(char *)(this + 0x938) != '\0' ? 1 : 0;
    if (*(char *)(this + 0x938) == '\0' && bestSlot == -1) bestSlot = 1;
    activeCount += *(char *)(this + 0xDDC) != '\0' ? 1 : 0;
    if (*(char *)(this + 0xDDC) == '\0' && bestSlot == -1) bestSlot = 2;
    activeCount += *(char *)(this + 0x1280) != '\0' ? 1 : 0;
    if (*(char *)(this + 0x1280) == '\0' && bestSlot == -1) bestSlot = 3;
    activeCount += *(char *)(this + 0x1724) != '\0' ? 1 : 0;
    if (*(char *)(this + 0x1724) == '\0' && bestSlot == -1) bestSlot = 4;
    // Check if active count is below maximum allowed
    if (activeCount >= *(int *)(this + 0x174C)) { // max slots limit
        bestSlot = -1;
    }
    // If no free slot found, fallback: try to select best candidate based on timestamps
    if (bestSlot == -1) {
        logNoSlotAvailable();
        bestSlot = findBestCandidateSlot(requestInfo); // calls FUN_005e29b0
        if (bestSlot == -1) {
            // Manual fallback: check each slot's flag and compare timestamps
            if (*(char *)(this + 0x494) != '\0' && *(int *)(this + 0x268) < *(int *)(requestInfo + 0x54)) {
                bestSlot = 0;
            }
            if (*(char *)(this + 0x938) != '\0' && *(int *)(this + 0x70C) < *(int *)(requestInfo + 0x54) &&
                (bestSlot == -1 || *(int *)(this + 0x70C) < *(int *)(this + bestSlot * 0x4A4 + 0x268))) {
                bestSlot = 1;
            }
            if (*(char *)(this + 0xDDC) != '\0' && *(int *)(this + 0xBB0) < *(int *)(requestInfo + 0x54) &&
                (bestSlot == -1 || *(int *)(this + 0xBB0) < *(int *)(this + bestSlot * 0x4A4 + 0x268))) {
                bestSlot = 2;
            }
            if (*(char *)(this + 0x1280) != '\0' && *(int *)(this + 0x1054) < *(int *)(requestInfo + 0x54) &&
                (bestSlot == -1 || *(int *)(this + 0x1054) < *(int *)(this + bestSlot * 0x4A4 + 0x268))) {
                bestSlot = 3;
            }
            if (*(char *)(this + 0x1724) != '\0' && *(int *)(this + 0x14F8) < *(int *)(requestInfo + 0x54) &&
                (bestSlot == -1 || *(int *)(this + bestSlot * 0x4A4 + 0x268) <= *(int *)(this + 0x14F8))) {
                bestSlot = 4;
            }
            if (bestSlot != -1) {
                // Initialize the selected slot
                int slotBase = this + bestSlot * 0x4A4 + 4;
                processSlotStruct(1, 0, 0, 0.0f); // calls FUN_005e9440 (probably sets local variables)
                resetSlot(slotBase - 4); // calls FUN_005e86e0 twice (on the slot)
                *(int *)(slotBase + 0x1FC) = 0;
                *(int *)(slotBase + 0x200) = 0;
            }
        }
    }
    return bestSlot;
}