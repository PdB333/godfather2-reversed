// FUNC_NAME: Application::handleFocusChange

#include <windows.h>

// Global variables (addresses from Ghidra)
extern char DAT_00e50b88;  // +0x00e50b88: cursor clipped flag
extern char DAT_0112a065;  // +0x0112a065: cursor visible flag
extern char DAT_00e50b8a;  // +0x00e50b8a: some cursor state
extern char DAT_0112a064;  // +0x0112a064: application focused flag

// Forward declarations for internal functions
void onLoseFocus(void);               // FUN_0069d510
HWND getWindowHandle(void);           // FUN_0069d500 (returns cast to HWND)
void updateFrame(void);               // FUN_0069e8b0
char isCursorCurrentlyVisible(void);  // FUN_0069e7a0 (sets/checks global)
void setCursorState(int state);       // FUN_0040f950

// Handles application focus change
// param_1 = 0 -> losing focus, param_1 != 0 -> gaining focus
void Application::handleFocusChange(char gainingFocus)
{
    HWND hWnd;

    if (gainingFocus == 0) {
        // Losing focus
        onLoseFocus();
        hWnd = getWindowHandle();
        IsIconic(hWnd);  // Check if window is minimized (result unused)
        updateFrame();
        return;
    }

    // Gaining focus
    getWindowHandle();  // Side effect? Return value ignored

    if (DAT_00e50b88 != '\0') {
        // Unclip cursor if it was clipped
        ClipCursor(NULL);
    }

    if ((DAT_0112a065 != '\0') && (isCursorCurrentlyVisible(), DAT_00e50b8a != '\0')) {
        // Show cursor if it was hidden and condition holds
        ShowCursor(TRUE);
    }

    setCursorState(0);
    DAT_0112a064 = 0;   // Clear focused flag
    DAT_0112a065 = 0;   // Clear cursor visibility flag
}