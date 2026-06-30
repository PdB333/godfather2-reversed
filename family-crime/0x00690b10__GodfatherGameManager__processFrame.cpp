// FUNC_NAME: GodfatherGameManager::processFrame
void __thiscall GodfatherGameManager::processFrame(void) {
    // Global singleton pointer to some manager (likely a core app or framework object)
    // +0x4 is a pointer-to-pointer check (possibly a validity flag or interface pointer)
    if (g_pCoreManager) {
        if (*(void**)((char*)g_pCoreManager + 4)) {
            // Some internal state is valid – process accordingly
            void* result = someConvertFunction(this);        // e.g., gets game state handle
            someOutputFunction(result);                     // e.g., writes to a stream
            return;
        }
        void* result = someConvertFunction(this);
        someOutputFunction(result);
    }
}