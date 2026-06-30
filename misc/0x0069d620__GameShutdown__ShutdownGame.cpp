// FUNC_NAME: GameShutdown::ShutdownGame
void __cdecl GameShutdown(HWND hMainWindow)
{
    // Register shutdown callback for frame processing (arg0 = priority 0, callback = 0x0069d540)
    RegisterFrameShutdownCallback(0, ShutdownFrameCallback);
    // Shutdown audio system (EA EARS AudioDataManager)
    ShutdownAudioManager(0);
    // Shutdown input device manager (XInput, 16 controller slots)
    ShutdownInputManager(0);
    // Shutdown player/simulation manager
    ShutdownPlayerManager(0);
    // Destroy the main application window
    DestroyWindow(hMainWindow);
    // Final cleanup (frees remaining resources, terminates networking)
    FinalCleanup();
}