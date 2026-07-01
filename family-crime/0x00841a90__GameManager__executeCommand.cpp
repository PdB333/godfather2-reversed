// FUNC_NAME: GameManager::executeCommand
void GameManager::executeCommand(void *param_1) {
    CommandManager *cmdMgr = GetCommandManager();
    CommandData cmdData;
    cmdData.commandId = 2;
    cmdData.param1 = 0x10;
    cmdData.param2 = 0;
    cmdMgr->vtable->execute(param_1, &cmdData);
}