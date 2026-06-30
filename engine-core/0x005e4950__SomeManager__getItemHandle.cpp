// FUNC_NAME: SomeManager::getItemHandle
int SomeManager::getItemHandle(int param_1) {
    char unusedByte = 0;
    int handle = globalQuery(DAT_01223514, &unusedByte);
    if (handle != 0) {
        return resolveHandle(param_1, handle);
    }
    return 0;
}