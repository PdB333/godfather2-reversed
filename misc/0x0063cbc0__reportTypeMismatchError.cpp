// FUNC_NAME: reportTypeMismatchError
// Address: 0x0063cbc0
// Role: Debug helper that prints type mismatch errors for script/argument validation.
// Called when a string starting with '#' is encountered, indicating a type assertion.
// Uses global variables for expected type string and debug verbosity.

void __fastcall reportTypeMismatchError(const char* inputString)
{
    // Global variables (likely from debug system)
    // g_expectedType: pointer to expected type string (e.g., "int", "float", "array")
    // g_showArrayDetail: flag to print array-specific error messages
    // g_currentArgIndex: current argument index being validated
    extern const char* g_expectedType;      // _DAT_00000008
    extern int g_showArrayDetail;           // _DAT_00000004
    extern int g_currentArgIndex;           // uRam00000000

    const char* typeStr = g_expectedType;   // uVar6

    if (*inputString == '#')
    {
        // Parse the type indicator after '#'
        const char* parsedType = parseTypeString();  // FUN_0063ca10

        char nextChar = inputString[1];
        if (nextChar == 'f')
        {
            // Argument type mismatch: expected array, got something else
            const char* argStr = inputString + 2;  // skip "#f"
            if (g_showArrayDetail)
            {
                debugPrintf("%s\n     argument #%d is array of '%s'; array of '%s' expected.\n",
                            argStr, g_currentArgIndex, parsedType, typeStr);
            }
            debugPrintf("%s\n     argument #%d is '%s'; '%s' expected.\n",
                        argStr, g_currentArgIndex, parsedType, typeStr);
        }
        else if (nextChar != 'v')
        {
            // Unknown type indicator, just print the original string
            debugPrintf(inputString);
            return;
        }

        // Handle 'v' (value) case
        const char* valueStr = inputString + 2;  // skip "#v"
        if (g_showArrayDetail)
        {
            debugPrintf("%s\n     value is array of '%s'; array of '%s' expected.\n",
                        valueStr, parsedType, typeStr);
        }
        debugPrintf("%s\n     value is '%s'; '%s' expected.\n",
                    valueStr, parsedType, typeStr);
    }
    else
    {
        // No type indicator, just print the string as-is
        debugPrintf(inputString);
    }
}