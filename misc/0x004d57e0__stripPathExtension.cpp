// FUNC_NAME: stripPathExtension

// Structure holding a string pointer and an offset result
struct PathInfo {
    char* str;      // +0x00: input/output null-terminated string path
    int dotOffset;  // +0x04: offset of the found '.' after stripping (or -1 if none)
};

/**
 * Finds the first unescaped '.' in the path string (not preceded by '\\', '/', or another '.'),
 * truncates the string at that point, and stores the dot offset.
 * 
 * @param pathInfo Pointer to PathInfo structure (passed in ECX via __fastcall)
 * @return True if a valid dot was found and string was truncated, false otherwise.
 */
bool __fastcall stripPathExtension(PathInfo* pathInfo)
{
    char curChar;
    char* dotPos;
    int offset;

    // Start at the beginning of the string
    dotPos = pathInfo->str;

    while (true) {
        // If we reached the end of string or a null terminator, no dot found
        if ((dotPos == nullptr) || (*dotPos == '\0')) {
            return false;
        }

        // Find the next '.' in the remaining string
        dotPos = strchr(dotPos, '.');

        // No more dots -> failure
        if (dotPos == nullptr) {
            return false;
        }

        // Check the character following the dot
        curChar = dotPos[1];

        // Skip dots that are escaped (\.), part of a path separator (/.), or double dots (..)
        if ((curChar != '\\') && (curChar != '/') && (curChar != '.')) {
            break;
        }

        // Skip the dot and the following character
        dotPos += 2;
    }

    // Valid dot found: compute offset from start of string
    offset = (int)(dotPos - pathInfo->str);
    pathInfo->dotOffset = offset;

    // Truncate the string at the dot position (replace '.' with null terminator)
    pathInfo->str[offset] = '\0';

    return true;
}