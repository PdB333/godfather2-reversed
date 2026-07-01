// FUNC_NAME: SomeManager::initSingleton
void __thiscall SomeManager::initSingleton() {
    g_someVersion = 0x16; // global version indicator (DAT_00e5672c)
    *(int*)(this + 0x60) = 0; // clear a field at +0x60 (e.g., timer, state)

    // One-time initialization guarded by global flag bit 0
    if ((g_initializationFlags & 1) == 0) {
        // Set up internal callback/handler; first arg is pointer to a sub‑object at this+0x14
        registerSetupCallback((void*)(this + 0x14), (void*)0x00931e00, 0);
        g_initializationFlags |= 1;
    }
}