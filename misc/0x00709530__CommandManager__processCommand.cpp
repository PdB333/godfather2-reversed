// FUNC_NAME: CommandManager::processCommand
void CommandManager::processCommand(int commandId) {
    // Buffer to hold the command string representation (12 bytes)
    char commandStr[12];

    // Resolve the numeric command ID to a string or structured data
    GameUtil::getCommandString(commandId, commandStr);

    // Call the virtual method at vtable offset 0x1c (index 7)
    // This is likely the command execution handler
    (this->vtable[7])(commandStr);
    return;
}