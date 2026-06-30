// FUNC_NAME: installLowLevelKeyboardHook
#include <windows.h>

// Global hook handle for low-level keyboard hook (WH_KEYBOARD_LL = 13)
static HHOOK g_hKeyboardHook = NULL;

// Forward declarations for internal helper functions
int __cdecl checkHookInstallable(void); // FUN_006a17c0
void __cdecl initKeyboardHookState(void); // FUN_0069d2d0
LRESULT __stdcall keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam); // FUN_0069d150

void __cdecl installLowLevelKeyboardHook(void)
{
    if (g_hKeyboardHook == NULL)
    {
        int result = checkHookInstallable();
        if (result >= 0)
        {
            initKeyboardHookState();
            HMODULE hInstance = GetModuleHandleA(NULL);
            g_hKeyboardHook = SetWindowsHookExA(WH_KEYBOARD_LL, keyboardHookProc, hInstance, 0);
        }
    }
}