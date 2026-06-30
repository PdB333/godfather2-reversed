// FUNC_NAME: SeekToPositionSM::initStateMachine
// Address: 0x0075ecf0
// Constructs the SeekToPosition state machine with state transitions and timers

void SeekToPositionSM::initStateMachine(void)
{
    unsigned int allocator;

    // Get memory allocator for state machine
    allocator = getStateMachineAllocator();

    // Set state machine name
    setStateMachineName("SeekToPositionST", allocator);

    // Add default transition to transition table (ID -1 means no transition)
    addTransitionEntry(&DAT_00d63420, 0xffffffff); // possibly empty string placeholder

    // Set timer for state 10
    setStateTimer(10);

    // Add states with priorities (state name, state ID)
    addState("closeToPos", 0xd);
    addState("seekToPos", 0xb);
    addState("turnToSeekPos", 4);

    // Set default transition for "turnToSeekPos"
    addTransitionEntry("turnToSeekPos", 0xffffffff);

    // Set terminate table for "turnToPositionTerminateTable" with flag 1
    setStateTerminateTable("turnToPositionTerminateTable", 1);

    // Add more states
    addState("turnToSeekPos", 0xc);
    addState("seekToPos", 1);

    // Set initial state to 0x11
    setInitialState(0x11);

    // Override transition for "seekToPos" to default
    addTransitionEntry("seekToPos", 0xffffffff);

    // Set timers for states 0xb and 8
    setStateTimer(0xb);
    setStateTimer(8);

    // Set state flags for states 0x10 and 8
    setStateFlag(0x10);
    setStateFlag(8);

    // Add states
    addState("closeToPos", 0xd);
    addState("seekFailure", 10);

    // Set initial state to 0xc
    setInitialState(0xc);

    // Default transition for "closeToPos"
    addTransitionEntry("closeToPos", 0xffffffff);

    // Add more states
    addState("stopExactly", 0xe);
    addState(&DAT_00d63afc, 4); // empty string placeholder

    // Default transition for "stopExactly"
    addTransitionEntry("stopExactly", 0xffffffff);

    addState("decelerateToStop", 0xf);
    addState("trackToPositionStop", 4);

    // Default transition for "decelerateToStop"
    addTransitionEntry("decelerateToStop", 0xffffffff);

    // Set timers for states 0x12, 0x13, 0x14
    setStateTimer(0x12);
    setStateTimer(0x13);
    setStateTimer(0x14);

    // Set state flags for 0x14
    setStateFlag(0x14);

    addState("decelerateStopFinalize", 0x10);
    addState("seekFailure", 0x11);

    // Default transition for "decelerateStopFinalize"
    addTransitionEntry("decelerateStopFinalize", 0xffffffff);

    addState(&DAT_00d63afc, 3); // empty string placeholder

    // Default transition for "trackToPositionStop"
    addTransitionEntry("trackToPositionStop", 0xffffffff);

    // Set timer for state 0x12
    setStateTimer(0x12);

    // Set terminate table for "trackToPositionAndDirectionStateTable" with flag 0
    setStateTerminateTable("trackToPositionAndDirectionStateTable", 0);

    addState(&DAT_00d63afc, 1); // empty string placeholder

    // Default transition for "seekFailure"
    addTransitionEntry("seekFailure", 0xffffffff);

    // Set timers for states 0xd and 8
    setStateTimer(0xd);
    setStateTimer(8);

    // Add transition condition: from state 6, with marker 0x20, enable true
    addTransitionCondition(6, 0x20, 1);

    // Set timer for state 2
    setStateTimer(2);

    // Default transition for empty state
    addTransitionEntry(&DAT_00d63afc, 0xffffffff);

    // Set timer for state 2 again (possibly override)
    setStateTimer(2);

    // Register state machine with callback address (0x0075ec90) and name
    registerStateMachine(0x17a70916, &LAB_0075ec90, "SeekToPositionSM");

    // Finalize state machine construction
    finalizeStateMachine();
}