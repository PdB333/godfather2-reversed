// FUNC_NAME: NPCStateMachineBuilder::buildFleeStateMachine
void NPCStateMachineBuilder::buildFleeStateMachine()
{
    unsigned int fleeStateId = generateStateId(); // FUN_009c8f80 – get a unique ID for the state

    // Register the main "NPCFleeST" state
    registerState("NPCFleeST", fleeStateId); // FUN_004ad9d0

    // Set default transition (0xFFFFFFFF = -1 means error/default?)
    setTransition("NPCFleeST", 0xFFFFFFFF); // FUN_004adae0

    // Configure state 3 with a flag
    setStateFlag(3, 0x20, 1); // FUN_004ad0f0 – state 3, flag 0x20 (maybe "active" or "valid"), enable

    // Set state enter actions
    setStateEnterAction(0x25); // FUN_004acf70 – action ID 0x25 (maybe "enterFlee")
    setStateEnterAction(0xC);  // FUN_004acf70 – action ID 0xC (maybe "enterFleeSetup")

    // Configure state 0x21 with a flag (0xE30449ED appears to be a hash or bitmask)
    setStateFlag(0x21, 0xE30449ED, 1); // FUN_004ad0f0

    // Add event transitions from "FleeFailed"
    addEventTransition("FleeFailed", 0x12);           // FUN_004acc70 – event ID 0x12
    addEventTransition("FleeFailed", 0x14);           // FUN_004acc70 – event ID 0x14 (DAT_00d65484 => "FleeFailed")
    addEventTransition("pathToGraph", 4);             // FUN_004acc70 – event ID 4

    // Set default transition for "pathToGraph" state
    setTransition("pathToGraph", 0xFFFFFFFF);         // FUN_004adae0

    // Transition to "FollowPathST" with condition flag 1
    setConditionalTransition("FollowPathST", 1);      // FUN_004acf10

    // More event transitions from "FleeFailed"
    addEventTransition("FleeFailed", 0x13);           // FUN_004acc70
    addEventTransition("FleeFailed", 0x12);           // Again
    addEventTransition("Terminate", 0x17);            // FUN_004acc70
    addEventTransition("FleeFailed", 0x18);           // FUN_004acc70 (DAT_00d65484)
    addEventTransition("FleeFailed", 1);              // FUN_004acc70

    // Set default transition for "FleeFailed"
    setTransition("FleeFailed", 0xFFFFFFFF);          // FUN_004adae0

    // Set state enter actions for additional states
    setStateEnterAction(0x23);                        // FUN_004acf70
    setStateExitAction(0x26);                         // FUN_004acff0

    // Transition to "OnGraphPathingST" with condition flag 1
    setConditionalTransition("OnGraphPathingST", 1);  // FUN_004acf10

    // More event transitions
    addEventTransition("FleeFailed", 0x15);           // FUN_004acc70
    addEventTransition("Terminate", 0x17);            // FUN_004acc70
    addEventTransition("FleeFailed", 0x16);           // FUN_004acc70
    addEventTransition("FleeFailed", 0x13);           // FUN_004acc70
    addEventTransition("FleeFailed", 1);              // FUN_004acc70

    // Default transition for "FleeFailed" again
    setTransition("FleeFailed", 0xFFFFFFFF);          // FUN_004adae0

    // Set enter action for state 0x24
    setStateEnterAction(0x24);                        // FUN_004acf70

    // Event transitions for "Terminate"
    addEventTransition("Terminate", 4);               // FUN_004acc70

    // Set default transition for "Terminate"
    setTransition("Terminate", 0xFFFFFFFF);           // FUN_004adae0

    // Set enter action for state 2
    setStateEnterAction(2);                           // FUN_004acf70

    // Finalize the state machine with a unique identifier and label
    finalizeStateMachine(0xEA2E0D61, &label_NPCFleeSM, "NPCFleeSM"); // FUN_004adc90

    returnToInitialState(); // FUN_004ada40 – reset to initial state
}