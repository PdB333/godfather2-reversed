// Xbox PDB: EARS_Modules_PlayerJumpSM_BuildStateMachine
// FUNC_NAME: PlayerJumpSM::initStateTable
void PlayerJumpSM::initStateTable(void)
{
    int stateMachineId = getStateMachineId();                     // FUN_009c8f80 - returns current state machine ID
    registerStateTable("playerJumpStateTable", stateMachineId);   // FUN_004ad9d0

    setStateTransition("terminate", 0xffffffff);                  // FUN_004adae0 - initial transition to terminate (no timeout)
    addState(0x31);                                               // FUN_004acf70 - add state ID 0x31 (likely jump state)
    addState(0x32);                                               // FUN_004acff0
    addState(0x33);                                               // FUN_004acff0
    addState(0x34);                                               // FUN_004acff0
    addStateTransition("terminate", 0x13);                        // FUN_004acc70 - transition from terminate to state 0x13?
    setStateTransition("terminate", 0xffffffff);                  // FUN_004adae0 - reset terminate transition (no timeout)
    addState(2);                                                  // FUN_004acf70 - add state ID 2
    registerTransitionHandler(0xf3131a29, &LAB_007d1b50, "PlayerJumpSM"); // FUN_004adc90 - register handler for transition ID 0xf3131a29
    finalizeStateMachine();                                       // FUN_004ada40
}