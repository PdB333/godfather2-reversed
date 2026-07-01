// FUNC_NAME: FollowPathStateMachine::buildFSM

void FollowPathStateMachine::buildFSM(void)
{
    // Get the state machine factory or manager
    StateMachineFactory* factory = getStateMachineFactory();

    // Set the name "FollowPathST" on the builder
    setFSMClassName(factory, "FollowPathST");

    // Set a default transition (likely to idle or initial state)
    setDefaultTransition(factory, 0);

    // Push a state stack? Or set options?
    pushStateOptions(factory, 10);

    // Add states with their IDs
    addState(factory, "blocked", 0x1c);
    addState(factory, "seekToTarget", 0xd);
    addState(factory, "findPath", 0xe);

    // Define a transition from state? The string is "clearStrafeAndReorient" with ID 1
    defineTransition(factory, "clearStrafeAndReorient", 1);

    pushStateOptions(factory, 0x20);
    addState(factory, "seekToGraph", 4);

    defineTransition(factory, "seekToGraph", 2);

    // Add a conditional transition: ID 3, event 0x20, condition 1
    addConditionalTransition(factory, 3, 0x20, 1);

    // Push more state options
    pushStateOptions(factory, 0xb);
    pushStateOptions(factory, 0x19);
    pushStateOptions(factory, 0x1a);

    // Define a composite state named "SeekToPositionST" with ID 1
    defineCompositeState(factory, "SeekToPositionST", 1);

    addState(factory, "blocked", 0x1b);
    addState(factory, "blocked", 0x1c);

    // Define a timed transition: from "blocked" (6) with event 0x20, condition 1
    defineTimedTransition(factory, "blocked", 6, 0x20, 1);

    addState(factory, "seekToTarget", 0x13);
    addState(factory, "initGraphClient", 0x14);
    addState(factory, "seekToSpecialNode", 0xc);
    addState(factory, "seekToGraph", 0x22);

    // Finalize last added state? Or set exit?
    finalizeState(factory, 0xc);

    // Another conditional transition with ID 4, event 0x20, condition 1
    addConditionalTransition(factory, 4, 0x20, 1);

    defineTransition(factory, "findPath", 3);

    pushStateOptions(factory, 0xe);
    // Set default entry for state? Or set as initial?
    setInitialState(factory, 0xf);

    addState(factory, "seekToGraph", 10);
    addState(factory, "seekToTarget", 0x12);
    addState(factory, "findPathFailure", 0x11);
    addState(factory, "blocked", 0x1c);

    finalizeState(factory, 0x23);
    finalizeState(factory, 0x10);

    defineTransition(factory, "findPathFailure", 4);

    pushStateOptions(factory, 0x17);
    addState(factory, "noPathDone", 4);

    defineTransition(factory, "initGraphClient", 5);

    pushStateOptions(factory, 0x16);
    addState(factory, "followGraphClient", 4);

    defineTransition(factory, "followGraphClient", 6);

    pushStateOptions(factory, 0xb);
    setInitialState(factory, 0x15);
    setInitialState(factory, 0x24);

    addState(factory, "clearStrafeAndReorient", 0x1d);
    addState(factory, "blocked", 0x1c);
    addState(factory, "followGraphIdle", 0x16);
    addState(factory, "noPathDone", 0x15);
    addState(factory, "blocked", 0x18);
    addState(factory, "seekToSpecialNode", 0x1e);
    addState(factory, "seekToTarget", 0xb);
    addState(factory, "seekToTarget", 0x10);
    addState(factory, "blocked", 0xf);

    finalizeState(factory, 0xc);

    defineTransition(factory, "seekToSpecialNode", 7);

    defineCompositeState(factory, "SeekToPositionST", 1);

    addState(factory, "blocked", 0x18);
    addState(factory, "blocked", 0x1f);
    addState(factory, "reachedSpecialNode", 1);

    finalizeState(factory, 0x21);

    defineTransition(factory, "reachedSpecialNode", 8);

    addConditionalTransition(factory, 3, 0x20, 1);

    defineCompositeState(factory, "SpecialMotionST", 1);

    defineTimedTransition(factory, "blocked", 6, 0x20, 1);

    addState(factory, "postSpecialNode", 1);

    finalizeState(factory, 0x22);

    addConditionalTransition(factory, 4, 0x20, 1);

    defineTransition(factory, "postSpecialNode", 9);

    addState(factory, "reachedSpecialNode", 0x21);
    addState(factory, "followGraphClient", 4);

    defineTransition(factory, "followGraphIdle", 10);

    pushStateOptions(factory, 0x1c);
    pushStateOptions(factory, 8);
    setInitialState(factory, 8);

    addState(factory, &DAT_00d63420, 0x17);
    addState(factory, &DAT_00d63afc, 0x19);

    defineTransition(factory, "seekToTarget", 0xb);

    addConditionalTransition(factory, 3, 0x20, 1);

    pushStateOptions(factory, 0xb);
    pushStateOptions(factory, 0x11);

    defineCompositeState(factory, "SeekToPositionST", 1);

    addState(factory, "blocked", 0x1c);

    defineTimedTransition(factory, "blocked", 6, 0x20, 1);

    addState(factory, &DAT_00d63afc, 1);

    finalizeState(factory, 0xc);

    addConditionalTransition(factory, 4, 0x20, 1);

    defineTransition(factory, "waitGeo", 0xc);

    pushStateOptions(factory, 0x1d);
    pushStateOptions(factory, 8);
    setInitialState(factory, 8);

    addState(factory, &DAT_00d63420, 0x1a);

    defineTransition(factory, "blocked", 0xd);

    pushStateOptions(factory, 0x25);
    pushStateOptions(factory, 0xd);
    addState(factory, "noPathDone", 4);

    defineTransition(factory, "noPathDone", 0xe);

    pushStateOptions(factory, 0x18);
    pushStateOptions(factory, 2);

    defineTransition(factory, &DAT_00d63afc, 0xf);

    pushStateOptions(factory, 0x1f);
    pushStateOptions(factory, 2);

    // Register the state machine with an entry function and debug name
    registerStateMachine(0x6862a74c, &entryFunction_00757b00, "FollowPathStateMachine");

    // Finalize building
    finalizeBuild();

    return;
}