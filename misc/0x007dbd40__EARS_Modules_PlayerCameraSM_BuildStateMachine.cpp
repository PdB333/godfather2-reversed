// Xbox PDB: EARS_Modules_PlayerCameraSM_BuildStateMachine
// FUNC_NAME: PlayerCamera::initializeStateMachine
// Address: 0x007dbd40 - Initializes the player camera state machine (PlayerCameraSM) by registering states and handlers.
void PlayerCamera::initializeStateMachine()
{
    // Look up or create the state table by name
    StateTableHandle tableHandle = StateTableManager::findTable("playerCameraStateTable");
    
    // Check if the table is already initialized
    int32_t isInitialized = StateTableManager::isTableInitialized(tableHandle);
    if (isInitialized == 0)
    {
        // Create a new state machine instance
        StateMachineInstance* machine = StateMachineFactory::createInstance();
        
        // Associate the state table with this machine
        StateTableManager::setStateTable("playerCameraStateTable", machine);
        
        // Set the parent state table (none) with ID -1
        // +0x00: gPlayerCameraStateTable is the data structure for camera state table
        StateTableManager::setStateTableParent(&gPlayerCameraStateTable, -1);
        
        // Register state with ID 0x31 (49)
        StateTableManager::registerState(0x31);
        
        // Add a transition or handler for the state: hash 0x12f25c12, handler function at LAB_007dbcf0
        // and name "PlayerCameraSM"
        StateTableManager::addTransition(0x12f25c12, &PlayerCameraState_Update, "PlayerCameraSM");
        
        // Finalize the state table construction
        StateTableManager::finalizeStateTable();
    }
}