// FUNC_NAME: StreamManager::closeCurrentStream
void __fastcall StreamManager::closeCurrentStream(StreamManager* this) {
    if (*(int*)((uintptr_t)this + 0x148) != 0) {
        releaseStream(*(int*)((uintptr_t)this + 0x148));
        bool bShuttingDown = g_bShuttingDown == '\0';
        *(int*)((uintptr_t)this + 0x148) = 0;
        if (bShuttingDown) {
            // Additional cleanup when not shutting down
            FUN_004a8f30(this);   // Likely a function that performs extra cleanup
            FUN_009473d0();       // Global cleanup function
        }
    }
}