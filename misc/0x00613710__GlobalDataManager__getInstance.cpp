// FUNC_NAME: GlobalDataManager::getInstance
void* GlobalDataManager::getInstance() {
    // Returns pointer to global singleton data at 0x011f6a30
    extern char g_globalData[]; // located at 0x011f6a30
    return g_globalData;
}