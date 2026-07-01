// FUNC_NAME: StreamPlayback::stop
void __fastcall StreamPlayback::stop(int param_1)
{
    // Check if the stream is currently playing (flag at offset 0x81)
    if (*(char *)(param_1 + 0x81) != '\0')
    {
        // Notify the global stream manager to stop this stream
        stopStream(&g_StreamManager);  // FUN_004086d0
        // Clear the playing flag
        *(char *)(param_1 + 0x81) = '\0';
    }
    return;
}