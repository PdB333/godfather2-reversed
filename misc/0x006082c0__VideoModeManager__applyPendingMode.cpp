// FUNC_NAME: VideoModeManager::applyPendingMode
// Address: 0x006082c0
// This function handles switching to a pending video mode (resolution/fullscreen).
// It uses global state to track current and pending display settings, and interacts
// with the rendering device (via vtable) and the Win32 window.

// Global state (extern declarations for clarity)
extern char g_bFullscreenCurrent;          // DAT_00f15a3b
extern char g_bFullscreenPending;          // DAT_00f15a39
extern unsigned short g_nCurrentWidth;     // DAT_01205760
extern unsigned short g_nCurrentHeight;    // DAT_01205880
extern char g_bCurrentUnknown;             // DAT_0120587f
extern unsigned short g_nCurrentUnknown2;  // DAT_0120587c
extern char g_bModeChangePending;          // DAT_01205763
extern unsigned short g_nPendingWidth;     // DAT_0119da5c
extern unsigned short g_nPendingHeight;    // DAT_011a0f24
extern unsigned short g_nPendingUnknown;   // DAT_011d97e8
extern char g_bPendingUnknown;             // DAT_0119474a
extern char g_bPendingFullscreen;          // DAT_0119474b
extern char g_bModeChangeActive;           // DAT_0119da5e
extern int g_nModeChangeTimer;             // DAT_00f15a74
extern void* g_pDevice;                    // DAT_01205750 (pointer to device with vtable)
extern int g_nDeviceArg;                   // DAT_01205764 (argument to test function)
extern DWORD g_dwWindowStyle;              // DAT_012058c4
extern DWORD g_dwFullscreenWindowStyle;    // DAT_012058c0
extern UINT g_uWindowPosFlags;             // DAT_012058c8
extern int g_nScaleDivisor;                // DAT_00f15a70
extern int g_nResultFlag;                  // DAT_00f15a48
extern HWND g_hWnd;                        // DAT_011d91a4
extern float g_fAspectRatio;               // DAT_01205878
extern unsigned short g_nCurrentHeight2;   // DAT_0120588c
extern unsigned short g_nCurrentWidth2;    // DAT_01205898

// Forward declarations of internal functions
bool testDeviceSettings(int arg);          // FUN_00608250
void applyDisplaySettings(unsigned short width, unsigned short height, unsigned short unknown, char unknown2, char fullscreen); // FUN_00607790
void sleepMs(int ms);                      // FUN_00ab4b40

