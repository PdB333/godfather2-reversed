// FUNC_NAME: Entity::getEntityName
// Function address: 0x0095f980
// Role: Retrieves a display name string for the entity's internal ID (stored at this+0x14)
// using a global table (DAT_01130804) of 0x10-byte entries: [stringPtr, param].
// The param argument is passed to FUN_005c4660 (likely safe string copy: strncpy_s).
// If ID out of range, sets output buffer to empty string.

extern unsigned int DAT_01130808;          // Max ID count
extern unsigned int DAT_01130804;          // Base of string table
extern char DAT_0120546e;                  // Default fallback string (e.g. "unknown")

// Forward declaration of a safe string copy (destination, source, max_len, extra_param)
void safeStringCopy(char *dest, const char *src, int maxLen, int param);

// Pre-call initialization function (e.g., table load or lock)
void ensureTableInitialized_0x0095ecd0(void);

void __thiscall Entity::getEntityName(char *outBuffer) {
    unsigned int id;
    unsigned int *entry;
    const char *str;

    ensureTableInitialized_0x0095ecd0();

    id = *(unsigned int *)(this + 0x14); // +0x14: entity type ID
    if (id < DAT_01130808) {
        entry = (unsigned int *)(DAT_01130804 + id * 0x10);
        str = (const char *)*entry;                // first dword: string pointer
        if (str == (const char *)0x0) {
            str = &DAT_0120546e;
        }
        safeStringCopy(outBuffer, str, 0x80, entry[1]); // entry[1] passed as extra param
    } else {
        *outBuffer = '\0';
    }
    return;
}