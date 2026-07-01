// Xbox PDB: EARS::Modules::OffPathFleeStateMachine::BuildInteriorFleeStateTable
// FUNC_NAME: OffPathFleeStateMachine::registerStates
void OffPathFleeStateMachine::registerStates(void)
{
    uint stateId;

    // Get a unique identifier for the state machine (likely a hash or index)
    stateId = getNextStateMachineId();

    // Create the state machine with name "offPathFleeSM"
    stateMachineCreate("offPathFleeSM", stateId);

    // Set initial state: offpathFleeInit (ID 0xFFFFFFFF means no initial state? Actually later set explicitly)
    setInitialState("offpathFleeInit", 0xFFFFFFFF);

    // State ID 0x13 (19) added
    addState(0x13); // likely offpathFleeInit state itself?

    // Add transition from state 5 to state? (flags: 0x4020, condition: 1)
    addTransition(5, 0x4020, 1); // 5: some state ID, 0x4020: transition flags, 1: target state?

    // Register transition events/conditions
    addEvent("preSeekToFleeNode", 0xF);           // event name, state ID
    addEvent("seekToCoverNode", 0x11);            // event name, state ID
    addEvent("cower", 4);                         // event, state ID

    // Set initial state explicitly now? Actually this sets initial state to "preSeekToFleeNode" with ID -1 again?
    setInitialState("preSeekToFleeNode", 0xFFFFFFFF);

    addEvent("turnTowards", 0xE);
    addEvent("seekToFleeNode", 4);
    setInitialState("seekToFleeNode", 0xFFFFFFFF);

    // Add a state table? "FollowPathST" with 1 transition?
    addStateTable("FollowPathST", 1);

    // Add conditional transition: from state 6, event "fleeToFleeFailed", flags 0x4000, condition 1
    addConditionalTransition("fleeToFleeFailed", 6, 0x4000, 1);

    addEvent("terminate", 10);
    addEvent("closeEnoughToFleeNode", 1);
    addStateEvent(0x23); // add state event (maybe event ID)
    setInitialState("closeEnoughToFleeNode", 0xFFFFFFFF);

    addEvent("turnTowards", 0xE);
    addEvent("fleeToFleeFailed", 4);
    setInitialState("fleeToFleeFailed", 0xFFFFFFFF);

    addState(0x25); // state ID 0x25
    addEvent("offpathFleeInit", 4);
    setInitialState("seekToCoverNode", 0xFFFFFFFF);

    addStateTable("FollowPathST", 1); // reuse follow path state table
    addEvent("terminate", 0xB);
    addEvent("cower", 0xD);
    addConditionalTransition("fleeToCoverFailed", 6, 0x4000, 1);
    addEvent("closeEnoughToCoverNode", 1);
    addStateEvent(0x23);
    setInitialState("closeEnoughToCoverNode", 0xFFFFFFFF);

    addEvent("cower", 0xD);
    addEvent("fleeToCoverFailed", 4);
    setInitialState("fleeToCoverFailed", 0xFFFFFFFF);

    addState(0x24);
    addEvent("offpathFleeInit", 4);
    setInitialState("turnTowards", 0xFFFFFFFF);

    addState(0xC); // state ID 12
    addState(0xD); // state ID 13
    addStateTable("turnToEntityTerminateTable", 1);
    addEvent("performAction", 0x14);
    addEvent("fleeOnGraph", 0x19);
    addEvent("cower", 1);
    addEvent("terminate", 10);
    setInitialState("performAction", 0xFFFFFFFF);

    addState(0x12); // state ID 18
    removeState(8); // likely a state removal (maybe an error)
    removeState(0x14);
    addStateEvent(0x15);
    addEvent("recover", 7);
    setInitialState("recover", 0xFFFFFFFF);

    addState(0x1F);
    addStateTable("recoverStateTable", 0);
    addEvent("fleeOnGraph", 0x19);
    addEvent("cower", 1);
    setInitialState("fleeOnGraph", 0xFFFFFFFF);

    addState(0x16);
    addEvent("terminate", 4);
    setInitialState("cower", 0xFFFFFFFF);

    addState(0xC);
    addState(0xD);
    addState(0x18);
    addState(0x26);
    removeState(0x1E);
    removeState(0x26);
    addStateTable("seekTargetTable", 1);
    addEvent("shouldCowerEnd", 0x18);
    addEvent("shouldCowerEnd", 0x21);
    addStateEvent(0x1C);
    setInitialState("shouldCowerEnd", 0xFFFFFFFF);

    addState(0x13);
    addEvent("terminate", 0x10);
    addEvent("playCowerEnd", 0xF);
    addEvent("playCowerEnd", 0x11);
    addEvent("cower", 0x1B);
    setInitialState("playCowerEnd", 0xFFFFFFFF);

    addState(0x1A);
    addStateTable("seekTargetTable", 1);
    addEvent("cowerEnded", 7);
    addStateEvent(0x1B);
    setInitialState("cowerEnded", 0xFFFFFFFF);

    addEvent("preSeekToFleeNode", 0xF);
    addEvent("seekToCoverNode", 0x11);
    setInitialState("combatCower", 0xFFFFFFFF);

    addState(0x19);
    removeState(0x1E);
    addEvent("offpathFleeInit", 0x18);
    addExplicitTransition("terminate", 2, DAT_00d5779c, 1); // based on a global flag (DAT)
    addEvent("terminate", 0x21);
    addStateEvent(0x1D);
    setInitialState("terminate", 0xFFFFFFFF);

    addState(2); // final state ID 2

    // Finalize the state machine registration
    finalizeStateMachine(0x996586b0, &offPathFleeInitializeCode, "OffPathFleeStateMachine");
    enableStateMachine();
    return;
}