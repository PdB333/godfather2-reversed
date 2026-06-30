// FUNC_NAME: DebugLog::logBool
void DebugLog::logBool(const char* contextString, bool value) {
    // First push of context string (likely begins a logging scope or sets context)
    debugPushContext(contextString);

    // Check if debug output is enabled (e.g., global debug flag or valid index range)
    bool bDebugAllowed = isDebugEnabled() != 0;
    if (!bDebugAllowed) {
        // Range check using global debug index and array bounds
        // g_currentDebugIndex: int at 0x00e506ac
        // g_debugArrayStart: pointer at 0x01129f8c
        // g_debugArrayEnd: pointer at 0x01129f90
        int indexRange = (int)(g_debugArrayEnd - g_debugArrayStart) >> 2; // number of ints
        bDebugAllowed = (g_currentDebugIndex >= 0 && g_currentDebugIndex < indexRange);
    }

    if (bDebugAllowed) {
        // Second push of context (e.g., for nested logging or re-pushing identifier)
        debugPushContext(contextString);

        // Convert boolean to string
        const char* boolStr = value ? "true" : "false";

        // Construct temporary debug object (likely a string buffer or scope guard)
        int debugObject[3];       // local_10 (3 ints)
        code* destructorFunc;      // local_4 (function pointer)
        constructDebugLogObject(debugObject); // initializes object and sets destructorFunc

        // Output the boolean string
        debugOutputString(boolStr);

        // Invoke destructor if object is valid
        if (debugObject[0] != 0) {
            (*destructorFunc)(debugObject[0]);
        }
    }
}