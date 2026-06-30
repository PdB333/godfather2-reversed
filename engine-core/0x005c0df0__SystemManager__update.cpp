// FUNC_NAME: SystemManager::update
// Address: 0x005c0df0
// Role: Update system state, initializing if necessary
int SystemManager::update(void)
{
    int isReady = isSystemReady(); // FUN_005c0cc0 - check if system is ready
    if (isReady != 0) {
        if (g_systemInitialized == 0) { // DAT_01205664 - global initialization flag
            initializeSystem(); // FUN_005c39d0 - perform one-time initialization
        }
        updateSystemInternal(); // FUN_005c28c0 - per-frame update
    }
    return 0;
}