// FUNC_NAME: clampGlobalsAndStoreParameter
void clampGlobalsAndStoreParameter(uint8 paramValue)
{
    // Clamp global state 1 to a maximum of 7
    if (g_stateLimit1 < 7) {
        g_stateLimit1 = 7;
    }

    // Clamp global state 2 to a maximum of 7 and store parameter
    if (7 < g_stateLimit2) {
        g_stateLimit2 = 7;
        g_storedParam = (uint32)paramValue;
        return;
    }

    // Store parameter regardless
    g_storedParam = (uint32)paramValue;
    return;
}