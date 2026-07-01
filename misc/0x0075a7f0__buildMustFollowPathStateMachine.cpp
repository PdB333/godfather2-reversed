// FUNC_NAME: buildMustFollowPathStateMachine

void buildMustFollowPathStateMachine()
{
    // Allocate a new state machine instance
    uVar1 = stateMachineManager_allocate(); // 0x009c8f80: returns handle/ID

    // Begin building the state machine with name "MustFollowPathST"
    stateMachine_begin("MustFollowPathST", uVar1); // 0x004ad9d0

    // Add an unnamed state? (DAT_00d63420 is likely a string constant)
    stateMachine_addState(&DAT_00d63420, 0xFFFFFFFF); // 0x004adae0, -1 as parent or flag

    // Add transition from current state to state ID 10
    stateMachine_addTransition(10); // 0x004acf70

    // Set transition condition: type 5, value 0x20, flags 1
    stateMachine_setTransitionCondition(5, 0x20, 1); // 0x004ad0f0

    // Add a state named "regularFollowPath" with ID 10
    stateMachine_addStateNamed("regularFollowPath", 10); // 0x004acc70

    // Set the state named "regularFollowPath" as active/child? with -1 flag
    stateMachine_addState("regularFollowPath", 0xFFFFFFFF); // 0x004adae0

    // Set initial state to "FollowPathST" with flag 1
    stateMachine_setInitialState("FollowPathST", 1); // 0x004acf10

    // Add transition to state ID 0x14 (20)
    stateMachine_addTransition(0x14); // 0x004acff0

    // Add transition with condition named "checkPosition", state ID 6, condition type 0x20, value 1
    stateMachine_addConditionalTransition("checkPosition", 6, 0x20, 1); // 0x004acd20

    // Add state "checkPosition" with ID 1
    stateMachine_addStateNamed("checkPosition", 1); // 0x004acc70

    // Set "checkPosition" state (no parent? -1)
    stateMachine_addState("checkPosition", 0xFFFFFFFF); // 0x004adae0

    // Add state "noClipFollowPath" with ID 0xB (11)
    stateMachine_addStateNamed("noClipFollowPath", 0xB); // 0x004acc70

    // Add state from DAT_00d63630 (string constant) with ID 0xC (12)
    stateMachine_addStateNamed(&DAT_00d63630, 0xC); // 0x004acc70

    // Add state from DAT_00d63afc with ID 0xD (13)
    stateMachine_addStateNamed(&DAT_00d63afc, 0xD); // 0x004acc70

    // Set state from DAT_00d63630 with -1 flag (child?)
    stateMachine_addState(&DAT_00d63630, 0xFFFFFFFF); // 0x004adae0

    // Add transitions for state ID 0xB
    stateMachine_addTransition(0xB); // 0x004acf70

    // Add transition to state ID 0xC
    stateMachine_addTransition(0xC); // 0x004acff0

    // Add transition from state ID 8
    stateMachine_addTransition(8); // 0x004acf70

    // Add transition to state ID 8
    stateMachine_addTransition(8); // 0x004acff0

    // Add state "regularFollowPath" with ID 0x11 (17)
    stateMachine_addStateNamed("regularFollowPath", 0x11); // 0x004acc70

    // Set "noClipFollowPath" state with -1 flag
    stateMachine_addState("noClipFollowPath", 0xFFFFFFFF); // 0x004adae0

    // Add transition from state ID 0xD
    stateMachine_addTransition(0xD); // 0x004acf70

    // Add transition to state ID 0xF (15)
    stateMachine_addTransition(0xF); // 0x004acff0

    // Add transition from state ID 8
    stateMachine_addTransition(8); // 0x004acf70

    // Add transition to state ID 8
    stateMachine_addTransition(8); // 0x004acff0

    // Add state "regularFollowPath" with ID 0x12 (18)
    stateMachine_addStateNamed("regularFollowPath", 0x12); // 0x004acc70

    // Add state from DAT_00d63afc with ID 0xE (14)
    stateMachine_addStateNamed(&DAT_00d63afc, 0xE); // 0x004acc70

    // Add state "noClipRePath" with ID 0xF (15)
    stateMachine_addStateNamed("noClipRePath", 0xF); // 0x004acc70

    // Set state 0xE as active/type (maybe "stateMarker")
    stateMachine_setStateActive(0xE); // 0x004ad070

    // Set "noClipRePath" state with -1 flag
    stateMachine_addState("noClipRePath", 0xFFFFFFFF); // 0x004adae0

    // Add transition from state ID 0x11
    stateMachine_addTransition(0x11); // 0x004acf70

    // Add transition from state ID 8
    stateMachine_addTransition(8); // 0x004acf70

    // Add transition to state ID 8
    stateMachine_addTransition(8); // 0x004acff0

    // Add transition to state ID 0x13 (19)
    stateMachine_addTransition(0x13); // 0x004acff0

    // Add state "noClipFollowPath" with ID 0x10 (16)
    stateMachine_addStateNamed("noClipFollowPath", 0x10); // 0x004acc70

    // Set state 0x12 as active/type
    stateMachine_setStateActive(0x12); // 0x004ad070

    // Set state from DAT_00d63afc with -1 flag
    stateMachine_addState(&DAT_00d63afc, 0xFFFFFFFF); // 0x004adae0

    // Add transition from state ID 0x10
    stateMachine_addTransition(0x10); // 0x004acf70

    // Add transition from state ID 2
    stateMachine_addTransition(2); // 0x004acf70

    // Register the state machine with a callback address (function pointer at LAB_0075a510) and name "MustFollowPathStateMachine"
    stateMachine_register(0xE7934180, &LAB_0075a510, "MustFollowPathStateMachine"); // 0x004adc90

    // Finalize the state machine construction
    stateMachine_finalize(); // 0x004ada40

    return;
}