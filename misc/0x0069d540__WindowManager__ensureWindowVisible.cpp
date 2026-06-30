// FUNC_NAME: WindowManager::ensureWindowVisible
void WindowManager::ensureWindowVisible(void)
{
    char cVar1;
    BOOL bIsMinimized;
    HWND hGameWindow;
    tagRECT gameRect;
    tagRECT desktopRect;
    tagRECT intersectRect;

    // Check if the game is in a state that allows window repositioning
    cVar1 = WindowManager::isWindowRepositioningAllowed(); // FUN_0060e860
    if (((cVar1 == '\0') &&
         (bIsMinimized = IsIconic(DAT_0112a024), bIsMinimized == 0)) &&
        (bIsMinimized = GetWindowRect(DAT_0112a024, &gameRect), bIsMinimized != 0))
    {
        hGameWindow = GetDesktopWindow();
        GetWindowRect(hGameWindow, &desktopRect);
        bIsMinimized = IntersectRect(&intersectRect, &gameRect, &desktopRect);
        if (bIsMinimized == 0)
        {
            // Window is completely off-screen; move it to top-left corner
            // SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE = 0x15
            SetWindowPos(DAT_0112a024, (HWND)0x0, 0, 0, 0, 0, 0x15);
        }
    }
    return;
}