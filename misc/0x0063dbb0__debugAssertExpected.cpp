// FUNC_NAME: debugAssertExpected
// Address: 0x0063dbb0
// Role: Formats and displays an assertion failure message with an expression string, then triggers a breakpoint.
// Called by assertion macros when an expected condition fails.

void debugAssertExpected(int errorCode)
{
    // errorCode is the identifier for the expected expression.
    // Range: 0-255 are "common" error expressions stored in a global string,
    // 256+ are custom error strings stored in a table at 0x00e2a4bc.
    const char* expressionString;
    if (errorCode < 0x101) {
        // Use the global "common" expression string (likely "true" or a fixed string)
        expressionString = (const char*)&DAT_00e4242c; // DAT_00e4242c is a global string
    } else {
        // Lookup custom error string from table
        expressionString = *(const char**)(&DAT_00e2a4bc + errorCode * 4); // array of char*
    }

    // Format the assertion message: "`<expressionString>' expected"
    char* formattedMessage = FUN_00636c00("`%s' expected", expressionString);

    // Output the formatted message (likely to debug console or log)
    FUN_00638b80(formattedMessage);

    // Trigger debug break (software interrupt 3)
    (*(void(*)())swi(3))();  // swi(3) returns a function pointer that is called
}