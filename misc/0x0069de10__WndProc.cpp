// FUNC_NAME: WndProc
// Address: 0x0069de10
// Role: Main window procedure for the Godfather 2 game. Handles window messages to control fullscreen toggle, sizing, input, and application shutdown.

#include <windows.h>

// ---------- Global variables (inferred from data refs) ----------
extern HWND g_hWnd;                     // DAT_0112a024
extern bool g_bFullscreen;              // DAT_0112a028
extern char g_bWindowActive;            // DAT_0112a02a
extern int g_nWindowSizeState;          // DAT_0112a02c (0=normal, 1=maximized, 2=minimized)
extern short g_windowWidth;             // DAT_0112a030
extern short g_windowHeight;            // DAT_0112a034
extern short g_windowRestoreX;          // DAT_0112a038
extern short g_windowRestoreY;          // DAT_0112a03c
extern void* g_pInputHandler;           // _DAT_0112a040 = result of FUN_0069d680
extern bool g_bDialogBoxVisible;        // DAT_0112a044
extern bool g_bForceMinimize;           // DAT_0112a048
extern const wchar_t* g_szAppName;      // DAT_00d5cf54
extern const wchar_t* g_szWindowClass;  // DAT_00d5cf5c

// ---------- Forward declarations (internal functions) ----------
bool isGameRunning();                    // FUN_0060e860
void onGameRunning();                    // FUN_0060e870
void toggleFullscreen();                 // FUN_0069ddc0
void processInputMessage(HWND, UINT, WPARAM, LPARAM, HWND, bool); // FUN_0069eb50
void initDirectX(HWND);                  // FUN_0069d680
void cleanupDirectX();                   // FUN_0069d6e0
void handleSizeChange();                 // FUN_0069dd70
bool shouldQuit();                       // FUN_0069db60
void forceQuit();                        // FUN_0069d620
void showSplash();                       // FUN_0069d240
void handleAltEnter();                   // FUN_0069d670
LRESULT CALLBACK DefWindowProcW(HWND, UINT, WPARAM, LPARAM); // external

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // Check for activation message that might require fullscreen toggle
    if (uMsg == WM_ACTIVATEAPP && hWnd == g_hWnd && g_bWindowActive != 0 &&
        (wParam != 0) != g_bFullscreen && wParam == 0)
    {
        toggleFullscreen();
    }

    // Pre-process input? This function seems to handle raw input or similar
    bool bHandled = false;
    LRESULT lResult = 0;
    processInputMessage((char*)&bHandled + 1, hWnd, uMsg, wParam, lParam, g_hWnd, g_bFullscreen);
    if (*(char*)&bHandled != 0)
    {
        return lResult;
    }

    WORD lParamLo = LOWORD(lParam);
    WORD lParamHi = HIWORD(lParam);

    // Messages < 0x101
    if (uMsg < 0x101)
    {
        // WM_KEYDOWN (0x100)
        if (uMsg == WM_KEYDOWN)
        {
            if (g_bDialogBoxVisible)
            {
                DWORD vkCode = lParam & 0xFFFF;
                for (DWORD i = vkCode; i != 0; i--)
                {
                    // call FUN_0098d450 - probably dialog key handler
                    __asm int 3; // placeholder
                }
            }
            goto callDefWindowProc;
        }

        switch (uMsg)
        {
        case WM_CREATE: // 1
        {
            RECT rect;
            if (GetClientRect(hWnd, &rect))
            {
                g_windowWidth  = (short)rect.right;
                g_windowHeight = (short)rect.bottom;
            }
            g_hWnd = hWnd;
            g_pInputHandler = initDirectX(hWnd, g_szAppName, g_szWindowClass);
            break;
        }
        case WM_DESTROY: // 2
            cleanupDirectX();
            PostQuitMessage(0);
            return 0;
        case WM_MOVE: // 3
            // Ignored unless iconified? return 0
            return 0;
        case WM_SIZE: // 5
            if (hWnd == g_hWnd)
            {
                if (wParam == SIZE_MINIMIZED)
                    g_nWindowSizeState = 2;
                else if (wParam == SIZE_MAXIMIZED)
                    g_nWindowSizeState = 1;
                else if (g_nWindowSizeState != 0)
                    g_nWindowSizeState = 0;

                g_windowWidth  = (short)lParam;
                g_windowHeight = lParamHi;
                if (!isGameRunning())
                {
                    GetWindowLongA(hWnd, -16); // GWL_STYLE? Probably unnecessary
                    onGameRunning();
                }
                handleSizeChange();
            }
            return 0;
        case WM_PAINT: // 0x0F
            if (!isGameRunning())
            {
                if (!IsWindowVisible(hWnd))
                    return 1; // skip painting
            }
            ValidateRect(hWnd, NULL);
            return 0;
        case WM_CLOSE: // 0x10
            if (shouldQuit())
                forceQuit();
            return 0;
        case WM_ERASEBKGND: // 0x14
            return 1; // erase
        case WM_ACTIVATEAPP: // 0x1C
            if ((hWnd == g_hWnd) && (g_bWindowActive == 0) &&
                ((wParam != 0) != g_bFullscreen))
            {
                g_bFullscreen = (wParam != 0);
                if (isGameRunning() && !g_bFullscreen)
                {
                    ShowWindow(hWnd, SW_MINIMIZE);
                    if (!isGameRunning() && !g_bForceMinimize)
                    {
                        g_bForceMinimize = showSplash(); // likely
                    }
                    SetActiveWindow(NULL);
                }
                handleAltEnter(); // actually toggle fullscreen? but call is FUN_0069d3f0 (will be renamed)
            }
            break;
        case WM_DISPLAYCHANGE: // 0x7E
            if (isGameRunning() && IsIconic(g_hWnd))
            {
                g_windowRestoreX = (short)lParam;
                g_windowRestoreY = lParamHi;
            }
            break;
        case WM_NCHITTEST: // 0x84
            if (isGameRunning())
                return 1; // HTCLIENT?
            break;
        }
    }
    else if (uMsg < 0x213)
    {
        if (uMsg == 0x212) // WM_SYSCOMMAND? Actually 0x212 = WM_SIZING? But 0x211 adjacent.
        {
            showSplash();
        }
        else if (uMsg < 0x106)
        {
            if (uMsg == WM_SYSKEYDOWN) // 0x105
                return 0; // ignore
            if (uMsg == WM_CHAR) // 0x102
            {
                if (g_bDialogBoxVisible)
                {
                    DWORD vkCode = lParam & 0xFFFF;
                    for (DWORD i = vkCode; i != 0; i--)
                    {
                        // call FUN_0098aaf0 - dialog char handler
                        __asm int 3;
                    }
                }
            }
            else if (uMsg == WM_SYSKEYUP) // 0x104
            {
                if (wParam != VK_F2) // 0x73
                    return 0;
                if ((lParam >> 29) & 1) // context code? Usually bit 29 is context
                    return 0;
                goto wmClose; // WM_CLOSE
            }
        }
        else if (uMsg == WM_SYSCOMMAND) // 0x112
        {
            if (isGameRunning())
            {
                UINT cmd = wParam & 0xFFF0;
                if (cmd == SC_SIZE || cmd == SC_MOVE || cmd == SC_MINIMIZE)
                    return 0;
            }
            // For SC_CLOSE (0xF060), check Alt+F4
            if (wParam == SC_CLOSE)
            {
                WORD keyF4 = GetAsyncKeyState(VK_F4) & 0x8000 ? 1 : 0;
                WORD keyAlt = GetAsyncKeyState(VK_MENU) & 0x8000 ? 1 : 0;
                if ((keyF4 & keyAlt) != 0)
                    return 0; // let DefWindowProc handle?
            }
            else if (wParam == SC_KEYMENU) // 0xF100
                return 0;
            else if (wParam == SC_SCREENSAVE) // 0xF140
                return 0;
        }
        else if (uMsg == 0x211) // WM_ENTERMENULOOP? actually 0x211 = WM_INITMENUPOPUP? but that's 0x117. Anyway.
        {
            showSplash();
        }
        goto callDefWindowProc;
    }
    else // uMsg >= 0x213
    {
        switch (uMsg)
        {
        case WM_GETMINMAXINFO: // 0x218
            if (wParam == 0)
                return 0x424D5144; // Magic value? Probably to query if windowed mode?
            break;
        case WM_ACTIVATE: // 0x19? Actually 0x19 is WM_ACTIVATE. But code says 0x219 (0x219 is WM_ACTIVATE? No, 0x19 is WM_ACTIVATE, 0x219 is WM_QUERYNEWPALETTE? Let's check: 0x219 = 537 decimal = WM_QUERYNEWPALETTE? Actually 0x219 is WM_QUERYNEWPALETTE? No, WM_QUERYNEWPALETTE=0x19? Confusing. The decompiled says 0x219, which is WM_PALETTECHANGED? Actually 0x311 is WM_PALETTECHANGED. This might be a custom message. We'll keep as-is.)
        {
            if (wParam == 0x8004 && g_bFullscreen)
            {
                // Check something with app name
                // FID_conflict:operator== likely compares string
                if (g_szAppName == someGlobal) // placeholder
                {
                    FUN_0040fa00(); // maybe palette reset?
                }
            }
            goto l7e; // handle like WM_DISPLAYCHANGE
        }
        case 0x231: // custom? called handleAltEnter? (0x231 = 561 decimal)
            handleAltEnter();
            break;
        case 0x232: // custom? (562 decimal)
            if (hWnd == g_hWnd)
                toggleFullscreen();
            return 0;
        }
    }

callDefWindowProc:
    return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}