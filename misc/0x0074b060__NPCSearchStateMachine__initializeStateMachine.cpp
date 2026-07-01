// FUNC_NAME: NPCSearchStateMachine::initializeStateMachine
void NPCSearchStateMachine::initializeStateMachine() {
    // Allocate state machine ID
    int stateMachineId = getStateMachineManager();

    // Create state machine "NPCSearchST"
    createStateMachine("NPCSearchST", stateMachineId);

    // Set initial state (likely invalid)
    setInitialState(&DAT_00d63420, 0xffffffff); // +0x?  (global context)

    // Define states with IDs
    addState("searchFailure", 0x17);
    addState("initSearch", 4);
    setInitialState("initSearch", 0xffffffff);
    addStateAction(0x26); // Unknown action

    addState("PreIsSearchComplete", 0x16);
    addState("startSearch", 4);
    setInitialState("startSearch", 0xffffffff);
    addStateAction(0x23);
    addStateAction(0x29);

    addState("JustTurn", 0x12);
    addState("BeginSearch", 4);
    setInitialState("JustTurn", 0xffffffff);
    addStateAction(0x23);
    addTransitionTable("turnToPositionTerminateTable", 1);

    addState("PreIsSearchComplete", 0x16);
    addState("BeginSearch", 0x13);
    addState("PreIsSearchComplete", 0x14);
    addState("PreIsSearchComplete", 1);
    setInitialState("BeginSearch", 0xffffffff);
    addTransition(3, 0x20, 1);
    addStateAction(0x24);
    setStateEntryAction(0x23);

    addState("JustTurn", 0x12);
    addState("PreIsSearchComplete", 1);
    addTimedTransition("PreIsSearchComplete", 6, 0x20, 1);
    addTransitionWithFlags(4, 0x20, 1);
    setInitialState("PreIsSearchComplete", 0xffffffff);
    addStateAction(0x25);
    addStateAction(0x28);

    addState("IsSearchComplete", 7);
    setInitialState("IsSearchComplete", 0xffffffff);
    addState("RandomSearchWalk", 0x15);
    addState("UpdateSearchPos", 4);
    setInitialState("UpdateSearchPos", 0xffffffff);
    addStateAction(0x27);

    addState("PreIsSearchComplete", 0x16);
    addState("startSearch", 4);
    setInitialState("RandomSearchWalk", 0xffffffff);
    addTransitionTable("RandomSearchST", 1);
    addState("Terminate", 1);
    setInitialState("searchFailure", 0xffffffff);
    addTransition(6, 0x40000, 1);
    addState("Terminate", 4);
    setInitialState("Terminate", 0xffffffff);
    addStateAction(2);

    // Finalize state machine with hash and entry point label
    finalizeStateMachine(0xe653ff63, &LAB_0074aad0, "NPCSearchSM");
    returnStateMachineHandle();
}