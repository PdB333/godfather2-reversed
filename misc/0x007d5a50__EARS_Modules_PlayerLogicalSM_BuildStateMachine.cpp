// Xbox PDB: EARS_Modules_PlayerLogicalSM_BuildStateMachine
// FUNC_NAME: Player::initializeStateMachines
void Player::initializeStateMachines()
{
    // Look up the "playerLogicalStateTable" - main state table for player logic
    StateTable* logicalStateTable = StateMachineManager::findStateTable("playerLogicalStateTable");

    // If not yet created, initialize all state tables and state machines
    if (logicalStateTable == nullptr) {
        // Create a new state table for player logical states
        logicalStateTable = StateMachineManager::createStateTable();
        StateMachineManager::registerStateTable("playerLogicalStateTable", logicalStateTable);

        // Initialize global state table data block (size: -1 means unknown or all)
        StateMachineManager::initGlobalStateTable(&g_GlobalStateTableData, 0xffffffff);

        // Register specific state table types with flag 1 (active/valid)
        StateMachineManager::registerStateTableType("playerInventoryBrowserStateTable", 1);
        StateMachineManager::registerStateTableType("playerTargetingStateTable", 1);
        StateMachineManager::registerStateTableType("playerActionableTargetStateTable", 1);

        // Register individual state IDs (0x31..0x36) - corresponds to PlayerSM sub-states
        StateMachineManager::registerState(0x31);  // e.g., kStateIdle
        StateMachineManager::registerState(0x32);  // e.g., kStateMove
        StateMachineManager::registerState(0x33);  // e.g., kStateAim
        StateMachineManager::registerState(0x34);  // e.g., kStateShoot
        StateMachineManager::registerState(0x35);  // e.g., kStateCover
        StateMachineManager::registerState(0x36);  // e.g., kStateGrapple

        // Register the logical state machine definition (hash of "PlayerLogicalSM")
        // LAB_007d59f0 is the transition table definition function
        StateMachineManager::registerStateMachine(
            0x44b1dfaf,                    // CRC32 of "PlayerLogicalSM"
            reinterpret_cast<StateMachineDef>(&PlayerLogicalSM::transitionTable),
            "PlayerLogicalSM"
        );

        // Finalize state table registration
        StateMachineManager::finalize();
    }
}