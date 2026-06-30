// Xbox PDB: AptAnimationPoolData::tickIntervalTimers
// FUNC_NAME: AptAnimation::processIntervalTimers
void AptAnimation::processIntervalTimers(int deltaMs)
{
    // Global pointer to the AptAnimation instance (or static data)
    // DAT_0119a9cc likely points to the singleton or manager
    int* basePtr = *(int**)0x0119a9cc; // g_aptAnimationManager
    if (!basePtr) return;

    int timerCount = basePtr[0x3018 / 4]; // Number of timer slots
    int currentIndex = 0;
    int processedCount = 0;

    // Pointer to the first timer entry's callback pointer field (each entry is 0x2c = 44 bytes)
    int* timerEntryPtr = basePtr + 0x2528 / 4; // Points to offset 0x10 inside first entry

    do {
        if (currentIndex >= timerCount) {
            return;
        }

        // Check if the timer is active (active flag at offset -0x10 from this pointer)
        if (timerEntryPtr[-4] != 0) {
            // Current remaining time (float stored as int)
            float remainingTime = (float)timerEntryPtr[-1];
            timerEntryPtr[-1] = (int)(remainingTime - (float)deltaMs);

            if (remainingTime - (float)deltaMs < 0.0f) {
                // Timer expired
                // Check if the callback is a script function (FUN_005a3dc0 likely isScriptFunction)
                bool isScript = FUN_005a3dc0();
                if (!isScript) {
                    // Debug assertion fails here
                    const char* expr = "aIntervalTimers[i].pCBFunction->isScriptFunction()";
                    const char* file = "..\\source\\Apt\\AptAnimation.cpp";
                    int line = 0x221;
                    int level = 2;
                    volatile char* debugFlag = (volatile char*)0x01128f8f;
                    if (*debugFlag) {
                        // Debug output mechanism
                        int** debugPtr = *(int***)(*(int*)(__readgsdword(0x2C) + 0x30) + 0x30);
                        uint flags = 1;
                        if (debugPtr == NULL) {
                            // Call some debug function
                            flags = (**(code**)(*debugPtr[0] + 8))(&expr, "aIntervalTimers[i].pCBFunction->isScriptFunction()");
                        }
                        if ((debugFlag != NULL) && ((flags & 2) != 0)) {
                            *debugFlag = 0;
                        }
                        if ((debugPtr != NULL) || (level != 4)) {
                            if (((flags & 1) != 0) || (level == 0) || (level == 1)) {
                                // Trigger a debug break
                                code* breakFunc = (code*)swi(3);
                                (*breakFunc)();
                                return;
                            }
                        }
                    }
                }

                // Get the global state manager (FUN_005a3ae0 likely returns some singleton)
                int* stateMgr = FUN_005a3ae0();
                bool canExecute = true;

                // Check if the system is locked or busy
                if (stateMgr[0x50 / 4] != 0) {
                    // Check a bit flag (bit 15?) at offset 0x58
                    uint* flagsPtr = (uint*)(stateMgr[0x58 / 4]);
                    if (((*flagsPtr >> 0xf) & 1) == 0) {
                        canExecute = false;
                    }
                }
                // Also check another condition (FUN_005a4140)
                if (canExecute && FUN_005a4140()) {
                    canExecute = false;
                }

                if (canExecute) {
                    // Get the callback index from the timer entry (lower 15 bits of a uint pointer?)
                    uint callbackIndex = *(uint*)timerEntryPtr[-3] & 0x7fff;
                    // Call the registered callback function from a global table at 0x0103aee0
                    (**(code**)(0x0103aee0 + callbackIndex * 4))((uint*)timerEntryPtr[-3]);
                    // Mark the timer as inactive
                    timerEntryPtr[-4] = 0;
                } else {
                    // Cannot execute, so reschedule the timer
                    if (timerEntryPtr[0] < 1) {
                        // No retries, just reset with a different method
                        uint param = *(uint*)(stateMgr[0x58 / 4]);
                        int retry = -1;
                        // Call some reset function
                        FUN_005aec20(param, retry);
                    } else {
                        // Retry loop
                        for (int i = 0; i < timerEntryPtr[0]; i++) {
                            FUN_005a70a0(i);
                            FUN_005a4210(&DAT_01221700);
                        }
                        int retryCount = timerEntryPtr[0];
                        uint param = *(uint*)(stateMgr[0x58 / 4]);
                        FUN_005aec20(param, retryCount);
                    }
                    FUN_005a0c50();
                    // Add back the interval to the remaining time
                    timerEntryPtr[-1] = (int)((float)timerEntryPtr[-2] + (float)timerEntryPtr[-1]);
                }
            }
        }

        processedCount++;
        currentIndex++;
        // Move to the next timer entry (each entry is 0x2c = 44 bytes = 11 ints)
        timerEntryPtr += 11;

        if (processedCount > 0x3f) { // Max 64 timers
            return;
        }
    } while (true);
}