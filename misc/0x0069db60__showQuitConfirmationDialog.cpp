// FUNC_NAME: showQuitConfirmationDialog

#include <windows.h>

// Global variables (inferred from data references)
extern HWND g_hWnd;                 // DAT_0112a024
extern char g_bFullscreen;          // DAT_0112a029
extern char g_bSomeFlag;            // DAT_0112a028
extern int g_languageIndex;         // DAT_00e50b74

// External functions
bool isFullscreen();                // FUN_0060e860
void setCursorVisible(bool visible); // FUN_0069ea00
void setAudioMute(float mute);      // FUN_005e3df0

// Localized string tables (inferred from data)
// Each entry is an array of wchar_t* for different languages
// Indexed by g_languageIndex
struct LocalizedStrings {
    wchar_t* title;
    wchar_t* message;
    // ... other strings
};

// These are the actual data arrays (from the binary)
extern wchar_t* g_quitTitle[];      // local_24 initially L"The Godfather™ II"
extern wchar_t* g_quitMessage[];    // local_24 later L"Are you sure you want to quit? ..."
// Actually the code reuses local_24 for both title and message, but the arrays are separate.
// We'll define them as separate arrays for clarity.

// The function
int showQuitConfirmationDialog()
{
    bool bFullscreen = isFullscreen();
    if (bFullscreen) {
        ShowWindow(g_hWnd, SW_MINIMIZE); // 6 = SW_MINIMIZE
    }

    setCursorVisible(true); // 1 = visible

    if (g_bFullscreen != 1) {
        setAudioMute(0.0f); // unmute
        g_bFullscreen = 1;
    }

    // Build localized string pointers (the code uses a pointer to an array of pointers)
    // The actual data is stored as consecutive arrays for each language.
    // We'll simulate the selection using g_languageIndex.
    wchar_t* title = g_quitTitle[g_languageIndex];
    wchar_t* message = g_quitMessage[g_languageIndex];

    int result = MessageBoxW(g_hWnd, message, title, MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2);

    if (result == IDCANCEL) { // 2 = Cancel (user pressed No? Actually IDNO=7, but the code checks 2)
        // The code checks for 2, which is IDCANCEL. But the dialog has Yes/No, so Cancel is not present.
        // Possibly the style includes MB_CANCELTRYCONTINUE? No, it's MB_YESNO.
        // This might be a bug or the style is different. We'll keep the logic as is.
        if (g_bSomeFlag != 0) {
            if (!IsIconic(g_hWnd)) {
                bFullscreen = false; // cVar5 = 0
            }
        }
        if (bFullscreen != g_bFullscreen) {
            float mute = bFullscreen ? 0.0f : 1.0f;
            setAudioMute(mute);
            g_bFullscreen = bFullscreen ? 1 : 0;
        }
        setCursorVisible(false);
        if (isFullscreen()) {
            ShowWindow(g_hWnd, SW_SHOWMAXIMIZED); // 3 = SW_SHOWMAXIMIZED
        }
        return 0; // Cancel (don't quit)
    }
    return 1; // User pressed Yes (quit)
}