// FUNC_NAME: StreamManager::updateStreamTiming
void StreamManager::updateStreamTiming(int slotIndex) {
    // Read local stream struct from this pointer (fields at offsets +0x00 and +0x04)
    int streamId = *(int*)this;          // +0x00
    float startTime = *(float*)((char*)this + 4); // +0x04

    // Compute elapsed time from global game time
    float elapsed = g_gameTime - startTime; // DAT_00e44564

    // Access global array of per-stream flags (structured as rows of 11 slots)
    // DAT_01125d78 = number of active streams, stride = 0xB entries per stream
    int* flagArray = (int*)&DAT_01125c48;
    int streamIndex = DAT_01125d78 * 0xB + slotIndex;
    int streamFlag = flagArray[streamIndex];

    if (streamFlag != 0) {
        // Build a copy of the stream header (id + startTime)
        int streamHeader[2];
        streamHeader[0] = streamId;
        streamHeader[1] = *(int*)((char*)this + 4); // same startTime

        // Call the stream completion handler
        // DAT_01125ba4 is a global manager pointer
        FUN_0060add0(DAT_01125ba4, streamFlag, &streamHeader);
    }
}