// FUNC_NAME: StreamManager::setStreamBuffer
void __thiscall StreamManager::setStreamBuffer(void *source1, void *source2)
{
    // Free previously allocated stream buffer at offset +0x11C
    streamBufferFree(*(void **)((char *)this + 0x11C));

    // Allocate a new stream buffer of size 0x440 (1088 bytes)
    void *newBuffer = streamBufferAlloc(0x440);
    if (newBuffer != nullptr)
    {
        // Initialize the new buffer with the given parameters and store it
        *(void **)((char *)this + 0x11C) = streamBufferInit(source1, source2);
    }
    else
    {
        // Allocation failed, clear pointer
        *(void **)((char *)this + 0x11C) = nullptr;
    }
}

// External helper functions (defined elsewhere in the engine)
extern void streamBufferFree(void *buffer);
extern void *streamBufferAlloc(int size);
extern void *streamBufferInit(void *param1, void *param2);