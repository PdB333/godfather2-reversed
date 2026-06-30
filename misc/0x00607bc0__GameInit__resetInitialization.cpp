// FUNC_NAME: GameInit::resetInitialization
int resetInitialization(void) {
    // Global flag indicating whether initialization has been done
    g_bInitialized = 0;            // DAT_01205759 = 0
    // Perform subsystem teardown or reset
    FUN_00608f10();                // likely deinit call
    // Build a temporary structure from a global configuration value
    SomeInitParams params;
    params.field0 = g_configValue; // DAT_00e2b1a4
    params.field4 = g_configValue; // same value
    params.field8 = 0;             // zero-initialized third field
    // Execute the second initialization step using the parameters
    FUN_00609090(&params);         // likely a constructor or setup call
    return 0;
}