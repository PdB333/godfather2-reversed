// FUNC_NAME: installGetMessageHook

#include <windows.h>

// Global hook handle for WH_GETMESSAGE hook (0xD)
static HHOOK g_hGetMessageHook = nullptr;

// Forward declaration of the hook procedure (callee at FUN_0069d150)
LRESULT CALLBACK getMessageHookProc(int nCode, WPARAM wParam, LPARAM lParam);

/**
 * Checks whether the hook should be installed (e.g., anti‑debug check).
 * Returns >= 0 if allowed, negative otherwise.
 */
int shouldInstallGetMessageHook(void); // FUN_006a17c0

/**
 * Performs any necessary setup before the hook is installed.
 */
void prepareHookInstallation(void); // FUN_0069d2d0

void installGetMessageHook(void)
{
    // Only install once
    if (g_hGetMessageHook != nullptr)
        return;

    // Verify conditions (likely debugger check)
    if (shouldInstallGetMessageHook() < 0)
        return;

    // Run setup tasks
    prepareHookInstallation();

    // Install a global WH_GETMESSAGE hook (dwThreadId = 0)
    // Hook procedure will process all messages for this thread.
    HMODULE hModule = GetModuleHandleA(nullptr);
    g_hGetMessageHook = SetWindowsHookExA(WH_GETMESSAGE, getMessageHookProc, hModule, 0);
}