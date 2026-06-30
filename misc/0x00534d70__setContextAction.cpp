// FUNC_NAME: setContextAction
// Function at address 0x00534D70: Sets the current action context and triggers associated sounds if the active context is the default.
void __fastcall setContextAction(int modifier, int subIndex, int actionType)
{
    // g_contextActionType stores the action type (0-4 special)
    g_contextActionType = actionType;

    if (actionType == 3) {
        g_contextIndex1 = 0;
        g_contextIndex2 = 0x12; // 18
    }
    else if (actionType == 4) {
        g_contextIndex1 = 2;
        g_contextIndex2 = 0x13; // 19
    }
    else {
        // Normal action types (0,1,2)
        g_contextIndex1 = (subIndex == 1) ? 1 : 0;
        // Compute index2: base = actionType*3 + subIndex; add 9 if modifier == 1
        g_contextIndex2 = ((modifier == 1) ? 9 : 0) + actionType * 3 + subIndex;
    }

    // Look up sound IDs from tables using indices
    g_contextSoundId1 = g_soundLookupTable1[g_contextIndex1];   // table at &DAT_01219c50
    g_contextSoundId2 = *(int*)(&g_soundLookupTable2 + (uint)g_contextIndex2 * 4); // table at &DAT_01219c5c

    // Store the original parameters for reference
    g_contextModifier = modifier;
    g_contextSubIndex = subIndex;

    // If the active context is the default instance, trigger the sounds
    if (g_activeContext == &g_defaultContext) {
        triggerSound(g_contextSoundId1); // FUN_0060a460
        triggerSound(g_contextSoundId2); // FUN_0060a460
    }
}