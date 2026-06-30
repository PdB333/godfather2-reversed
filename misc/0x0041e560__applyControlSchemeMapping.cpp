// FUNC_NAME: applyControlSchemeMapping
void applyControlSchemeMapping(int mappingIndex, int param2, int param3)
{
    // Global state variables for mapped values
    static int s_mappedValue = 0;       // _DAT_011f3ab8
    static int s_mappedParam2 = 0;      // _DAT_011f3abc
    static int s_mappedParam3 = 0;      // _DAT_011f3ac0
    static int s_minValueA = 0;         // DAT_012058d0
    static int s_minValueB = 0;         // DAT_00f15988

    // Map mappingIndex (0-7) to a predefined control scheme value
    switch (mappingIndex)
    {
        case 0: s_mappedValue = 1; break;
        case 1: s_mappedValue = 8; break;
        case 2: s_mappedValue = 2; break;
        case 3: s_mappedValue = 4; break;
        case 4: s_mappedValue = 3; break;
        case 5: s_mappedValue = 7; break;
        case 6: s_mappedValue = 5; break;
        case 7: s_mappedValue = 6; break;
        default: s_mappedValue = param3; break; // fallback (overwritten later)
    }

    // Enforce minimum bound on s_minValueA
    if (s_minValueA < 0x38) {
        s_minValueA = 0x38;
    }
    if (s_minValueB > 0x38) {
        s_minValueB = 0x38;
    }
    if (s_minValueA < 0x39) {
        s_minValueA = 0x39;
    }
    if (s_minValueB > 0x39) {
        s_minValueB = 0x39;
    }

    // Store secondary parameters
    s_mappedParam2 = param2;
    if (s_minValueA < 0x3a) {
        s_minValueA = 0x3a;
    }
    if (s_minValueB < 0x3b) {
        s_mappedParam3 = param3;
        return;
    }
    s_minValueB = 0x3a;
    s_mappedParam3 = param3;
}