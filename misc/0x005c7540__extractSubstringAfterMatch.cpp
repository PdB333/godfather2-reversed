// FUNC_NAME: extractSubstringAfterMatch
// Extracts a substring from param_3 that follows the first occurrence of param_2,
// up to the delimiter character param_4. The result is stored in a fixed-size global buffer.
// Returns pointer to the buffer on success, or NULL if param_2 not found.
char* __fastcall extractSubstringAfterMatch(void* this_unused, char* prefix, char* source, char delimiter)
{
    char* p;
    char* afterPrefix;
    int prefixLen;

    // Compute length of prefix
    p = prefix;
    while (*p != '\0') {
        p++;
    }
    prefixLen = p - prefix; // length excluding null

    // Find first occurrence of prefix in source
    afterPrefix = _strstr(source, prefix);
    if ((afterPrefix != NULL) && (afterPrefix + prefixLen != NULL)) {
        // Copy from after the prefix into global buffer (max 0x40 chars)
        _strncpy(g_parseBuffer, afterPrefix + prefixLen, 0x40);
        g_parseBuffer[0x3F] = '\0'; // ensure null termination

        // Truncate at delimiter if found
        p = _strchr(g_parseBuffer, (int)delimiter);
        if (p != NULL) {
            *p = '\0';
        }
        return &g_parseBuffer;
    }
    return NULL;
}