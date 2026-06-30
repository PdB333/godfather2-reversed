// FUNC_NAME: parseFloatAfterStringMatch
// Address: 0x005c7680
// Role: Searches for a key substring in a source string, then extracts a float value from the remainder after the key.
// Uses strlen-like loop to compute key length, then strstr to find it. If found and key is not at string end, calls a helper to convert the trailing text to float and stores via outValue.

#include <cstring>

// Forward declaration of the helper that parses a float from a string (in XMM0)
extern "C" float FUN_005c7270(const char* str); // actually returns float via XMM0

void parseFloatAfterStringMatch(const char* source, const char* key, float* outValue) {
    // Compute length of key (including null terminator not counted)
    const char* end = key;
    while (*end != '\0') {
        ++end;
    }
    // Now end points to the null terminator; length = end - key
    int keyLen = end - key;  // number of characters before null

    // Find key in source
    const char* found = std::strstr(source, key);
    if (found != nullptr && *(found + keyLen) != '\0') {
        // There is a character after the key; parse float starting from that position
        *outValue = FUN_005c7270(found + keyLen);
    }
}