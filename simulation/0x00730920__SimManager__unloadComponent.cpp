// FUNC_NAME: SimManager::unloadComponent
void __fastcall SimManager::unloadComponent(SimManager* thisPtr)
{
    char streamBuffer[20]; // buffer for stream data
    int* streamResult = reinterpret_cast<int*>(streamBuffer + 16); // offset 0x14 within buffer, overlaps with local_8 used in decompiled
    // Note: streamResult points to the last 8 bytes of the buffer, but we treat as separate variable for clarity.

    preCleanupCheck(); // generic initial check, possibly a mutex or vtable validation

    void* streamPtr = *reinterpret_cast<void**>(reinterpret_cast<uint32_t>(thisPtr) + 0x758);
    if (streamPtr != nullptr)
    {
        stopAllStreams(0); // halt any active streams globally
        unregisterStream(thisPtr, 0); // remove this stream from manager tracking
        getStreamData(streamPtr, streamBuffer); // read pending stream data into local buffer

        if (*streamResult != 0)
        {
            freeStreamData(streamResult); // release the data if present
        }
    }
}