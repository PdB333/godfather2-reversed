// FUNC_NAME: AudioManager::tickStreams
void AudioManager::tickStreams(void)
{
    ushort uPlaybackPos;
    int pStream;

    if (g_pStream1 != 0) {
        g_Stream1Counter = g_Stream1Counter + 1;
        pStream = FUN_00407da0();
        if (pStream == 0) {
            FUN_004084d0(&g_pStream1, 0x6000);
        }
        else {
            uPlaybackPos = *(ushort *)(pStream + 0x14); // +0x14 = playback position
            *(ushort *)(pStream + 0x14) =
                ((short)((int)((uint)uPlaybackPos * 2) >> 1) + 1U ^ uPlaybackPos) & 0x7fff ^ uPlaybackPos;
        }
    }
    if (g_pStream2 != 0) {
        g_Stream2Counter = g_Stream2Counter + 1;
        pStream = FUN_00407da0();
        if (pStream != 0) {
            uPlaybackPos = *(ushort *)(pStream + 0x14); // +0x14 = playback position
            *(ushort *)(pStream + 0x14) =
                ((short)((int)((uint)uPlaybackPos * 2) >> 1) + 1U ^ uPlaybackPos) & 0x7fff ^ uPlaybackPos;
            return;
        }
        FUN_004084d0(&g_pStream2, 0x6000);
    }
    return;
}