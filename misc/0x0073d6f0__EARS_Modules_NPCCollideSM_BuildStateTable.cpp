// Xbox PDB: EARS::Modules::NPCCollideSM::BuildStateTable
// FUNC_NAME: buildNPCCollideStateMachine
void buildNPCCollideStateMachine(void)
{
    // Get handle to state machine builder context
    uint stateMachineHandle = getStateMachineHandle();

    // Set the name of the state machine table
    setStateMachineName("NPCCollideST", stateMachineHandle);

    // Set default transition for global state machine data? (offset 0x00d63420)
    setDefaultTransition(&DAT_00d63420, 0);

    // Add state with ID 0xC (12) – likely "collide" state
    addState(0xC);

    // Add transition "terminate" with ID 0x12 (18)
    addTransition("terminate", 0x12);

    // Add transition "orientToCollide" with ID 4
    addTransition("orientToCollide", 4);

    // Set target state for transition "orientToCollide" to state ID 1
    setTransitionTarget("orientToCollide", 1);

    // Set a transition table for "turnToPositionTerminateTable" with parameter 1
    setTransitionTable("turnToPositionTerminateTable", 1);

    // Add transition "terminate" again with ID 0x12 (maybe different context)
    addTransition("terminate", 0x12);

    // Add transition "playCollide" with ID 1
    addTransition("playCollide", 1);

    // Set target state for transition "playCollide" to state ID 2
    setTransitionTarget("playCollide", 2);

    // Add state with ID 0x23 (35) – likely "playCollide" state
    addState(0x23);

    // Add transition "terminate" with target state ID 2, using data from global DAT_00e445ac and parameter 1
    addTransitionWithTarget("terminate", 2, DAT_00e445ac, 1);

    // Set default transition "terminate" to no target (0xFFFFFFFF)
    setTransitionTarget("terminate", 0xFFFFFFFF);

    // Add state with ID 2 – likely "orientToCollide" state
    addState(2);

    // Register state machine update function at address 0x0073d6c0 with name "NPCCollideSM"
    registerStateMachineUpdate(0x408c7112, &LAB_0073d6c0, "NPCCollideSM");

    // Finalize state machine construction
    finalizeStateMachine();
    return;
}