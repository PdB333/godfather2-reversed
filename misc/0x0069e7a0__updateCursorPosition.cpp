// FUNC_NAME: updateCursorPosition
// Function address: 0x0069e7a0
// Role: Updates the system cursor position based on relative input (e.g., controller stick or mouse delta).
// Uses a function pointer to retrieve scaled deltas, applies screen scaling, and sets cursor via Win32 API.

#include <windows.h>

// Global state (inferred from data references)
extern bool g_bCursorEnabled;          // DAT_0112a06d - flag to enable/disable cursor update
extern void (*g_pfnGetCursorDelta)(int mode, float* outX, float* outY); // DAT_0112a070 - callback to get relative movement
extern float g_fScreenWidthScale;      // DAT_0120587c - scaling factor for X (likely screen width)
extern float g_fScreenHeightScale;     // DAT_01205880 - scaling factor for Y (likely screen height)
extern int g_nCursorX;                 // _DAT_00e50b7c - internal cursor X position
extern int g_nCursorY;                 // _DAT_00e50b80 - internal cursor Y position

// Forward declaration of function that returns the main window handle
HWND getMainWindowHandle();            // FUN_0069d500

void updateCursorPosition()
{
    // Only update if cursor is enabled and a delta callback is registered
    if (!g_bCursorEnabled || g_pfnGetCursorDelta == nullptr)
        return;

    float deltaX, deltaY;
    // Call the delta callback with mode=1 (likely relative movement)
    g_pfnGetCursorDelta(1, &deltaX, &deltaY);

    // Scale the deltas by screen dimensions to convert to pixel coordinates
    deltaX *= g_fScreenWidthScale;
    deltaY *= g_fScreenHeightScale;

    // Update internal cursor position (truncated to integer)
    g_nCursorX = static_cast<int>(deltaX);
    g_nCursorY = static_cast<int>(deltaY);

    // Convert to screen coordinates and set system cursor position
    POINT pt;
    pt.x = g_nCursorX;
    pt.y = g_nCursorY;
    HWND hWnd = getMainWindowHandle();
    ClientToScreen(hWnd, &pt);
    SetCursorPos(pt.x, pt.y);
}