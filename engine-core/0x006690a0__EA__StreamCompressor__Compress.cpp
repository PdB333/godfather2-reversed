// FUNC_NAME: EA::StreamCompressor::Compress
int Compress(int context, uint flags)
{
    // Local structures representing dynamic buffers with data, capacity, length
    struct Buffer {
        void* data;
        int capacity;
        int length;
    } sourceBuffer, destBuffer, tempBuffer;

    // Check early condition: if bit0 of flags is 0 and context->flag == 1, return error
    if (((flags & 1) == 0) && (*(int*)(context + 8) == 1)) {
        return -3; // Compressor already finalised?
    }

    // Allocate intermediate buffers (64 bytes each)
    sourceBuffer.data = calloc(4, 0x40);
    if (sourceBuffer.data == nullptr) {
        return -2; // Out of memory
    }
    sourceBuffer.capacity = 0x40;
    sourceBuffer.length = 0;

    tempBuffer.data = calloc(4, 0x40);
    if (tempBuffer.data == nullptr) {
        FreeBuffer(&sourceBuffer);
        return -2;
    }
    tempBuffer.capacity = 0x40;
    tempBuffer.length = 0;

    Buffer outputBuffer;
    outputBuffer.data = calloc(4, 0x40);
    if (outputBuffer.data == nullptr) {
        FreeBuffer(&sourceBuffer);
        FreeBuffer(&tempBuffer);
        return -2;
    }
    outputBuffer.capacity = 0x40;
    outputBuffer.length = 0;

    // Save and reset context state
    int savedFlag = *(int*)(context + 8);
    *(int*)(context + 8) = 0;

    // Initialise compressor module
    InitCompressor();

    int result = 0;
    do {
        // Check for input data availability
        result = HasMoreInputData();
        if (result != 0) break;

        // Read input data into source buffer (size = flags - 1)
        result = ReadDataIntoBuffer(&sourceBuffer, flags - 1);
        if (result != 0) break;

        // Encode source buffer into temporary buffer
        result = EncodeBlock(&outputBuffer, &sourceBuffer, &tempBuffer);
        if (result != 0) break;

        // Apply transform to temporary buffer using context
        result = ApplyTransform(&tempBuffer, context);
        if (result != 0) break;

        // Merge output buffer with temporary buffer
        result = MergeBuffers(&outputBuffer, flags, &outputBuffer);
        if (result != 0) break;

        // XOR temporary buffer with output buffer
        result = XorBuffers(&tempBuffer, &outputBuffer, &outputBuffer, 0);
        if (result != 0) break;

        // Copy output buffer to source buffer
        result = CopyBuffer(&sourceBuffer, &outputBuffer);
        if (result != 0) break;

    } while ((tempBuffer.length != outputBuffer.length) || (result = CheckForMoreData(), result != 0));

    // Finalise encoding
    result = ReadDataIntoBuffer(&sourceBuffer, flags);
    if (result == 0) {
        while (true) {
            result = GetNextByte();
            if (result != 1) break; // No more data
            result = FlushBuffer(&sourceBuffer, 1, &sourceBuffer);
            if (result != 0) break;
            result = ReadDataIntoBuffer(&sourceBuffer, flags);
            if (result != 0) break;
        }
        // Restore context state
        *(int*)(context + 8) = savedFlag;

        // Get compressor statistics and store high part
        CompressorStats stats = GetStats();
        *(int*)((int)stats + 8) = (int)((ulonglong)stats >> 32);
        result = 0;
    }

    // Cleanup
    FreeBuffer(&outputBuffer);
    FreeBuffer(&tempBuffer);
    FreeBuffer(&sourceBuffer);
    return result;
}