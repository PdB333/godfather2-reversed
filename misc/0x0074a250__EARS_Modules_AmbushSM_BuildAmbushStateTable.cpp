// Xbox PDB: EARS::Modules::AmbushSM::BuildAmbushStateTable
// FUNC_NAME: AmbushStateMachine::initializeAmbushStates
void AmbushStateMachine::initializeAmbushStates() {
    // Get some identifier (likely a behavior ID or state machine handle)
    int behaviorID = getBehaviorID();  // FUN_009c8f80
    
    // Register initial state transition for "AmbushST" state
    registerStateTransition("AmbushST", behaviorID);  // FUN_004ad9d0
    
    // Set "ambushCover" state to have an infinite timeout (-1)
    setStateTimeout(&DAT_00d63420, -1);  // FUN_004adae0, DAT_00d63420 likely "ambushCover" string
    
    // Add actions to the state machine
    addStateAction("ambushCover", 0x12);   // FUN_004acc70: action ID 0x12 (maybe "take cover"?)
    addStateAction("ambushStand", 4);      // action ID 4 (maybe "stand and fire"?)
    
    // Set "ambushCover" timeout back to infinite (overwrites previous?)
    setStateTimeout("ambushCover", -1);    // FUN_004adae0
    
    // Set default/global state to 0x23 (maybe "idle" or "alert")
    setDefaultState(0x23);                 // FUN_004acff0
    
    // Register transition "CoverST" to state 1
    registerStateTransition("CoverST", 1); // FUN_004acf10
    
    // Add actions to some default state (DAT_00d63afc likely a string like "ambushDefault")
    addStateAction(&DAT_00d63afc, 1);      // action ID 1
    addStateAction(&DAT_00d63afc, 0x13);   // action ID 0x13
    
    // Reset "ambushStand" timeout to infinite
    setStateTimeout("ambushStand", -1);    // FUN_004adae0
    
    // Set default state back to 0x23
    setDefaultState(0x23);                 // FUN_004acff0
    
    // More actions on default state
    addStateAction(&DAT_00d63afc, 1);      // action 1
    addStateAction(&DAT_00d63afc, 0x14);   // action 0x14
    
    // Add action to "ambushCover" state (action 0x12 again)
    addStateAction("ambushCover", 0x12);   // FUN_004acc70
    
    // Set timeout of default state to infinite
    setStateTimeout(&DAT_00d63afc, -1);    // FUN_004adae0
    
    // Set number of simultaneous transitions to 2
    setNumTransitions(2);                  // FUN_004acf70
    
    // Register the entire state machine with a name and a handler function
    // 0x9c39bace is likely a hash of "AmbushSM" (maybe for fast lookup)
    // &LAB_0074a160 is the pointer to the state machine's main loop function
    registerStateMachine(0x9c39bace, &LAB_0074a160, "AmbushSM"); // FUN_004adc90
    
    // Finalize/commit the state machine configuration
    finalizeStateMachine();                // FUN_004ada40
}