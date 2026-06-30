// FUNC_NAME: windowManager_handleDeviceResetAndWindowChange
// Address: 0x006082c0
// This function handles device reset (D3D device lost) and switching between windowed/fullscreen modes.
// It uses a counter (g_deviceResetCountdown) to wait, calls a virtual function on a D3D device via pointer at g_pD3DDevice9,
// and if device lost, attempts to reset; if device not reset, it calls a function to restore fullscreen parameters.
// It also adjusts window style and position after reset.

#include <windows.h>

// Global variables with guessed types based on usage
extern char g_windowModeFlag; // DAT_00f15a3b - current window mode (0=windowed? 1=fullscreen?)
extern char g_targetWindowMode; // DAT_00f15a39 - desired window mode
extern ushort g_windowWidth; // DAT_0120587c
extern ushort g_windowHeight; // DAT_01205880
extern char g_windowBpp; // DAT_0120587f - bits per pixel? or fullscreen flag?
extern ushort g_windowSomething; // DAT_01205760
extern char g_windowedFullscreen; // DAT_01205763 - non-zero means currently in fullscreen? Used as flag
extern char g_deviceResetSucceeded; // DAT_0119da5e - flag indicating reset succeeded
extern int g_deviceResetCountdown; // DAT_00f15a74 - countdown timer for retry
extern void* g_pD3DDevice9; // DAT_01205750 - pointer to IDirect3DDevice9 object (0x10 offset for virtual function table)
extern char g_fullScreenFlag2; // DAT_0119474a
extern char g_fullScreenFlag3; // DAT_0119474b
extern ushort g_resolutionX; // DAT_011a0f24
extern ushort g_resolutionY; // DAT_0119da5c
extern ushort g_desktopResX; // DAT_011d97e8
extern uint g_windowStyle; // DAT_012058c4 - current window style
extern uint g_windowStyleFullScreen; // DAT_012058c0 - window style for fullscreen
extern uint g_windowPosFlags; // DAT_012058c8 - flags for SetWindowPos
extern HWND g_hWnd; // DAT_011d91a4 - main window handle
extern float g_aspectRatio; // DAT_01205878
extern int g_windowWidthAdjusted; // DAT_01205898
extern int g_windowHeightAdjusted; // DAT_0120588c
extern int g_someScaleFactor; // DAT_00f15a70 - maybe DPI or monitor scale
extern char g_resetDeviceParam; // DAT_01205764 - parameter for reset function

// Forward declarations
bool FUN_00608250(char param); // attempt device reset or similar
void FUN_00607790(ushort resX, ushort resY, ushort deskResX, char bpp, char flag); // switch to windowed/fullscreen
void FUN_00ab4b40(int* pDelay); // Sleep for given milliseconds

