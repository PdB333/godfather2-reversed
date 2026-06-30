// FUNC_NAME: WindowManager::handleFocusChange
void WindowManager::handleFocusChange(bool isActive)
{
    if (!isActive) {
        // Game lost focus: save application state, check if window is iconic, then process focus loss
        WindowManager::saveWindowState();          // FUN_0069d510
        HWND hWnd = WindowManager::getWindowHandle(); // FUN_0069d500
        IsIconic(hWnd); // Probably to ensure we don't try to clip cursor when minimized
        WindowManager::onFocusLost();               // FUN_0069e8b0
        return;
    }

    // Game gained focus
    WindowManager::getWindowHandle();               // FUN_0069d500 (unused return)

    // Unclip cursor if it was previously clipped
    if (s_clipCursorEnabled != 0) {                 // DAT_00e50b88
        ClipCursor(nullptr);
    }

    // Show cursor if required
    if (s_hasFocus != 0 && WindowManager::shouldShowCursor() && s_cursorVisible != 0) { // DAT_0112a065, FUN_0069e7a0, DAT_00e50b8a
        ShowCursor(TRUE);
    }

    InputManager::setInputMode(0);                  // FUN_0040f950(0) – likely restore normal input

    // Clear the focus flags
    s_hasFocus = 0;                                 // DAT_0112a064
    s_isActive = 0;                                 // DAT_0112a065
}