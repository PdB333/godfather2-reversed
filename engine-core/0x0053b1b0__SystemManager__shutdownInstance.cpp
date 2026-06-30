// FUNC_NAME: SystemManager::shutdownInstance
void __thiscall SystemManager::shutdownInstance() {
    // Store pointer to this instance in global tracker (debug/logging)
    // Global address: 0x012058e8, likely a pointer to the active manager instance
    g_pActiveSystemManager = this;

    // Release resources at offsets +0x10 and +0x14 (e.g., COM-style interfaces or sub-managers)
    // FUN_0060a460 is likely a Release/DecRef function
    if (void* pResource1 = *(void**)((char*)this + 0x10)) {
        FUN_0060a460(pResource1);
    }
    if (void* pResource2 = *(void**)((char*)this + 0x14)) {
        FUN_0060a460(pResource2);
    }
}