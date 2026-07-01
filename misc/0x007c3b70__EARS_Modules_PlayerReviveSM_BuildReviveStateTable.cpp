// Xbox PDB: EARS_Modules_PlayerReviveSM_BuildReviveStateTable
// FUNC_NAME: PlayerReviveSM::registerStates
void PlayerReviveSM::registerStates(void)
{
    // Get the state machine manager handle (likely from a singleton)
    uint stateMachineHandle = getStateMachineManager();

    // Register the main state table for player revive
    registerStateTable("playerReviveStateTable", stateMachineHandle);

    // Add the initial state "ReviveStart" with no transition (0xFFFFFFFF)
    addState("ReviveStart", 0xFFFFFFFF);

    // Add transitions from ReviveStart to other states (IDs 0x35 and 0x28)
    addTransition(0x35);
    addTransition(0x28);

    // Register a sub-state table for tracking position and direction
    registerTrackStateTable("trackToPositionAndDirectionStateTable", 1);

    // Add states for the revive multiplayer loop and terminate
    addState("revive_mp_loop", 0x13);
    addState("terminate", 7);

    // Add transitions from revive_mp_loop to other states (IDs 0x31 and 0x27)
    addTransition(0x31);
    addTransition(0x27);

    // Add a transition from revive_mp_loop back to itself? (0xFFFFFFFF means no transition)
    addState("revive_mp_loop", 0xFFFFFFFF);

    // Add transition to revive_mp_end (ID 0x33)
    addTransition(0x33);

    // Add state revive_mp_end with ID 7
    addState("revive_mp_end", 7);

    // Add transitions from revive_mp_end (IDs 0x32)
    addTransition(0x32);

    // Add transition from revive_mp_end to itself? (0xFFFFFFFF)
    addState("revive_mp_end", 0xFFFFFFFF);

    // Add transition to terminate (ID 0x34)
    addTransition(0x34);

    // Add state terminate with ID 7
    addState("terminate", 7);

    // Add transition from terminate to itself? (0xFFFFFFFF)
    addState("terminate", 0xFFFFFFFF);

    // Add transition to initial state (ID 2)
    addTransition(2);

    // Register the state machine with a callback function and name
    registerStateMachineCallback(0xA56520B0, &PlayerReviveSM::onStateChange, "PlayerReviveSM");

    // Finalize the state machine registration
    finalizeStateMachine();
}