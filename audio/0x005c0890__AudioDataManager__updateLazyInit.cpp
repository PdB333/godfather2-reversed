// FUNC_NAME: AudioDataManager::updateLazyInit
void __thiscall AudioDataManager::updateLazyInit(void) {
    int allocResult;
    // +0x0: global manager instance pointer (DAT_01205664)
    static AudioDataManager* s_managerInstance = nullptr;

    if (s_managerInstance == nullptr) {
        // Allocate a block of 200 bytes for the manager
        allocResult = allocateMemory(200, 0); // FUN_005c4410
        if (allocResult != 0) {
            s_managerInstance = constructManager(); // FUN_005c3070
            initializeManager(); // FUN_005c31d0
            performUpdate(this); // FUN_005c3b10(this)
            return;
        }
        s_managerInstance = nullptr;
        initializeManager(); // FUN_005c31d0
    }
    performUpdate(this); // FUN_005c3b10(this)
    return;
}