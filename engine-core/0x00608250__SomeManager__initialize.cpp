// FUNC_NAME: SomeManager::initialize
int SomeManager::initialize()
{
    int iVar1;
    
    this->preInit();
    iVar1 = g_someManager->someMethod(&g_someData);
    if ((g_bFlagA != 0) || ((g_flagB & 2) == 0)) {
        g_bFlagC = 1;
    } else {
        g_bFlagC = 0;
    }
    if (iVar1 < 0) {
        return 0;
    }
    if (g_someManager != nullptr) {
        g_someManager->release();
    }
    this->postInit();
    return 1;
}