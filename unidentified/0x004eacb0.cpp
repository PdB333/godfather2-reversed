// FUN_004eacb0: StringHash::setFromString
void __thiscall StringHash::setFromString(uint32_t fields[4], const char* str) {
    if (str != nullptr) {
        // Find null terminator
        const char* end = str;
        while (*end != '\0') {
            end++;
        }
        int strLen = (int)(end - str);

        // Only process strings longer than 24 characters (0x17 < strLen-1)
        // This implies strLen >= 25 (since condition is strict)
        if (strLen > 24) {
            // Compute a hash of the initial part of the string:
            //   start = str, end = str + (strLen - 16)
            // This hashes the first (strLen - 16) characters.
            uint32_t hash = computeHash(str, str + (strLen - 16)); // FUN_004dafd0

            // Build a 24‑character combined string:
            //   "%08x" (8 hex digits) + the remaining 16-character suffix
            // The suffix begins at str + strLen - 16.
            char buffer[24]; // local_18, size 24
            sprintf(buffer, "%08x%s", hash, str + strLen - 16);

            // Store the resulting hash string into the object's internal representation
            setHashString(buffer); // FUN_004eadc0
        }
        return;
    } else {
        // Null input: zero out the 16-byte storage (four uint32_t fields)
        // Offsets: +0x00, +0x04, +0x08, +0x0C
        fields[0] = 0;
        fields[1] = 0;
        fields[2] = 0;
        fields[3] = 0;
    }
}