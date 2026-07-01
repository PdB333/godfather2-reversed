// Xbox PDB: EARS_Modules_PlayerStrafeMovementSM_BuildStateMachine
// FUNC_NAME: PlayerStrafeMovementSM::initStateMachine
void PlayerStrafeMovementSM::initStateMachine()
{
    // Allocate a new state table for this state machine (FUN_009c8f80)
    void* stateTable = getStateMachineAllocator();

    // Register the state table under the name "playerStrafeMovementStateTable"
    registerStateTable("playerStrafeMovementStateTable", stateTable);

    // Add a state called "strafe" with a default parameter (-1 = no initial transition)
    addState("strafe", 0xffffffff);

    // Set state machine flags (0x31 = combination of flags, e.g., allow strafe movement)
    setStateMachineFlags(0x31);

    // Duplicate call? Possibly sets additional flags or initial state index
    setStateMachineFlags(0x31);

    // Register a transition from state with hash 0xda1e5cf9 to function at LAB_007d2af0
    // The label identifies the state machine for debugging
    registerTransition(0xda1e5cf9, reinterpret_cast<void*>(0x007d2af0), "PlayerStrafeMovementSM");

    // Finalize state machine construction (builds transition tables, etc.)
    finalizeStateMachine();
}