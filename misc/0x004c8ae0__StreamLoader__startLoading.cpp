// FUNC_NAME: StreamLoader::startLoading
// Function at 0x004c8ae0 attempts to start an asynchronous load operation.
// Returns true if the load was initiated successfully, false otherwise.
// This appears to be part of a custom streaming system.
bool StreamLoader::startLoading()
{
    bool loadStarted = false;

    // Check if the stream data is valid (e.g., file or buffer present)
    if (*(int*)(this + 0x0C) != 0)
    {
        // Local variable to hold the callback address
        void* callbackFunc = reinterpret_cast<void*>(0x004c89c0); // Load completion callback
        void* callbackPtr = &callbackFunc;

        // Call the engine's streaming loader with the global manager, stream ID (offset 0x10), and callback pointer
        int resultHandle = FUN_005e4f90(*(void**)0x012234bc, *(int*)(this + 0x10), &callbackPtr); // g_streamManager, streamID, callback

        // Store the resulting handle (likely a stream handle or request ID)
        *(int*)(this + 0x14) = resultHandle;

        // If a valid handle was returned, loading was initiated
        if (resultHandle != 0)
        {
            loadStarted = true;
        }
    }

    return loadStarted;
}