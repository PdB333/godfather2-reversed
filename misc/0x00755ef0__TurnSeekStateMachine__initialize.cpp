// FUNC_NAME: TurnSeekStateMachine::initialize
void TurnSeekStateMachine::initialize(void)
{
    // Look up or create the "seekToPositionTerminateTable" animation table
    int tableId = findTableByName("seekToPositionTerminateTable");
    if (tableExists(tableId) == 0) {
        // Table doesn't exist – create and configure it
        int newTable = createAnimationTable();
        registerAnimationTable("seekToPositionTerminateTable", newTable);

        // Set the default animation for "seekToPositionNoAnims" to -1 (no animation)
        setTableAnimation("seekToPositionNoAnims", 0xffffffff);

        // Add states 0x15 and 0x17 to the animation state machine
        addAnimationState(0x15);
        addAnimationState(0x17);

        // Configure state transitions for the global animation state machine (DAT_00d63afc)
        // Set transition from state 0xb (probably something like "idle")
        setTransitionState(&DAT_00d63afc, 0xb);
        setTableAnimation(&DAT_00d63afc, 0xffffffff);

        // Add a transition rule with parameter 2
        addTransitionRule(2);

        // Register the turn-seek state machine with hash 0x1b2d5c51,
        // referencing code at address 0x00755af0 (the state machine handler)
        registerStateMachine(0x1b2d5c51, &LAB_00755af0, "TurnSeekStateMachine");

        // Finalize the initialization
        finalizeStateMachineSetup();
    }
}