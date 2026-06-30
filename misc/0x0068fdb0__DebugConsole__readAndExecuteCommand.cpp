// FUNC_NAME: DebugConsole::readAndExecuteCommand
char DebugConsole::readAndExecuteCommand(int param_1, int param_2, int sourceId) {
    char buffer[2048];
    // param_2 is unused in this function (likely reserved or input flag)
    char result = this->readLine(buffer, 0x800, sourceId); // FUN_0068fc60
    if (result != '\0') {
        this->executeCommand(buffer); // FUN_004d3d90
    }
    return result;
}