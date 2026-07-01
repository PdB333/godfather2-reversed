// Xbox PDB: EARS::Modules::NPCDesignerActionSM::BuildStateMachine
// FUNC_NAME: NPCDesignerActionSM::initialize
void __thiscall NPCDesignerActionSM::initialize(void)
{
    uint stateTableId;

    // Retrieve a unique identifier for the state table (likely from a manager)
    stateTableId = StateTableManager::allocateId();  // FUN_009c8f80

    // Register the state table under the name "NPCDesignerActionST"
    StateTableManager::registerStateTable("NPCDesignerActionST", stateTableId);  // FUN_004ad9d0

    // Set default transition for the entire state machine (0xFFFFFFFF = no default?)
    StateTableManager::setDefaultTransition(&gGlobalStateData, 0xFFFFFFFF);  // FUN_004adae0 with DAT_00d63420

    // Add state with id 0x14 (20)
    StateTableManager::addState(0x14);  // FUN_004acf70

    // Add transitions for state 0x14:
    // - On "terminate" action, go to state 0xC (12)
    StateTableManager::addTransition("terminate", 0xC);  // FUN_004acc70
    // - On "noTurnPerformAction", go to state 0xB (11)
    StateTableManager::addTransition("noTurnPerformAction", 0xB);
    // - On "terminate", go to state 10 (0xA) – note: duplicate action name with different target? Possibly a second transition under same state?
    StateTableManager::addTransition("terminate", 10);
    // - On "turnFirst", go to state 4
    StateTableManager::addTransition("turnFirst", 4);

    // Set default transition for "turnFirst" action (0xFFFFFFFF = no default? Or global?)
    StateTableManager::setDefaultTransition("turnFirst", 0xFFFFFFFF);

    // Create a specialized transition table for "turnToEntityTerminateTable" with subtable ID 1
    StateTableManager::createTransitionTable("turnToEntityTerminateTable", 1);  // FUN_004acf10

    // Add states 0xD (13) and 0xC (12)
    StateTableManager::addState(0xD);
    StateTableManager::addState(0xC);

    // Add transitions for these states:
    // - "terminate" -> 0xC
    StateTableManager::addTransition("terminate", 0xC);
    // - "terminate" -> 10
    StateTableManager::addTransition("terminate", 10);
    // - "performAction" -> 1
    StateTableManager::addTransition("performAction", 1);

    // Set default transition for "performAction" (global scope)
    StateTableManager::setDefaultTransition("performAction", 0xFFFFFFFF);

    // Add states 0x13 (19), 0x12 (18), 0xD (13), 0xC (12)
    StateTableManager::addState(0x13);
    StateTableManager::addState(0x12);
    StateTableManager::addState(0xD);
    StateTableManager::addState(0xC);

    // Create transition table for "seekTargetTable" with subtable ID 1
    StateTableManager::createTransitionTable("seekTargetTable", 1);

    // Add transitions:
    // - "terminate" -> 0xC
    StateTableManager::addTransition("terminate", 0xC);
    // - "terminate" -> 10
    StateTableManager::addTransition("terminate", 10);
    // - "terminate" -> 7
    StateTableManager::addTransition("terminate", 7);

    // Set default transition for "noTurnPerformAction"
    StateTableManager::setDefaultTransition("noTurnPerformAction", 0xFFFFFFFF);

    // Add states 0x13 (19), 0x12 (18), 0xD (13)
    StateTableManager::addState(0x13);
    StateTableManager::addState(0x12);
    StateTableManager::addState(0xD);

    // Add transitions:
    // - "terminate" -> 0xC
    StateTableManager::addTransition("terminate", 0xC);
    // - "terminate" -> 7
    StateTableManager::addTransition("terminate", 7);

    // Set default transition for "terminate"
    StateTableManager::setDefaultTransition("terminate", 0xFFFFFFFF);

    // Add state with ID 2
    StateTableManager::addState(2);

    // Create the state machine object with a unique hash (0x47563f5c), an entry function (LAB_0073dae0), and name "NPCDesignerActionSM"
    StateTableManager::createStateMachine(0x47563f5c, &sStateMachineEntryFunc, "NPCDesignerActionSM");  // FUN_004adc90

    // Commit and finalize the state machine setup
    StateTableManager::finalize();  // FUN_004ada40

    return;
}