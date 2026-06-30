// FUNC_NAME: GameStateManager::updateContextTimer

// Global context tracking and timer for idle actions
static int g_currentContextId;   // DAT_0112a064
static int g_previousContextId;  // DAT_0112a065
static float g_contextTimer;     // DAT_0112a068
extern float g_frameDeltaTime;   // DAT_01206800 (engine frame time)

void updateContextTimer(void)
{
    // Check if context changed
    if (g_currentContextId != g_previousContextId)
    {
        // Decrement timer by frame time
        g_contextTimer -= g_frameDeltaTime;
        if (g_contextTimer <= 0.0f)
        {
            // Timer expired, trigger context-specific action
            triggerContextChangeAction(g_currentContextId); // FUN_0069e8b0
        }
    }
}