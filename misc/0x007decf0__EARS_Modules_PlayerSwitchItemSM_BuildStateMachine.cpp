// Xbox PDB: EARS_Modules_PlayerSwitchItemSM_BuildStateMachine
// FUNC_NAME: PlayerSwitchItemSM::initialize
void PlayerSwitchItemSM::initialize()
{
    // Allocate or obtain the state table factory (e.g., from a singleton manager)
    void* factory = StateMachineFactory::getInstance(); // FUN_009c8f80

    // Register the main "playerSwitchItemStateTable" with the factory
    StateTableManager::registerTable("playerSwitchItemStateTable", factory); // FUN_004ad9d0

    // Add states to the table
    StateTableManager::addState("conceal", 0x13); // FUN_004adae0 — note: 0x13 = conceal state ID
    StateTableManager::addState("reveal", 4);     // FUN_004adae0 — note: 4 = reveal state ID

    // Set transitions from conceal (no exit? 0xFFFFFFFF = no next state)
    StateTableManager::addTransition("conceal", 0xFFFFFFFF); // FUN_004acc70

    // Set initial state for the conceal sub‑table
    StateTableManager::setInitialState("playerConcealItemStateTable", 0); // FUN_004acf10

    // Add transitions from reveal
    StateTableManager::addTransition("reveal", 0x14);         // event 0x14 → trigger reveal → terminate?
    StateTableManager::addTransition("terminate", 4);         // event 4 → terminate state

    // Set transition from reveal (no exit)
    StateTableManager::addTransition("reveal", 0xFFFFFFFF);   // FUN_004adae0

    // Set some count/limit (0x31 = 49)
    StateTableManager::setStateCount(0x31); // FUN_004acf70

    // Set initial state for the reveal sub‑table
    StateTableManager::setInitialState("playerRevealItemStateTable", 0); // FUN_004acf10

    // Add transition from terminate
    StateTableManager::addTransition("terminate", 4);         // event 4

    // Set some value (2 = number of sub‑tables?)
    StateTableManager::setSubTableCount(2); // FUN_004acf70

    // Register the complete state machine with the name "PlayerSwitchItemSM"
    StateMachineRegistry::registerStateMachine(0x4C774C1F, &LAB_007decc0, "PlayerSwitchItemSM"); // FUN_004adc90

    // Finalize/build the state machine
    StateMachineRegistry::build(); // FUN_004ada40
}