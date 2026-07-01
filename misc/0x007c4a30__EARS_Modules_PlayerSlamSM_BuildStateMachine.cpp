// Xbox PDB: EARS_Modules_PlayerSlamSM_BuildStateMachine
// FUNC_NAME: PlayerSlamStateMachine::initStateMachine
void PlayerSlamStateMachine::initStateMachine(void)
{
    uint hash = getStateMachineHash(); // FUN_009c8f80 returns hash ID for this state machine type
    registerStateTable("playerSlamStateTable", hash); // FUN_004ad9d0 - register the state table
    addState("enter", 0xffffffff); // FUN_004adae0 - add state with ID 0xffffffff (default/entry)
    addStateExit(0x1b); // FUN_004acf70 - set exit action for state 0x1b
    addState("slamforward", 0x13); // FUN_004acc70 - add state "slamforward" with ID 0x13
    addState("slamleft", 0x14);
    addState("slamright", 0x15);
    addState("burnleft_in", 0x16);
    addState("burnright_in", 0x17);
    addState("slamforward", 0xffffffff); // overwriting? or setting initial? Actually FUN_004adae0 may set transition or initial state

    // Transition from "enter" to "slamforward"? Let's interpret FUN_004ad0f0(0x16,0x43,1) as something else.
    // Actually FUN_004ad0f0 likely adds a transition: from state, to state, condition.
    // Here it's used many times. We'll rename accordingly.
    addTransition(0x16, 0x43, 1); // FUN_004ad0f0: from burnleft_in (0x16) to 0x43 with condition data 1
    addStateExit(0x18);
    addStateExit(0x1b);
    addStateExit(0x32);
    addStateExit(0x35);
    addStateExit(0x38);
    addTransition(0x34, 0x43, 1); // FUN_004ad130: same but different args? Actually it's FUN_004ad130 not 0f0, maybe another transition function
    addStateExit(0x3b);
    setStateEnterAction(0x3c); // FUN_004ad070: set enter action for state 0x3c
    setTrackTable("trackToPositionAndDirectionStateTable", 1); // FUN_004acf10: set tracking state table name with flag 1
    addState("terminate", 1); // FUN_004acc70: add "terminate" state with ID 1? (note: previously addState used 0xffffffff for "slamforward" so maybe this is different)

    // Reset initial state for "slamleft"
    setInitialState("slamleft", 0xffffffff); // FUN_004adae0 used again, probably set initial state for a subtable
    addTransition(0x16, 0x44, 1);
    addStateExit(0x18);
    addStateExit(0x1b);
    addStateExit(0x32);
    addStateExit(0x35);
    addStateExit(0x38);
    addTransition(0x34, 0x44, 1);
    addStateExit(0x30);
    setTrackTable("trackToPositionAndDirectionStateTable", 1);
    addState("terminate", 1);
    setInitialState("slamright", 0xffffffff);
    addTransition(0x16, 0x45, 1);
    addStateExit(0x18);
    addStateExit(0x1b);
    addStateExit(0x32);
    addStateExit(0x35);
    addStateExit(0x38);
    addTransition(0x34, 0x45, 1);
    addStateExit(0x30);
    setTrackTable("trackToPositionAndDirectionStateTable", 1);
    addState("terminate", 1);
    setInitialState("burnleft_in", 0xffffffff);
    addTransition(0x16, 0x46, 1);
    addStateExit(0x18);
    addStateExit(0x1b);
    addStateExit(0x30);
    addStateExit(0x3d);
    setTrackTable("trackToPositionAndDirectionStateTable", 1);
    addState("burnleft_hold", 7); // Note: different ID (7) for state name
    setInitialState("burnleft_hold", 0xffffffff);
    addTransition(0x16, 0x47, 1);
    addStateExit(0x18);
    addStateExit(0x39);
    setStateEnterAction(0x3a);
    setStateStayAction(0x37); // FUN_004acff0: set stay/update action for state 0x37
    setStateStayAction(0x36);
    addState("burnleft_out", 0x18);
    setInitialState("burnleft_out", 0xffffffff);
    addTransition(0x16, 0x48, 1);
    addStateExit(0x18);
    addState("terminate", 7);
    setInitialState("burnright_in", 0xffffffff);
    addTransition(0x16, 0x49, 1);
    addStateExit(0x18);
    addStateExit(0x1b);
    addStateExit(0x30);
    addStateExit(0x3d);
    setTrackTable("trackToPositionAndDirectionStateTable", 1);
    addState("burnright_hold", 7);
    setInitialState("burnright_hold", 0xffffffff);
    addTransition(0x16, 0x4a, 1);
    addStateExit(0x18);
    addStateExit(0x39);
    setStateEnterAction(0x3a);
    setStateStayAction(0x37);
    setStateStayAction(0x36);
    addState("burnright_out", 0x18);
    setInitialState("burnright_out", 0xffffffff);
    addTransition(0x16, 0x4b, 1);
    addStateExit(0x18);
    addState("terminate", 7);
    setInitialState("terminate", 0xffffffff);
    addStateExit(2); // set exit action for state 2
    registerStateMachine(0x6bda3054, &onStateMachineEvent, "PlayerSlamSM"); // FUN_004adc90: register the state machine with a handler (LAB_007c44b0 is address of event handler)
    finalizeStateMachine(); // FUN_004ada40
    return;
}
```