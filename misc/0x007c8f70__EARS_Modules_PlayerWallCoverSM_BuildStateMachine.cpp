// Xbox PDB: EARS_Modules_PlayerWallCoverSM_BuildStateMachine
// FUNC_NAME: PlayerWallCoverSM::buildStateMachine
void PlayerWallCoverSM::buildStateMachine(void)
{
    // Get the state machine table pointer (likely from a global or singleton)
    void* stateMachineTable = getStateMachineTable(); // FUN_009c8f80

    // Register the state table with a name
    registerStateTable("playerWallCoverStateTable", stateMachineTable); // FUN_004ad9d0

    // Remove any existing state with ID -1 (clear)
    removeState(&DAT_00d63420, 0xffffffff); // FUN_004adae0

    // Add states (IDs are likely enum values)
    addState(0x54); // FUN_004acf70
    addState(0x52);
    addTransition("cornerCheck", 3); // FUN_004acc70
    removeState("cornerCheck", 0xffffffff);
    addState(0x39);
    addTransition("enterAtCorner", 0x16);
    addTransition("enter", 4);
    setInitialState(0x33); // FUN_004ad070
    removeState("enter", 0xffffffff);
    addState(0x43);
    addTransitionWithCondition(0x34, 1, 1); // FUN_004ad0f0
    addState(0x3f);
    setSubStateMachine("trackToPositionAndDirectionStateTable", 0); // FUN_004acf10
    addTransition(&DAT_00d64b74, 1);
    addTransition(&DAT_00d63ba4, 0x13);
    setTransitionCondition(0x34, 0, 1); // FUN_004ad170
    setInitialState(0x51);
    removeState("enterAtCorner", 0xffffffff);
    addState(0x43);
    addTransitionWithCondition(0x35, 1, 1);
    addTransitionWithCondition(0x3a, 1, 1);
    addState(0x3f);
    setSubStateMachine("trackToPositionAndDirectionStateTable", 1);
    addTransition("cornerIdle", 1);
    addTransition(&DAT_00d63ba4, 0x13);
    setTransitionCondition(0x35, 0, 1);
    setInitialState(0x51);
    removeState(&DAT_00d64b74, 0xffffffff);
    addState(0x44);
    addStateFlag(0x31); // FUN_004acff0
    addStateFlag(0x45);
    addStateFlag(0x59);
    addTransition(&DAT_00d63ba4, 0x13);
    addTransition("lockToCorner", 0x16);
    addTransition("starting", 0x14);
    addTransition("shootEnter", 0x19);
    addTransition("throwItem", 0x1a);
    removeState("starting", 0xffffffff);
    addState(0x31);
    addTransitionWithCondition(0x3a, 0, 1);
    addState(0x46);
    addStateFlag(0x31);
    addStateFlag(0x50);
    addStateFlag(0x59);
    addTransition(&DAT_00d63ba4, 0x13);
    addTransition("lockToCorner", 0x16);
    addTransition("lockToBoundary", 0x17);
    addTransitionWithPriority(&DAT_00d6e9d8, 2, DAT_00d58cbc, 1); // FUN_004acd80
    removeState(&DAT_00d6e9d8, 0xffffffff);
    addStateFlag(0x48);
    addStateFlag(0x31);
    addStateFlag(0x50);
    addStateFlag(0x59);
    addState(0x5a);
    setInitialState(0x5b);
    addTransition(&DAT_00d63ba4, 0x13);
    addTransition("lockToCorner", 0x16);
    addTransition("lockToBoundary", 0x17);
    addTransition("stopping", 0x15);
    removeState("stopping", 0xffffffff);
    addState(0x47);
    addStateFlag(0x31);
    addStateFlag(0x50);
    addStateFlag(0x59);
    addTransition(&DAT_00d63ba4, 0x13);
    addTransition("lockToCorner", 0x16);
    addTransition("lockToBoundary", 0x17);
    addTransition("starting", 0x14);
    addTransitionWithPriority(&DAT_00d64b74, 2, DAT_00d58cbc, 1);
    removeState("lockToBoundary", 0xffffffff);
    addState(0x47);
    addTransitionWithCondition(0x3e, 1, 1);
    addStateFlag(0x59);
    setSubStateMachine("trackToPositionAndDirectionStateTable", 1);
    addTransition("boundaryIdle", 1);
    addTransition(&DAT_00d63ba4, 0x13);
    removeState("boundaryIdle", 0xffffffff);
    addStateFlag(0x31);
    addStateFlag(0x59);
    addTransition(&DAT_00d63ba4, 0x13);
    addTransition("starting", 0x14);
    addTransition("lockToCorner", 0x16);
    setTransitionCondition(0x3e, 0, 1);
    removeState("lockToCorner", 0xffffffff);
    addState(0x47);
    addTransitionWithCondition(0x3a, 1, 1);
    addStateFlag(0x59);
    setSubStateMachine("trackToPositionAndDirectionStateTable", 1);
    addTransition("cornerIdle", 1);
    addTransition(&DAT_00d63ba4, 0x13);
    removeState("cornerIdle", 0xffffffff);
    addState(0x44);
    addState(0x58);
    addState(0x53);
    setInitialState(0x54);
    setSubStateMachine("trackToPositionAndDirectionStateTable", 1);
    addStateFlag(0x32);
    addStateFlag(0x38);
    addStateFlag(0x59);
    addStateFlag(0x45);
    addStateFlag(0x40);
    addStateFlag(0x5c);
    addTransition(&DAT_00d63ba4, 0x13);
    addTransition("throwItem", 0x1d);
    addTransition("shootEnter", 0x18);
    addTransition("starting", 0x14);
    removeState("throwItem", 0xffffffff);
    addState(0x55);
    addState(0x56);
    addTransitionWithCondition(0x3b, 1, 1);
    addStateFlag(8);
    addStateFlag(0x5c);
    setInitialState(0x57);
    setTransitionCondition(0x3b, 0, 1);
    addTransition("cornerIdle", 7);
    removeState("shootEnter", 0xffffffff);
    addTransitionWithCondition(0x37, 1, 1);
    addTransitionWithCondition(0x3b, 1, 1);
    addState(0x49);
    setSubStateMachine("trackToPositionAndDirectionStateTable", 1);
    addStateFlag(0x4a);
    addStateFlag(0x5c);
    addTransition("shoot", 1);
    addTransition("shootExit", 0x1c);
    addTransition("exitFromCornerShoot", 0x13);
    setTransitionCondition(0x37, 0, 1);
    removeState("shoot", 0xffffffff);
    addState(0x4b);
    addTransitionWithCondition(0x3c, 1, 1);
    addStateFlag(8);
    addStateFlag(0x4d);
    addStateFlag(0x4c);
    addStateFlag(0x5c);
    setTransitionCondition(0x3c, 0, 1);
    addTransition("shoot", 0x1b);
    addTransition("shootExit", 0x1c);
    addTransition("exitFromCornerShoot", 0x13);
    removeState("shootExit", 0xffffffff);
    addStateFlag(0x5c);
    addTransition("shootExitToCorner", 4);
    removeState("shootExitToCorner", 0xffffffff);
    addTransitionWithCondition(0x36, 1, 1);
    addState(0x4e);
    setSubStateMachine("trackToPositionAndDirectionStateTable", 1);
    addStateFlag(0x5c);
    addTransition("cornerIdle", 1);
    addTransition("exitFromCornerShoot", 0x13);
    setTransitionCondition(0x36, 0, 1);
    setTransitionCondition(0x3b, 0, 1);
    removeState("exitFromCornerShoot", 0xffffffff);
    addState(0x4f);
    addTransition("terminate", 0x1e);
    removeState(&DAT_00d63ba4, 0xffffffff);
    addState(0x4f);
    addTransition("terminate", 4);
    removeState("terminate", 0xffffffff);
    addState(2);
    registerStateMachine(0xda3329f2, &LAB_007c8d40, "PlayerWallCoverSM"); // FUN_004adc90
    finalizeStateMachine(); // FUN_004ada40
    return;
}