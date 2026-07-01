// Xbox PDB: EARS::Modules::NPCRandomSearchSM::BuildStateTable
// FUNC_NAME: NPCRandomSearchSM::buildStateMachine
void NPCRandomSearchSM::buildStateMachine(void)
{
    // Register the "RandomSearchST" state (state machine type?) and get an ID/handle
    uint32_t stateHandle = registerState("RandomSearchST", 0);  // FUN_004ad9d0 called with result of FUN_009c8f80()

    // Set the initial state or transition to the random search state
    addTransition(stateHandle, -1);  // FUN_004adae0(&DAT_00d63420, 0xffffffff)

    // Push a state action (likely enter action) with ID 0x26
    pushStateAction(0x26);  // FUN_004acf70(0x26)

    // Add a state named "searchRandom" with priority 4
    addState("searchRandom", 4);  // FUN_004acc70("searchRandom", 4)

    // Transition from searchRandom back to the state machine root or forward
    addTransition("searchRandom", -1);  // FUN_004adae0("searchRandom", 0xffffffff)

    // Push another state action with ID 0x28
    pushStateAction(0x28);  // FUN_004acf70(0x28)

    // Set a transition condition (from state 3 to state 0x20 with condition 1)
    setTransitionCondition(3, 0x20, 1);  // FUN_004ad0f0(3, 0x20, 1)

    // Push state action with ID 0x24
    pushStateAction(0x24);  // FUN_004acf70(0x24)

    // Add a state with a name from a global string (likely "doneNoEnemySighted") and priority 0x15
    addState("doneNoEnemySighted", 0x15);  // FUN_004acc70(&DAT_00d63afc, 0x15)

    // Add a transition from this state (index 6) to state 0x20 with condition 1
    addStateTransition("doneNoEnemySighted", 6, 0x20, 1);  // FUN_004acd20(&DAT_00d63afc, 6, 0x20, 1)

    // Set an exit action for a state with ID 0x2a
    setStateExitAction(0x2a);  // FUN_004ad070(0x2a)

    // Transition from doneNoEnemySighted to root
    addTransition("doneNoEnemySighted", -1);  // FUN_004adae0(&DAT_00d63afc, 0xffffffff)

    // Push state action with ID 0x25
    pushStateAction(0x25);  // FUN_004acf70(0x25)

    // Set a state enter action with count 8
    setStateEnterAction(8);  // FUN_004acff0(8)

    // Add state "endSearch" with priority 7
    addState("endSearch", 7);  // FUN_004acc70("endSearch", 7)

    // Transition from endSearch to root (exit doneNoEnemySighted)
    addTransition("doneNoEnemySighted", -1);  // FUN_004adae0("doneNoEnemySighted", 0xffffffff)

    // Push state action with ID 0x25 again
    pushStateAction(0x25);  // FUN_004acf70(0x25)

    // Set another enter action with count 8
    setStateEnterAction(8);  // FUN_004acff0(8)

    // Add state "searchRandom" with priority 7 (reuse name? might be a different instance)
    addState("searchRandom", 7);  // FUN_004acc70("searchRandom", 7)

    // Transition from endSearch to root (now exiting endSearch)
    addTransition("endSearch", -1);  // FUN_004adae0("endSearch", 0xffffffff)

    // Push a state action with ID 2 (likely final transition or cleanup)
    pushStateAction(2);  // FUN_004acf70(2)

    // Register the entire state machine with name "NPCRandomSearchSM" and starting code address LAB_0074a1a0
    registerStateMachine(0xcf840186, (void*)0x0074a1a0, "NPCRandomSearchSM");  // FUN_004adc90(0xcf840186, LAB_0074a1a0, "NPCRandomSearchSM")

    // Finalize/commit the state machine definition
    commitStateMachine();  // FUN_004ada40()
}