// FUNC_NAME: shutdownEngine
void shutdownEngine(HWND mainWindow)
{
    // Register a shutdown callback (likely to finalize game states)
    registerShutdownCallback(0, reinterpret_cast<void*>(0x0069d540)); // FUN_00607d50
    // Release memory manager resources
    releaseMemoryManager(0); // FUN_009caa80
    // Clean up input system
    cleanupInputSystem(0); // FUN_0040d790
    // Clean up audio system
    cleanupAudioSystem(0); // FUN_0060e7f0
    // Destroy the main application window
    DestroyWindow(mainWindow);
    // Perform final shutdown/cleanup routines
    finalShutdownCleanup(); // FUN_0069d210
}