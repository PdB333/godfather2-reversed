// FUNC_NAME: AssetStream::processUntilComplete
void __thiscall AssetStream::processUntilComplete(int thisPtr, uint streamHandle)
{
    char finished;
    uint dataHandle;
    void* dataBuffer;

    // Initialize the stream with the given handle
    streamInit(streamHandle);
    streamSetFourCC(streamHandle, 'KRA\x27');  // Magic identifier "KRA'"

    // Loop until the stream processing is complete
    finished = streamIsFinished(streamHandle);
    while (finished == 0) {
        // Pump the stream's internal processing
        streamUpdate(streamHandle);

        // Check if a data chunk is available
        dataHandle = streamGetNextChunk(streamHandle);
        if (dataHandle == 0) {
            // No chunk yet, keep pumping
            streamUpdate(streamHandle);
            // Get the actual data buffer from the chunk
            dataBuffer = streamGetChunkData(streamHandle);
            // Store the buffer pointer in the object (offset +0x50)
            *(void**)(thisPtr + 0x50) = dataBuffer;
        }

        // Advance to next chunk
        streamAdvanceChunk(streamHandle);
        finished = streamIsFinished(streamHandle);
    }
}