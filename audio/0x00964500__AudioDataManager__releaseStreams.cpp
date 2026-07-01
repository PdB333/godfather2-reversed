// FUNC_NAME: AudioDataManager::releaseStreams
void AudioDataManager::releaseStreams(void* stream1, void* stream2, void* stream3)
{
    // Check if the global audio data manager is initialized and has active streams
    if (gAudioDataManager != nullptr && *(int*)(gAudioDataManager + 0xc) != 0) {
        // Release the three stream objects
        releasePointer(stream1);
        releasePointer(stream2);
        releaseHandle(stream3);
        // Release the static stream table (10 entries)
        releaseTable(&gStreamTable, 10);
    }
}