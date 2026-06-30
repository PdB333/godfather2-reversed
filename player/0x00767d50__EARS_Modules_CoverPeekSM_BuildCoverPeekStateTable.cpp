// Xbox PDB: EARS::Modules::CoverPeekSM::BuildCoverPeekStateTable
// FUNC_NAME: PlayerWallCoverSM::initCoverPeekStates
void PlayerWallCoverSM::initCoverPeekStates(void)
{
    int stateTableId;

    // Get a unique ID for the cover peek state table
    stateTableId = getStateTableID();

    // Register the cover peek state table with the name "CoverPeekST"
    registerStateTable("CoverPeekST", stateTableId);

    // Set the default state for the cover peek machine (0xffffffff = invalid, clear)
    setStateProperty(&gCoverPeekDefaultState, 0xFFFFFFFF);

    // Create the main state table for tracking position and direction
    createStateTable("trackToPositionAndDirectionStateTable", 1);

    // Add transition "toPeek" with ID 1
    addTransition("toPeek", 1);

    // Set the next state for "toPeek" to invalid (cleared)
    setTransitionProperty("toPeek", 0xFFFFFFFF);

    // Add states: CoverPeekEntry (0x23), PeekIdle (0x24), etc.
    addState(0x23); // Entry state
    addState(0x24); // Peek idle state

    // Add transitions with IDs 8 and 31
    addTransition(8);
    addTransition(0x1F); // 31

    // Transition "peekIdle" with ID 7 (into peek idle state)
    addTransition("peekIdle", 7);
    setTransitionProperty("peekIdle", 0xFFFFFFFF);

    // State 0x25 (fromPeek state)
    addState(0x25);

    // Transition ID 31 (shared)
    addTransition(0x1F);

    // Transition "fromPeek" with ID 0x12 (18)
    addTransition("fromPeek", 0x12);
    setTransitionProperty("fromPeek", 0xFFFFFFFF);

    // State 0x26 (peek done state)
    addState(0x26);

    // Transitions 8 and 31
    addTransition(8);
    addTransition(0x1F);

    // Transition "peekDone" with ID 7
    addTransition("peekDone", 7);
    setTransitionProperty("peekDone", 0xFFFFFFFF);

    // State 0x23 again (return to entry) and state ID 2 (exit)
    addState(0x23);
    addState(2);

    // Register the entire cover peek state machine with behavior function at 0x00767690
    registerStateMachine(0xA4AC966C, &CoverPeekSM_behavior, "CoverPeekSM");

    // Finalize/cleanup state machine registration
    finalizeStateMachine();
}