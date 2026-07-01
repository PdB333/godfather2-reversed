// Xbox PDB: EARS_Modules_NPCPunchSM_BuildStateTable
// FUNC_NAME: NPCPunchStateMachineBuilder::build
void buildNPCPunchStateMachine(void)
{
    // Get string ID for "NPCPunchST" state machine name
    unsigned int stateMachineId = getStringId("NPCPunchST");
    
    // Check if state machine already exists; if not, create it
    if (getStateMachine(stateMachineId) == 0)
    {
        // Create a new state machine instance
        IStateMachine* newMachine = createStateMachine();
        // Register it with the given string ID
        registerStateMachine("NPCPunchST", newMachine);
        
        // Add a state "punchInit" with ID -1 (no entry/exit?)
        addState("punchInit", 0xFFFFFFFF);
        // Add transition from state 0x2A? (these IDs are state IDs)
        addTransition(0x2A);
        
        // Add states with specific entry/exit? (stateID, entryActionID, exitActionID, flag?)
        addStateWithTransition("counterJab", 0x12, 10, 1);
        addStateWithTransition("counterJab", 0x12, 0xB, 1);
        addStateWithTransition("counterJab", 0x12, 0xC, 1);
        addStateWithTransition("fightIdle", 0x12, 9, 1);
        addStateWithTransition("comboStart", 0x12, 8, 1);
        
        // Add standalone state "simpleAttack" with ID 4
        addState("simpleAttack", 4);
        // Set state "fightIdle" as default? (ID -1 means no state)
        addState("fightIdle", 0xFFFFFFFF);
        // Add transitions to states 0x26, 0x25, 8
        addTransition(0x26);
        addTransition(0x25);
        addTransition(8);
        // Set default transition? (to state 8)
        setDefaultTransition(8);
        // Set attribute "setHeadingToEntityTable" to true
        setStateAttribute("setHeadingToEntityTable", 1);
        // Add a state with the constant string (likely empty or placeholder) and ID 0x14
        addState(G_stEmptyStr, 0x14);
        // Set state "simpleAttack" as default
        addState("simpleAttack", 0xFFFFFFFF);
        // Transition to 0x27, 8
        addTransition(0x27);
        addTransition(8);
        setDefaultTransition(8);
        setStateAttribute("setHeadingToEntityTable", 1);
        
        // Add state "simpleAttackEnd" with ID 7
        addState("simpleAttackEnd", 7);
        // Set state "simpleAttackEnd" as default
        addState("simpleAttackEnd", 0xFFFFFFFF);
        // Transition to 0x28, 8
        addTransition(0x28);
        addTransition(8);
        setDefaultTransition(8);
        setStateAttribute("setHeadingToEntityTable", 1);
        // Add placeholder state with ID 7
        addState(G_stEmptyStr, 7);
        // Set state "comboStart" as default
        addState("comboStart", 0xFFFFFFFF);
        // Transition to 0x29
        addTransition(0x29);
        // Add state "comboPlay" with ID 4
        addState("comboPlay", 4);
        // Set state "comboPlay" as default
        addState("comboPlay", 0xFFFFFFFF);
        // Transition to 0x2C
        addTransition(0x2C);
        setStateAttribute("setHeadingToEntityTable", 1);
        addTransition(8);
        setDefaultTransition(8);
        // Add state "comboTestFinish" with ID 7
        addState("comboTestFinish", 7);
        // Set state "comboTestFinish" as default
        addState("comboTestFinish", 0xFFFFFFFF);
        // Add state "comboFinishedEarly" with ID 0x13
        addState("comboFinishedEarly", 0x13);
        // Add placeholder state with ID 0x15
        addState(G_stEmptyStr, 0x15);
        // Add state "comboContinue" with ID 4
        addState("comboContinue", 4);
        // Set state "comboContinue" as default
        addState("comboContinue", 0xFFFFFFFF);
        // Transition to 0x2E
        addTransition(0x2E);
        // Add state "comboPlay" with ID 4 again? (overwrites?)
        addState("comboPlay", 4);
        // Set state "comboFinishedEarly" as default
        addState("comboFinishedEarly", 0xFFFFFFFF);
        // Transition to 0x2D
        addTransition(0x2D);
        setStateAttribute("setHeadingToEntityTable", 1);
        // Add placeholder state with ID 7
        addState(G_stEmptyStr, 7);
        // Set state "counterJab" as default
        addState("counterJab", 0xFFFFFFFF);
        // Transition to 0x2B
        addTransition(0x2B);
        addTransition(8);
        setDefaultTransition(8);
        setStateAttribute("setHeadingToEntityTable", 1);
        // Add placeholder state with ID 7
        addState(G_stEmptyStr, 7);
        // Set placeholder state as default
        addState(G_stEmptyStr, 0xFFFFFFFF);
        // Transition to 2
        addTransition(2);
        
        // Add a sub-state machine "NPCPunchSM" (another FSM) starting at address LAB_0076b310
        addSubStateMachine(0xD4D01407, &LAB_0076b310, "NPCPunchSM");
        
        // Finalize the state machine (build internal data)
        finalizeStateMachine();
    }
}