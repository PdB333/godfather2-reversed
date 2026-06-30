// FUNC_NAME: initializeCoreComponent
void __cdecl initializeCoreComponent(void) {
    // Global flags indicating initialization state (probably in .bss)
    if (g_systemInitialized == 0) {
        if (g_secondaryInitFlag == 0) {
            // Perform pre-initialization only if secondary flag is not set
            subsystemPreInit(0); // FUN_0068baf0 – likely sets up core state
        }
        // Allocate a 32-byte block (0x20)
        void* pBuffer = allocateMemory(0x20); // FUN_009c8e50 – memory allocator
        if (pBuffer != 0) {
            // Retrieve a handle (probably an index or offset)
            uint handle = getMemoryHandle(); // FUN_009c8f80 – returns handle from allocator
            // Construct an object using the handle
            constructObjectFromHandle(handle); // FUN_008d0f10 – object constructor
        }
        // Post-initialization cleanup or finalize
        subsystemPostInit(0); // FUN_0068bcd0 – likely sets up secondary structures
    }
}