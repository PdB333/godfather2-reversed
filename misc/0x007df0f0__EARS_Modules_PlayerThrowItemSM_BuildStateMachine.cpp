// Xbox PDB: EARS_Modules_PlayerThrowItemSM_BuildStateMachine
// FUNC_NAME: PlayerThrowItemSM::initializeStateMachine
// Address: 0x007df0f0
// Role: Registers the state machine table, states, transitions, and update function for PlayerThrowItemSM.

void PlayerThrowItemSM::initializeStateMachine(void)
{
    // Create a new state machine instance and get its ID
    uint stateMachineId = StateMachine::create(); // FUN_009c8f80

    // Register the state machine table with a name and ID
    StateMachine::registerTable("playerThrowItemStateTable", stateMachineId); // FUN_004ad9d0

    // Add states with explicit names or IDs
    StateMachine::addState("throwStart", 0xFFFFFFFF); // FUN_004adae0
    StateMachine::addState(0x31); // FUN_004acf70
    StateMachine::addState(0x32); // FUN_004acff0

    // Add a transition: from state 0 to state 1 on event 9
    StateMachine::addTransition("terminate", 9, 0, 1); // FUN_004acd20

    // Add another state with name and ID
    StateMachine::addState("terminate", 0xFFFFFFFF); // FUN_004adae0
    StateMachine::addState(2); // FUN_004acf70

    // Register the update function for this state machine (hash of name)
    StateMachine::registerUpdateFunction(0xE90D7AB2, &PlayerThrowItemSM::update, "PlayerThrowItemSM"); // FUN_004adc90

    // Finalize the state machine setup
    StateMachine::finalize(); // FUN_004ada40
}