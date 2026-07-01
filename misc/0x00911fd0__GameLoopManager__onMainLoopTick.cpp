// FUNC_NAME: GameLoopManager::onMainLoopTick

void __fastcall GameLoopManager::onMainLoopTick(GameLoopManager* this)
{
    // Get the current thread/context ID from the global main loop context (+0x4)
    int currentThreadId = getCurrentThreadId(*(int*)(g_mainLoopContext + 4));
    // Get the ID for the "GameMainLoop" string (likely a hash or enum)
    int mainLoopId = getStringId("GameMainLoop");

    // If this is the first call (tickCount == 0) and we are on the main loop thread
    if ((this->tickCount == 0) && (currentThreadId == mainLoopId)) {
        initializeMainLoop();      // Perform one-time main loop setup
        setMainLoopActive(1);      // Mark main loop as active
        beginFrame(1);             // Start the first frame
    }

    // Increment the tick counter (guards against re-entry)
    this->tickCount++;
}