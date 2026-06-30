// Xbox PDB: EARS::Modules::TurnSeekStateMachine::BuildTurnToEntityTerminateStateTable
// FUNC_NAME: initTurnToEntityTables
void initTurnToEntityTables(void)
{
    // Get or create the termination table for turn-to-entity animations
    int terminateTableHandle = getTable("turnToEntityTerminateTable");
    if (tableExists(terminateTableHandle) == 0) {
        // Create the table and initialise it
        terminateTableHandle = createTable();
        setTable("turnToEntityTerminateTable", terminateTableHandle);
        // Disable idle animations during turn-to-entity (0xFFFFFFFF = all slots)
        setFlag("turnToEntityNoIdleAnims", 0xffffffff);
        // Register animation IDs that should terminate the turn-to-entity state
        addTerminateAnim(0x1a);  // Likely a specific idle/exit anim
        addTerminateAnim(0x19);  // Another termination anim
        addNoIdleAnimId(0x12);   // Anim that should not play idle during turn
        // Add entries to the turn seek state machine table (key: "TurnSeekStateMachine")
        addStateMachineEntry("TurnSeekStateMachine", 10);
        addStateMachineEntry("TurnSeekStateMachine", 0xb);
        // Set flag for the state machine (disable idle? or default value)
        setFlag("TurnSeekStateMachine", 0xffffffff);
        // Register a new termination anim for entry ID 2
        addTerminateAnim(2);
        // Register the state machine function with name "TurnSeekStateMachine"
        registerStateMachine(0x1b2d5c51, (void*)0x00755af0, "TurnSeekStateMachine");
        // Finalise or commit the table changes
        finalizeTable();
    }
    return;
}