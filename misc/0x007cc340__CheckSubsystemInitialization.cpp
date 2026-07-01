// FUNC_NAME: CheckSubsystemInitialization
bool CheckSubsystemInitialization(void)
{
    // +0x0 Global flags: g_subsystemEnabled, g_subsystemReady, g_subsystemInitResult
    g_subsystemReady = false;
    bool result = false;

    if (g_subsystemEnabled != 0) {
        g_subsystemInitResult = InitSubsystem(); // FUN_00849a30 - performs subsystem initialization
        if (g_subsystemInitResult != 0) {
            g_subsystemReady = true;
            return true;
        }
        g_subsystemInitResult = 0;
        result = g_subsystemReady; // will be false
    }
    g_subsystemReady = result;
    return result;
}