// FUNC_NAME: setGlobalCallback
typedef void (*GlobalCallbackFunc)(void);

// Global function pointer stored at 0x0110ac08
GlobalCallbackFunc g_globalCallback = nullptr;

// Stores a callback function pointer into the global slot.
// Likely called during initialization to register a handler.
void setGlobalCallback(GlobalCallbackFunc callback) {
    g_globalCallback = callback;
}