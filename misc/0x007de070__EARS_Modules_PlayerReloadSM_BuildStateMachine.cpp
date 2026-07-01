// Xbox PDB: EARS_Modules_PlayerReloadSM_BuildStateMachine
// FUNC_NAME: PlayerStateMachine::setupPlayerReloadStateMachine
void PlayerStateMachine::setupPlayerReloadStateMachine(void)
{
    // Acquire the state table handle by name
    void* tableHandle = stateMachineTableGet("playerReloadStateTable");
    int isInitialized = stateMachineTableIsValid(tableHandle);
    if (isInitialized == 0) {
        // Create a new state machine context
        void* smContext = stateMachineContextCreate();
        // Register the table with the context
        stateMachineTableSet("playerReloadStateTable", smContext);
        // Add the main reload state (ID -1 indicates no explicit ID)
        stateMachineAddState("reload", 0xffffffff);
        // Set a transition source state (0x31 likely a state index)
        stateMachineSetTransitionSource(0x31);
        // Add a transition to a default state (at offset 0x13 in transition data)
        stateMachineAddTransition(&gDefaultTransitionData, 0x13);
        // Add another state (empty name used as marker)
        stateMachineAddState(&gDefaultTransitionData, 0xffffffff);
        // Set another transition source (2)
        stateMachineSetTransitionSource(2);
        // Register the state machine with a hash key and function table
        stateMachineRegister(0x9327b82a, &playerReloadSM_FuncTable, "PlayerReloadSM");
        // Finalize the state machine construction
        stateMachineFinalize();
    }
}