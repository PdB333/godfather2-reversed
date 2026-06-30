// FUNC_NAME: findGameWindow
void findGameWindow(void)
{
    // Array of wide strings for window title, indexed by language selection.
    // These are static strings stored in the .rdata section.
    static const wchar_t* g_windowTitles[] = {
        (const wchar_t*)0x00d5a340,  // String 0
        (const wchar_t*)0x00d5a32c,  // String 1 (pointer to pointer? Actually PTR_LAB_...)
        (const wchar_t*)0x00d5a30c,  // String 2
        (const wchar_t*)0x00d5a2f0   // String 3
    };
    // Additional local strings (unused in this function, possibly for other purposes)
    // static const wchar_t* someOtherStrings[] = { ... };

    // Global variable holding the current language/title index (0x00e50b74)
    extern int g_windowTitleIndex;

    // Look for an existing window with class "Godfather2WndClass" and the appropriate title.
    FindWindowW(L"Godfather2WndClass", g_windowTitles[g_windowTitleIndex]);
}