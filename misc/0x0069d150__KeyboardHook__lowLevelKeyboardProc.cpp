// FUNC_NAME: KeyboardHook::lowLevelKeyboardProc
LRESULT CALLBACK KeyboardHook::lowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    // 0x69d150 - Low-level keyboard hook procedure
    // Blocks system keys (Win, Alt+Tab, Alt+F4, Ctrl+Esc) when hook is active

    // Check hook enable flag (global)
    if (FUN_0069d510() != 0 && g_keyHookEnabled != 0) {
        DWORD vkCode = ((KBDLLHOOKSTRUCT*)lParam)->vkCode;  // param_3 points to KBDLLHOOKSTRUCT
        DWORD flags = ((KBDLLHOOKSTRUCT*)lParam)->flags;
        bool ctrlDown = (GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0;

        // Only process WM_SYSKEYDOWN (0x104) and WM_SYSKEYUP (0x105) when nCode is HC_ACTION (0)
        if (nCode == 0 && wParam > 0x103 && wParam < 0x106) {
            if (!ctrlDown) {
                // No Ctrl: check for Windows keys or Alt combos
                if ((flags & LLKHF_ALTDOWN) == 0) {
                    // Alt not down: block left/right Windows keys (VK_LWIN=0x5b, VK_RWIN=0x5c)
                    if (vkCode == VK_LWIN || vkCode == VK_RWIN) {
                        return 1; // Block key
                    }
                } else {
                    // Alt is down: block Escape (Alt+Tab) and F4 (Alt+F4)
                    if (vkCode == VK_ESCAPE || vkCode == VK_F4) {
                        return 1; // Block key
                    }
                }
            } else {
                // Ctrl is down: block Escape (Ctrl+Esc = Start Menu)
                if (vkCode == VK_ESCAPE) {
                    return 1; // Block key
                }
            }
        }
    }

    // Pass through to next hook
    return CallNextHookEx(g_hHook, nCode, wParam, (LPARAM)lParam);
}