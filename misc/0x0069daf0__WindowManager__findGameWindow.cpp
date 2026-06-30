// FUNC_NAME: WindowManager::findGameWindow
// Address: 0x0069daf0
// Role: Finds the game window using the class name "Godfather2WndClass" and a selectable title string.
// The title index is taken from a global variable (g_windowTitleIndex, 0x00e50b74).
// An array of four title strings (at 0x00d5a340, 0x00d5a32c, 0x00d5a30c, 0x00d5a2f0) is indexed,
// but additional unused string pointers are also loaded.

#include <windows.h> // For FindWindowW

// External data references (locations from the original binary)
extern const wchar_t* g_windowTitle0;  // 0x00d5a340
extern const wchar_t* g_windowTitle1;  // 0x00d5a32c
extern const wchar_t* g_windowTitle2;  // 0x00d5a30c
extern const wchar_t* g_windowTitle3;  // 0x00d5a2f0

// Additional strings loaded but not used in this function (potential leftover or debug data)
extern const wchar_t* g_otherString0;  // 0x00d5a2d0
extern const wchar_t* g_otherString1;  // 0x00d5a2a4
extern const wchar_t* g_otherString2;  // 0x00d5a280
extern const wchar_t* g_otherString3;  // 0x00d5a260
extern const wchar_t* g_otherString4;  // 0x00d5a23c

extern int g_windowTitleIndex;          // 0x00e50b74 – selects which window title to use

void WindowManager::findGameWindow()
{
    const wchar_t* titleArray[4];
    titleArray[0] = g_windowTitle0;
    titleArray[1] = g_windowTitle1;
    titleArray[2] = g_windowTitle2;
    titleArray[3] = g_windowTitle3;

    // Unused assignments (kept for fidelity to original decompilation)
    const wchar_t* unused0 = g_otherString0;
    const wchar_t* unused1 = g_otherString1;
    const wchar_t* unused2 = g_otherString2;
    const wchar_t* unused3 = g_otherString3;
    const wchar_t* unused4 = g_otherString4;

    // Find the window by class and (optionally) title
    FindWindowW(L"Godfather2WndClass", titleArray[g_windowTitleIndex]);
}