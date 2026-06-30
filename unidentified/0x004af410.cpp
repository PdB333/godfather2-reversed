// FUN_004af410: InputManager::getInstance
// 0x004af410: Returns the singleton instance of InputManager.
InputManager* InputManager::getInstance()
{
    return &gInputManager;
}