// FUNC_NAME: EARS::AudioStreamManager::stopAllStreams
// Iterates over all managed audio streams, stops active ones, resets flags, and increments a stop counter.
// Object layout:
//   this+0x0c: int streamCount
//   this+0x14: AudioStream** streamArray
// AudioStream layout:
//   +0x1fc: int activeState (non-zero means active/loaded)
//   +0x208: byte playingFlag
//   +0x209: byte pausedFlag
//   +0x20c: int stopCounter

void EARS::AudioStreamManager::stopAllStreams(EARS::AudioStreamManager* this)
{
    int streamCount = *(int*)((char*)this + 0x0c);                 // Number of stream slots
    EARS::AudioStream** streamArray = (EARS::AudioStream**)((char*)this + 0x14);

    for (int i = 0; i < streamCount; i++)
    {
        EARS::AudioStream* stream = streamArray[i];
        if (stream != nullptr && *(int*)((char*)stream + 0x1fc) != 0)
        {
            // Clear playback state flags
            *(char*)((char*)stream + 0x208) = 0;  // Reset playing flag
            *(char*)((char*)stream + 0x209) = 0;  // Reset paused flag
            FUN_00650be0(stream);                  // Stop/release stream (e.g., stop playback, unload)
            *(int*)((char*)stream + 0x20c) += 1;   // Increment stop count (tracking usage)
            FUN_00650de0();                         // Global audio system update (e.g., process stop events)
        }
    }
}