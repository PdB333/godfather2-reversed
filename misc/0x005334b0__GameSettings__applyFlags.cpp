// FUNC_NAME: GameSettings::applyFlags
void GameSettings::applyFlags(uint flags) {
    // Store flags in member variable at offset 0x8
    this->flags = flags;

    // Check if bit 7 is set (negative char)
    if ((flags & 0x80) != 0) {
        // High bit set: configure for "high quality" or "special mode"
        g_settingsMode = 4;
        g_settingsParam1 = 0;
        g_settingsParam2 = 0;
        g_settingsParam3 = 2;
        g_settingsParam4 = 0x13;
        g_resourcePtr1 = g_resourcePtrA;
        g_resourcePtr2 = g_resourcePtrB;
        if (g_systemState == &g_systemSentinel) {
            releaseResource(g_resourcePtrB);
            releaseResource(g_resourcePtrA);
        }
    } else if ((flags & 0x10) == 0) {
        // Bit 4 not set: determine sub-mode
        uint subMode;
        if ((flags & 2) == 0) {
            subMode = ~(flags >> 6) & 1; // bit 6 inverted
        } else {
            subMode = 2;
        }
        applySubMode(subMode);
    } else {
        // Bit 4 set: configure for "medium quality" or "other mode"
        g_resourcePtr1 = g_resourcePtrC;
        g_settingsMode = 3;
        g_settingsParam1 = 0;
        g_settingsParam2 = 0;
        g_settingsParam3 = 0;
        g_settingsParam4 = 0x12;
        g_resourcePtr2 = g_resourcePtrD;
        if (g_systemState == &g_systemSentinel) {
            releaseResource(g_resourcePtrD);
            releaseResource(g_resourcePtrC);
        }
    }

    // Apply common settings
    resetSomeState(0);
    updateSomeState();
    updateAnotherState();
    applyBitFlag(flags >> 2 & 2);
    applyTripleParam(1, 5, 6);

    // Enforce minimum/maximum values for two global limits
    if (g_limitLow < 7) g_limitLow = 7;
    if (g_limitHigh > 7) g_limitHigh = 7;
    g_globalFlag1 = 1;

    if (g_limitLow < 0xe) g_limitLow = 0xe;
    if (g_limitHigh > 0xe) g_limitHigh = 0xe;
    g_globalFlag2 = 1;

    // If bit 0 set, call special function with two pointers
    if ((flags & 1) != 0) {
        applySpecialEffect(g_pointerX, g_pointerY);
    }

    if (g_limitLow < 0x19) g_limitLow = 0x19;
    if (g_limitHigh > 0x19) g_limitHigh = 0x19;
    g_globalFlag3 = 5;

    if (g_limitLow < 0x18) g_limitLow = 0x18;
    if (g_limitHigh > 0x18) g_limitHigh = 0x18;
    g_globalFlag4 = 0;

    if (g_limitLow < 0xf) g_limitLow = 0xf;
    if (g_limitHigh > 0xf) g_limitHigh = 0xf;
    g_globalFlag5 = 0;

    // Clear byte at offset 0x4
    this->field_4 = 0;
}