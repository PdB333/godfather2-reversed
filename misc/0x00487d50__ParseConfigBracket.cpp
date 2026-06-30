// FUNC_NAME: ParseConfigBracket
// Function address: 0x00487d50
// Parses a bracket-enclosed configuration token like "[b=123]".
// Handles callbacks for parsed key-value pairs.
// Parameters: inputStr (string to parse), outConsumed (bytes consumed if success),
//             outValue (parsed integer value), callback (function to handle the token).
// Returns 0 on success, -1 on failure.

int __cdecl ParseConfigBracket(const char* inputStr, int* outConsumed, int* outValue, bool (*callback)(const char*, int*))
{
    *outValue = -1;
    *outConsumed = 0;

    // Check for opening bracket
    if (inputStr[0] != '[' || callback == nullptr)
        return -1;

    // Normalize the key letter (lowercase)
    char keyChar = inputStr[1];
    if (keyChar >= 'A' && keyChar <= 'Z')
        keyChar += 0x20; // tolower

    // Expect format: "[b=..." where key is 'b' and '=' follows
    if (keyChar != 'b' || inputStr[2] != '=')
        return -1;

    // Skip "[b=" prefix
    const char* valueStr = inputStr + 3;

    // Parse the value using internal helper functions
    // This likely allocates a temporary buffer, converts string to int,
    // and provides a destructor via local_4 (a function pointer stored on stack)
    void* tokenObj = nullptr; // local_20
    void (*tokenDestructor)(void*) = nullptr; // pcStack_14
    int parsedValue = 0; // local_10[0]
    void (*valueHandler)(int) = nullptr; // local_4

    // First parse the substring (extract token up to ']'? FUN_004d3bc0 maybe sets up a token)
    tokenObj = (void*)FUN_004d3bc0(/* arg? Actually passes (valueStr) */ valueStr);

    // Convert string to integer; likely returns a struct with value and handler
    int result = FUN_004d4e90(&parsedValue, &valueHandler, &DAT_00e337c0); // Not sure about parameters
    FUN_004d3e20(result); // Cleanup

    // If we got a value, call its handler
    if (parsedValue != 0 && valueHandler != nullptr)
        valueHandler(parsedValue);

    // If token object is non-null (meaning we successfully parsed the string)
    if (tokenObj != nullptr)
    {
        const char* contextStr = (const char*)tokenObj;
        if (contextStr == nullptr)
            contextStr = (const char*)&DAT_0120546e; // default context

        // Call the user-provided callback with the context and pointer to output value
        bool callbackResult = callback(contextStr, &outValue); // note: might be &outValue or outValue; we assume passing pointer to int
        if (callbackResult)
        {
            *outValue = (int)(char)outValue; // Truncates to char? Unclear, preserve decompiled behavior
            *outConsumed = (int)tokenObj + 3; // Consumed bytes = parsed length + 3 ("[b=")
            return 0;
        }
    }

    // Cleanup if token object was allocated
    if (tokenObj != nullptr && tokenDestructor != nullptr)
        tokenDestructor(tokenObj);

    return -1;
}

// Note: Internal helper functions:
// FUN_004d3bc0 - likely parses a string into a temporary object (maybe a string token)
// FUN_004d4e90 - converts string to integer with virtual method table (local_4, local_10)
// FUN_004d3e20 - cleanup/destruction of temporary structures
// DAT_00e337c0 - global data (possibly format descriptor)
// DAT_0120546e - default null-string constant