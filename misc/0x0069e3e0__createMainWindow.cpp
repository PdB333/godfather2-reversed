// FUNC_NAME: createMainWindow
HWND createMainWindow(bool fullscreen, int mode, int x, int y, uint width, int height)
{
    ATOM atom;
    HMODULE hInstance;
    HCURSOR hCursor;
    int showState;
    DWORD dwStyle;
    UINT flags;
    RECT rect;
    LPCWSTR windowTitle;
    static const LPCWSTR windowTitles[] = {
        L"The Godfather II",
        L"",
        L"",
        L"",
        L"",
        L"",
        L"",
        L"",
        L"",
        L""
    };
    // Global window title index (from DAT_00e50b74)
    int titleIndex = gWindowTitleIndex; // DAT_00e50b74
    // Global fullscreen mode flag (from DAT_00e50b70)
    int fullscreenFlag = gFullscreenMode; // DAT_00e50b70

    hInstance = GetModuleHandleW(NULL);

    WNDCLASSW wc;
    wc.style = 0x2000; // CS_HREDRAW | CS_VREDRAW? Actually 0x2000 = CS_DBLCLKS
    wc.lpfnWndProc = (WNDPROC)FUN_0069de10; // WindowProc
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursorA(NULL, (LPCSTR)0x7f00); // IDC_ARROW
    wc.hIcon = LoadIconA(hInstance, (LPCSTR)0x65); // IDI_APPLICATION? 0x65 = 101
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = L"Godfather2WndClass";

    atom = RegisterClassW(&wc);
    if (atom == 0) {
        return NULL;
    }

    // Determine window style and initial show state
    if (!fullscreen) {
        dwStyle = 0x10CB0000; // WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN? (0xCF0000? Actually 0x10CB0000: bits 24-31: 0x10=WS_VISIBLE? No)
        flags = 2; // SWP_NOZORDER?
        showState = 2; // SW_SHOWMINIMIZED? Possibly SW_SHOWNORMAL? Usually 1 is normal.
        if (mode != 1) {
            showState = fullscreenFlag; // Use global flag for show state
            if (mode == 2) {
                showState = 3; // SW_SHOWMAXIMIZED?
            }
        }
    } else {
        dwStyle = 0x90080000; // WS_POPUP | WS_VISIBLE | WS_SYSMENU? (0x90080000 = WS_POPUP | WS_VISIBLE | WS_SYSMENU? Actually 0x90000000 is WS_POPUP, 0x080000=WS_VISIBLE)
        flags = 3; // SWP_SHOWWINDOW?
        showState = 1; // SW_SHOWNORMAL
    }

    rect.left = 0;
    rect.top = 0;
    rect.right = width;
    rect.bottom = height;
    AdjustWindowRect(&rect, dwStyle, FALSE);

    int nWidth = rect.right - rect.left;
    int nHeight = rect.bottom - rect.top;

    ImmDisableIME(0);

    // Window title selection (use array of strings from data, indexed by gWindowTitleIndex)
    windowTitle = windowTitles[titleIndex]; // Actually points to array of LPCWSTR pointers from data

    // Create window
    gMainWindow = CreateWindowExW(0, L"Godfather2WndClass", windowTitle,
                                   dwStyle, x, y, nWidth, nHeight,
                                   NULL, NULL, hInstance, NULL);
    if (gMainWindow != NULL) {
        int screenWidth = GetSystemMetrics(SM_CXSCREEN); // 0
        int screenHeight = GetSystemMetrics(SM_CYSCREEN); // 1
        gScreenWidth = (short)screenWidth; // DAT_0112a038
        gScreenHeight = (short)screenHeight; // DAT_0112a03c
        SetWindowPos(gMainWindow, NULL, x, y, nWidth, nHeight, flags);
        ShowWindow(gMainWindow, showState);
        UpdateWindow(gMainWindow);
    }

    // Additional initialization calls (likely set display mode, etc.)
    setWindowStyle(0x10CB0000); // FUN_0060e870
    setWindowStyle2(0x90080000); // FUN_0060e890
    setShowCommand(2); // FUN_0060e8b0
    setFullscreenFlag(fullscreen); // FUN_0060e850
    setMainWindowHandle(gMainWindow); // FUN_0060e7f0
    setWindowSize(width, height); // FUN_0060e810

    return gMainWindow;
}