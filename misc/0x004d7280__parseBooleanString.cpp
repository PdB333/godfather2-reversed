// FUNC_NAME: parseBooleanString
bool parseBooleanString(const char* str, bool* outValue) {
    bool result = false;
    bool parsedBool = false;

    if (str == nullptr || *str == '\0') {
        result = true;  // treat empty/null as successful parse with false value
    } else {
        if (__stricmp(str, "true") != 0) {
            if (__stricmp(str, "1") != 0) {
                // Try alternate boolean strings (e.g., "yes")
                // FUN_004d5c90 likely checks a global or performs another comparison
                if (checkAltBool()) {  // first call
                    if (checkAltBool()) {  // second call (why twice? possibly a bug or stateful)
                        goto afterParse;
                    }
                }
                result = true;  // fallback: treat as true but parsedBool remains false
                goto afterParse;
            }
        }
        result = true;
        parsedBool = true;
    }

afterParse:
    if (outValue != nullptr) {
        *outValue = parsedBool;
    }
    return result;
}