// FUNC_NAME: buildNPCMeleeSupporterStateMachine
void buildNPCMeleeSupporterStateMachine(void)
{
    // Get the global state machine manager (EARS framework)
    StateMachineManager* smMgr = getStateMachineManager();

    // Create the primary state machine for NPC melee supporter
    createStateMachine("NPCMeleeSupporterST", smMgr);

    // Add transition: from any state to state ID 0xFFFF (likely "any" or "global")
    addTransition(&gNPCMeleeSupporterSM, 0xFFFFFFFF); // 0xFFFFFFFF == any state

    // --- State 0x23 (initial/entry state?) ---
    addState(0x23);
    setAction(&gNPCMeleeSupporterToggle, 0x12); // likely action ID for toggle
    setAction(&gNPCMeleeSupporterReaction, 4);  // reaction type
    addTransition(&gNPCMeleeSupporterReaction, 0xFFFFFFFF); // transition out on any condition

    // --- State 0x21 variable setup ---
    // Add a variable with hash 0xD3965004, initial value 1
    addVariable(0x21, 0xD3965004, 1);

    // --- State 0x24 ---
    addState(0x24);
    // probably no explicit actions, but two addStateFlags?
    addStateFlag(0x24); // maybe "interruptible" flag
    addStateFlag(0x24); // duplicate?

    // --- State 0x25 ---
    addState(0x25);
    setAction(&gNPCMeleeSupporterToggle, 0x12); // same toggle action
    setAction("advance", 0x13);                // "advance" action type
    setAction("retreat", 0x14);
    setAction("circleLeft", 0x15);
    setAction("circleRight", 0x16);
    addTransition("advance", 0xFFFFFFFF);       // from advance to any

    // --- Sub-state machine: Chase ---
    addSubStateMachine("NPCChaseST", 1);        // 1 = priority

    // --- State 0x26 (chase?) ---
    addState(0x26);
    setAction(&gNPCMeleeSupporterToggle, 0x12);
    setAction(&gNPCMeleeSupporterReaction, 0x19);
    setAction(&gNPCMeleeSupporterReaction, 1); // override?
    addTransition("retreat", 0xFFFFFFFF);

    // --- State 0x26 (again?) with flags ---
    addState(0x26);
    addStateFlag(8);    // flag 8
    addStateFlag(0x29); // flag 0x29
    setAction(&gNPCMeleeSupporterToggle, 0x12);
    setAction(&gNPCMeleeSupporterReaction, 0x1A);
    setAction(&gNPCMeleeSupporterReaction, 0x1B);
    addTransition("circleLeft", 0xFFFFFFFF);

    // --- State 0x27 ---
    addState(0x27);
    addStateFlag(8);
    addStateFlag(0x29);
    setAction(&gNPCMeleeSupporterToggle, 0x12);
    setAction(&gNPCMeleeSupporterReaction, 0x1C);
    setAction(&gNPCMeleeSupporterReaction, 0x17);
    setAction(&gNPCMeleeSupporterReaction, 0x1B);
    setAction(&gNPCMeleeSupporterReaction, 0x1D);
    addTransition("circleRight", 0xFFFFFFFF);

    // --- State 0x28 ---
    addState(0x28);
    addStateFlag(8);
    addStateFlag(0x29);
    setAction(&gNPCMeleeSupporterToggle, 0x12);
    setAction(&gNPCMeleeSupporterReaction, 0x1C);
    setAction(&gNPCMeleeSupporterReaction, 0x18);
    setAction(&gNPCMeleeSupporterReaction, 0x1B);
    setAction(&gNPCMeleeSupporterReaction, 0x1D);
    addTransition(&gNPCMeleeSupporterToggle, 0xFFFFFFFF);

    // --- Final state ---
    addState(2);    // 2 = exit or wait?
    // Setup entry callback for state machine
    setStateMachineEntryCallback(0x48F032EC, &NPCMeleeSupporterSMEntryCallback, "NPCMeleeSupporterSM");
    // Finalize and return
    finalizeStateMachine();
}