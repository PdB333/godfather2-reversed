// FUNC_NAME: InputHookManager::shutdownInputHooks
void InputHookManager::shutdownInputHooks(char shouldUninstallHook)
{
    if (!g_inputHooksEnabled) {
        return;
    }
    if (shouldUninstallHook == 0) {
        disableKeyboardHook();
        disableMouseHook();
        return;
    }
    uninstallHookChain();
    if (g_hookHandle != nullptr) {
        UnhookWindowsHookEx(g_hookHandle);
        g_hookHandle = nullptr;
    }
}