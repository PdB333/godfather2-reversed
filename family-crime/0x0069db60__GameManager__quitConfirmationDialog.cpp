// FUNC_NAME: GameManager::quitConfirmationDialog
// Address: 0x0069db60
// Handles "Are you sure you want to quit?" dialog with multilingual support.
// Controls audio mute/unmute, cursor visibility, and window state.

#include <Windows.h>

// External functions (reconstructed names)
extern bool IsFullscreen(); // FUN_0060e860
extern void SetCursorVisible(bool visible); // FUN_0069ea00
extern void SetMasterVolume(float volume); // FUN_005e3df0

// Global variables
extern HWND g_hWindow; // DAT_0112a024
extern bool g_bWindowMinimized; // DAT_0112a028 (likely)
extern bool g_bAudioMuted; // DAT_0112a029 (initially false)

// Language index global (DAT_00e50b74)
extern int g_LanguageIndex;

// Multilingual string tables (each array is 8 pointers, one per language)
// Offsets: 0=English, 1=Italian, 2=Dutch? (from pattern)
extern const wchar_t* g_QuitTitle[8]; // PTR_LAB_00d5a32c, etc.
extern const wchar_t* g_QuitMessage[8]; // DAT_00d5a770, etc.

// Function implementation
int GameManager::quitConfirmationDialog()
{
    bool wasFullscreen = IsFullscreen();

    if (wasFullscreen)
    {
        ShowWindow(g_hWindow, SW_MINIMIZE); // 6 = SW_MINIMIZE
    }

    SetCursorVisible(true); // Show cursor for dialog

    if (!g_bAudioMuted)
    {
        SetMasterVolume(0.0f); // Mute audio
        g_bAudioMuted = true;
    }

    // Prepare string pointers (array base + index*4 for pointer)
    const wchar_t* title = g_QuitTitle[g_LanguageIndex];
    const wchar_t* message = g_QuitMessage[g_LanguageIndex];

    // Flags: 0x10031 = MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2? (System modal)
    int result = MessageBoxW(g_hWindow, message, title, 0x10031);

    if (result == IDNO) // 2 = IDNO (user clicked No)
    {
        // Restore previous audio state
        bool needUnmute = true;
        if (g_bWindowMinimized)
        {
            if (!IsIconic(g_hWindow))
            {
                needUnmute = false;
            }
        }

        if (needUnmute != g_bAudioMuted)
        {
            float volume = needUnmute ? 1.0f : 0.0f;
            SetMasterVolume(volume);
            g_bAudioMuted = needUnmute;
        }

        SetCursorVisible(false); // Hide cursor again

        if (wasFullscreen)
        {
            ShowWindow(g_hWindow, SW_MAXIMIZE); // 3 = SW_MAXIMIZE (or SW_RESTORE?)
        }

        return 0; // Abort quit
    }

    // User clicked Yes (IDYES = 6) or closed dialog -> proceed with quit
    return 1;
}