// FUNC_NAME: StreamManager::isStreamingComplete
// Function address: 0x007af890
// Role: Checks if a streaming operation (e.g., animation, audio, or asset loading) has completed.
// Returns false (0) if in progress, true (1) if done or unavailable.
bool StreamManager::isStreamingComplete() {
    // Get the singleton stream manager (FUN_007ab710)
    int* streamMgr = (int*)GetStreamManager();
    if (streamMgr != nullptr) {
        // Call virtual function at vtable offset 0xC0 (assumed to return progress as float)
        // vtable[0xC0/4] = index 48 (since each pointer is 4 bytes)
        float progress = (*(float (__thiscall**)(int*))(*streamMgr + 0xC0))(streamMgr);
        if (progress > 0.0f) {
            return false; // Still streaming/playing
        }
    }
    return true; // Finished or manager not present
}