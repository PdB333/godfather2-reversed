// Xbox PDB: EARS_Modules_PlayerTargetingSM_BuildStateMachine
// FUNC_NAME: PlayerTargetingSM::buildStateMachine

void PlayerTargetingSM::buildStateMachine()
{
    // Get or create the player targeting state table
    uint32_t tableHandle = getStateTableByName("playerTargetingStateTable");
    int32_t tableExists = checkTableExists(tableHandle);

    if (tableExists == 0) {
        // Create new state table
        uint32_t newTable = createNewStateTable();
        assignStateTableName("playerTargetingStateTable", newTable);

        // --- State: noTarget (ID: 0xffffffff = -1) ---
        setStartState("noTarget", -1);              // Initial state
        addState(0x1e);                              // State 30
        addState(0x31);                              // State 49
        addStateWithName("disabled", 0x13);          // State 19
        addStateWithName("noTargetFreeAim", 0x15);   // State 21
        setStartState("noTargetFreeAim", -1);        // Another start state? (Maybe override)
        addTransition(0x38);                         // Transition 56
        addState(0x1e);                              // State 30 (duplicate? maybe condition)
        addState(0x31);                              // State 49
        addState(0x3c);                              // State 60
        addState(0x3b);                              // State 59
        addState(0x3d);                              // State 61
        addCondition(0x39);                          // Condition 57
        addStateWithName("disabled", 0x13);          // State 19
        addStateWithName("noTarget", 0x16);          // State 22
        addStateWithName("targetLock", 0x1a);        // State 26
        addStateWithName("precisionAim", 0x17);      // State 23
        addStateWithName("sniperMode", 0x1d);        // State 29
        setStartState("precisionAim", -1);           // Another start state
        addTransition(0x36);                         // Transition 54
        addTransition(0x42);                         // Transition 66
        addState(0x31);                              // State 49
        addState(0x3b);                              // State 59
        addState(0x42);                              // State 66
        addState(0x3c);                              // State 60
        addCondition(0x3d);                          // Condition 61
        addCondition(0x37);                          // Condition 55
        addStateWithName("disabled", 0x13);          // State 19
        addStateWithName("noTarget", 0x16);          // State 22
        addStateWithName("noTargetFreeAim", 0x18);   // State 24
        addStateWithName("targetLock", 0x19);        // State 25
        addStateWithName("sniperMode", 0x1d);        // State 29
        setStartState("targetLock", -1);             // Start state
        addTransition(0x35);                         // Transition 53
        addStateWithFlags(0x32, 1, 1);               // State 50 with flags
        addState(0x32);                              // State 50
        addState(0x3b);                              // State 59
        addState(0x33);                              // State 51
        addState(0x3c);                              // State 60
        addCondition(0x3d);                          // Condition 61
        addCondition(0x34);                          // Condition 52
        addStateWithName("disabled", 0x13);          // State 19
        addStateWithName("noTarget", 0x16);          // State 22
        addStateWithName("noTargetFreeAim", 0x1b);   // State 27
        addStateWithName("precisionAim", 0x1c);      // State 28
        addStateWithName("sniperMode", 0x1d);        // State 29
        setStartState("sniperMode", -1);             // Start state
        addStateWithFlags(0x1e, 1, 1);               // State 30 with flags
        addTransition(0x3f);                         // Transition 63
        addState(0x3c);                              // State 60
        addState(0x31);                              // State 49
        addState(0x41);                              // State 65
        addState(0x3b);                              // State 59
        addCondition(0x3d);                          // Condition 61
        addCondition(0x40);                          // Condition 64
        addStateWithName("disabled", 0x13);          // State 19
        addStateWithName("noTarget", 0x21);          // State 33
        addStateWithName("noTarget", 0x20);          // State 32
        addStateWithName("noTarget", 0x16);          // State 22
        addStateWithName("noTargetFreeAim", 0x1e);   // State 30
        addSpecialState("noTargetFreeAim", 6, 1, 1); // Special state 30 with parameters
        addStateWithName("targetLock", 0x1f);        // State 31
        setStartState("disabled", -1);               // Final start state
        addTransition(0x3a);                         // Transition 58
        addTransition(0x3e);                         // Transition 62
        addStateWithName("noTarget", 0x14);          // State 20

        // Register the state machine with the game systems
        registerStateMachine(0x9099d271, &gameUpdateCallback, "PlayerTargetingSM");
        finalizeStateTable();
    }
}