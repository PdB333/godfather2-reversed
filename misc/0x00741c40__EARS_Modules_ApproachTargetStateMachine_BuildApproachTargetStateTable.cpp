// Xbox PDB: EARS::Modules::ApproachTargetStateMachine::BuildApproachTargetStateTable
// FUNC_NAME: ApproachTargetStateMachine::initialize
void ApproachTargetStateMachine::initialize()
{
    // Get the entity table handle (likely from a singleton manager)
    int entityTable = getEntityTable(); // FUN_009c8f80

    // Register the state machine's entity table with a name key
    registerEntityTable("approachEntityTable", entityTable); // FUN_004ad9d0

    // Set the default state to "approach" with an initial ID of -1 (no state)
    setState("approach", -1); // FUN_004adae0

    // Add states with specific IDs (0x0E, 0x0B, 8) - likely animation or behavior IDs
    addState(0x0E); // FUN_004acff0
    addState(0x0B);
    addState(8);

    // Add a transition from the string constant (likely "approach") with transition ID 10
    addTransition(&DAT_00d63afc, 10); // FUN_004acc70

    // Set the state again on that transition (maybe set initial transition state)
    setState(&DAT_00d63afc, -1); // FUN_004adae0

    // Set the update function for state ID 2
    setUpdateFunction(2); // FUN_004acf70

    // Register a state machine definition: hash, entry function, name
    registerStateMachine(0x6de5ffd8, &LAB_00741bb0, "ApproachTargetStateMachine"); // FUN_004adc90

    // Finalize the state machine setup (e.g., compile transitions)
    finalizeSetup(); // FUN_004ada40
}