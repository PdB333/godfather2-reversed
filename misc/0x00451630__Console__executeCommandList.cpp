// FUNC_NAME: Console::executeCommandList
// Address: 0x00451630
// Role: Executes an array of command strings, with per-command callback support.
void Console::executeCommandList(const char** commandArray, uint count) {
    // Begin processing the command buffer at offset +0x6C8
    this->beginProcessing(*(void**)(this + 0x6C8));

    if (count != 0) {
        for (uint i = 0; i < count; i++) {
            const char* commandStr = commandArray[i];
            if (commandStr != nullptr && commandStr[0] != '\0') {
                // Lock or begin command execution context
                commandSystem::beginCommand(0);
                // Parse and execute the command string
                commandSystem::executeString(commandStr);
                // Check for post-command callback (sets local_14 and local_8 via global state)
                commandSystem::retrieveCallback(); // sets callbackData and callbackFunction
                if (callbackData != 0) {
                    callbackFunction(callbackData);
                }
            }
        }
    }
    // Finalize batch execution
    this->finalizeExecution();
}