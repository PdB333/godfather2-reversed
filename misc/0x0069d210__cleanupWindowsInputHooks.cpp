// FUNC_NAME: cleanupWindowsInputHooks
#include <windows.h>

// Static globals for Windows hook state
static BOOL g_bHooksInitialized = 0;   // +0x0 (DAT_01129fac)
static HHOOK g_hKeyboardHook = NULL;   // +0x4 (DAT_01129fb0)

// Forward declaration of internal helper
extern uint sub_69d060(void);

uint cleanupWindowsInputHooks(void)
{
    // Mark hooks as uninitialized
    g_bHooksInitialized = 0;

    // Unhook existing keyboard hook if present
    if (g_hKeyboardHook != NULL) {
        UnhookWindowsHookEx(g_hKeyboardHook);
        g_hKeyboardHook = NULL;
    }

    // Call internal cleanup helper and mask result
    uint uResult = sub_69d060();
    return uResult & 0xffffff00;
}