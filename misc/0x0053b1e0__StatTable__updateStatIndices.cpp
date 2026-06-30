// FUNC_NAME: StatTable::updateStatIndices
void __thiscall StatTable::updateStatIndices(int category, int param1, int param2)
{
    // Global state variables hold the parameters
    int in_EAX = category; // Actually passed in EAX, but treated as first parameter

    g_statCategory = in_EAX;    // DAT_0112537c
    g_statParam2 = param2;      // DAT_01125380
    g_statParam1 = param1;      // DAT_01125384

    if (in_EAX == 3) {
        g_statIndex1 = 0;       // DAT_01125388
        g_statIndex2 = 0x12;    // DAT_01125389 (18)
    }
    else if (in_EAX == 4) {
        g_statIndex1 = 2;
        g_statIndex2 = 0x13;    // 19
    }
    else if (in_EAX == 5) {
        g_statIndex1 = 2;
        g_statIndex2 = 0x14;    // 20
    }
    else if (in_EAX == 6) {
        g_statIndex1 = 2;
        g_statIndex2 = 0x15;    // 21
    }
    else {
        // Default formula: index1 = (param2 == 1), index2 = combined calculation
        g_statIndex1 = (param2 == 1) ? 1 : 0;
        // Formula: ((param1 != 1) - 1U & 9) + category * 3 + param2
        unsigned int temp = (param1 != 1) ? 0 : 1; // (param1 != 1) - 1U yields 0 or -1 (0xFFFFFFFF) but &9 masks to 9?
        // Actually in the original: ((param1 != 1) - 1U & 9)
        // This is tricky: if param1 == 1, then (0 - 1) & 9 = 0xFFFFFFFF & 9 = 9; if param1 != 1, then (1 - 1) & 9 = 0.
        g_statIndex2 = ((param1 == 1) ? 9 : 0) + (char)in_EAX * 3 + (char)param2;
    }

    // Use the indices to look up values from static tables
    g_statValue1 = g_statTable1[g_statIndex1];        // DAT_011252e8 from array at DAT_0112538c
    g_statValue2 = *(int*)((int)&g_statTable2 + g_statIndex2 * 4);  // DAT_011252ec from array at DAT_01125398
}