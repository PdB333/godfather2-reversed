// Xbox PDB: EARS_Modules_PlayerHoldThrowSM_BuildStateMachine
// FUNC_NAME: PlayerHoldThrowSM::buildStateMachine
void PlayerHoldThrowSM::buildStateMachine(void)
{
    // Get the state machine table manager
    void* tableMgr = getStateMachineTableManager();

    // Create a new state table named "playerHoldThrowStateTable"
    createStateTable("playerHoldThrowStateTable", tableMgr);

    // Add transition: from all states (-1) to state "activate" on event "activate"
    addTransition("activate", 0xffffffff);

    // State 0x16 (hold?) with animation group 0x3e and entry action id 1
    addState(0x16, 0x3e, 1);
    addEntryAction(0x18);
    addUpdateAction(0x34);
    addEntryAction(0x1b);
    addEntryAction(0x35);

    // Sub-state machine "trackToPositionAndDirectionStateTable" with initial state 0
    setSubStateMachine("trackToPositionAndDirectionStateTable", 0);

    // Transition from state 0x13 on "terminate"
    addTransition("terminate", 0x13);
    // Transition from state 1 on string at DAT_00d6e3b4 (likely "activate" or similar)
    addTransition(&DAT_00d6e3b4, 1);
    // Transition from all states on same string
    addTransition(&DAT_00d6e3b4, 0xffffffff);

    // State 0x16 with animation group 0x3f and entry action 1
    addState(0x16, 0x3f, 1);
    addEntryAction(0x18);
    addExitAction(0x1b);
    addEntryAction(0x3c);
    addExitAction(0x3b);
    addEntryAction(0x37);
    addExitAction(0x38);
    addUpdateAction(0x39);
    addEntryAction(0x31);
    addUpdateAction(0x32);

    // Transitions from state 0x13 on "terminate", from 0x15 on "throw", from 0x16 on "release"
    addTransition("terminate", 0x13);
    addTransition("throw", 0x15);
    addTransition("release", 0x16);
    addTransition("release", 0xffffffff);

    // State 0x16 with anim 0x41 and entry 1
    addState(0x16, 0x41, 1);
    addEntryAction(0x18);
    addExitAction(0x1b);
    addTransition("terminate", 0x13);
    addTransition("terminate", 7);
    addTransition("throw", 0xffffffff);

    // State 0x16 with anim 0x42 and entry 1
    addState(0x16, 0x42, 1);
    addState(0x3a, 0, 1);
    addEntryAction(0x18);
    addEntryAction(0x36);
    addEntryAction(0x28);
    addEntryAction(0x3f);
    addEntryAction(0x40);
    setStateProperty(0x3a, 1, 1);  // likely enables something on state 0x3a

    addTransition("terminate", 0x13);
    addTransition("throwreturn", 0x17);
    addTransition("throwreturn", 7);
    addTransition("throwreturn", 0xffffffff);

    addState(0x3d, 0, 1);
    addEntryAction(0x3e);
    addEntryAction(0x33);
    addTransition("terminate", 7);
    addTransition("terminate", 0xffffffff);
    addEntryAction(0x27);
    addEntryAction(2);

    // Register the state machine with a unique hash and a reference to the function that continues setup
    registerStateMachine(0x99b244e, &LAB_007c1430, "PlayerHoldThrowSM");

    // Finalize
    finalizeStateMachine();
}