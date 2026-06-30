// FUNC_NAME: CursorManager::setCursorClip
void CursorManager::setCursorClip(bool enableClip)
{
    HWND hWnd = getMainWindowHandle(); // FUN_0069d500
    bool wasConstrained; // uVar2

    if (!enableClip) {
        // Unconstrain cursor
        if (g_bCursorConfineEnabled) {
            ClipCursor(nullptr);
        }
        if (g_bCursorConstrained) {
            showCursorInternal(); // FUN_0069e7a0 - restore cursor visibility state
            if (g_bCursorVisible) {
                ShowCursor(1);
            }
        }
        wasConstrained = false;
    } else {
        // Confine cursor
        g_windowScreenOffsetX = 0;
        g_windowScreenOffsetY = 0;
        ClientToScreen(hWnd, (LPPOINT)&g_windowScreenOffsetX);

        RECT clipRect;
        bool isFullScreen = isFullScreenMode(); // FUN_0060e860

        if (!isFullScreen) {
            // Windowed mode - calculate client area in screen coordinates
            GetClientRect(hWnd, &clipRect);
            g_cursorCenterX = (clipRect.right - clipRect.left) / 2;
            g_cursorCenterY = (clipRect.bottom - clipRect.top) / 2;
            // Offset the rect to screen coordinates
            clipRect.left   += g_windowScreenOffsetX;
            clipRect.right  += g_windowScreenOffsetX;
            clipRect.top    += g_windowScreenOffsetY;
            clipRect.bottom += g_windowScreenOffsetY;
        } else {
            // Fullscreen mode - use screen dimensions
            clipRect.right  = g_screenWidth;   // DAT_0120587c
            clipRect.bottom = g_screenHeight;  // DAT_01205880
            g_cursorCenterX = g_screenWidth / 2;
            g_cursorCenterY = g_screenHeight / 2;
            clipRect.top  = 0;
            clipRect.left = 0;
        }

        if (!g_bCursorConstrained) {
            hideCursorInternal(); // FUN_0069e680
            if (g_bCursorVisible) {
                ShowCursor(0);
            }
        }

        if (g_bCursorConfineEnabled) {
            ClipCursor(&clipRect);
        }

        wasConstrained = true;
    }

    updateCursorState(wasConstrained); // FUN_0040f950
    g_bCursorConstrained = wasConstrained;
    g_bSomeCursorFlag    = wasConstrained; // DAT_0112a064
}