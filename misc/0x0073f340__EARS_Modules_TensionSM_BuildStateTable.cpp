// Xbox PDB: EARS::Modules::TensionSM::BuildStateTable
// FUNC_NAME: TensionStateMachine::initialize
void TensionStateMachine::initialize(void)
{
    int iVar2;
    uint uVar1;

    uVar1 = getStateMachineID("TensionST");
    iVar2 = hasStateMachine(uVar1);
    if (iVar2 == 0) {
        uVar1 = getSomeGlobalValue();
        createStateMachine("TensionST", uVar1);
        setStatePriority(DAT_00d63420, 0xffffffff); // +0x10: unknown string constant, likely "TensionST" or priority string
        setStateMachineFlags(5, 0x8000, 1); // flags: 5=??, 0x8000, 1
        addState("DetermineNewTensionZone", 4); // state ID 4
        setStatePriority("DetermineNewTensionZone", 0xffffffff);
        addTransition(10); // transition from? to state ID 10? Or set transition timeout?
        addState("RELAXED", 0xb); // state ID 11
        addState("AWARE", 0xc); // state ID 12
        addState(DAT_00d638bc, 0xd); // +0x38bc: some string? "ALERT" or similar? => state ID 13
        addState("ACTION", 0xe); // state ID 14
        setStatePriority("RELAXED", 0xffffffff);
        addTransition(0xd); // transition to state 13
        addTransition(0xc); // transition to state 12
        setDefaultState("NPCActionST", 1);
        addTransitionCondition("DetermineNewTensionZone", 6, 0x8000, 1);
        addState("DetermineNewTensionZone", 10); // duplicate? or update state ID 10?
        setStatePriority("AWARE", 0xffffffff);
        addTransition(0xc);
        setDefaultState("NPCActionST", 1);
        addTransitionCondition("DetermineNewTensionZone", 6, 0x8000, 1);
        addState("DetermineNewTensionZone", 10);
        setStatePriority(DAT_00d638bc, 0xffffffff);
        addTransition(0xb);
        addTransitionFromState(0xb); // add transition from state 11?
        setDefaultState("NPCActionST", 1);
        addTransitionCondition("DetermineNewTensionZone", 6, 0x8000, 1);
        addState("DetermineNewTensionZone", 10);
        setStatePriority("ACTION", 0xffffffff);
        addTransition(0xb);
        addTransition(0xe);
        addTransitionFromState(0xb);
        addTransitionFromState(0xf); // state ID 15? maybe "COMBAT"?
        setDefaultState("NPCActionST", 1);
        addState("DetermineNewTensionZone", 10);
        addTransitionCondition("DetermineNewTensionZone", 6, 0x8000, 1);
        registerStateMachineEvent(0x390ca3ec, &LAB_0073f2b0, "TensionSM"); // event for tension state machine
        finalizeStateMachine();
    }
    return;
}