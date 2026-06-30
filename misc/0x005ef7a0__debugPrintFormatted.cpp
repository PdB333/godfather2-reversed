// FUNC_NAME: debugPrintFormatted
// Address: 0x005ef7a0
// Role: Output a formatted debug message using the global debug manager, if enabled.
// The context object (param_1) contains a format string at +0x10 and argument list at +0x20.

// Global singleton for debug output management.
extern void* gDebugManager; // DAT_0122350c

// Internal debug output function (printf-like).
// Parameters: manager, pointer to context pointer, format string, argList, unknown (usually -1).
void __fastcall debugPrintfInternal(void* manager, void** contextPtr, const char* fmt, void* args, int unknown);

// Flush debug output buffer.
void __fastcall debugFlush(void);

void __fastcall debugPrintFormatted(void* debugContext)
{
    const char* formatString;
    char* defaultString = "unknown"; // DAT_0120546e

    // Retrieve format string from context; fallback to default if null.
    formatString = *(const char**)((char*)debugContext + 0x10);
    if (formatString == (const char*)0x0) {
        formatString = defaultString;
    }

    // Check if debug output is enabled (flag at offset 0x1744 in global manager).
    if (*(char*)((char*)gDebugManager + 0x1744) != '\0') {
        // Pass &debugContext as pointer to context (allows manager to store it).
        debugPrintfInternal(gDebugManager, &debugContext, formatString,
                           (void*)((char*)debugContext + 0x20), 0xffffffff);
    }

    // Flush output after printing.
    debugFlush();
}