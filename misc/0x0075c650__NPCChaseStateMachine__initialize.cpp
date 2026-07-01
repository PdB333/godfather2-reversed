// FUNC_NAME: NPCChaseStateMachine::initialize

void NPCChaseStateMachine::initialize()
{
    // Get the shared state machine builder instance
    StateMachineBuilder* builder = getStateMachineBuilder();

    // Set the initial state of the top-level state machine
    builder->setInitialState("NPCChaseST");

    // Add a default transition (timeout or fallthrough) from the unnamed state to invalid
    builder->addDefaultTransition(/* DAT_00d63420 */ "NPCChaseST", 0xFFFFFFFF);

    // Add a state group with ID 5, flags 0x20, and a parameter 1 (likely group type)
    builder->addStateGroup(5, 0x20, 1);

    // Set a global timeout value of 10 (possibly for all states)
    builder->setGlobalTimeout(10);

    // Add two states using internal string constants
    builder->addState(/* DAT_00d63afc */ "move", 12);
    builder->addState(/* DAT_00d651b0 */ "chase", 11);

    // Add a state named "followPath" with ID 4
    builder->addState("followPath", 4);

    // Add a transition from "followPath" to the default exit (-1)
    builder->addTransition("followPath", 0xFFFFFFFF);

    // Set timeout to 11 for the current context (likely top-level)
    builder->setTimeout(11);

    // Add a nested sub-state machine script "FollowPathST"
    builder->addSubStateScript("FollowPathST", 1);

    // Add states with IDs 15 and 12 (might be internal indices)
    builder->addState(15);
    builder->addState(12);

    // Add states "doneNoPath" and "followPath" with new IDs
    builder->addState("doneNoPath", 14);
    builder->addState("followPath", 13);

    // Add a transition from "doneNoPath" to state 6, with condition flags 0x20 and 1
    builder->addTransitionWithCondition("doneNoPath", 6, 0x20, 1);

    // Re-add state "move" with IDs 12 and 1 (likely redefining transitions)
    builder->addState(/* DAT_00d63afc */ "move", 12);
    builder->addState(/* DAT_00d63afc */ "move", 1);

    // Add a default transition from "chase" to exit
    builder->addDefaultTransition(/* DAT_00d651b0 */ "chase", 0xFFFFFFFF);

    // Set timeout to 13
    builder->setTimeout(13);

    // Add sub-state machine "SeekToPositionST"
    builder->addSubStateScript("SeekToPositionST", 1);

    // Add states with IDs 15 and 14
    builder->addState(15);
    builder->addState(14);

    // Add another conditional transition
    builder->addTransitionWithCondition("followPath", 6, 0x20, 1);

    // Again add state "move" with IDs 12 and 1
    builder->addState(/* DAT_00d63afc */ "move", 12);
    builder->addState(/* DAT_00d63afc */ "move", 1);

    // Default transition from "move" to exit
    builder->addDefaultTransition(/* DAT_00d63afc */ "move", 0xFFFFFFFF);

    // Set timeout to 2
    builder->setTimeout(2);

    // Default transition from "doneNoPath" to exit
    builder->addDefaultTransition("doneNoPath", 0xFFFFFFFF);

    // Add state groups with IDs 4 and 6, same flags
    builder->addStateGroup(4, 0x20, 1);
    builder->addStateGroup(6, 0x20, 1);

    // Set timeout to 2 again
    builder->setTimeout(2);

    // Register this state machine with its hash and an execution callback
    builder->registerStateMachine(0x485311A7, &NPCChaseSM_execute, "NPCChaseSM");

    // Finalize the builder and apply all configuration
    builder->finalize();
}