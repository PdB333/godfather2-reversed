// FUNC_NAME: Engine::shutdown
void Engine::shutdown(void)
{
    uint counter = 0;
    // Wait for pending processes? (loop does nothing; possibly optimized away or a debug spin)
    if (globalPendingCount != 0) {
        do {
            counter = counter + 1;
        } while (counter < globalPendingCount);
    }
    // Shutdown the global engine object (e.g., network, audio, etc.)
    shutdownGlobalObject(&globalEngineObject); // FUN_0041f560
    // Perform final cleanup (e.g., deallocate singletons)
    finalCleanup(); // FUN_00491650
    return;
}