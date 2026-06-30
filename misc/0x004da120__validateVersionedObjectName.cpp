// FUNC_NAME: validateVersionedObjectName
// Validates a string pattern: <name>_<8hex>_<8hex>_v3
// Returns non-zero on success, 0 on failure (or pointer to error location)
uint __fastcall validateVersionedObjectName(const char* str) {
    const char* cur = str;
    const char* marker; // tracks current position for error reporting

    if (str == nullptr) {
        return 0;
    }

    while (true) {
        char c = *cur;

        // Skip leading alphanumeric characters (a-z, A-Z, 0-9)
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))) {
            marker = cur; // mark first non-alphanumeric position
            break;
        }

        if (c != '\0') {
            int count = 0;
            do {
                if (c == '_') {
                    break; // underscore terminates the name segment
                }
                marker = cur; // update marker as we traverse valid chars

                // Check limit of 10 characters and that character is alphanumeric
                if (count > 10 ||
                    !((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))) {
                    goto fail;
                }

                c = cur[1];
                cur++;
                count++;
            } while (c != '\0');
        }

        // After name segment, expect underscore
        const char* afterName = cur + 1;
        marker = afterName;
        if (*cur != '_') {
            break;
        }

        // Expect exactly 8 hex digits (0-9, a-f, A-F)
        for (const char* hexStart = cur; hexStart != cur + 8; hexStart++) {
            char h = *hexStart;
            if (!((h >= '0' && h <= '9') || (h >= 'a' && h <= 'f') || (h >= 'A' && h <= 'F'))) {
                marker = hexStart;
                goto fail;
            }
        }
        const char* afterHex1 = cur + 9;
        marker = afterHex1;
        if (*(cur + 8) != '_') {
            break;
        }

        // Expect second set of 8 hex digits
        for (const char* hexStart = afterHex1; hexStart != afterHex1 + 8; hexStart++) {
            char h = *hexStart;
            if (!((h >= '0' && h <= '9') || (h >= 'a' && h <= 'f') || (h >= 'A' && h <= 'F'))) {
                marker = hexStart;
                goto fail;
            }
        }
        const char* afterHex2 = afterHex1 + 9;
        marker = afterHex2;
        if (*(afterHex1 + 8) != '_') {
            break;
        }

        // Expect "_v3" suffix
        const char* afterUnderscore = afterHex2 + 1;
        marker = afterUnderscore;
        if (*(afterHex2) != 'v' || *(afterUnderscore) != '3') {
            break;
        }

        // Check null terminator after "v3"
        const char* end = afterUnderscore + 1;
        marker = end;
        if (*end == '\0') {
            // Success: return 1 with end position encoded? Original returns CONCAT31(end>>8, 1)
            // Simplified: return 1
            return 1;
        }
        // If not null, there might be more patterns? The loop continues.
        cur = end + 1; // original: pcVar2 + 4 = afterHex2 + 4? Actually careful: after checking, in_EAX = pcVar2 + 4, where pcVar2 is afterHex2? Let's trust original: after "_v3" check, it sets in_EAX = afterHex2 + 4 (if not null).
        // But this seems to allow multiple patterns? The original loop continues.
    }

fail:
    // Return marker with low byte cleared (indicates error position)
    return (uint)marker & 0xFFFFFF00;
}