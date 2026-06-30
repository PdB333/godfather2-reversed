// FUNC_NAME: LocaleManager::getLanguageCodeAndPath
// Address: 0x006986e0
// Role: Reads the game's locale setting from the registry (SOFTWARE\EA Games\The Godfather I\locale),
// extracts a language code (default 9 = English), and constructs a path "EA Games\<language_name>" into a global buffer.

#include <windows.h>

// Forward declarations of helper functions (simplified signatures)
bool RegistryReadString(HKEY hKey, const char* subKey, const char* valueName, char* outBuffer, DWORD bufferSize);
int ExtractLanguageCodeFromLocaleString(const char* localeStr, int flags);
const wchar_t* GetLanguageCodeName(int languageCode);
void wsprintfW(wchar_t* buffer, const wchar_t* format, ...); // FUN_00b98205 (likely wsprintfW or similar)

// Global buffer for the constructed path
wchar_t g_localePathBuffer[260]; // DAT_01129d80, assumed size

int LocaleManager::getLanguageCodeAndPath()
{
    char localeBuffer[64]; // local_40
    int languageCode = 9; // uVar4, default English

    // Read the "locale" string from registry under "SOFTWARE\EA Games\The Godfather I"
    if (RegistryReadString(HKEY_LOCAL_MACHINE, "SOFTWARE\\EA Games\\The Godfather I",
                           "locale", localeBuffer, sizeof(localeBuffer)))
    {
        // Check if the retrieved string has more than just a null terminator
        size_t len = strlen(localeBuffer);
        if (len > 1)
        {
            // Extract the language code from the locale string (e.g., "en_US" -> code 9)
            languageCode = ExtractLanguageCodeFromLocaleString(localeBuffer, 2);
        }
    }

    // Get the language name corresponding to the code (e.g., "english")
    const wchar_t* languageName = GetLanguageCodeName(languageCode); // uVar3

    // Build the final path: "EA Games\<language_name>"
    wsprintfW(g_localePathBuffer, L"%ws\\%ws", L"EA Games", languageName);

    return languageCode;
}