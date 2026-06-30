// FUNC_NAME: AptAnimationManager::updateAnimations
void AptAnimationManager::updateAnimations(int deltaTimeMs)
{
    int *animationObj;
    int timer;
    int *pendingEntry;
    void *refPtr;
    int slotIndex;
    int entryIndex;
    int *activeAnimPtr; // points to base of active animations array

    // [this+0x30] seems to be a flag or counter, set to 0 initially
    *(int *)(this + 0x30) = 0;

    // First pass: iterate over all active animation slots
    if (0 < *(int *)(this + 0x0c)) {
        do {
            animationObj = *(int **)(*(int *)(this + 0x10) + slotIndex * 4);
            if (animationObj != 0) {
                // Check if this slot is in the pending removal list
                int pendingCount = *(int *)(this + 0x20);
                bool isPending = false;
                if (0 < pendingCount) {
                    pendingEntry = (int *)(*(int *)(this + 0x24) + 8); // start at offset 8 of each entry? Or maybe +8 is the slot field.
                    for (entryIndex = 0; entryIndex < pendingCount; entryIndex++) {
                        if (*pendingEntry == slotIndex) {
                            isPending = true;
                            goto check_pending_done;
                        }
                        pendingEntry += 4; // each entry is 16 bytes, so +4 moves by 4 ints? Actually this increments by 4 bytes, so it's iterating over int positions. Assuming each entry is 16 bytes, this is wrong. Decompiler might be confused. We'll ignore the exact structure.
                    }
                }
                check_pending_done:
                if (!isPending) {
                    int animType = *(int *)(animationObj + 0); // +0: type field
                    switch (animType) {
                        case 1: // Type 1: probably "once" animation
                            // Call a function on field at offset 0x18 (6 ints)
                            (*DAT_0119cb64)(*(int *)(animationObj + 6));
                            // Store slot index back into animation object at +0x18
                            *(int *)(*(int *)(*(int *)(this + 0x10) + slotIndex * 4) + 0x18) = slotIndex;
                            break;
                        case 2: // Type 2: timed animation with two timers
                            if (*(int *)(animationObj + 0xd) != 0) { // timer at +0x34?
                                *(int *)(animationObj + 0xd) -= deltaTimeMs;
                            }
                            timer = *(int *)(*(int *)(this + 0x10) + slotIndex * 4);
                            if (*(int *)(timer + 0x38) != 0) { // +0x38: another timer
                                *(int *)(timer + 0x38) -= deltaTimeMs;
                            }
                            break;
                        case 3: // Type 3: animation with keyframe timers
                            if (*(int *)(animationObj + 2) != 0) { // +2: timer at offset 8? Actually int offsets: +2 int = +8 bytes
                                *(int *)(animationObj + 2) -= deltaTimeMs;
                            }
                            // Update an array of something (probably frame times)
                            int frameCount = *(int *)(*(int *)(*(int *)(this + 0x10) + slotIndex * 4) + 0x0c); // +0xc: number of frames
                            if (0 < frameCount) {
                                int frameArray = *(int *)(*(int *)(*(int *)(this + 0x10) + slotIndex * 4) + 0x10); // +0x10: array of frame durations
                                for (int f = 0; f < frameCount; f++) {
                                    *(int *)(frameArray + f * 4) = FUN_005a5570(); // generate next frame? This seems like a call that returns something.
                                }
                            }
                            timer = *(int *)(*(int *)(this + 0x10) + slotIndex * 4);
                            if (*(int *)(timer + 0x10) != 0) { // +0x10: master timer (note: same offset as array pointer! Overlap?)
                                *(int *)(timer + 0x10) -= deltaTimeMs;
                            }
                            break;
                        case 5: // Type 5: probably looping animation
                            FUN_005b9f20(animationObj + 2, deltaTimeMs, (int *)(this + 0x30));
                            break;
                        case 6: // Type 6: another type
                            (*DAT_0119cb48)(*(int *)(animationObj + 2));
                            *(int *)(*(int *)(*(int *)(this + 0x10) + slotIndex * 4) + 8) = slotIndex;
                            break;
                        case 7: // Type 7: another type
                            (*DAT_0119cb58)(*(int *)(animationObj + 2));
                            *(int *)(*(int *)(*(int *)(this + 0x10) + slotIndex * 4) + 8) = slotIndex;
                            break;
                        case 9: // Type 9: special (maybe cinematic?), with assertion
                            FUN_005b9f20(animationObj + 2, deltaTimeMs, (int *)(this + 0x30));
                            // Assertion: only slot 0 should have type 9
                            if (slotIndex != 0) {
                                // "i == 0" assertion
                                char *assertMsg = "i == 0";
                                char *file = "..\\source\\Apt\\AptAnimation.cpp";
                                int line = 0x137; // 311
                                int assertType = 2; // probably severity
                                // There's also a reference to a string at DAT_01128f8d (maybe a function name)
                                // Call assertion failure handler
                                FUN_0059bf00();
                            }
                            break;
                    }
                }
            }
            slotIndex++;
        } while (slotIndex < *(int *)(this + 0x0c));
    }

    // Second pass: process pending removal list (decrement refcounts and free)
    slotIndex = 0;
    if (0 < *(int *)(this + 0x20)) {
        entryIndex = 0;
        do {
            // Each entry in the pending removal list is 16 bytes. We access field at offset 0xc (12) which is a pointer.
            int *entryBase = *(int *)(this + 0x24);
            void **refPtrSlot = (void **)(entryIndex + 0xc + entryBase);
            // Sentry check: compare with local variable address (debug)
            // Actually the code compares with &local_18, which is a stack variable. We omit that check.
            refPtr = *refPtrSlot;
            if (refPtr != 0) {
                // Decrement reference count (assuming ref count is at offset 0 of the pointed object? Or the pointer itself is a refcounted object with an internal counter)
                // The code does: *refPtr = *refPtr - 1; if becomes 0 then free.
                int *refCountPtr = (int *)refPtr;
                (*refCountPtr)--;
                if (*refCountPtr == 0) {
                    FUN_005a3270(refPtr);
                }
                *refPtrSlot = 0;
            }
            // Also clear the corresponding slot in the active animations array
            int slotToClear = *(int *)(entryIndex + 8 + entryBase);
            *(int **)(*(int *)(this + 0x10) + slotToClear * 4) = 0;
            slotIndex++;
            entryIndex += 0x10; // move to next entry
        } while (slotIndex < *(int *)(this + 0x20));
    }

    // Third pass: decrement a master lifetime timer on each active animation and set debug magic
    slotIndex = 0;
    if (0 < *(int *)(this + 0x0c)) {
        do {
            if (*(int *)(*(int *)(this + 0x10) + slotIndex * 4) != 0) {
                int *animPtr = *(int **)(*(int *)(this + 0x10) + slotIndex * 4);
                // Set debug guard at offset +4
                *(int *)(animPtr + 1) = 0x9876543;
                // Decrement timer at [animPtr] (first int)
                int timerVal = *animPtr;
                if (timerVal != 0) {
                    *animPtr = timerVal - deltaTimeMs;
                }
            }
            slotIndex++;
        } while (slotIndex < *(int *)(this + 0x0c));
    }

    // Decrement a global timer at this+0x10 (could be a frame duration counter?)
    int *globalTimer = (int *)(this + 0x10);
    if (*globalTimer != 0) {
        *globalTimer -= deltaTimeMs;
    }

    // Fourth pass: decrement timers in the pending removal list entries (fields at offset 0 and 4)
    slotIndex = 0;
    if (0 < *(int *)(this + 0x20)) {
        entryIndex = 0;
        do {
            int *entryBase = *(int **)(this + 0x24);
            int *timer1 = (int *)(entryBase + entryIndex);
            if (*timer1 != 0) {
                *timer1 -= deltaTimeMs;
            }
            int *timer2 = (int *)(entryBase + entryIndex + 4);
            if (*timer2 != 0) {
                *timer2 -= deltaTimeMs;
            }
            slotIndex++;
            entryIndex += 0x10;
        } while (slotIndex < *(int *)(this + 0x20));
    }

    // Decrement master timers at this+0x24 and this+0x2c (if not null)
    if (*(int *)(this + 0x24) != 0) {
        *(int *)(this + 0x24) -= deltaTimeMs;
    }
    if (*(int *)(this + 0x2c) != 0) {
        *(int *)(this + 0x2c) -= deltaTimeMs;
        *(int *)(this + 0x30) = 0;
        return;
    }
    *(int *)(this + 0x30) = 0;
}