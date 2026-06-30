// FUNC_NAME: SomeSingletonManager::lazyInit
void SomeSingletonManager::lazyInit(void* initParam) {
    // FUN_00637f10: returns a pointer to the singleton instance sentinel
    void* instancePtr = (void*)FUN_00637f10();
    // Compare to global sentinel address (0x00e2a93c)
    if (instancePtr == (void*)&DAT_00e2a93c) {
        // FUN_00637d60: performs actual initialization using initParam
        FUN_00637d60(initParam);
    }
}