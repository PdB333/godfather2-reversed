// FUNC_NAME: GameEngine::processFrame

void GameEngine::processFrame(void)
{
    int threadContext;
    char isActive;
    int thisPtr; // implicitly in EAX (this)

    // Check if game is active (e.g., not paused or minimised)
    if (g_gameActive != 0) {
        // Access thread-local storage pointer: FS:[0x2c] -> some struct -> at +0x34
        // This likely checks if current thread is the main thread or a specific context
        threadContext = *(int *)(**(int **)(__readfsdword(0x2c) + 0x34));
        if (threadContext == 0) {
            // Normal frame: increment frame counter (modulo frame rate limit)
            g_frameCounter = (g_frameCounter + 1) % g_frameRateLimit;
            // Update input systems
            InputManager::update();
            // Activate renderer (e.g., begin frame)
            Renderer::setActive(1);
            // Update game state (e.g., physics, AI)
            GameState::update(thisPtr);
            return;
        }
        // If thread context is non-zero (e.g., background thread or debug mode)
        if (g_debugMode != '\0') {
            InputManager::update();
            Renderer::setActive(1);
            AudioSystem::update();
            // Try to trigger some audio event (e.g., a sound effect)
            int offset = g_someOffset;
            AudioSystem::playSound();
            isActive = Sound::isPlaying(g_audioSystemPtr, offset + 0x80, 1);
            if (isActive == '\0') {
                AudioSystem::playSound(); // fallback
            }
        }
    }
    return;
}