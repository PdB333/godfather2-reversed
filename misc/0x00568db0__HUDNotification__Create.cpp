// FUNC_NAME: HUDNotification::Create
// Address: 0x00568db0
// Constructs a HUD notification with localized strings from language system.

#include <cstring>
#include <cstdio>

// Forward declaration for the object being created
class HUDNotification;

// Unknown helpers, likely from engine's localization module
extern void LanguageInit(int context);
extern const char* GetLanguageString();  // returns base language string
extern int GetStringLength(const char* s);
extern void TruncateString(const char* s, int len);  // modifies global?
extern void CopyString(char* dest, const char* src);  // maybe from global buffer

// Allocation function for HUDNotification (0x00568fb0)
extern HUDNotification* AllocateNotification();

// Global string buffers used for default strings
extern const char* const gDefaultString1; // 0x00e2f048
extern const char* const gDefaultString2; // 0x0120546e

class HUDNotification {
public:
    // Offsets from base (relative to 'this')
    // +0x00: vtable? Not set here.
    // +0x08: title[0x80]   // offset 8
    // +0x88: body[0x80]    // offset 0x88
    // +0x108: param4 (duration?) // int
    // +0x10c: param1 (type?)     // int
    // +0x110: extraText (variable) // copied from param5
    // +0x120: param2 (icon?)     // int

    char title[0x80];       // +0x08
    char body[0x80];        // +0x88
    int duration;           // +0x108
    int type;               // +0x10c
    char extraText[1];      // +0x110 (flexible, null-terminated)
    int iconIndex;          // +0x120
};

HUDNotification* __fastcall HUDNotification::Create(
    int type,               // param_1
    int iconIndex,          // param_2
    int languageContext,    // param_3
    int duration,           // param_4
    const char* extraText   // param_5
)
{
    char titleBuffer[0x100];  // local_200
    char bodyBuffer[0x100];   // local_100
    const char* defaultString = nullptr; // local_220
    const char* languagePtr = nullptr;   // local_210 (uninitialized in decompiler, probably set somewhere)
    int languageOffset = 0;              // local_20c (uninitialized int)
    void (*destructor)(const char*) = nullptr; // local_204, unused?

    memset(titleBuffer, 0, 0x100);
    memset(bodyBuffer, 0, 0x100);

    // Initialize language system with the given context
    LanguageInit(languageContext);

    // Get base language string and store into body
    const char* langStr = GetLanguageString();
    snprintf(bodyBuffer, 0x100, "%s", langStr);

    // Possibly trim or adjust language string based on offset
    if (languageOffset != 0) {
        int len = GetStringLength(languagePtr);
        if (len != 0 && languagePtr < (const char*)(len - languageOffset)) {
            TruncateString(languagePtr, len - languageOffset);
            goto after_default; // skip setting defaultString to null?
        }
    }

    defaultString = nullptr;

after_default:
    // Get another string, possibly a default title
    CopyString(const_cast<char*>(gDefaultString1), const_cast<char*>(gDefaultString1)); // side effect ignored? Probably copies into global buffer

    const char* titleSrc = defaultString;
    if (titleSrc == nullptr) {
        titleSrc = gDefaultString2; // empty or placeholder
    }
    snprintf(titleBuffer, 0x100, "%s", titleSrc);

    // Allocate notification object
    HUDNotification* notification = AllocateNotification();

    // Fill notification fields
    notification->iconIndex = iconIndex;             // +0x120
    strncpy(notification->title, titleBuffer, 0x80); // +0x08
    notification->title[0x7F] = '\0';                 // +0x87 (null at end of title)
    notification->type = type;                        // +0x10c
    strncpy(notification->body, bodyBuffer, 0x80);    // +0x88
    notification->body[0x7F] = '\0';                   // +0x107 (null at end of body)
    notification->duration = duration;                 // +0x108

    // Copy extra text to flexible array at +0x110
    char* dest = reinterpret_cast<char*>(notification) + 0x110;
    const char* src = extraText;
    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';

    if (defaultString != nullptr) {
        // code *0x0? This is likely a dereference that shouldn't happen.
        // The decompiler shows (*(code *)0x0)(defaultString);
        // Probably an error in decompilation; skip.
        // Or maybe it was a function call to release the string.
    }

    if (languagePtr != nullptr) {
        // Also calls destructor function at local_204
        // Destructor for languagePtr? Skipped due to ambiguity.
    }

    return notification;
}