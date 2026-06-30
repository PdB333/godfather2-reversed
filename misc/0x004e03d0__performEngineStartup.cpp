// FUNC_NAME: performEngineStartup
// 0x004e03d0 - Engine initialization routine that retrieves a subsystem pointer from TLS (FS:[0x2c] + 0x24)
// and calls a series of initialization functions.

void __cdecl performEngineStartup(void* unusedParam, void* subsystemPtr) {
    if (subsystemPtr == nullptr) {
        // Retrieve subsystem pointer from thread-local storage.
        // FS segment base + 0x2c points to a thread structure (TEB), then dereference to get
        // a global object (likely the engine application singleton), and offset 0x24 holds the subsystem pointer.
        uintptr_t* threadInfoBase = (uintptr_t*)__readfsdword(0x2c);
        uintptr_t* engineSingleton = *(uintptr_t**)threadInfoBase;
        subsystemPtr = (void*)engineSingleton[0x24 / 4];  // offset 0x24
    }
    void* localCopy = subsystemPtr;
    engineInitA(subsystemPtr);   // 0x004e9fa0 - initialize subsystem base
    engineInitB(localCopy);      // 0x004ea6b0 - initialize subsystem components
    engineGlobalInit();          // 0x0051c350 - global engine state initialization
    engineInitC(subsystemPtr);   // 0x0051c390 - finalize subsystem init
}