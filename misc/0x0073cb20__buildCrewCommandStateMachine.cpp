// FUNC_NAME: buildCrewCommandStateMachine
void buildCrewCommandStateMachine(void)
{
    // Get or create a new state machine handle
    uint32_t stateMachineId = getNewStateMachineID();

    // Register the top-level state table name
    registerStateTable("crewCommandStateTable", stateMachineId);

    // Set a transition for the "idle" state (DAT_00d63420 likely "idle") to default
    setTransition(&("idle"), 0xFFFFFFFF);

    // Set state flags: state 3, flags 0x4020, no clear?
    setStateFlags(3, 0x4020, 1);

    // Add states with their numerical IDs
    addState("stealthKill", 0x14);
    addState("plantCarBomb", 0x1A);
    addState("csaCommand", 0x13);
    addState("moveToPos", 0x12);
    addState("terminate", 4);

    // Set transition for "moveToPos" to default
    setTransition("moveToPos", 0xFFFFFFFF);

    // Set properties on states 0x24 and 0x30
    setStateProperty(0x24);
    setStateProperty(0x30);
    setStateFlags(0x20, 0, 1);

    // Set initial state for NPCGuardST
    setInitialState("NPCGuardST", 1);

    // Add more states
    addState("forceTeleportCloser", 0x26);
    addState(&("idle"), 0x20); // likely another state named "idle" with different ID? Or a different string.

    // Add transitions with type/flags: moveToPathingFailure, state 6, flags 0x4000, clear? 
    addTransition("moveToPathingFailure", 6, 0x4000, 1);
    addTransition("pathingFailureBlocked", 6, 0x20, 1);

    addState("moveComplete", 1);

    // Set state action on 0x31
    setStateAction(0x31);

    // Remove transition for "moveToPathingFailure"
    setTransition("moveToPathingFailure", 0xFFFFFFFF);

    // Add transition for "moveToPos" with state 0x25, flags 0, clear?
    addTransition("moveToPos", 0x25, 0, 1);

    addState("pathingFailure", 4);
    setStateAction(0x42);
    setTransition("moveComplete", 0xFFFFFFFF);

    setStateProperty(0x28);
    setStateProperty(0x38);

    addState("terminate", 4);
    setTransition("stealthKill", 0xFFFFFFFF);

    setStateProperty(0x24);
    setStateProperty(0x32);
    setInitialState("npcStealthKillST", 1);

    addTransition("pathingFailure", 6, 0x4000, 1);
    addTransition("pathingFailure", 6, 0x20, 1);

    addState("terminate", 1);
    setTransition("plantCarBomb", 0xFFFFFFFF);

    setStateProperty(0x24);
    setStateProperty(0x32);
    setInitialState("npcPlantCarBombST", 1);

    addState("forceTeleportCloser", 0x26);
    addTransition("pathingFailure", 6, 0x4000, 1);
    addTransition("pathingFailureBlocked", 6, 0x20, 1);

    addState("terminate", 1);
    setTransition("csaCommand", 0xFFFFFFFF);

    setStateProperty(0x32);
    setStateProperty(0x33);
    setStateProperty(0x37);

    addState("trackToCSAPosAndDir", 0x1E);
    addState("csaCommandInRange", 0x15);
    addState("moveToCSARange", 0x16);
    addState("pathingFailureEndSM", 0x23);
    addState("terminate", 4);

    setTransition("moveToCSARange", 0xFFFFFFFF);

    addState("stealthMoveToCSARange", 0x22);
    addState("combatMoveToCSARange", 4);

    setTransition("combatMoveToCSARange", 0xFFFFFFFF);

    setStateProperty(0x24);
    setInitialState("CombatPathST", 1);

    addState("forceTeleportCloser", 0x26);
    addState(&("idle"), 0x20);
    addState("trackToCSAPosAndDir", 0x1E);
    addState("csaCommandInRange", 0x15);
    addTransition("pathingFailure", 6, 0x4000, 1);
    addTransition("pathingFailureBlocked", 6, 0x20, 1);

    addState("terminate", 1);
    setStateAction(0x28);
    setTransition("stealthMoveToCSARange", 0xFFFFFFFF);

    setStateProperty(0x24);
    setInitialState("FollowPathST", 1);

    addState("forceTeleportCloser", 0x26);
    addState(&("idle"), 0x20);
    addState("trackToCSAPosAndDir", 0x1E);
    addState("csaCommandInRange", 0x15);
    addTransition("pathingFailure", 6, 0x4000, 1);
    addTransition("pathingFailureBlocked", 6, 0x20, 1);

    addState("pathingFailureEndSM", 0x23);
    addState("terminate", 1);
    setStateAction(0x28);
    setTransition("trackToCSAPosAndDir", 0xFFFFFFFF);

    setInitialState("trackToPositionAndDirectionStateTable", 0);

    addState("csaCommandInRange", 1);
    addState("pathingFailureEndSM", 0x23);
    setTransition("csaCommandInRange", 0xFFFFFFFF);

    setStateProperty(0x2B);
    setStateProperty(0x29);
    setStateProperty(0x34);
    setStateProperty(0x3B);
    setStateProperty(0x3F);
    setStateFlag(0x3F); // toggle flag

    addState("csaLoop", 0x1C);
    addState("csaLoop", 7);
    addState("pathingFailureEndSM", 0x23);
    setTransition("csaLoop", 0xFFFFFFFF);

    setStateProperty(0x3C);
    setStateProperty(0x27);
    setStateProperty(0x35);
    setStateProperty(0x3F);
    setStateFlag(0x3F);
    setStateFlag(0x23);

    addState("csaLockPick", 0x1B);
    addState("csaExplosive", 0x19);
    addState("csaSuccess", 0x17);
    addState("csaSuccess", 0x18);
    addState("pathingFailureEndSM", 0x23);
    setTransition("csaLockPick", 0xFFFFFFFF);

    setStateProperty(0x38);
    setStateProperty(0x2A);
    setStateProperty(0x36);
    setStateProperty(0x3F);
    setStateFlag(0x3F);
    setStateFlag(0x2F);
    setStateFlag(0x43);

    setStateAction(0x2E);
    setStateAction(0x3E);
    setStateAction(0x2D);

    addState("pathingFailureEndSM", 0x23);
    addState("terminate", 0x1D);
    addState("terminate", 7);
    setTransition("csaExplosive", 0xFFFFFFFF);

    setStateProperty(0x38);
    setStateProperty(0x2A);
    setStateProperty(0x36);
    setStateProperty(0x3F);
    setStateFlag(0x3F);
    setStateFlag(0x45);
    setStateFlag(0x43);
    setStateAction(0x45);
    setStateAction(0x3E);
    setStateAction(0x2D);

    addState("pathingFailureEndSM", 0x23);
    addState("terminate", 0x1D);
    addState("terminate", 7);
    setTransition("csaSuccess", 0xFFFFFFFF);

    setStateProperty(0x38);
    setStateProperty(0x2A);
    setStateProperty(0x36);
    setStateProperty(0x3F);
    setStateFlag(0x3F);
    setStateFlag(0x43);

    addState("pathingFailureEndSM", 0x23);
    addState("terminate", 0x1D);
    addState("terminate", 7);
    setStateAction(0x2D);
    setStateAction(0x3E);
    setTransition("pathingFailure", 0xFFFFFFFF);

    setStateProperty(0x3A);
    setStateProperty(0x44);
    addState(&("idle"), 0x1F);
    addState("pathingFailurePrepareToTerminate", 4);
    setTransition("pathingFailurePrepareToTerminate", 0xFFFFFFFF);

    setStateProperty(0x46);
    addState("terminate", 4);
    setTransition("pathingFailureEndSM", 0xFFFFFFFF);

    setStateProperty(0x38);
    setStateProperty(0x40);
    addState("terminate", 4);
    setTransition("pathingFailureBlocked", 0xFFFFFFFF);

    setStateProperty(0x26);
    setStateProperty(0x3A);
    addState(&("idle"), 0x1F);
    addTransition("forceTeleportCloser", 0x24, 3, 1);
    addTransitionTimeout(&("idle"), 2, 1.0f, 1); // timeout transition

    setStateAction(0x42);
    setTransition("forceTeleportCloser", 0xFFFFFFFF);

    setStateProperty(0x41);
    addState(&("idle"), 0x1F);
    addState("terminate", 4);
    setTransition(&("idle"), 0xFFFFFFFF); // unclear: likely the string at 0x00d63630

    setStateProperty(0x26);
    addState(&("idle"), 0x21);
    addState("pathingFailureEndSM", 0x23);
    setStateAction(0x25);
    setTransition("terminate", 0xFFFFFFFF);

    setStateProperty(0x3D);
    setStateProperty(2);

    // Register the state machine with an ID and name
    registerStateMachine(0x8AEB8C80, &callbackFunction, "CrewCommandStateMachine");

    // Finalize state machine construction
    finalizeStateMachine();
}