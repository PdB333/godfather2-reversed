// FUNC_NAME: SystemManager::initializeGlobalSystem
void __cdecl SystemManager::initializeGlobalSystem(void)
{
    // Global flag indicating if the system manager has been initialized (DAT_0112a9f4)
    if (!g_systemInitialized)
    {
        // Allocate memory for the system object (size 0x218 = 536 bytes)
        SystemManager* system = (SystemManager*)allocator::allocate(0x218);
        if (system != nullptr)
        {
            // Call the constructor or initialization routine (FUN_006fdd70)
            SystemManager::constructor(system);
        }
    }
}