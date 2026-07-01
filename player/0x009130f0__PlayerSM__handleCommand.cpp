// FUNC_NAME: PlayerSM::handleCommand
// Address: 0x009130f0
// Dispatches action commands to the current state handler.
// The player has a state index at +0x54 (0=ground, 1=air, 2=cover?, 3=other?).
// param_2 is a command ID: 0 returns 1; 0xc triggers an animation if in ground state.

uint PlayerSM::handleCommand(int commandId) {
    // Check if the command matches a global pause/cutscene state
    if (commandId == FUN_00466840()) { // possibly isPaused or isCutsceneActive
        // Post a specific event (DAT_01130448 is likely an event ID, e.g., "Pause")
        uint eventCode = DAT_01130448;
        int param2 = 0;
        byte param3 = 0;
        FUN_00408a00(&eventCode, 0); // sendEvent? (first param is address of event struct)
    }

    // Check if the command matches a different global state, e.g., "dead"
    if (commandId == FUN_00466860()) { // maybe isDead
        FUN_00957d00(); // maybe handle death transition
        uint eventCode = DAT_01130310;
        int param2 = 0;
        byte param3 = 0;
        FUN_00408a00(&eventCode, 0);
    } else {
        if (commandId == 0) {
            return 1; // command 0 is always accepted
        }
        if (commandId == 0xc) {
            // Command 0xc: if currently in ground state (stateIndex == 0), play animation 8
            if (*(int*)(this + 0x54) == 0) {
                FUN_00922e20(8, 0); // playAnimation(8, false)
            }
        }
    }

    // Dispatch to current state handler
    switch (*(int*)(this + 0x54)) {
    case 0:
        return FUN_009125c0(commandId); // ground state handler
    case 1:
        return FUN_00912670(commandId); // air state handler
    case 2:
        return FUN_00912740(commandId); // cover state handler
    case 3:
        return FUN_00912810(commandId); // wall/cover? state handler
    default:
        return 0;
    }
}