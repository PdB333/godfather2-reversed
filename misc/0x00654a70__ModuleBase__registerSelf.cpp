// FUNC_NAME: ModuleBase::registerSelf
void CModuleBase::registerSelf(void)
{
    // Static flag to ensure one-time initialization of the module manager (DAT_0120588f)
    static bool s_managerInitialized = false;
    // Static instance of the module manager (DAT_01203740)
    static CModuleManager s_moduleManager;

    if (!s_managerInitialized)
    {
        s_managerInitialized = true;
        s_moduleManager.initialize(); // FUN_00662100 - Initialize the manager's internal state
        s_moduleManager.startup();    // FUN_006622a0 - Start up the manager (e.g., allocate resources)
    }

    // Register this module with the manager under ID 8
    // FUN_00662350 - takes (this, moduleID, manager)
    s_moduleManager.registerModule(this, 8);
}