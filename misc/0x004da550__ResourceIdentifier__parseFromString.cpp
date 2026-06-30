// FUNC_NAME: ResourceIdentifier::parseFromString
// Address: 0x004da550
// Parses a versioned identifier string of format: "name_XXXXXXX_XXXXXXX_v3" or "name_XXXXXXX_XXXXXXX_v3/subpath"
// where name is up to 10 alphanumeric characters, and each XXXXXXX is 7 hex digits (28 bits).
// On success, stores parsed values and returns without setting m_valid.
// On failure, sets m_valid = 1 and cleans up any allocated subpath.

#include <cstdint>
#include <cstring>

// Forward declarations of helper functions (assumed to be in same module)
extern int readHexDigit(); // Reads next hex digit from a global string pointer (advances pointer)
extern void* allocateMemory(int size); // FUN_009c8e50
extern char* copyString(const char* src); // FUN_004d8c00
extern void freeString(char* str); // FUN_009c8eb0
extern void someCleanup(int flag); // FUN_004d8c70

struct ResourceIdentifier {
    uint8_t m_valid;          // +0x00: 0 = valid, 1 = invalid/error
    uint8_t _pad1[0x0B];      // +0x01 to +0x0B: padding
    uint32_t m_hashLow;       // +0x0C: first 28-bit hash (bits 27:0)
    uint32_t m_hashHigh;      // +0x10: second 28-bit hash (bits 27:0)
    char* m_subpath;          // +0x14: allocated subpath string (null if none)
};

void __thiscall ResourceIdentifier::parseFromString(char* thisPtr, const char* inputStr) {
    // Clean up any existing subpath
    char* subpath = *(char**)(thisPtr + 0x14);
    if (subpath != nullptr) {
        if (*(int*)(subpath + 0x14) != 0) {
            someCleanup(1);
        }
        freeString(subpath);
    }
    // Clear subpath pointer
    *(uint32_t*)(thisPtr + 0x14) = 0;

    if (inputStr == nullptr) {
        goto failure;
    }

    char c = *inputStr;
    int charCode = (int)c;
    // Check if first character is alphanumeric
    if (!((charCode - 0x61U < 0x1a) || (charCode - 0x41U < 0x1a) || (charCode - 0x30U < 10))) {
        goto failure;
    }

    // Parse name (up to 10 alphanumeric characters, no underscores)
    char* dest = thisPtr;
    while (c != '\0' && c != '_') {
        if (dest == thisPtr + 10) {
            // Name too long
            goto failure;
        }
        charCode = (int)c;
        if ((charCode - 0x61U > 0x19) && (charCode - 0x41U > 0x19) && (charCode - 0x30U > 9)) {
            // Not alphanumeric
            goto failure;
        }
        inputStr++;
        *dest = c;
        dest++;
        c = *inputStr;
    }

    // Expect underscore after name
    if (*inputStr != '_') {
        goto failure;
    }

    // Null-terminate name (at offset 10)
    thisPtr[10] = '\0';

    // Clear hash fields
    *(uint32_t*)(thisPtr + 0x0C) = 0;
    *(uint32_t*)(thisPtr + 0x10) = 0;

    // Parse first 7 hex digits (28 bits) into m_hashLow
    int digit = readHexDigit();
    if (digit < 0) goto failure;
    *(int*)(thisPtr + 0x0C) = digit << 24;

    digit = readHexDigit();
    if (digit < 0) goto failure;
    *(uint32_t*)(thisPtr + 0x0C) |= digit << 20;

    digit = readHexDigit();
    if (digit < 0) goto failure;
    *(uint32_t*)(thisPtr + 0x0C) |= digit << 16;

    digit = readHexDigit();
    if (digit < 0) goto failure;
    *(uint32_t*)(thisPtr + 0x0C) |= digit << 12;

    digit = readHexDigit();
    if (digit < 0) goto failure;
    *(uint32_t*)(thisPtr + 0x0C) |= digit << 8;

    digit = readHexDigit();
    if (digit < 0) goto failure;
    *(uint32_t*)(thisPtr + 0x0C) |= digit << 4;

    digit = readHexDigit();
    if (digit < 0) goto failure;
    *(uint32_t*)(thisPtr + 0x0C) |= digit;

    // Expect underscore after first hash
    if (inputStr[8] != '_') {
        goto failure;
    }

    // Parse second 7 hex digits into m_hashHigh
    digit = readHexDigit();
    if (digit < 0) goto failure;
    *(int*)(thisPtr + 0x10) = digit << 24;

    digit = readHexDigit();
    if (digit < 0) goto failure;
    *(uint32_t*)(thisPtr + 0x10) |= digit << 20;

    digit = readHexDigit();
    if (digit < 0) goto failure;
    *(uint32_t*)(thisPtr + 0x10) |= digit << 16;

    digit = readHexDigit();
    if (digit < 0) goto failure;
    *(uint32_t*)(thisPtr + 0x10) |= digit << 12;

    digit = readHexDigit();
    if (digit < 0) goto failure;
    *(uint32_t*)(thisPtr + 0x10) |= digit << 8;

    digit = readHexDigit();
    if (digit < 0) goto failure;
    *(uint32_t*)(thisPtr + 0x10) |= digit << 4;

    digit = readHexDigit();
    if (digit < 0) goto failure;
    *(uint32_t*)(thisPtr + 0x10) |= digit;

    // Expect "_v3" after second hash
    if (inputStr[0x10] != '_' || inputStr[0x11] != 'v' || inputStr[0x12] != '3') {
        goto failure;
    }

    // Check for end or subpath
    if (inputStr[0x13] == '\0') {
        // Valid, no subpath
        return;
    }

    if (inputStr[0x13] == '/' && inputStr[0x14] != '\0') {
        // Allocate and copy subpath
        void* mem = allocateMemory(0x18);
        char* subpathStr;
        if (mem == nullptr) {
            subpathStr = nullptr;
        } else {
            subpathStr = copyString(inputStr + 0x14);
        }
        *(char**)(thisPtr + 0x14) = subpathStr;
        if (*subpathStr != '\x01') {
            // Subpath valid (first byte not 0x01)
            return;
        }
    }

failure:
    // Mark as invalid and clean up
    *thisPtr = '\x01'; // m_valid = 1
    char* oldSubpath = *(char**)(thisPtr + 0x14);
    if (oldSubpath != nullptr) {
        if (*(int*)(oldSubpath + 0x14) != 0) {
            someCleanup(1);
        }
        freeString(oldSubpath);
    }
    *(uint32_t*)(thisPtr + 0x14) = 0;
    return;
}