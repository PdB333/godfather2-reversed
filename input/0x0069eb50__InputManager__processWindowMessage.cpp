// FUNC_NAME: InputManager::processWindowMessage
/* 0x0069eb50 - Window message handler for the game's main window.
 * Processes mouse movement, button clicks, activation, cursor tracking, etc.
 * Returns a result struct: [0]=handled flag (1=handled), [4]=result value (e.g., HT code or 0).
 */

#include <windows.h>

// Constants for flags used in TrackMouseEvent
constexpr uint32_t TME_LEAVE = 2;
constexpr uint32_t TME_NONCLIENT = 0x10;
constexpr uint32_t TME_HOVER = 1;

// Message result structure
struct MessageResult {
    uint8_t handled;   // +0x00: 1 if message was handled
    int32_t value;     // +0x04: result value (e.g., HT code or 0)
};

// Global state (might be static members of InputManager)
static bool g_mouseTrackingEnabled;      // DAT_0112a067: tracks if we have called TrackMouseEvent for client area
static bool g_nonClientTrackingEnabled;  // DAT_0112a06c: tracks if we have called TrackMouseEvent for non-client
static bool g_cursorVisible;             // DAT_0112a065: true when cursor is visible
static uint8_t g_menuCursorState;        // DAT_0112a066: saved cursor visibility state when entering menu
static int32_t g_mouseDeltaX;            // DAT_0112a04c: accumulated horizontal mouse delta (in client coords)
static int32_t g_mouseDeltaY;            // DAT_0112a050: accumulated vertical mouse delta
static int32_t g_lastMouseX;             // DAT_00e50b7c: last mouse X client coordinate
static int32_t g_lastMouseY;             // DAT_00e50b80: last mouse Y client coordinate
static LRESULT g_lastNcHitTestResult;    // DAT_00e50b84: result for NC_HITTEST if not handled by game

// External helper functions
bool checkEditorMode();                             // FUN_0060e860: likely checks if game editor is active
void showCursor(bool visible);                     // FUN_0069e8b0: show/hide cursor
void hideCursor();                                 // FUN_0069e680: force hide cursor
void enableHighPrecisionMouse(bool enable);        // FUN_0069ea90: enable/disable high precision mouse mode
void getMouseClientCoords(int16_t x, int16_t y, int32_t &outX, int32_t &outY); // FUN_0069e840: convert to client coords? Actually seems to return something
void stopMouseCapture();                           // FUN_0069e7a0: stop capturing mouse if in non-client area

