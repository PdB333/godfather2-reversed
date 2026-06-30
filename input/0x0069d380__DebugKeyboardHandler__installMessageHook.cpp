// FUNC_NAME: DebugKeyboardHandler::installMessageHook
// Address: 0x0069d380
// Installs a WH_GETMESSAGE hook for debug keyboard input. Only runs once.
// Parameters: param_1 and param_2 are stored as configuration bytes.

#include <windows.h>

// Static globals (mapped to DAT_01129fac etc.)
static bool g_initialized = false;        // +0x0
static char g_configByte1 = 0;            // DAT_01129fad
static char g_configByte2 = 0;            // DAT_01129fae
static HHOOK g_messageHook = nullptr;     // DAT_01129fb0

// Forward declarations of called internal functions
void DebugKeyboardHandler::initKeyboardSystem(); // FUN_0069d010
bool DebugKeyboardHandler::areHooksAllowed();     // FUN_006a17c0 (return -1 on failure)
void DebugKeyboardHandler::finalizeHookSetup();   // FUN_0069d2d0

// Hook procedure (FUN_0069d150) – defined elsewhere
LRESULT CALLBACK DebugKeyboardHandler::messageHookProc(int nCode, WPARAM wParam, LPARAM lParam);

char DebugKeyboardHandler::installMessageHook(char param1, char param2)
{
    if (g_initialized)
        return g_initialized;

    g_initialized = true;
    g_configByte1 = param1;
    g_configByte2 = param2;

    DebugKeyboardHandler::initKeyboardSystem();

    if (g_messageHook == nullptr && DebugKeyboardHandler::areHooksAllowed())
    {
        DebugKeyboardHandler::finalizeHookSetup();

        DWORD threadId = 0; // Hook all threads (dwThreadId=0)
        HMODULE hModule = GetModuleHandleA(nullptr);
        g_messageHook = SetWindowsHookExA(WH_GETMESSAGE,
                                           DebugKeyboardHandler::messageHookProc,
                                           hModule,
                                           threadId);
    }

    return g_initialized;
}