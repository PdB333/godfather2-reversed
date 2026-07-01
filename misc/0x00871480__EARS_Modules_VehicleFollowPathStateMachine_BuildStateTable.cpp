// Xbox PDB: EARS_Modules_VehicleFollowPathStateMachine_BuildStateTable
// FUNC_NAME: VehicleFollowPathStateMachine::initialize
// Address: 0x00871480
// Role: Initializes the state machine table and states for vehicle follow path behavior.

void VehicleFollowPathStateMachine::initialize()
{
    // Look up "vehicleFollowPathTable" in the global table registry
    void* table = findNamedTable("vehicleFollowPathTable"); // thunk_FUN_004dafd0
    int count = getTableEntryCount(table); // FUN_00621530

    if (count == 0) {
        // First-time setup – clear any leftover state and create a new table
        clearStateMachine(); // FUN_0086b400
        table = createStateMachineTable(); // FUN_009c8f80
        registerNamedTable("vehicleFollowPathTable", table); // FUN_004ad9d0

        // Add a transition from the default start state (global string) with no condition
        addTransition(gStateNameStart, 0xFFFFFFFF); // FUN_004adae0, -1 = unconditional

        // Define states and their transitions
        addState("seekToTarget", 0xB); // ID = 11 // FUN_004acc70
        addTransition("seekToTarget", 0xFFFFFFFF); // unconditional transition from seekToTarget
        setStatePriority(10); // FUN_004acf70 – set priority for a previous state? (maybe for state ID 10)
        setStateDefaultTransition(0xB); // FUN_004acff0 – set default transition for state 11

        // Another state from a global string constant (e.g., "chase" or "idle")
        addState(gStateNameAnother, 0xC); // ID = 12 // FUN_004acc70

        // "reverse" state with its own behavior table
        addState("reverse", 10); // ID = 10
        addTransition("reverse", 0xFFFFFFFF);
        setStateBehaviorTable("vehicleReverseTable", 1); // FUN_004acf10

        // Reuse the same global start state with ID 1
        addState(gStateNameStart, 1); // ID = 1
        addTransition(gStateNameAnother, 0xFFFFFFFF);
        setStatePriority(0xC); // for state 12
        setStatePriority(2); // for state 2

        // Register the state machine with its unique hash and entry point
        registerStateMachineDefinition(0xB1C4C5B5, &stateMachineFunction, "VehicleFollowPathStateMachine"); // FUN_004adc90

        // Finalize the state machine setup
        finalizeStateMachineRegistration(); // FUN_004ada40
    }
}