// The main window message processing function
MessageResult* InputManager::processWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam,
                                                   HWND targetWindow, bool showMouse, char param8)
{
    MessageResult* result = reinterpret_cast<MessageResult*>(param1);  // param_1 cast to output struct
    result->handled = 0;
    result->value = -1;

    // Only process messages for our target window
    if (hWnd != targetWindow) {
        return result;
    }

    if (msg < 0x201) {  // Messages below WM_ERASEBKGND (0x201)
        if (msg == WM_MOUSEMOVE) {
            // First WM_MOUSEMOVE: enable mouse leave tracking
            if (!g_mouseTrackingEnabled) {
                g_mouseTrackingEnabled = true;
                TRACKMOUSEEVENT tme;
                tme.cbSize = sizeof(tme);
                tme.dwFlags = TME_LEAVE;
                tme.hwndTrack = targetWindow;
                tme.dwHoverTime = 0;
                TrackMouseEvent(&tme);

                // If cursor is currently hidden (some condition), do nothing if cursor is not visible
                if (/* some condition */ false) {  // DAT_0112a06d != 0
                    if (!g_cursorVisible) {
                        return result;
                    }
                    hideCursor();  // FUN_0069e680
                }
            }

            // Only accumulate mouse deltas if cursor is visible
            if (g_cursorVisible) {
                int16_t y = HIWORD(lParam);
                int16_t x = LOWORD(lParam);
                int32_t outX, outY;
                // Get something from the mouse coordinates (maybe relative to the window?)
                // Actually FUN_0069e840 seems to return two ints encoded in a 64-bit value
                uint64_t result64 = getMouseDeltaConversion(x, y);  // FUN_0069e840
                int32_t deltaXadd = static_cast<int32_t>(result64);       // low part
                int32_t deltaYadd = static_cast<int32_t>(result64 >> 32); // high part

                int32_t newX = x + deltaXadd;
                int32_t newY = y + deltaYadd;

                // Accumulate deltas relative to last position
                g_mouseDeltaX += (newX - deltaXadd) - g_lastMouseX;
                g_mouseDeltaY += (newY - deltaYadd) - g_lastMouseY;

                g_lastMouseX = newX;
                g_lastMouseY = newY;

                result->handled = 1;
                result->value = 0;
                return result;
            }
        }
        else {
            switch (msg) {
            case WM_SIZE:
                if (wParam == 0) {  // SIZE_RESTORED
                    if (!g_cursorVisible && checkEditorMode()) {
                        showMouse ? showCursor(false) : showCursor(0);  // FUN_0069e8b0(param_7)
                        return result;
                    }
                }
                else if (wParam == 1) {  // SIZE_MINIMIZED
                    goto hideAndReturn;
                }
                else if (wParam == 2) {  // SIZE_MAXIMIZED
                    goto hideAndReturn;
                }
                else {
                    if (!g_cursorVisible && checkEditorMode()) {
                        showMouse ? showCursor(true) : showCursor(1);
                    }
                }
                break;

            case WM_ACTIVATEAPP:
                if (param8 == 0) {  // param_8 could be the activation state (true = active?)
                    bool isActivating = (wParam != 0);
                    bool allowTracking = true;
                    if (isActivating && 
                        (/* some condition, DAT_00e50b8b != 0 */) &&
                        (g_lastNcHitTestResult != -2) &&
                        (g_lastNcHitTestResult != 1)) {
                        allowTracking = false;
                    }
                    if (isActivating != showMouse) {  // showMouse is param_7 (bool)
                        if (isActivating) {
                            if (allowTracking) {
                                enableHighPrecisionMouse(isActivating);  // FUN_0069ea90
                            }
                        }
                        else {
                            showCursor(0);  // FUN_0069e8b0(0)
                        }
                        g_menuCursorState = 0;
                        g_lastNcHitTestResult = -2;
                        return result;
                    }
                }
                break;

            case 0x47:  // Possibly WM_SETCURSOR or custom? (0x47 = 71 decimal, not standard)
                if (g_cursorVisible) {
                    showCursor(showMouse ? 1 : 0);  // FUN_0069e8b0(param_7)
                    stopMouseCapture();              // FUN_0069e7a0
                    return result;
                }
                break;

            case 0x7e:  // Possibly WM_? (0x7E = 126, not standard)
                if (g_cursorVisible) {
hideAndReturn:
                    showCursor(showMouse ? 1 : 0);  // FUN_0069e8b0(param_7)
                    return result;
                }
                break;

            case WM_NCHITTEST:
                if (checkEditorMode()) {
                    result->handled = 1;
                    result->value = 1;  // HTCLIENT? Or maybe HTCAPTION? 
                    g_lastNcHitTestResult = 1;
                    return result;
                }
                // Fall through to DefWindowProc
                g_lastNcHitTestResult = DefWindowProcW(hWnd, msg, wParam, lParam);
                result->handled = 1;
                result->value = static_cast<int32_t>(g_lastNcHitTestResult);
                return result;

            case WM_NCMOUSEMOVE:
                if (!g_nonClientTrackingEnabled) {
                    g_nonClientTrackingEnabled = true;
                    TRACKMOUSEEVENT tme;
                    tme.cbSize = sizeof(tme);
                    tme.dwFlags = TME_LEAVE | TME_NONCLIENT;
                    tme.hwndTrack = targetWindow;
                    tme.dwHoverTime = 0;
                    TrackMouseEvent(&tme);
                    return result;
                }
                break;
            }
        }
    }
    else {  // Messages >= 0x201
        switch (msg) {
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
            if (!g_cursorVisible) {
                showCursor(showMouse ? 1 : 0);  // FUN_0069e8b0(param_7)
                return result;
            }
            break;

        case WM_ENTERMENULOOP:     // 0x211
            g_menuCursorState = g_cursorVisible ? 1 : 0;
            // fall through
        case 0x212:               // WM_EXITMENULOOP? Actually 0x212
            // In ENTERMENULOOP, we hide cursor; in EXITMENULOOP, restore
            showCursor(msg == WM_ENTERMENULOOP ? 0 : g_menuCursorState);
            break;

        case 0x2A2:  // Possibly WM_MOUSEHOVER? (0x2A2 = 674, but WM_MOUSEHOVER is 0x2A1)
            g_menuCursorState = 0;
            g_nonClientTrackingEnabled = false;
            g_lastNcHitTestResult = -2;
            return result;

        case WM_MOUSELEAVE:  // 0x2A3
            g_menuCursorState = 0;
            g_mouseTrackingEnabled = false;
            g_lastNcHitTestResult = -2;
            return result;
        }
    }

    return result;
}