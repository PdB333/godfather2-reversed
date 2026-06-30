// FUNC_NAME: DebugConsole::registerCommand
// Address: 0x005d95b0
int DebugConsole::registerCommand(char* commandString, int arg1, int arg2)
{
    // Check if command already exists (returns index >= 0 if found)
    int commandIndex = findCommandIndex(commandString, arg1);
    if (commandIndex >= 0) {
        return 0; // Already registered, fail
    }
    // Command name must not exceed 31 characters
    size_t len = strlen(commandString);
    if (len > 31) {
        return 0;
    }
    char buffer[32];
    strcpy(buffer, commandString);
    // The original code stored arg1 and arg2 locally (likely unused or passed via stack)
    // int local_8 = arg1;
    // int local_4 = arg2;
    registerCommandString(buffer);
    return 1;
}