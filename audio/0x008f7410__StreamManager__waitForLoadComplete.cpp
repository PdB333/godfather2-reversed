// FUNC_NAME: StreamManager::waitForLoadComplete
void StreamManager::waitForLoadComplete(StreamManager* thisPtr)
{
    // +0x00: thisPtr is the StreamManager object
    // Initialize the load operation context
    initLoadContext(thisPtr);
    // Register the load operation with a specific identifier (0x6346924e likely a hash/ID)
    registerLoadOperation(thisPtr, 0x6346924e);
    
    char isComplete;
    isComplete = checkLoadComplete();
    while (isComplete == '\0') {
        // Process next chunk of loading
        processLoadChunk();
        // Get current buffer pointer (16-byte structure)
        LoadBuffer* buffer = getCurrentLoadBuffer();
        // Check if any of the 4 ints in the buffer are non-zero (i.e., buffer has data)
        if ( ((buffer->data0 != 0) || (buffer->data1 != 0)) || 
             ((buffer->data2 != 0) || (buffer->data3 != 0)) ) {
            // Process the loaded buffer
            handleLoadedBuffer(buffer);
        }
        // Update load progress
        updateLoadProgress();
        // Check if load is complete again
        isComplete = checkLoadComplete();
    }
    // Load operation finished
}