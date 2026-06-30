// FUNC_NAME: EventScheduler::processExpiredTimers
void __thiscall EventScheduler::processExpiredTimers(void* thisPtr, void* timerEntry, float timeThreshold)
{
    uint count;
    uint bestIndex;
    float* pFloatArray;
    uint i;
    long double resultTime;
    float fVar6;
    int node;
    int originalNext;
    float localTime;
    long long doubleData1;
    long long doubleData2;

    // Determine the actual time to use: if timeThreshold equals a sentinel value
    // (likely "use object's own time"), fetch time from the timer entry's offset +0x130.
    if (timeThreshold == DAT_00d5ccf8) {
        resultTime = FUN_004702b0(timerEntry + 0x130); // getObjectTime or similar
    } else {
        resultTime = timeThreshold;
    }

    // Read a double from the global manager (via this+0xc) at offsets 0x253c/0x2544.
    // This likely represents a time range (maybe min/max clamp values).
    doubleData1 = *(long long*)(*(int*)(thisPtr + 0xc) + 0x253c);
    doubleData2 = *(long long*)(*(int*)(thisPtr + 0xc) + 0x2544);

    // Clamp or adjust the time using the range.
    resultTime = FUN_00726710(&doubleData1, (float)resultTime);
    localTime = (float)resultTime;

    count = *(uint*)(thisPtr + 0x74); // Number of entries in the priority list

    if (count < 8) {
        // If there are fewer than 8 entries, simply add this timer to the intrusive list.
        if (timerEntry == 0) {
            node = 0;
        } else {
            node = timerEntry + 0x48; // Offset of the linked list node in the timer object
        }
        originalNext = 0;
        if (node != 0) {
            originalNext = *(int*)(node + 4); // Save original next pointer
            *(int**)(node + 4) = &node;       // Point next to itself (circular? or sentinel?)
        }
        FUN_0071dc80(&node); // Insert node into a list (probably push front)
        if (node != 0) {
            FUN_004daf90(&node); // Cleanup / destructor
            return;
        }
    } else {
        // Find the timer entry with the smallest first float value (priority/delay).
        bestIndex = 0xffffffff;
        i = 0;
        fVar6 = DAT_00d5f6f0; // Some large initial value (INF?)

        if (3 < (int)count) {
            pFloatArray = (float*)(thisPtr + 0x28); // Start at second group of floats
            do {
                // Compare four consecutive floats: previous entry's first, and three floats of current entry.
                if (pFloatArray[-3] < fVar6) {
                    bestIndex = i;
                    fVar6 = pFloatArray[-3];
                }
                if (*pFloatArray < fVar6) {
                    bestIndex = i + 1;
                    fVar6 = *pFloatArray;
                }
                if (pFloatArray[3] < fVar6) {
                    bestIndex = i + 2;
                    fVar6 = pFloatArray[3];
                }
                if (pFloatArray[6] < fVar6) {
                    bestIndex = i + 3;
                    fVar6 = pFloatArray[6];
                }
                i = i + 4;
                pFloatArray = pFloatArray + 0xc; // Each group of 3 floats (0xc bytes)
            } while (i < count - 3);
        }

        // Process remaining entries (less than a full group)
        if (i < count) {
            pFloatArray = (float*)(thisPtr + 0x1c + i * 0xc); // Start at entry i's first float
            do {
                if (*pFloatArray < fVar6) {
                    bestIndex = i;
                    fVar6 = *pFloatArray;
                }
                i = i + 1;
                pFloatArray = pFloatArray + 3; // Skip to next entry's first float
            } while (i < count);
        }

        // If the smallest value is less than the current time, remove that entry.
        if (fVar6 < localTime) {
            if (timerEntry == 0) {
                node = 0;
            } else {
                node = timerEntry + 0x48;
            }
            originalNext = 0;
            if (node != 0) {
                originalNext = *(int*)(node + 4);
                *(int**)(node + 4) = &node;
            }
            FUN_0071dce0(&node, bestIndex); // Remove entry at bestIndex from list
            if (node != 0) {
                FUN_004daf90(&node); // Cleanup
            }
        }
    }
    return;
}