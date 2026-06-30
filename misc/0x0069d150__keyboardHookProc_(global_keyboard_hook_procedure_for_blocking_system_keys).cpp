// FUNC_NAME: keyboardHookProc (global keyboard hook procedure for blocking system keys)
LRESULT keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT* pKbd = (KBDLLHOOKSTRUCT*)lParam;
    bool ctrlDown;

    // Check if the keyboard hook is enabled and the global block flag is set
    // FUN_0069d510 likely returns whether the hook system is active
    if (isKeyboardHookActive() && g_blockKeys)
    {
        // Check if Ctrl key is currently held
        ctrlDown = (GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0;

        // Only process when the hook code is HC_ACTION (0) and the message is a system key down/up
        // Messages 0x104-0x105 correspond to WM_SYSKEYDOWN and WM_SYSKEYUP
        if ((nCode == 0) && (wParam >= 0x104 && wParam <= 0x105))
        {
            if (!ctrlDown)
            {
                // Alt key not held? Check flags bit 0x20 (LLKHF_ALTDOWN)
                if (!(pKbd->flags & LLKHF_ALTDOWN))
                {
                    // Block left and right Windows keys (VK_LWIN = 0x5B, VK_RWIN = 0x5C)
                    if (pKbd->vkCode == VK_LWIN || pKbd->vkCode == VK_RWIN)
                    {
                        return 1; // Block the key
                    }
                }
                else
                {
                    // Alt key is held: block Alt+Esc and Alt+S
                    if (pKbd->vkCode == VK_ESCAPE || pKbd->vkCode == 'S')
                    {
                        return 1;
                    }
                }
            }
            else
            {
                // Ctrl is down: block Ctrl+Esc
                if (pKbd->vkCode == VK_ESCAPE)
                {
                    return 1;
                }
            }
        }
    }

    // Pass the hook to the next handler in the chain
    return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}