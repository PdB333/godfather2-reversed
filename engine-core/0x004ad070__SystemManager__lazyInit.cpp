// FUNC_NAME: SystemManager::lazyInit
void SystemManager::lazyInit(void)
{
    // Delegates initialization to the main routine at 0x004ae6f0
    performInit();
    return;
}