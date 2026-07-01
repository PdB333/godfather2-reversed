// FUNC_NAME: NPCDefensiveActions::updateDefensiveAction
void __thiscall NPCDefensiveActions::updateDefensiveAction(int this, int deltaTicks)
{
    float randomChance;
    int managerPtr;
    float10 rngFloat;
    undefined4 logArg1;
    undefined4 logArg2;
    undefined1 logArg3;

    // Retrieve a pointer from the defensive manager at offset +0x6c, then offset +0x40 into that manager
    managerPtr = FUN_008c74d0(*(undefined4 *)(*(int *)(this + 0x6c) + 0x40));
    if (managerPtr != 0) {
        if (deltaTicks < 1) goto LAB_00937f48;
        randomChance = *(float *)(managerPtr + 0x100);
        rngFloat = (float10)FUN_008bd490();
        // Random check: if rng * (accumulated time + delta) <= threshold, skip defensive action
        if (rngFloat * (float10)(*(int *)(this + 0x58) + deltaTicks) <= (float10)(int)randomChance)
            goto LAB_00937f48;
    }

    // Check if current cooldown + delta is within max cooldown
    if (*(int *)(this + 0x50) + deltaTicks <= *(int *)(this + 0x54)) {
        // Cooldown not exceeded, perform regular defensive action update?
        FUN_00937e80();
        return;
    }

LAB_00937f48:
    // Cooldown exceeded or random fail: update timer and cooldown
    int newTime = *(int *)(this + 0x50) + deltaTicks;
    if ((-1 < newTime) && (newTime <= *(int *)(this + 0x54))) {
        *(int *)(this + 0x58) = *(int *)(this + 0x58) + deltaTicks;  // Accumulate time
        *(int *)(this + 0x50) = *(int *)(*(int *)(this + 0x6c) + 0x58) + *(int *)(this + 0x58); // Reset cooldown from manager
        FUN_00937920(); // Possibly recalculate internal state
        logArg1 = 0;
        logArg2 = 0;
        logArg3 = 0;
        if (deltaTicks < 1) {
            logArg1 = DAT_011304e8;  // "success" string?
        } else {
            logArg1 = DAT_01130230;  // "failure" string?
        }
        FUN_00408a00(&logArg1, 0); // Log something
        FUN_005a04a0("UpdateDefensiveActions", 0, &DAT_00d8a1e4, 0); // Debug log
        return;
    }

    // Invalid time range, log error
    logArg1 = DAT_01130318; // error string?
    logArg2 = 0;
    logArg3 = 0;
    FUN_00408a00(&logArg1, 0);
    return;
}