// FUNC_NAME: InputHandler::handleMoveRight
void __fastcall InputHandler::handleMoveRight(void* thisPtr)
{
    // +0x50: flag indicating whether move right action is allowed
    if (*(char*)((int)thisPtr + 0x50) == '\0')
    {
        // Register "MoveRight" action with the game's action manager
        // FUN_00929a20 likely is ActionManager::registerAction or similar
        // DAT_00d90fa8, DAT_011304d8, DAT_011302c0 are global data/strings
        FUN_00929a20("MoveRight", &DAT_00d90fa8, &DAT_011304d8, &DAT_011302c0);
    }
}