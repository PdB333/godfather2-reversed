// FUNC_NAME: CursorManager::setCursorClipMode
void CursorManager::setCursorClipMode(char enableCapture) // 0x0069e8b0
{
    HWND hWnd;
    char isFullscreen;
    tagRECT clipRect;
    uint newCursorState;

    hWnd = (HWND)getMainWindowHandle(); // FUN_0069d500
    newCursorState = 0;
    if (enableCapture == '\0') {
        // Disable capture: release clip cursor, restore cursor visibility
        if (g_bClipCursorEnabled != '\0') {
            ClipCursor((RECT *)0x0);
        }
        if (g_bCursorVisible != '\0') {
            restoreCursorVisibility(); // FUN_0069e7a0
            if (g_bShowCursorOnCapture != '\0') {
                ShowCursor(1);
            }
        }
    }
    else {
        // Enable capture: compute clip region and set cursor
        g_screenOffsetX = 0;
        g_screenOffsetY = 0;
        ClientToScreen(hWnd, (LPPOINT)&g_screenOffsetX);
        isFullscreen = isFullscreenMode(); // FUN_0060e860
        if (isFullscreen == '\0') {
            // Windowed mode: get client rect, compute center
            GetClientRect(hWnd, &clipRect);
            g_centerX = (clipRect.right - clipRect.left) / 2;
            g_centerY = (clipRect.bottom - clipRect.top) / 2;
            clipRect.left += g_screenOffsetX;
            clipRect.right += g_screenOffsetX;
            clipRect.top += g_screenOffsetY;
            clipRect.bottom += g_screenOffsetY;
        }
        else {
            // Fullscreen mode: use global screen dimensions
            clipRect.right = (LONG)g_screenWidth;   // DAT_0120587c
            clipRect.bottom = (LONG)g_screenHeight; // DAT_01205880
            g_centerX = (uint)clipRect.right / 2;
            g_centerY = (uint)clipRect.bottom / 2;
            clipRect.top = 0;
            clipRect.left = 0;
        }
        if (g_bCursorVisible == '\0') {
            showCursorInMode(); // FUN_0069e680
            if (g_bShowCursorOnCapture != '\0') {
                ShowCursor(0);
            }
        }
        if (g_bClipCursorEnabled != '\0') {
            ClipCursor(&clipRect);
        }
        newCursorState = 1;
    }
    setCursorInternalState(newCursorState); // FUN_0040f950
    g_bCursorVisible = newCursorState;      // DAT_0112a065
    g_bCursorActive = newCursorState;       // DAT_0112a064
}