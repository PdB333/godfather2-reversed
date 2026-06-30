// FUNC_NAME: App::createMainWindow
HWND App::createMainWindow(bool isFullscreen, int displayMode, int x, int y, uint width, int height)
{
    HMODULE hInstance;
    WNDCLASSW wc;
    ATOM atom;
    HCURSOR hCursor;
    HWND hWnd;
    int nCmdShow;
    DWORD dwStyle;
    UINT uFlags;
    RECT rect;
    int nWidth, nHeight;
    LPCWSTR windowTitle;
    // Array of window title string pointers (indexed by global g_windowTitleIndex)
    LPCWSTR* titleTable[] = {
        (LPCWSTR*)&DAT_00d5a340,
        &PTR_LAB_00d5a32c,
        &PTR_DAT_00d5a30c,
        &PTR_DAT_00d5a2f0,
        &DAT_00d5a2d0,
        &DAT_00d5a2a4,
        &DAT_00d5a280,
        &DAT_00d5a260,
        &DAT_00d5a23c
    };

    hInstance = GetModuleHandleW(NULL);

    // Initialize window class
    wc.style = CS_HREDRAW | CS_VREDRAW; // 0x2000
    wc.lpfnWndProc = FUN_0069de10; // Window procedure
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIconA(hInstance, (LPCSTR)0x65); // IDI_APPLICATION?
    wc.hCursor = LoadCursorA(NULL, (LPCSTR)IDC_ARROW);
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = L"Godfather2WndClass";

    atom = RegisterClassW(&wc);
    if (atom != 0)
    {
        nCmdShow = 1; // SW_SHOWNORMAL?
        if (!isFullscreen)
        {
            nCmdShow = 2; // SW_SHOWMINIMIZED?
            dwStyle = WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX; // 0x10cb0000
            uFlags = 2;
            if ((displayMode != 1) && (nCmdShow = DAT_00e50b70, displayMode == 2))
            {
                nCmdShow = 3;
            }
        }
        else
        {
            dwStyle = WS_POPUP | WS_VISIBLE | WS_SYSMENU; // 0x90080000
            uFlags = 3;
        }

        rect.left = 0;
        rect.top = 0;
        rect.right = width;
        rect.bottom = height;
        AdjustWindowRect(&rect, dwStyle, FALSE);
        nWidth = rect.right - rect.left;
        nHeight = rect.bottom - rect.top;

        ImmDisableIME(0);

        // Choose title from global index
        windowTitle = titleTable[DAT_00e50b74]; // g_windowTitleIndex

        g_hWndMain = CreateWindowExW(
            0,
            L"Godfather2WndClass",
            windowTitle,
            dwStyle,
            x, y,
            nWidth, nHeight,
            NULL,
            NULL,
            hInstance,
            NULL
        );

        if (g_hWndMain != NULL)
        {
            g_screenWidth = (short)GetSystemMetrics(SM_CXSCREEN);
            g_screenHeight = (short)GetSystemMetrics(SM_CYSCREEN);

            SetWindowPos(g_hWndMain, HWND_TOP, x, y, nWidth, nHeight, uFlags);
            ShowWindow(g_hWndMain, nCmdShow);
            UpdateWindow(g_hWndMain);
        }
    }

    // Additional initialization calls
    FUN_0060e870(0x10cb0000);
    FUN_0060e890(0x90080000);
    FUN_0060e8b0(2);
    FUN_0060e850(isFullscreen);
    FUN_0060e7f0(g_hWndMain);
    FUN_0060e810(width, height);

    return g_hWndMain;
}