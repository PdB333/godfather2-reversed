// FUNC_NAME: registerInitializationFunctions
void registerInitializationFunctions(void)
{
    // Register various initialization callbacks for game subsystems
    registerCallback(FUN_0086d3a0);          // e.g., AudioSystem::init
    registerCallback((void*)&LAB_009b61e0);  // string or data pointer for registration
    registerCallback(FUN_0086cdf0);          // e.g., InputManager::init
    registerCallback(FUN_00460d40);          // e.g., ScriptEngine::setup
    registerCallback((void*)&LAB_00460d80);  // string or data
    registerCallback((void*)&LAB_00472420);  // 
    registerCallback((void*)&LAB_00472440);  //
    registerCallback((void*)&LAB_00861730);  //
    registerCallback((void*)&LAB_00545ef0);  //
    registerCallback(FUN_00545f00);          // e.g., Networking::register
    registerCallback((void*)&LAB_00876fb0);  //
    registerCallback((void*)&LAB_00861740);  //
    registerCallback((void*)&LAB_0087e490);  //
    registerCallback(FUN_00861ba0);          // e.g., UIController::registerCommands
    return;
}