// This function returns 1 if no reset needed, 0 if busy waiting
int windowManager_handleDeviceResetAndWindowChange(void)
{
    char currentMode;
    char targetMode;
    ushort width, height, desktopWidth;
    char bpp;

    // Update current mode if different from target
    currentMode = g_windowModeFlag;
    if (g_windowModeFlag != g_targetWindowMode)
    {
        // Check if we are in fullscreen mode and need to switch
        if (g_windowedFullscreen == '\0' ||
            (currentMode = g_targetWindowMode, // use target for parameters
             g_windowWidth = g_resolutionX,
             g_windowHeight = g_resolutionY,
             bpp = g_fullScreenFlag2,
             width = g_resolutionX,
             // When switching from fullscreen to windowed, use desktop resolution?
             // Actually the code uses different globals depending on condition.
             // This is messy but we'll replicate.
             g_fullScreenFlag3 != g_targetWindowMode))
        {
            // Call function to adjust display mode
            FUN_00607790(g_resolutionX, g_resolutionY, g_desktopResX, g_fullScreenFlag2, g_targetWindowMode);
            currentMode = g_targetWindowMode;
        }
        g_windowModeFlag = currentMode;
    }

    width = g_windowHeight;
    bpp = g_windowBpp;
    desktopWidth = g_windowWidth;
    height = g_windowSomething;
    targetMode = g_targetWindowMode;

    if (g_windowedFullscreen == '\0') // Currently in windowed mode
    {
        if (g_deviceResetSucceeded == '\0')
        {
            return 1; // no reset needed
        }
        // Device lost, trying to restore
        g_deviceResetCountdown--;
        if (g_deviceResetCountdown < 0)
        {
            // Call TestCooperativeLevel on D3D device?
            int result = (*(int (__stdcall**)(void*))(*(uint32_t*)g_pD3DDevice9 + 0xc))(g_pD3DDevice9);
            if (result >= 0) // S_OK or D3D_OK
            {
                g_deviceResetCountdown = 2;
                g_deviceResetSucceeded = 0;
                return 1;
            }
            if (result != 0x88760868) // D3DERR_DEVICELOST
            {
                if (result == 0x88760869 && // D3DERR_DEVICENOTRESET
                    (currentMode = FUN_00608250(0), currentMode != '\0')) // try reset?
                {
                    g_deviceResetSucceeded = '\0';
                    g_deviceResetCountdown = 2;
                }
                return 0; // still waiting
            }
            // else device lost, just return 0
        }
        return 0;
    }
    else // Currently in fullscreen mode, need to switch to windowed? Actually the flag is g_windowedFullscreen != 0 means need to switch? Let's follow logic.
    {
        g_deviceResetCountdown--;
        if (g_deviceResetCountdown < 0)
        {
            // Transfer new resolution values
            g_windowHeight = g_resolutionY;
            g_windowHeightAdjusted = g_resolutionY;
            g_windowWidth = g_resolutionX;
            g_windowWidthAdjusted = g_resolutionX;
            g_windowSomething = g_desktopResX;
            g_aspectRatio = (float)g_resolutionX / (float)g_resolutionY;
            g_windowBpp = g_fullScreenFlag2;
            g_targetWindowMode = g_fullScreenFlag3;

            int attempt = 0;
            char resetResult;
            uint style = g_windowStyle;

            resetResult = FUN_00608250(g_resetDeviceParam);
            while (resetResult == '\0')
            {
                if (attempt < 2)
                {
                    int delay = 100;
                    FUN_00ab4b40(&delay);
                }
                else
                {
                    attempt = 0;
                    // If failed twice, revert to windowed mode
                    FUN_00607790(g_windowHeight, g_windowWidth, g_windowSomething, g_windowBpp, g_targetWindowMode);
                    // Restore windowed resolution
                    g_windowWidth = g_resolutionX;
                    g_windowWidthAdjusted = g_resolutionX;
                    g_windowHeight = g_resolutionY;
                    g_windowHeightAdjusted = g_resolutionY;
                    g_windowSomething = g_desktopResX;
                    g_aspectRatio = (float)g_resolutionX / (float)g_resolutionY;
                    g_windowBpp = g_fullScreenFlag2;
                    g_targetWindowMode = g_fullScreenFlag3;
                }
                attempt++;
                resetResult = FUN_00608250(g_resetDeviceParam);
                style = g_windowStyle;
            }

            // After successful reset
            g_windowStyle = style;
            // Set a flag for window style based on fullscreen flag
            g_windowPosFlags = (g_targetWindowMode != '\0') ? 2 : 0; // SWP_SHOWWINDOW? Actually it's -(uint)(g_targetWindowMode != 0) & 2
            if (g_windowBpp == '\0') // windowed mode
            {
                SetWindowLongA(g_hWnd, GWL_STYLE, style);
                RECT rect;
                rect.left = 0;
                rect.top = 0;
                rect.right = (LONG)((unsigned long long)g_windowWidth / (unsigned long long)g_someScaleFactor);
                rect.bottom = (LONG)((unsigned long long)g_windowHeight / (unsigned long long)g_someScaleFactor);
                AdjustWindowRect(&rect, style, FALSE);
                SetWindowPos(g_hWnd, HWND_TOPMOST, 0, 0, rect.right - rect.left, rect.bottom - rect.top, g_windowPosFlags);
            }
            else // fullscreen
            {
                SetWindowLongA(g_hWnd, GWL_STYLE, g_windowStyleFullScreen);
            }
            g_windowedFullscreen = '\0'; // reset flag
            g_deviceResetCountdown = 2;
        }
        return 0;
    }
}