// FUNC_NAME: CommandManager::registerCommand
int CommandManager::registerCommand(char* commandName, unsigned int param2, unsigned int param3, unsigned int param4)
{
    bool success = false;
    int commandId = 0;
    int delta = s_commandArrayEnd - s_commandArrayStart; // +0x00 global difference (unused result)
    CommandEntry* entry = (CommandEntry*)malloc(0x4c);
    if (entry == 0) {
        commandId = 0;
    }
    else {
        char* p = commandName;
        while (*p != '\0') {
            p++;
        }
        int nameLen = (int)p - (int)(commandName + 1);
        hashString(commandName, nameLen); // likely hashes the command name
        success = true;
        commandId = createCommandEntry(commandInfo, &s_commandRegistry, param3, param2, param4); // stores results in commandInfo
    }

    // Insert commandId into global dynamic array (s_commandArray)
    if (s_commandArrayPtr < s_commandArrayEnd) {
        *s_commandArrayPtr = commandId;
        s_commandArrayPtr++;
    }
    else {
        growCommandArray(s_commandArrayPtr, &commandId);
    }

    if (success && commandInfo[0] != 0) {
        // Callback stored in commandInfo? local_4 is function pointer, commandInfo[0] is argument
        ((void (*)(int))commandCallback)(commandInfo[0]); // local_4 is likely the callback from createCommandEntry
    }
    return delta >> 2; // returns some value (maybe number of commands?)
}