// FUNC_NAME: ModuleManager::performAction
int __thiscall ModuleManager::performAction(int param2, int param3)
{
    int result = getGlobalStatus(); // FUN_0071ce20 - returns some status/context
    // +0x4 points to a sub-module object
    executeSubAction(*(int *)(this + 4), param2, param3); // FUN_0071c720
    return result;
}