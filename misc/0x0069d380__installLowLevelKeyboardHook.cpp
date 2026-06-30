// FUNC_NAME: installLowLevelKeyboardHook
char installLowLevelKeyboardHook(char param1, char param2)
{
    int iVar1;
    HMODULE hmod;
    DWORD dwThreadId;

    if (s_isHookInitialized == '\0') {
        s_isHookInitialized = '\x01';
        s_hookParam2 = param2;
        s_hookParam1 = param1;
        initHookData(); // FUN_0069d010
        if ((s_hookHandle == (HHOOK)0x0) && (iVar1 = isHookAllowed(), -1 < iVar1)) {
            setupHookContext(); // FUN_0069d2d0
            dwThreadId = 0;
            hmod = GetModuleHandleA((LPCSTR)0x0);
            s_hookHandle = SetWindowsHookExA(WH_KEYBOARD_LL, keyboardHookProc, hmod, dwThreadId);
        }
    }
    return s_isHookInitialized;
}