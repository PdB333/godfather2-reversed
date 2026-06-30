// Xbox PDB: EARS::Modules::TrackToPositionAndDirectionSM::BuildStateMachine
// FUNC_NAME: registerTrackToPositionAndDirectionStateMachine
void registerTrackToPositionAndDirectionStateMachine(void)
{
    // Look up the state table by name "trackToPositionAndDirectionStateTable"
    // This function returns a handle/pointer to the table if it exists, else NULL.
    void* stateTable = getStateTableByName("trackToPositionAndDirectionStateTable");
    
    // Check if the table is already registered (non-null)
    if (stateTable == nullptr) {
        // Create a new state table
        stateTable = createStateTable();
        
        // Register the table with the given name
        registerStateTable("trackToPositionAndDirectionStateTable", stateTable);
        
        // Add state with ID -1 (invalid/undefined state?) - "tracking" is the state name
        addState("tracking", 0xFFFFFFFF);
        
        // Set initial state to 10
        setInitialState(10);
        
        // Add transitions from state 10 -> 11
        addTransition(staticSomeStateMachineID, 10);   // DAT_00d63ba4 is likely a state machine instance pointer or ID
        addTransition(staticSomeStateMachineID, 11);   // second transition
        
        // Set state ID to -1 (exit state?)
        addState(staticSomeStateMachineID, 0xFFFFFFFF);
        
        // Set state machine flags to 2 (e.g., allow repeats, etc.)
        setStateMachineFlags(2);
        
        // Register a function pointer for the state machine logic (likely a state machine update function)
        registerStateMachineFunction(0x27A0F69C, &TrackToPositionAndDirectionSM_StateHandler, "TrackToPositionAndDirectionSM");
        
        // Finalize the state machine setup
        finalizeStateMachine();
    }
}