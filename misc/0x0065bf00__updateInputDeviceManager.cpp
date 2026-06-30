// FUNC_NAME: updateInputDeviceManager

// Global input device manager instance (at 0x01203740)
InputDeviceManager g_inputDeviceManager;

// Static initialization flag (at 0x0120588f)
static bool g_inputDeviceManagerInitialized = false;

void updateInputDeviceManager(int param1, int param2) {
    // One-time initialization on first call
    if (!g_inputDeviceManagerInitialized) {
        g_inputDeviceManagerInitialized = true;
        // Initialize and setup the input device manager
        initializeInputDeviceManager(&g_inputDeviceManager);
        setupInputDeviceManager(&g_inputDeviceManager);
    }
    // Process the input device manager with the given parameters
    processInputDeviceManager(&g_inputDeviceManager, param1, param2);
}