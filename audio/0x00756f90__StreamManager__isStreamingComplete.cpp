// FUNC_NAME: StreamManager::isStreamingComplete
bool __fastcall StreamManager::isStreamingComplete(void* thisPtr)
{
    // Check if there is an active stream request at offset +0x108
    if (*(int*)((uint8_t*)thisPtr + 0x108) != 0)
    {
        // If a request exists, delegate to a function that checks its completion status
        // (function at 0x005f6820 with argument 0 likely returns whether the stream is done)
        return (bool)FUN_005f6820(0);
    }
    // No active request means streaming is considered complete
    return true;
}