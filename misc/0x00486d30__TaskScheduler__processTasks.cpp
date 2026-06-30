// FUNC_NAME: TaskScheduler::processTasks
void __thiscall TaskScheduler::processTasks(int* thisPtr) {
    // Constants derived from global frequency (QPC)
    extern uint64_t g_qpcFrequency; // DAT_01163ec0 (low) and DAT_01163ec4 (high)

    // Local variables
    uint32_t taskCount = *(uint32_t*)(thisPtr + 0x94); // Number of task slots
    uint32_t activeMask = (1u << taskCount) - 1;       // Bitmask of active tasks
    int totalBudget = *(int*)(thisPtr + 0x98);          // Total time budget for this frame

    int iterationCounter = 0;
    bool reachedLimit = false;

    // Compute base time and durations
    LARGE_INTEGER counterStart;
    QueryPerformanceCounter(&counterStart);

    uint64_t qpcFrequency = ((uint64_t)g_qpcFrequencyHigh << 32) | g_qpcFrequencyLow;

    uint64_t frameStart = (uint64_t)counterStart.LowPart | ((uint64_t)counterStart.HighPart << 32);

    // Maximum allowed time for this call (from param_1+0xc0)
    uint64_t maxDuration = __allmul(*(int*)(thisPtr + 0xc0), 0, qpcFrequency) / 1000000;
    uint64_t frameEnd = frameStart + maxDuration;

    // Time step for each task (from param_1+0xb8)
    uint64_t timeStep = __allmul(*(int*)(thisPtr + 0xb8), 0, qpcFrequency) / 1000000;

    // Another duration (from param_1+0xbc)
    uint64_t durationBc = __allmul(*(int*)(thisPtr + 0xbc), 0, qpcFrequency) / 1000000;

    // Periodic yield interval (derived from global function returning base tick)
    uint64_t yieldInterval = __aulldiv(FUN_00b9a1f6(), 20, 0); // Probably: getTick() / 20
    uint64_t nextYield = yieldInterval + frameStart;

    // Main processing loop
    while (true) {
        uint64_t remainingTime = timeStep;
        uint64_t currentBudget = totalBudget;

        if (taskCount != 0) {
            int* entryPtr = (int*)(thisPtr + 0x24); // Pointer to first task entry's budget field
            uint32_t slotIndex = 0;

            do {
                uint32_t slotMask = 1u << slotIndex;
                if ((activeMask & slotMask) != 0) {
                    int taskBudget = *entryPtr; // Budget for this task
                    uint64_t allocatedTime = __allmul(taskBudget, 0, remainingTime) / (int64_t)currentBudget;

                    // Compute time based on durationBc (clamp to allocatedTime)
                    uint64_t taskTime = __allmul(taskBudget, 0, durationBc) / totalBudget;
                    if (taskTime < allocatedTime) {
                        taskTime = allocatedTime;
                    }

                    // Determine which function to call (thiscall vs static)
                    LARGE_INTEGER callStart, callEnd;
                    QueryPerformanceCounter(&callStart);

                    uint32_t returnValue;
                    if (*(int*)(entryPtr - 2) == 0) { // No 'this' pointer? static function?
                        returnValue = ((uint32_t (*)(uint64_t, int))*(int*)(entryPtr - 8))(taskTime, iterationCounter);
                    } else {
                        returnValue = ((uint32_t (*)(void*, uint64_t, int))*(int*)(entryPtr - 2))
                                        (entryPtr - 8, taskTime, iterationCounter);
                    }

                    QueryPerformanceCounter(&callEnd);
                    uint64_t elapsed = (uint64_t)(callEnd.LowPart - callStart.LowPart)
                                     | ((uint64_t)(callEnd.HighPart - callStart.HighPart - (callEnd.LowPart < callStart.LowPart ? 1 : 0)) << 32);

                    // Adjust remaining time
                    if (elapsed < remainingTime) {
                        remainingTime -= elapsed;
                    } else {
                        remainingTime = 0;
                    }

                    currentBudget -= taskBudget;

                    // Check abort flag
                    if (returnValue & 2) {
                        return; // Abort all tasks
                    }
                    // Check completion flag
                    if ((returnValue & 1) == 0) {
                        activeMask &= ~slotMask; // Task completed
                        totalBudget -= taskBudget;
                    }

                    if (reachedLimit && *(int*)(thisPtr + 0xa4) == *(int*)(thisPtr + 0xa0)) {
                        break;
                    }
                }

                entryPtr += 9; // Move to next task (each entry is 9 ints = 36 bytes)
                slotIndex++;
            } while (slotIndex < taskCount);
        }

        if (activeMask == 0) {
            return; // All tasks done
        }

        // Update iteration counter
        if (*(uint32_t*)(thisPtr + 0xa4) < *(uint32_t*)(thisPtr + 0x9c)) {
            *(int*)(thisPtr + 0xa4) = *(int*)(thisPtr + 0x9c);
            reachedLimit = true;
            if (*(int*)(thisPtr + 0xa4) == *(int*)(thisPtr + 0xa0)) {
                return;
            }
        } else if (reachedLimit) {
            if (*(int*)(thisPtr + 0xa4) == *(int*)(thisPtr + 0xa0)) {
                return;
            }
        }

        // Check overall time limit
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);
        uint64_t nowTicks = (uint64_t)now.LowPart | ((uint64_t)now.HighPart << 32);
        if (frameEnd <= nowTicks) {
            return; // Exceeded max duration
        }

        // Periodic yield
        if (nextYield <= nowTicks) {
            FUN_00ab4b40(0); // Yield / Sleep(0)
            nextYield = yieldInterval + nowTicks;
        }

        if (reachedLimit && *(int*)(thisPtr + 0xa4) == *(int*)(thisPtr + 0xa0)) {
            return;
        }
        if (*(int*)(thisPtr + 0xbc) == 0) {
            return; // Termination condition
        }

        iterationCounter++;
    }
}