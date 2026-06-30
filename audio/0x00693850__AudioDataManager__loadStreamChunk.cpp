// FUNC_NAME: AudioDataManager::loadStreamChunk
// Function address: 0x00693850
// Initializes a 12-byte stream buffer and copies up to 0x8000 bytes of stream data into a global buffer.

void AudioDataManager::loadStreamChunk(void)
{
    void* mem = operatorNew(0xc); // allocate 12 bytes for stream state
    if (mem == 0) {
        g_audioStreamState = 0; // DAT_01129bc4
    } else {
        g_audioStreamState = initStreamState(); // FUN_00690860
    }
    void* streamData = getStreamData(); // FUN_00691a70 -> returns pointer to stream data source
    if (g_audioDataBuffer != 0) { // DAT_01206a08
        copyMemory(g_audioDataBuffer, streamData, 0x8000); // FUN_00408900(dst, src, size)
    }
}