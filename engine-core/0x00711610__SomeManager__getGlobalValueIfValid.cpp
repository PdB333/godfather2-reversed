// FUNC_NAME: SomeManager::getGlobalValueIfValid
// Function address: 0x00711610
// Role: Returns a value from a global singleton (DAT_0113105c) only if the given pointer is non-null; otherwise returns 0.
uint32_t SomeManager::getGlobalValueIfValid(void* obj) {
    if (obj != 0) {
        return getGlobalValue(DAT_0113105c); // 0x0043b870 - retrieves value from global manager
    }
    return 0;
}