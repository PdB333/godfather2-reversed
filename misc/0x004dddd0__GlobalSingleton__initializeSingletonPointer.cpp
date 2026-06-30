// FUNC_NAME: GlobalSingleton::initializeSingletonPointer
void GlobalSingleton::initializeSingletonPointer(void)
{
    // Initialize singleton pointer if not already set
    // DAT_012054bc is the global singleton instance pointer
    // PTR_PTR_0110ae94 is the default singleton instance address
    if (gSingletonInstance == (void**)0x0) {
        gSingletonInstance = &gDefaultSingletonInstance;
    }
    return;
}