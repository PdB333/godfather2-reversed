// FUN_NAME: AIDecisionManager::selectAndExecuteAction
void __thiscall AIDecisionManager::selectAndExecuteAction(int thisPtr, int *actionContext) {
    int randomVal;
    undefined4 actionParam;
    float *entryPtr;
    float cumulativeWeight;
    float randomThreshold;
    int contextParam;
    char dummy; // used for local_4

    // Compare current action ID with expected state (offset +0x14)
    if (*actionContext != *(int *)(thisPtr + 0x14)) {
        return;
    }

    randomVal = rand();
    entryPtr = (float *)(thisPtr + 0x1c);  // Start of weighted action table
    cumulativeWeight = 0.0f;

    // End of table is at offset 0x9c (exclusive)
    if (entryPtr == (float *)(thisPtr + 0x9c)) {
        return;
    }

    // Iterate over entries (each entry is 4 floats: weight, activeFlag, ?, actionThreshold)
    while (true) {
        // Skip entries where activeFlag (entry[1]) is zero
        if (entryPtr[1] != 0.0f) {
            cumulativeWeight += *entryPtr;  // Add weight
            // Random threshold based on global scale, totalWeight at +0x9c
            randomThreshold = (float)randomVal * DAT_00e44590 * *(float *)(thisPtr + 0x9c);
            if (cumulativeWeight > randomThreshold) {
                break;  // Found the selected entry
            }
        }
        entryPtr += 4;  // Move to next entry (16 bytes)
        if (entryPtr == (float *)(thisPtr + 0x9c)) {
            return;
        }
    }

    contextParam = actionContext[1];  // Additional context parameter

    if (entryPtr[3] > 0.0f) {  // Action threshold > 0 -> perform an action
        if ((contextParam == 0) || (randomVal = FUN_009c8e50(0xc), randomVal == 0)) {
            actionParam = 0;
        } else {
            actionParam = FUN_00476c80();  // Probably get some parameter like target
        }
        // Start the action: pass entryPtr+1 (likely action parameters), 0, actionThreshold, actionParam, 0
        FUN_00440590(entryPtr + 1, 0, entryPtr[3], actionParam, 0);
        return;
    }
    // else play sound/effect
    float soundId = entryPtr[1];  // activeFlag used as sound ID
    dummy = 0;
    FUN_00408a00(&soundId, 0);  // Play one-shot sound
    return;
}