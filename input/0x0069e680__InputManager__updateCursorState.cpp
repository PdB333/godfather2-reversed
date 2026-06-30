// FUNC_NAME: InputManager::updateCursorState
void InputManager::updateCursorState() {
    HWND hWnd = (HWND)FUN_0069d500(); // retrieve main window handle (likely EARS::Framework::getMainWindow)
    BOOL isMinimized = IsIconic(hWnd);

    if (isMinimized == FALSE) {
        POINT cursorPos;
        GetCursorPos(&cursorPos);
        ScreenToClient(hWnd, &cursorPos);

        // Clamp cursor to window client area? Actually if outside, center it unless flagged.
        if (cursorPos.x < 0 || cursorPos.x >= (int)sScreenWidth ||
            cursorPos.y < 0 || cursorPos.y >= (int)sScreenHeight) {
            cursorPos.x = sScreenWidth >> 1;  // center X
            cursorPos.y = sScreenHeight >> 1; // center Y

            // If cursor centering is enabled (flag at 0x0112a06d), reposition cursor to screen center
            if (sCursorCenterOnWindowExit == '\0') {
                POINT screenPos = cursorPos;
                ClientToScreen(hWnd, &screenPos);
                SetCursorPos(screenPos.x, screenPos.y);
            }
        }

        // Normalize cursor position to [0..1] range
        float normalizedX = (float)cursorPos.x / (float)sScreenWidth;
        float normalizedY = (float)cursorPos.y / (float)sScreenHeight;

        // Store absolute cursor coords (likely for other systems)
        sLastCursorX = cursorPos.x;
        sLastCursorY = cursorPos.y;
    } else {
        // When minimized, use a default normalized position (stored somewhere)
        normalizedX = sDefaultNormalizedCursor;
        normalizedY = sDefaultNormalizedCursor;
    }

    // Call the registered cursor movement callback (if any)
    if (sCursorMoveCallback != nullptr) {
        sCursorMoveCallback(0, &normalizedX, &normalizedY);
    }
}