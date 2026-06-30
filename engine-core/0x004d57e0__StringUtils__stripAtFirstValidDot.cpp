// FUNC_NAME: StringUtils::stripAtFirstValidDot
// Function address: 0x004d57e0
// Identified as a utility to truncate a string at the first '.' that is not part of a relative path component ("..", "./", ".\").
// Used to extract a base name from a path, storing the offset of the dot for potential extension access.
// The struct accessed: [0] = char* (string pointer), [1] = int (dot offset)

#include <cstring> // for strchr

class StringUtils {
public:
    // Struct layout expected by this function
    // +0x00: char* string
    // +0x04: int dotOffset
    // This function modifies the string in-place and updates dotOffset.

    // Strips the string at the first '.' that is not immediately followed by
    // a path separator ('\\', '/') or another dot (i.e., not part of ".." or "./" / ".\").
    // Returns true if such a dot was found and the string was truncated.
    bool __fastcall stripAtFirstValidDot() {
        char* p = this->string; // +0x00

        while (true) {
            // If pointer is null or empty, fail
            if (p == nullptr || *p == '\0') {
                return false;
            }

            // Find next '.' in the string
            p = strchr(p, '.');
            if (p == nullptr) {
                return false; // No dot found
            }

            char nextChar = p[1];

            // Check if the dot is part of a relative directory indicator:
            // - ".." (two dots)
            // - "./" (current dir)
            // - ".\\" (current dir in Windows paths)
            if (nextChar != '\\' && nextChar != '/' && nextChar != '.') {
                break; // Valid dot – not part of relative path
            }

            // Skip this dot and the next character (the one that made it false)
            p += 2;
        }

        // Compute offset from start of string to the valid dot
        int offset = (int)(p - this->string);
        this->dotOffset = offset; // +0x04

        // Null-terminate at the dot, effectively truncating the string
        this->string[offset] = '\0';

        return true;
    }

    // Members (only for clarity; actual layout is as above)
    char* string;
    int dotOffset;
};