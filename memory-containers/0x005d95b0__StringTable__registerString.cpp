// FUNC_NAME: StringTable::registerString
// Address: 0x005d95b0
// Role: Registers a null-terminated string into a global table, with optional parameters.
// The string is validated for length (max 31 characters plus null) and duplicates are rejected.
// Returns 1 on successful registration, 0 if too long or already exists.

#include <cstring>

// Forward declarations for internal functions
// FUN_005d9690: returns -1 if string not found, else index
int stringFindIndex(const char* str, int param1);
// FUN_005d9ab0: performs actual registration of the string
void stringRegisterAdd(const char* str);

int StringTable::registerString(const char* str, int param1, int param2) // str passed in EAX, param1, param2 on stack
{
    int result;
    char buffer[32]; // stack buffer for string copy
    int local8;
    int local4;

    // Check if string already exists; if so, return 0
    result = stringFindIndex(str, param1);
    if (result >= 0) {
        return 0;
    }

    // Check string length: max 31 characters (excluding null) to fit buffer
    const char* src = str;
    const char* start = str + 1; // skip first character? (decompiler artifact: in_EAX+1)
    int length;
    // Compute length (excluding possibly the first char)
    // Actually: start = str+1, then while(*src) src++; length = src - start;
    // That equals strlen(str) - 1.
    {
        const char* p = str;
        while (*p != '\0') p++;
        length = p - start;
    }
    if (length > 31) {
        return 0;
    }

    // Copy string to local buffer
    char* dst = buffer;
    // Using negative offset trick from decompilation: effectively strcpy
    {
        const char* s = str;
        do {
            *dst = *s;
            dst++;
            s++;
        } while (*s != '\0');
    }
    // Overwrite terminator at correct position (decompiler: sets null at index length)
    buffer[length] = '\0';

    // Store extra parameters (these seem unused in this function, maybe for logging)
    local8 = param1;
    local4 = param2;

    // Call the actual registration routine with the buffered string
    stringRegisterAdd(buffer);

    return 1;
}