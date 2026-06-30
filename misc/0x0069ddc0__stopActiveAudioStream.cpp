// FUNC_NAME: stopActiveAudioStream
void stopActiveAudioStream(void)
{
    // g_bStreamActive: global flag indicating an active stream (byte at 0x0112a02a)
    if (g_bStreamActive != '\0') {
        g_bStreamActive = '\0';
        // Stop the stream with its handle, volume, and pan (presumably floats or ints at 0x0112a02c, 0x0112a030, 0x0112a034)
        stopStream(g_hStream, g_fStreamVolume, g_fStreamPan);
        // g_bLoopEnabled: flag for looping playback (byte at 0x0112a028)
        if (g_bLoopEnabled != '\0') {
            setStreamLoopMode(0); // Disable looping
        }
    }
}