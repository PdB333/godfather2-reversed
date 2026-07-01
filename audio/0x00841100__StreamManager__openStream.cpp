// FUNC_NAME: StreamManager::openStream
void PlayStreamWithDefaultFlags(uint32_t streamHandle) {
    // Get the singleton stream manager instance
    StreamManager* streamMgr = GetStreamManager();

    // Default stream configuration: mode=2 (play?), flags=0x10 (high priority?), reserved=0
    StreamInfo info;
    info.mode = 2;
    info.flags = 0x10;
    info.reserved = 0;

    // Call the virtual function to open/play the stream
    streamMgr->openStream(streamHandle, &info);
}

// Helper: returns the global StreamManager instance
StreamManager* GetStreamManager() {
    return reinterpret_cast<StreamManager*>(FUN_009c8f80());
}