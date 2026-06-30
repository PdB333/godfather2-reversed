//FUNC_NAME: getCurrentLanguageString
// Address: 0x004e8f70
// Returns a pointer to a language string based on a thread-local storage flag.
// The TLS offset 0x34 likely indicates whether the game is in a specific mode (e.g., debug/retail).
// Two global strings are used: g_defaultLanguageString and g_alternateLanguageString.

#include <intrin.h> // for __readfsdword

// Global string pointers (defined elsewhere)
extern const char* g_defaultLanguageString;   // DAT_012054ec
extern const char* g_alternateLanguageString; // DAT_012054f0

const char* getCurrentLanguageString(void)
{
    // Retrieve the thread-local storage base pointer from FS:[0x2C]
    void* tlsBase = (void*)__readfsdword(0x2C);
    // Read the flag at offset 0x34 from the TLS block
    int tlsFlag = *(int*)((char*)tlsBase + 0x34);

    // If the flag is not 1, use the alternate string; otherwise use the default.
    if (tlsFlag != 1) {
        return g_alternateLanguageString;
    }
    return g_defaultLanguageString;
}