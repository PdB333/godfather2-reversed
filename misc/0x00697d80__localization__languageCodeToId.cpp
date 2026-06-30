// FUNC_NAME: localization::languageCodeToId
// Function at 0x00697d80: Maps ISO 639-1 language codes to internal language IDs.
// Czech (cs/cz) -> 1, Dutch (nl) -> 8, French (fr) -> 2, German (de) -> 3,
// Italian (it) -> 4, Polish (pl) -> 5, Russian (ru) -> 6, Spanish (es) -> 7,
// all others (including English) -> 0.

#include <string.h> // for _strnicmp

int languageCodeToId(const char* languageCode, size_t codeLength)
{
    // Check for Czech (two codes: cs and cz)
    if (_strnicmp("cs", languageCode, codeLength) != 0) {
        if (_strnicmp("cz", languageCode, codeLength) != 0) {
            // Not Czech/Czech – check other languages
            if (_strnicmp("nl", languageCode, codeLength) == 0) {
                return 8; // Dutch
            }
            if (_strnicmp("fr", languageCode, codeLength) == 0) {
                return 2; // French
            }
            if (_strnicmp("de", languageCode, codeLength) == 0) {
                return 3; // German
            }
            if (_strnicmp("it", languageCode, codeLength) == 0) {
                return 4; // Italian
            }
            if (_strnicmp("pl", languageCode, codeLength) == 0) {
                return 5; // Polish
            }
            if (_strnicmp("ru", languageCode, codeLength) == 0) {
                return 6; // Russian
            }
            if (_strnicmp("es", languageCode, codeLength) == 0) {
                return 7; // Spanish
            }
            // English (or any non-matched code) gets 0
            _strnicmp("en", languageCode, codeLength);
            return 0;
        }
    }
    // cs or cz matched
    return 1;
}