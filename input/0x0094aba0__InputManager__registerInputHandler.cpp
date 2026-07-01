// FUNC_NAME: InputManager::registerInputHandler
void __thiscall InputManager::registerInputHandler(void *this)
{
    // +0x6c is likely a handler ID or callback pointer field
    FUN_005c01d0(&gInputManager, (int)this + 0x6c, 1, &LAB_0094ab50, 0, 0);
    FUN_005c0890();
    return;
}