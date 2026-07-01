// Xbox PDB: EARS_Modules_PlayerGarotteSM_BuildStateMachine
// FUNC_NAME: PlayerGarotteSM::buildStateMachine
// Address: 0x007ae690
// Builds the state machine for player garotte (garrote) behavior.
// Uses the EARS state machine builder API.

void PlayerGarotteSM::buildStateMachine(void)
{
    // Get the state machine builder instance
    StateMachineBuilder* builder = StateMachineBuilder::getInstance();

    // Register the state table with name "playerGarotteStateTable"
    builder->addStateTable("playerGarotteStateTable", builder->getHandle());

    // --- State: garotteInit (ID: 0xFFFFFFFF) ---
    builder->addState("garotteInit", 0xFFFFFFFF);

    // Transition from state 0x16 to 0x4c with condition 1
    builder->addTransition(0x16, 0x4c, 1);

    // Entry actions for states 0x18, 0x38, 0x1b
    builder->addEntryAction(0x18);
    builder->addEntryAction(0x38);
    builder->addEntryAction(0x1b);

    // Transition from 0x2c to 0 with condition 1
    builder->addTransition(0x2c, 0, 1);
    // Transition from 0x2d to 0 with condition 1
    builder->addTransition(0x2d, 0, 1);

    // Timed transition: "garroteConnected" after 7 units
    builder->addTimedTransition("garroteConnected", 7);
    // State "garroteConnected" with ID 0xFFFFFFFF
    builder->addState("garroteConnected", 0xFFFFFFFF);

    // State "garotteGrabKneeling" with entry action 0x19, exit action 1, condition 1
    builder->addStateWithEntryAction("garotteGrabKneeling", 0x19, 1, 1);

    // Timed transition: "garotteGrab" after 4 units
    builder->addTimedTransition("garotteGrab", 4);
    // State "garotteGrabKneeling" with ID 0xFFFFFFFF
    builder->addState("garotteGrabKneeling", 0xFFFFFFFF);

    // Entry actions for states 0x1b, 0x31
    builder->addEntryAction(0x1b);
    builder->addEntryAction(0x31);

    // Timed transitions: "garotteBreak" after 0x13, "garottePullup" after 4
    builder->addTimedTransition("garotteBreak", 0x13);
    builder->addTimedTransition("garottePullup", 4);
    // State "garotteGrab" with ID 0xFFFFFFFF
    builder->addState("garotteGrab", 0xFFFFFFFF);

    // Entry actions for states 0x1b, 0x31
    builder->addEntryAction(0x1b);
    builder->addEntryAction(0x31);

    // Timed transitions: "garotteBreak" after 0x13, "garotteRelease" after 0x14
    builder->addTimedTransition("garotteBreak", 0x13);
    builder->addTimedTransition("garotteRelease", 0x14);

    // Timed transition: "garotteGrabIdle" after 4
    builder->addTimedTransition("garotteGrabIdle", 4);
    // State "garotteGrabIdle" with ID 0xFFFFFFFF
    builder->addState("garotteGrabIdle", 0xFFFFFFFF);

    // Transition from 0x16 to 0x4d with condition 1
    builder->addTransition(0x16, 0x4d, 1);
    // Entry action for state 0x18
    builder->addEntryAction(0x18);

    // Timed transitions: "garotteNeckSnap" after 0x18, "garotteBreak" after 0x13, "garotteRelease" after 0x14
    builder->addTimedTransition("garotteNeckSnap", 0x18);
    builder->addTimedTransition("garotteBreak", 0x13);
    builder->addTimedTransition("garotteRelease", 0x14);

    // Timed transition: "garotteStrangle" after 0x16
    builder->addTimedTransition("garotteStrangle", 0x16);
    // State "garotteStrangle" with ID 0xFFFFFFFF
    builder->addState("garotteStrangle", 0xFFFFFFFF);

    // Transition from 0x16 to 0x51 with condition 1
    builder->addTransition(0x16, 0x51, 1);
    // Entry actions for states 0x18, 0x36
    builder->addEntryAction(0x18);
    builder->addEntryAction(0x36);

    // Conditional transitions for states 0x1b, 0x32
    builder->addConditionalTransition(0x1b);
    builder->addConditionalTransition(0x32);

    // Timed transitions: "garotteNeckSnap" after 0x18, "garotteBreak" after 0x13, "garotteRelease" after 0x17, "garotteGrabIdle" after 0x1a
    builder->addTimedTransition("garotteNeckSnap", 0x18);
    builder->addTimedTransition("garotteBreak", 0x13);
    builder->addTimedTransition("garotteRelease", 0x17);
    builder->addTimedTransition("garotteGrabIdle", 0x1a);

    // Timed transition: "garotteKill" after 7
    builder->addTimedTransition("garotteKill", 7);
    // State "garotteRelease" with ID 0xFFFFFFFF
    builder->addState("garotteRelease", 0xFFFFFFFF);

    // Transition from 0x16 to 0x4f with condition 1
    builder->addTransition(0x16, 0x4f, 1);
    // Entry actions for states 0x18, 0x29
    builder->addEntryAction(0x18);
    builder->addEntryAction(0x29);

    // Transition from 0x34 to 1 with condition 1
    builder->addTransition(0x34, 1, 1);
    // Conditional transitions for states 0x1b
    builder->addConditionalTransition(0x1b);
    // Transition from 0x34 to 0 with condition 1
    builder->addTransition(0x34, 0, 1);

    // Timed transition: "terminate" after 7
    builder->addTimedTransition("terminate", 7);
    // State "garotteBreak" with ID 0xFFFFFFFF
    builder->addState("garotteBreak", 0xFFFFFFFF);

    // Transition from 0x16 to 0x4e with condition 1
    builder->addTransition(0x16, 0x4e, 1);
    // Entry actions for states 0x18, 0x29
    builder->addEntryAction(0x18);
    builder->addEntryAction(0x29);

    // Timed transition: "terminate" after 7
    builder->addTimedTransition("terminate", 7);
    // State "garotteKill" with ID 0xFFFFFFFF
    builder->addState("garotteKill", 0xFFFFFFFF);

    // Transition from 0x16 to 0x52 with condition 1
    builder->addTransition(0x16, 0x52, 1);
    // Entry actions for states 0x18, 0x29
    builder->addEntryAction(0x18);
    builder->addEntryAction(0x29);

    // Transition from 0x34 to 1 with condition 1
    builder->addTransition(0x34, 1, 1);
    // Exit action for state 0x33
    builder->addExitAction(0x33);
    // Transition from 0x34 to 0 with condition 1
    builder->addTransition(0x34, 0, 1);

    // Timed transitions: "terminate" after 0x12, "terminate" after 7
    builder->addTimedTransition("terminate", 0x12);
    builder->addTimedTransition("terminate", 7);
    // State "garottePullup" with ID 0xFFFFFFFF
    builder->addState("garottePullup", 0xFFFFFFFF);

    // Transition from 0x16 to 0x50 with condition 1
    builder->addTransition(0x16, 0x50, 1);
    // Entry action for state 0x18
    builder->addEntryAction(0x18);
    // Conditional transition for state 0x35
    builder->addConditionalTransition(0x35);

    // Timed transition: "garotteGrabIdle" after 7
    builder->addTimedTransition("garotteGrabIdle", 7);
    // State "garotteNeckSnap" with ID 0xFFFFFFFF
    builder->addState("garotteNeckSnap", 0xFFFFFFFF);

    // Entry action for state 0x37
    builder->addEntryAction(0x37);
    // Timed transition: "terminate" after 4
    builder->addTimedTransition("terminate", 4);
    // State "terminate" with ID 0xFFFFFFFF
    builder->addState("terminate", 0xFFFFFFFF);

    // Entry action for state 2
    builder->addEntryAction(2);

    // Register the state machine with a hash, vtable pointer, and name
    builder->registerStateMachine(0x8dbe4dc7, &LAB_007ae640, "PlayerGarotteSM");

    // Finalize the builder
    builder->finalize();
}