// FUNC_NAME: PathUtils::isAbsolutePath
// Address: 0x004dd560
// Checks if the given string represents an absolute path (drive letter or UNC with double backslash).
// The string is passed as a struct with pointer (offset 0x00) and length (offset 0x04).

#include <cstdint>

// External string comparison function (unknown purpose, may validate UNC server name or extended path)
extern int32_t FUN_00b9fa49(const uint16_t* str, const uint16_t* ref);

// Global reference string used in UNC check (likely "?" or a format like "?\")
extern const uint16_t DAT_00e36ef4[];

// Minimal string descriptor used by the engine (e.g., EA::StringCore)
struct StringData {
    const uint16_t* data; // +0x00
    int32_t         length; // +0x04 (number of characters)
};

int32_t PathUtils::isAbsolutePath(StringData* strDesc) {
    // Need at least 3 characters to check the first three.
    if (strDesc->length <= 2) {
        return 0;
    }

    const uint16_t* chars = strDesc->data;
    uint16_t c0 = chars[0];
    uint16_t c1 = chars[1];
    uint16_t c2 = chars[2];

    // Convert lowercase ASCII letters to uppercase for case‑insensitive comparison.
    if (c0 - 0x61 < 0x1a) c0 -= 0x20;
    if (c1 - 0x61 < 0x1a) c1 -= 0x20;
    if (c2 - 0x61 < 0x1a) c2 -= 0x20;

    // Pattern 1: "\\" followed by a drive letter or extended‑path marker.
    if (c0 == 0x5c) { // '\\'
        if (c1 == 0x5c && (c2 - 0x41) < 0x1a) { // second backslash and third char is A‑Z
            // Check the substring starting at the third character against a reference.
            // (May validate a UNC server name or an "\\?\" extension.)
            if (FUN_00b9fa49(chars + 2, DAT_00e36ef4) != 0) {
                return 1;
            }
        }
    }
    // Pattern 2: drive letter followed by ":\"  (e.g., "C:\")
    else if ((0x40 < c0 && c0 < 0x5b) && c1 == 0x3a && c2 == 0x5c) {
        return 1;
    }

    return 0;
}