int VideoModeManager::applyPendingMode()
{
    char bFullscreenPending = g_bFullscreenPending;
    char bFullscreenCurrent = g_bFullscreenCurrent;

    // If current and pending fullscreen flags differ, and either no mode change is pending
    // or the pending fullscreen flag is different from current, update the current flag
    if (bFullscreenCurrent != bFullscreenPending)
    {
        unsigned short uVar7 = g_nCurrentWidth;
        unsigned short uVar6 = g_nCurrentHeight;
        char cVar8 = g_bCurrentUnknown;
        unsigned short uVar5 = g_nCurrentUnknown2;

        if (g_bModeChangePending == '\0' ||
            (bFullscreenCurrent = g_bFullscreenPending,
             uVar7 = g_nPendingUnknown,
             uVar6 = g_nPendingWidth,
             cVar8 = g_bPendingUnknown,
             uVar5 = g_nPendingHeight,
             g_bPendingFullscreen != g_bFullscreenPending))
        {
            applyDisplaySettings(uVar5, uVar6, uVar7, cVar8, g_bFullscreenPending);
            bFullscreenCurrent = g_bFullscreenPending;
        }
        g_bFullscreenCurrent = bFullscreenCurrent;
    }

    unsigned short uVar5 = g_nCurrentHeight;
    char cVar8 = g_bCurrentUnknown;
    unsigned short uVar6 = g_nCurrentUnknown2;
    unsigned short uVar7 = g_nCurrentWidth;
    char bFullscreen = g_bFullscreenPending;

    if (g_bModeChangePending == '\0')
    {
        // No pending mode change
        if (g_bModeChangeActive == '\0')
        {
            return 1; // Success, nothing to do
        }
        // Mode change is active, decrement timer
        int iVar4 = g_nModeChangeTimer - 1;
        bool bTimerExpired = g_nModeChangeTimer < 1;
        g_nModeChangeTimer = iVar4;
        if (bTimerExpired)
        {
            // Call device's test method (vtable offset 0x0C)
            int (*deviceTest)(void*) = *(int (**)(void*))(*(int*)g_pDevice + 0x0C);
            int result = deviceTest(g_pDevice);
            if (result >= 0)
            {
                g_nModeChangeTimer = 2;
                g_bModeChangeActive = 0;
                return 1;
            }
            if (result != -0x7789f798) // Not device lost?
            {
                if (result == -0x7789f797) // Device not reset?
                {
                    if (testDeviceSettings(0))
                    {
                        g_bModeChangeActive = 0;
                        g_nModeChangeTimer = 2;
                    }
                }
                return 0;
            }
            // If device lost, fall through to return 0
        }
    }
    else
    {
        // Mode change is pending
        int iVar4 = g_nModeChangeTimer - 1;
        bool bTimerExpired = g_nModeChangeTimer < 1;
        g_nModeChangeTimer = iVar4;
        if (bTimerExpired)
        {
            // Copy pending settings to current
            g_nCurrentHeight = g_nPendingWidth;
            g_nCurrentHeight2 = g_nPendingWidth;
            g_nCurrentUnknown2 = g_nPendingHeight;
            g_nCurrentWidth2 = g_nPendingHeight;
            g_nCurrentWidth = g_nPendingUnknown;
            g_fAspectRatio = (float)g_nPendingHeight / (float)g_nPendingWidth;
            g_bCurrentUnknown = g_bPendingUnknown;
            g_bFullscreenPending = g_bPendingFullscreen;

            int iAttempt = 0;
            char cTestResult = testDeviceSettings(g_nDeviceArg);
            DWORD dwStyle = g_dwWindowStyle;

            // Retry loop: wait and test until device is ready
            while (g_dwWindowStyle = dwStyle, cTestResult == '\0')
            {
                if (iAttempt < 2)
                {
                    int sleepTime = 100;
                    sleepMs(&sleepTime);
                }
                else
                {
                    iAttempt = 0;
                    applyDisplaySettings(uVar6, uVar5, uVar7, cVar8, bFullscreen);
                    // Re-copy pending settings (in case apply changed them?)
                    g_nCurrentUnknown2 = g_nPendingHeight;
                    g_nCurrentWidth2 = g_nPendingHeight;
                    g_nCurrentHeight = g_nPendingWidth;
                    g_nCurrentHeight2 = g_nPendingWidth;
                    g_nCurrentWidth = g_nPendingUnknown;
                    g_fAspectRatio = (float)g_nPendingHeight / (float)g_nPendingWidth;
                    g_bCurrentUnknown = g_bPendingUnknown;
                    g_bFullscreenPending = g_bPendingFullscreen;
                }
                iAttempt++;
                cTestResult = testDeviceSettings(g_nDeviceArg);
                dwStyle = g_dwWindowStyle;
            }

            // Set result flag based on fullscreen
            g_nResultFlag = (g_bFullscreenPending != '\0') ? 2 : 0;

            if (g_bCurrentUnknown == '\0')
            {
                // Windowed mode: adjust window
                SetWindowLongA(g_hWnd, GWL_STYLE, dwStyle);
                RECT rect;
                rect.left = 0;
                rect.top = 0;
                rect.right = (LONG)((unsigned long long)g_nCurrentUnknown2 / (unsigned long long)g_nScaleDivisor);
                rect.bottom = (LONG)((unsigned long long)g_nCurrentHeight / (unsigned long long)g_nScaleDivisor);
                AdjustWindowRect(&rect, dwStyle, FALSE);
                SetWindowPos(g_hWnd, HWND_NOTOPMOST, 0, 0,
                             rect.right - rect.left,
                             rect.bottom - rect.top,
                             g_uWindowPosFlags);
            }
            else
            {
                // Fullscreen: set window style to fullscreen style
                SetWindowLongA(g_hWnd, GWL_STYLE, g_dwFullscreenWindowStyle);
            }

            g_bModeChangePending = '\0';
            g_nModeChangeTimer = 2;
        }
    }
    return 0;
}