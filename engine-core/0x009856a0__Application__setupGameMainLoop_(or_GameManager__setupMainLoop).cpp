// FUNC_NAME: Application::setupGameMainLoop (or GameManager::setupMainLoop)
// Address: 0x009856a0
// This function initializes and starts the game's main loop, setting the update
// interval based on the requested mode (1 = 60fps? 2 = 30fps?). It involves a
// virtual call through the global application singleton, registering a "GameMainLoop"
// callback, and finally enabling the main loop.

// Global application engine singleton (0x01129a74)
extern void* g_pApplication;

// Global main loop update interval in ms (0x00e5672c)
extern int32_t g_mainLoopUpdateInterval;

// Internal engine functions
void initBeforeMainLoop();                  // FUN_008f1e00
uint32_t createNamedFunction(const char*);  // FUN_00683280
void registerNamedFunction(uint32_t);       // FUN_006833d0
void startMainLoop();                       // FUN_0067c920

void setupGameMainLoop(int32_t mode)
{
    // Perform any pre-main-loop initialization
    initBeforeMainLoop();

    // Select update interval based on the requested mode
    if (mode == 1) {
        g_mainLoopUpdateInterval = 0x19; // 25 ms (40 fps)
    } else if (mode == 2) {
        g_mainLoopUpdateInterval = 0x11; // 17 ms (60 fps)
    }

    // Call virtual method at offset +0x2c on the application singleton.
    // Likely prepares the main loop (e.g., set up timer or callback infrastructure).
    (*(void (**)(void))(*((uint32_t*)g_pApplication) + 0x2c))();

    // Create a named function for the main loop (e.g., a function pointer or timer)
    uint32_t mainLoopFunc = createNamedFunction("GameMainLoop");

    // Register that function with the engine's main loop system
    registerNamedFunction(mainLoopFunc);

    // Finally, start the main loop
    startMainLoop();
}