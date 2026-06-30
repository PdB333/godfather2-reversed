// FUNC_NAME: GodfatherGameManager::startUp
// Function address: 0x00613180
// Role: Initializes core game subsystems during game startup.
// Called from higher-level initialization (0x0042ef20).
void GodfatherGameManager::startUp(void) {
    // First three calls likely initialize core engine components
    initializeCoreComponent(); // FUN_00417560
    initializeCoreComponent();
    initializeCoreComponent();

    // Then initialize major subsystems
    initializeNetworking();    // FUN_00611f70
    initializeGameLogic();    // FUN_00612130
    registerGlobalData(&DAT_011f6b70); // FUN_00612210 - global data pointer
}