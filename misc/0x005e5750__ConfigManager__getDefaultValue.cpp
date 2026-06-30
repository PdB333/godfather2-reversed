// FUNC_NAME: ConfigManager::getDefaultValue
int ConfigManager::getDefaultValue() {
    ConfigManager* mgr = (ConfigManager*)DAT_01223514; // global singleton pointer (DAT_01223514)
    char key = 0;   // default key (zero byte)
    int id = 0;     // placeholder (not used directly)
    int* entry = (int*)mgr->getEntry(&key); // get entry pointer by key (likely returns struct with 4-byte ID)
    if (entry != nullptr) {
        int entryId = *entry; // first member of entry structure is the ID
        return mgr->getValue(entryId); // retrieve value corresponding to that ID
    }
    return 0;
}