// FUNC_NAME: createNpcInformStateMachine
// Address: 0x00747630
// Builds the NPCInformSM finite state machine (FSM) used for NPC inform behaviors.
void createNpcInformStateMachine(void) {
    // Obtain the runtime handle for building state machines
    int smContext = getStateMachineContext(); // FUN_009c8f80

    // --- Register initial state ---
    // Register the state named "NPCInformST" (INFORM STATE?) in the context
    stateMachineRegisterState("NPCInformST", smContext); // FUN_004ad9d0

    // Set transition from DAT_00d63420 state to invalid (0xFFFFFFFF = no transition)
    stateMachineSetTransition(&DAT_00d63420, 0xFFFFFFFF); // FUN_004adae0

    // Define entry action for state index 10 (0xA)
    stateMachineSetStateEntryAction(10); // FUN_004acf70

    // --- Define states ---
    // Add "terminate" state with ID 0xB
    stateMachineAddState("terminate", 0xB); // FUN_004acc70
    // Add "approach" state with ID 4
    stateMachineAddState("approach", 4); // FUN_004acc70

    // Set "approach" state to have no outgoing transition
    stateMachineSetTransition("approach", 0xFFFFFFFF); // FUN_004adae0

    // Add "NPCChaseST" state with a flag (1 = active entry?)
    stateMachineAddState("NPCChaseST", 1); // FUN_004acf10

    // Add states from global data string at DAT_00d64070 with IDs 10 and 1
    stateMachineAddState(&DAT_00d64070, 10); // FUN_004acc70
    stateMachineAddState(&DAT_00d64070, 1); // FUN_004acc70

    // Set no outgoing transition for DAT_00d64070 state
    stateMachineSetTransition(&DAT_00d64070, 0xFFFFFFFF); // FUN_004adae0

    // Set entry action for state index 0xC
    stateMachineSetStateEntryAction(0xC); // FUN_004acf70

    // Add "turnToPositionTerminateTable" state with flag 1
    stateMachineAddState("turnToPositionTerminateTable", 1); // FUN_004acf10

    // Set entry action for state index 8
    stateMachineSetStateEntryAction(8); // FUN_004acf70
    // Set exit action for state index 8
    stateMachineSetStateExitAction(8); // FUN_004acff0

    // Add "inform" state with ID 1
    stateMachineAddState("inform", 1); // FUN_004acc70

    // Set no outgoing transition for "inform"
    stateMachineSetTransition("inform", 0xFFFFFFFF); // FUN_004adae0

    // Set entry action for state index 0xB
    stateMachineSetStateEntryAction(0xB); // FUN_004acf70

    // Set state timer (duration?) for state index 0xD
    stateMachineSetStateTimer(0xD); // FUN_004ad070

    // Set entry action for state index 8
    stateMachineSetStateEntryAction(8); // FUN_004acf70
    // Set exit action for state index 8
    stateMachineSetStateExitAction(8); // FUN_004acff0

    // Add "terminate" state with ID 7
    stateMachineAddState("terminate", 7); // FUN_004acc70

    // Set no outgoing transition for "terminate"
    stateMachineSetTransition("terminate", 0xFFFFFFFF); // FUN_004adae0

    // Set entry action for state index 2
    stateMachineSetStateEntryAction(2); // FUN_004acf70

    // --- Finalize and register the state machine ---
    // Register the NPCInformSM state machine:
    // Arguments: hashed ID (0x6e9ac264 = hash of "NPCInformSM"?),
    //            callback function pointer (LAB_007475f0 - state machine update function),
    //            state machine name string
    registerStateMachine(0x6e9ac264, &LAB_007475f0, "NPCInformSM"); // FUN_004adc90

    // Initialize/activate the state machine
    stateMachineFinalize(); // FUN_004ada40
}