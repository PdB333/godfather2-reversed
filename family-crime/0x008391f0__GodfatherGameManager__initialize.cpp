// FUNC_NAME: GodfatherGameManager::initialize
// Function address: 0x008391f0
// This function initializes the GodfatherGameManager and registers the main game loop callback.
void __fastcall GodfatherGameManager::initialize(void) {
    // Call internal initialization routine (likely sets up subsystems or base class)
    this->initSubsystems();  // FUN_00839c40

    // Perform global engine initialization (e.g., EARS framework startup)
    engineGlobalInit();  // FUN_008f1e00

    // Look up the "GameMainLoop" callback by name
    int callbackId = findCallback("GameMainLoop");  // FUN_00683280

    // Register the callback so it will be called each frame
    addCallback(callbackId);  // FUN_006833d0

    // Finalize initialization (e.g., enable subsystems, start threads)
    finalizeInit();  // FUN_0067c960
}