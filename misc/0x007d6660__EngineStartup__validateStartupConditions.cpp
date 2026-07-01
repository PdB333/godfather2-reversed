// FUNC_NAME: EngineStartup::validateStartupConditions
int EngineStartup::validateStartupConditions(void) {
    void* alloc = allocMemory(0x34); // FUN_00798f50 – allocate 0x34 bytes (likely a small struct)
    char allocOk = checkAllocation(alloc); // FUN_0079e970 – validates allocation succeeded
    if (!allocOk) {
        return 0;
    }
    char featureOk = checkFeatureSupport(0x400000); // FUN_007ab420 – checks if engine feature 0x400000 is available
    if (!featureOk) {
        return 0;
    }
    int sysCap = getSystemCapability(); // FUN_007ab350 – non-zero means engine/system is capable
    if (!sysCap) {
        return 0;
    }
    // Global structure at DAT_011299bc, offset +0x1c is a flag (0 = success, non-zero = block)
    if (*(int*)(DAT_011299bc + 0x1c) == 0) {
        return 1;
    }
    return 0;
}