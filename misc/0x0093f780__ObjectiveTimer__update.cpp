// FUNC_NAME: ObjectiveTimer::update
void __thiscall ObjectiveTimer::update(int this) {
    int gameManager = *(int*)0x01129c4c; // g_GameManager (singleton)
    int result; // eax from FUN_0093f4b0
    int callbackData; // local_30
    int callbackArg; // local_1c
    void (*callbackFunc)(int); // local_10
    void (*cleanupFunc)(int); // local_24

    // +0x1c likely a flag indicating objective is active
    if (*(int*)(this + 0x1c) == 0) {
        // Log / reset when objective not active
        logError(&DAT_012069c4); // FUN_004086d0 - likely a message
        if (*(char*)(gameManager + 0x48) == '\0') return;
        if ((*(byte*)(gameManager + 0x5c) & 1) == 0) return;
        startObjective(); // FUN_0093a5c0 - initiate objective?
        return;
    }

    // Objective active path
    if (*(char*)(gameManager + 0x48) == '\0') return;
    if ((*(uint*)(gameManager + 0x5c) >> 10) & 1) return; // Check some specific flag (bit 10)
    if ((*(byte*)(gameManager + 0x5c) & 1) != 0) {
        startObjective();
    }

    // Compute index into a table (0x34 bytes per entry)
    int tableEntry = *(int*)(this + 0x18) * 0x34 + *(int*)(this + 0x10);
    result = getTimerValue(tableEntry); // FUN_0093f4b0

    if (result == 0) {
        *(int*)(this + 0x20) = 0; // +0x20 likely timeRemaining
        initCountdown(&result); // FUN_0093a4a0
    } else {
        char paused = isPaused(0); // FUN_00911f40 - argument 0 usually indicates check without pausing
        if (paused == '\0') goto LAB_0093f851;
        *(int*)(this + 0x20) = 5000; // Set 5 second timer (ms)
        startTimer(&result); // FUN_0090f050
    }

    executeCallbacks(&result); // FUN_0093f400

LAB_0093f851:
    if (callbackArg != 0) {
        callbackFunc(callbackArg);
    }
    if (callbackData != 0) {
        cleanupFunc(callbackData);
    }
}