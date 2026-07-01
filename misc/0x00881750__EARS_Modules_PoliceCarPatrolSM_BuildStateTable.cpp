// Xbox PDB: EARS_Modules_PoliceCarPatrolSM_BuildStateTable
// FUNC_NAME: PoliceCarPatrolSM::buildStateMachine

void PoliceCarPatrolSM::buildStateMachine(void)
{
    // Get the state machine builder object (returns some handle/pointer)
    uVar1 = getStateMachineBuilder();

    // Set the root state of the state machine
    setRootState("PoliceCarRootST", uVar1);

    // Set default terminal state (0xFFFFFFFF = no transition?)
    setTerminalState(&DAT_00d63420, 0xFFFFFFFF);

    // Add state with ID 0xC (12)
    addState(0xC);

    // Add transitions: string -> state ID
    addTransition("driveAround", 0xC);
    addTransition("approachScene", 4);

    // Set terminal state again for "driveAround" path
    setTerminalState("driveAround", 0xFFFFFFFF);

    // Add entry actions? (or additional states)
    addEntryAction(10);
    addEntryAction(0xC);

    // Add more transitions
    addTransition("driveAroundEBrake", 0x16);
    addTransition("driveAroundEBrake", 0x15);
    addTransition("letCopsOut", 10);
    addTransition("letCopsOut", 0xF);
    addTransition("approachScene", 0xD);

    // Set terminal "driveAroundEBrake"
    setTerminalState("driveAroundEBrake", 0xFFFFFFFF);

    // Add state 0x12 (18)
    addState(0x12);
    addEntryAction(10);
    addEntryAction(0xE);

    addTransition("letCopsOut", 10);
    addTransition("letCopsOut", 0x12);
    addTransition("letCopsOut", 0x11);
    addTransition("letCopsOut", 0x17);

    // Conditional transition: stateName, target, globalCondition, param
    addConditionalTransition("letCopsOut", 2, _DAT_00e541d8, 1);

    // Terminal "approachScene"
    setTerminalState("approachScene", 0xFFFFFFFF);

    addEntryAction(0xD);
    addEntryAction(10);
    addEntryAction(0xE);

    addTransition("letCopsOut", 10);
    addTransition("letCopsOut", 0xF);
    addTransition("letCopsOut", 0xB);
    addTransition("letCopsOut", 0x14);
    addTransition("prepareForEBrake", 0x16);
    addTransition("prepareForEBrake", 0x15);
    addTransition("letCopsOut", 0x11);
    addTransition("letCopsOut", 0x12);

    setTerminalState("prepareForEBrake", 0xFFFFFFFF);

    addState(0x12);
    addEntryAction(10);
    addEntryAction(0xE);

    addTransition("letCopsOut", 10);
    addTransition("letCopsOut", 0xB);
    addTransition("letCopsOut", 0x11);
    addTransition("letCopsOut", 0x12);
    addTransition("letCopsOut", 0x17);

    addConditionalTransition("letCopsOut", 2, _DAT_00e541d8, 1);

    setTerminalState("letCopsOut", 0xFFFFFFFF);

    addState(0x10);
    addState(0x11);
    addEntryAction(0x11);

    addTransition("occupantsExit", 10);
    addTransition("occupantsExit", 0x10);

    setTerminalState("occupantsExit", 0xFFFFFFFF);

    addState(0xF);
    addEntryAction(10);

    addTransition("waitForOccupantsToExit", 10);

    setTerminalState("waitForOccupantsToExit", 0xFFFFFFFF);

    addEntryAction(10);

    addTransition(&DAT_00d63afc, 0x13);
    setTerminalState(&DAT_00d63afc, 0xFFFFFFFF);

    addState(0xB);
    addState(2);

    // Register the state machine with a hash and callback address
    registerStateMachine(0x6DC822DC, &LAB_008816B0, "PoliceCarPatrolSM");

    // Finalize builder
    finalizeBuilder();

    return;
}