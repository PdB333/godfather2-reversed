// FUNC_NAME: debugPrintTypeMismatchError
void debugPrintTypeMismatchError(char* errorString) {
    unsigned int expectedType = gExpectedType;       // _DAT_00000008
    unsigned int argumentIndex = gArgumentIndex;     // uRam00000000
    char specChar;

    if (*errorString == '#') {
        unsigned int providedType = getTypeName();  // FUN_0063ca10
        specChar = errorString[1];
        errorString += 2;

        if (specChar == 'f') {
            if (gVerbose != 0) {                     // _DAT_00000004
                debugPrintf("%s\n     argument #%d is array of '%s'; array of '%s' expected.\n",
                            errorString, argumentIndex, providedType, expectedType);
            }
            debugPrintf("%s\n     argument #%d is '%s'; '%s' expected.\n",
                        errorString, argumentIndex, providedType, expectedType);
        }
        // Note: the final else-if is inferred from the control flow; specChar != 'v' returns early
        if (specChar != 'v') {
            return;
        }
        // specChar == 'v' case
        if (gVerbose != 0) {
            debugPrintf("%s\n     value is array of '%s'; array of '%s' expected.\n",
                        errorString, providedType, expectedType);
        }
        debugPrintf("%s\n     value is '%s'; '%s' expected.\n",
                    errorString, providedType, expectedType);
    }

    // Fallback: print the string itself (or after spec part)
    debugPrintf(errorString);
}