// FUNC_NAME: HandleManager::isHandleValid
bool HandleManager::isHandleValid(void* thisPtr)
{
    int index = HandleManager::getIndexFromHandle(thisPtr); // FUN_008b7bb0
    return (index >= 0);
}