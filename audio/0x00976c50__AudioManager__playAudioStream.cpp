// FUNC_NAME: AudioManager::playAudioStream
// Address: 0x00976c50
// This function checks a flag and conditionally calls a virtual method on a global object,
// then dispatches the result to an audio playback function.

void __fastcall AudioManager::playAudioStream(AudioManager* this)
{
    uint8_t streamFlag = this->streamFlag; // +0x128: flag indicating if stream is active

    if (streamFlag != 0)
    {
        int adjustedThis;

        // g_AudioManagerTable is a global pointer array; element at index 4 points to
        // an object whose base (by subtracting 0x1f30) holds a vtable for audio callbacks.
        if (*(int**)(g_AudioManagerTable + 4) == nullptr)
        {
            adjustedThis = 0;
        }
        else
        {
            adjustedThis = **(int**)(g_AudioManagerTable + 4) - 0x1f30;
        }

        // Check global game state flag (bit 1 of a DWORD)
        if ((*(uint32_t*)(g_GameStateFlags + 0x14) >> 1) & 1)
        {
            uint32_t streamBuffer = this->streamBuffer; // +0x124: buffer for stream data

            // Virtual call on the derived object (offset 0x1f30) using vtable slot 2
            typedef void* (__thiscall *PlayCallback)(int, uint32_t, uint8_t);
            PlayCallback callback = *(PlayCallback*)(*(int*)(adjustedThis + 0x1f30) + 8);
            void* result = callback(adjustedThis + 0x1f30, streamBuffer, streamFlag);

            // Dispatch to actual playback primitive
            AudioSystem::dispatchPlayback(result, streamBuffer, streamFlag);
        }
    }
}