// FUNC_NAME: getFileNameFromPath
// Address: 0x005e3300
// Role: Extracts the filename (after last '/' or '\') from a path and calls an internal function.
//       This utility is used by multiple callers to obtain a file resource identifier.
// Note: The decompiled call to FUN_004dafd0 passes no arguments, possibly due to missing
//       parameter or global state. It likely should receive the extracted filename.

#include <string.h> // or equivalent

typedef unsigned int undefined4;

undefined4 getFileNameFromPath(char *path)
{
    char *lastSepPos; // pointer to the character after the last '/' or '\'
    char currentChar;
    undefined4 result;

    if (path != (char *)0x0) {
        currentChar = *path;
        lastSepPos = path; // will be updated if a separator is found
        while (currentChar != '\0') {
            if ((currentChar == '\\') || (currentChar == '/')) {
                // found a separator, set pointer to the start of the next segment
                lastSepPos = path + 1;
            }
            // move to next character
            path++;
            currentChar = *path;
        }
        // if a separator was found, process the filename (pointed by lastSepPos)
        if (lastSepPos != (char *)0x0) {
            // call internal function (likely to look up asset ID or load resource)
            result = FUN_004dafd0(); // Note: original decompiled shows no arguments
            return result;
        }
    }
    return 0;
}