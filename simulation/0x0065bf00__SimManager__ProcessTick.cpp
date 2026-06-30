// FUNC_NAME: SimManager::ProcessTick
// Address: 0x0065bf00
// This function performs lazy initialization of the global SimManager singleton and then calls its tick function with the provided parameters.

static bool s_simManagerInitialized = false;
static SimManager g_simManager; // at address DAT_01203740

void SimManager::ProcessTick(uint32_t param1, uint32_t param2)
{
    if (!s_simManagerInitialized)
    {
        s_simManagerInitialized = true;
        SimManager::Init(&g_simManager);   // FUN_00662100 - initializes base structures
        SimManager::Start(&g_simManager);  // FUN_006622a0 - starts manager subsystems
    }
    SimManager::Tick(&g_simManager, param1, param2); // FUN_00662350 - main update with parameters
}