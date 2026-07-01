//FUNC_NAME: findStringInListAndCallback
#include <cstring>

// Default empty string used when pointers are null
static const char kEmptyString[] = "";

// Searches for any substring from a list of strings (begin to end) within the given string.
// If a match is found, stops and returns pointer to the matching element in the list.
// If no match, returns end.
// After search, if str is not null, calls callback(str).
// Parameters:
//   begin, end - range of pointers to null-terminated strings (list of substrings to search for)
//   str        - string to search within (can be null)
//   unused1, unused2 - unused parameters (preserved for compatibility)
//   callback   - function to call with str after search (can be null? but called only if str != 0)
char** __cdecl findStringInListAndCallback(
    char** begin,
    char** end,
    const char* str,
    int unused1,          // unused
    int unused2,          // unused
    void (*callback)(const char*)
)
{
    char* found;
    const char* searchStr;

    if (begin != end) {
        do {
            // Get current string from list; use empty string if null
            const char* pattern = *begin;
            if (pattern == nullptr) {
                pattern = kEmptyString;
            }

            // Use empty string if input str is null
            searchStr = str;
            if (searchStr == nullptr) {
                searchStr = kEmptyString;
            }

            // Search for pattern in searchStr
            found = strstr(searchStr, pattern);
            if (found != nullptr) {
                break;
            }

            // Move to next element in list
            begin++;
        } while (begin != end);
    }

    // Call the callback with the original string if it's not null
    if (str != nullptr) {
        callback(str);
    }

    return begin;
}