// FUNC_NAME: Application::processMessages
// Address: 0x0069d700
// Role: Main window message pump; processes pending Windows messages, checks for quit, and adjusts audio/time scale based on application focus/minimization.

// External globals (assumed defined elsewhere):
// g_bApplicationActive (DAT_0112a028) - BOOL, whether application is considered active.
// g_hWnd (DAT_0112a024) - HWND, main window handle.
// g_bWasMinimized (DAT_0112a029) - BOOL, previous minimized/iconic state.

// External functions:
// void processIdleTasks();            // FUN_0069eac0 - called after message loop
// void setApplicationFocusVolume(float volume); // FUN_005e3df0 - set volume/time scale (1.0 = normal, 0.0 = muted/paused)

bool Application::processMessages()
{
    MSG msg;
    bool bContinue = true;

    // Drain the message queue (PM_REMOVE = 1, PM_NOYIELD = 2, combined = 3)
    while (PeekMessageW(&msg, (HWND)0, 0, 0, 3) != 0)
    {
        if (msg.message == WM_QUIT) // 0x12
        {
            bContinue = false;
        }
        else
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }

    // Perform any idle-time processing
    processIdleTasks();

    // Determine if the application is currently minimized or not active
    bool bMinimized = (!g_bApplicationActive) || (IsIconic(g_hWnd) != 0);

    // If the minimized state changed, adjust audio/time scale accordingly
    if (bMinimized != g_bWasMinimized)
    {
        float fVolume = bMinimized ? 0.0f : 1.0f; // 0x3f800000 = 1.0f
        setApplicationFocusVolume(fVolume);
        g_bWasMinimized = bMinimized;
    }

    return bContinue;
}