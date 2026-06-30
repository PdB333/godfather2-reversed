// FUNC_NAME: Game::shutdown

// This function performs a global game shutdown sequence.
// It takes an optional game instance handle (param_2). If zero, it retrieves the default instance via thread-local storage.
// It then calls several subsystem shutdown routines in sequence.

void Game::shutdown(Game* unusedThis, int gameInstance)
{
    int instanceCopy;

    if (gameInstance == 0) {
        // Retrieve the current game instance pointer from the thread's local storage.
        // FS:0x2c points to a structure containing a pointer to the game instance at offset 0x24.
        gameInstance = *(int*)((*(int**)(__readfsdword(0x2c)))[0x24]); // +0x24
    }

    instanceCopy = gameInstance;

    // Shutdown audio engine (e.g., stop all sounds, release buffers)
    stopAudio(instanceCopy);                 // FUN_004e9fa0

    // Destroy rendering system (e.g., release D3D resources, shut down GUI)
    shutdownRenderer(instanceCopy);          // FUN_004ea6b0

    // Close network layer (e.g., disconnect, clean up ghost managers)
    closeNetwork();                          // FUN_0051c350

    // Release remaining game resources (e.g., textures, models, scripts)
    cleanupResources(instanceCopy);          // FUN_0051c390

    return;
}