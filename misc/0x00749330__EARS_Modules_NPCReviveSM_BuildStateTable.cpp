// Xbox PDB: EARS::Modules::NPCReviveSM::BuildStateTable
// FUNC_NAME: NPCReviveSM::buildStateMachine
void NPCReviveSM::buildStateMachine()
{
    // Get an identifier for the state table (likely a hash or handle)
    int stateTableHandle = getOrCreateStateTable("NPCReviveST");

    // Register the initial state table
    registerStateTable("NPCReviveST", stateTableHandle);

    // Set default transition for a global table (DAT_00d63420) to -1 (no transition)
    removeAllTransitions(&DAT_00d63420);

    // Add state IDs (0x0E, 0x14, 0x0D, etc.) as defaults
    addDefaultState(0xF);
    addState("moveToTarget", 10);          // wait state
    removeAllTransitions("moveToTarget");   // clear transitions for this state
    addTransition(5, 0x4020, 1);           // from state 5 to state 0x4020 with flag 1
    addDefaultState(0xE);
    addDefaultState(0x14);
    addState("teleportCloser", 0xD);
    addStateWithTransition("moveFailed", 6, 0x20, 1);
    setInitialState("NPCChaseST", 1);
    addState("preRevive", 10);
    addState("preRevive", 0xB);
    addState("preRevive", 1);
    removeAllTransitions("moveFailed");
    addState("teleportCloser", 0xF);
    addState("moveToTargetWait", 4);
    removeAllTransitions("moveToTargetWait");
    addDefaultState(0xD);
    addStateWithFloat("moveToTarget", 2, 0x3F800000, 1); // 1.0f
    removeAllTransitions("teleportCloser");
    addDefaultState(0x10);
    addState("preRevive", 0xE);
    addState("waitingForTeleportSuccess", 0x10);
    addState("waitingForTeleportSuccess", 4);
    removeAllTransitions("waitingForTeleportSuccess");
    addDefaultState(0xD);
    addState("moveToTarget", 0x11);
    addStateWithFloat("moveToTarget", 2, DAT_00d642a4, 1); // global float
    addTimer(0x19);
    removeAllTransitions("preRevive");
    addState("revive", 0xB);
    addState("revive", 1);
    removeAllTransitions("revive");
    addDefaultState(10);
    setInitialState("trackToPositionAndDirectionStateTable", 1);
    addState("reviveLoop", 10);
    addState("reviveLoop", 7);
    addDefaultState(0xB);
    removeAllTransitions("reviveLoop");
    addDefaultState(0x12);
    addDefaultState(0x16);
    enableFlag(8);
    enableFlag(0x17);
    addState("reviveEnd", 10);
    addState("reviveEnd", 0xC);
    addTimer(0x11);
    removeAllTransitions("reviveEnd");
    addDefaultState(0x13);
    addDefaultState(0x15);
    addDefaultState(0x18);
    enableFlag(8);
    addState("reviveEnd", 7);
    removeAllTransitions("reviveEnd");
    addDefaultState(2);

    // Finalize: register the state machine with its vtable/function table at 0x00749210
    registerStateMachine(0x241E4070, &LAB_00749210, "NPCReviveSM");

    // Finalize the building process
    finalizeStateMachine();
}