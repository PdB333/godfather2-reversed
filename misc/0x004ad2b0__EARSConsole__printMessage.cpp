// FUNC_NAME: EARSConsole::printMessage
void __fastcall EARSConsole::printMessage(char* message) {
    // Scan to end of string (effectively strlen, result unused except for loop)
    char ch;
    do {
        ch = *message;
        message = message + 1;
    } while (ch != '\0');

    // Call internal function to output message (likely writes to debug console or log)
    FUN_004ae6f0();
}