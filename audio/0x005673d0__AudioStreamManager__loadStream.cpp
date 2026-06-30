// FUNC_NAME: AudioStreamManager::loadStream

void __thiscall AudioStreamManager::loadStream(AudioStreamManager* thisPtr, uint32_t resourceId)
{
    // Attempt to allocate a new stream buffer (0x340 bytes)
    void* newBuffer = allocateMemory(0x340);
    if (newBuffer != nullptr) {
        // Initialize the buffer from the given resource ID (e.g., file handle or bank index)
        void* streamHandle = createResourceFromId(resourceId);
        thisPtr->state = 5;             // +0x10: loading/active state
        thisPtr->streamBuffer = streamHandle; // +0x08: pointer to actual stream data / handle
        return;
    }
    // Allocation failed – set error state and null handle
    thisPtr->state = 5;                 // +0x10: still marks as loading (or error?)
    thisPtr->streamBuffer = nullptr;    // +0x08: no stream available
}