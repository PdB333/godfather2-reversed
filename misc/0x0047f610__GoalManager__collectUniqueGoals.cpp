// FUNC_NAME: GoalManager::collectUniqueGoals
void __thiscall GoalManager::collectUniqueGoals(GUID* pObjectGUIDs, Goal* pOutGoals, int* pOutCount) 
{
    // pObjectGUIDs points to an array of 16-byte GUIDs.
    // The number of GUIDs is passed via EAX (in_EAX in decompiled code).
    // This function collects unique Goal structures associated with each GUID.
    
    int numGUIDs = (int)this;  // Actually EAX holds the count, not this. We'll assume it's passed as first param.
    // In the original, the count is in EAX. For reconstruction, we assume pObjectGUIDs is the array and count is implicit.
    // We'll simulate by using pObjectGUIDs as the array and a separate count parameter if needed.
    // Since the signature shows only three stack parameters, we treat the count as the implicit 'this' in EAX.
    // For the reconstruction, we'll add a local count variable and assign it from the decompiled 'in_EAX'.
    int guidCount = (int)pObjectGUIDs; // HACK: but we need proper variable.

    // Actually, re-analyzing: param_1 is the array base, param_2 is output buffer, param_3 is output count pointer.
    // The count is passed in EAX. So the function is essentially:
    // void __thiscall collectGoalsFromGUIDs(int count, GUID* pGUIDs, Goal* outGoals, int* outCount)
    // But __thiscall can't have EAX param. We'll write it as a regular function with count first.
}

// Let's rewrite properly:

// The actual code from decompilation:
// void __thiscall FUN_0047f610(int param_1,int param_2,uint *param_3)
// with in_EAX holding the count.

// So we reconstruct:

void __thiscall GoalManager::collectGoalsFromGUIDs(int guidCount, GUID* pGUIDs, Goal* pOutGoals, int* pOutCount)
{
    if (guidCount == 0) return;

    // pGUIDs points to an array of GUIDs (16 bytes each).
    // The loop iterates by using a pointer piVar6 pointing to the middle (offset 8) of each GUID.
    // This allows simple indexing to get the four dwords of the GUID.

    for (int i = 0; i < guidCount; i++)
    {
        // Get pointer to the middle of the current GUID
        // Equivalent to piVar6 = (int*)(pGUIDs + i) + 2;  (since each GUID is 4 ints, middle is at offset 2 ints)
        GUID* pCurrentGUID = &pGUIDs[i];
        // Check if any dword of the GUID is non-zero
        bool guidNonZero = (pCurrentGUID->dw0 != 0 || pCurrentGUID->dw1 != 0 || 
                            pCurrentGUID->dw2 != 0 || pCurrentGUID->dw3 != 0);
        if (!guidNonZero) continue;

        // Lookup the GUID in the object database (FUN_00445ff0)
        // FUN_00445ff0 takes a GUID pointer and returns a pointer to an object structure.
        void* pObject = FindObjectByGUID(pCurrentGUID, 0);  // 0 is likely a flags parameter
        if (pObject == nullptr) continue;

        // Check if object has a specific flag at offset 0x14 (0x8000000)
        uint32_t flags = *(uint32_t*)((uint8_t*)pObject + 0x14);
        if ((flags & 0x8000000) == 0) continue;

        // Check if object has a goal list: count at offset 0x394
        int goalCount = *(int*)((uint8_t*)pObject + 0x394);
        if (goalCount == 0) continue;

        // Iterate over the goals in the object's goal list (starts at offset 0x9c)
        Goal* pObjectGoals = (Goal*)((uint8_t*)pObject + 0x9c);
        for (int j = 0; j < goalCount; j++)
        {
            // Check if this goal is already in the output buffer (by comparing first 4 dwords)
            bool alreadyExists = false;
            for (int k = 0; k < *pOutCount; k++)
            {
                Goal* pExistingGoal = &pOutGoals[k];
                if (pExistingGoal->data[0] == pObjectGoals[j].data[0] &&
                    pExistingGoal->data[1] == pObjectGoals[j].data[1] &&
                    pExistingGoal->data[2] == pObjectGoals[j].data[2] &&
                    pExistingGoal->data[3] == pObjectGoals[j].data[3])
                {
                    alreadyExists = true;
                    break;
                }
            }

            if (!alreadyExists)
            {
                // Copy the entire 6-int goal (24 bytes)
                pOutGoals[*pOutCount] = pObjectGoals[j];
                (*pOutCount)++;
            }
        }
    }
}