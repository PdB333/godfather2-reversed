// FUNC_NAME: repositionWindowIfOffscreen

void repositionWindowIfOffscreen(void)
{
    char cVar1;
    BOOL BVar2;
    HWND hWnd;
    tagRECT windowRect;       // +0x20
    tagRECT desktopRect;      // +0x30
    tagRECT intersectRect;    // +0x10

    // Check internal condition (likely whether window should be repositioned)
    cVar1 = isWindowStateLocked();
    if (((cVar1 == '\0') &&
         (BVar2 = IsIconic(mainWindowHandle), BVar2 == 0)) &&
        (BVar2 = GetWindowRect(mainWindowHandle, &windowRect), BVar2 != 0))
    {
        hWnd = GetDesktopWindow();
        GetWindowRect(hWnd, &desktopRect);
        BVar2 = IntersectRect(&intersectRect, &windowRect, &desktopRect);
        // If no intersection, window is off-screen; move to (0,0)
        if (BVar2 == 0)
        {
            // SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE
            SetWindowPos(mainWindowHandle, (HWND)0x0, 0, 0, 0, 0, 0x15);
        }
    }
    return;
}