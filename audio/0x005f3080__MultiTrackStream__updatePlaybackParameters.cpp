// FUNC_NAME: MultiTrackStream::updatePlaybackParameters

// Function address: 0x005f3080
// Purpose: Updates pitch and sample rate for a MultiTrackStream instance based on sound data from AudioDataManager.

// Known classes: MultiTrackStream, AudioDataManager
// Global: g_pAudioDataManager at 0x01223508

void MultiTrackStream::updatePlaybackParameters(MultiTrackStream* this) // __thiscall
{
    int* pSoundData;
    int soundId;
    char valid;
    float pitch = 0.0f;          // local_18
    float volume = 1.0f;         // local_14 (default volume = 1.0, from DAT_00e2b1a4)
    int sampleRate = 96000;      // local_10 (default 96 kHz)
    float finalPitch;            // local_c

    if (this != 0)
    {
        pSoundData = *(int**)(this + 0x2c);  // +0x2c: pointer to sound data structure (BankEntry?)
        finalPitch = 1.0f;                   // local_c default (from DAT_00e2b1a4)
        sampleRate = 96000;                  // local_4 default

        if (pSoundData != 0 && *(int*)(this + 0x30) != 0)  // +0x30: active flag or reference count
        {
            if (*pSoundData != 0)  // valid sound data flag
            {
                soundId = pSoundData[0x17];  // +0x5c: sound ID or bank index
                pitch = 0.0f;                // reset
                volume = 1.0f;               // default volume
                sampleRate = 96000;          // default sample rate

                // Check a flag in sound data
                if ((*(byte*)(pSoundData + 0x1c) & 4) == 0)  // +0x70? Actually +0x1c * 4 = +0x70? Need offset check.
                {
                    // Simple check: is sound valid?
                    valid = AudioDataManager::GetInstance()->isSoundValid(soundId);
                }
                else
                {
                    // Get precise pitch and volume from audio data manager
                    valid = AudioDataManager::GetInstance()->getPitchAndVolume(soundId, &pitch, &volume, pSoundData[0x1b]); // +0x6c: some parameter (e.g., speed factor)
                }

                if (valid != 0)
                {
                    finalPitch = pitch;
                    // volume is stored but not used further? Possibly intended for later.
                }

                // Get the sample rate from audio data manager
                valid = AudioDataManager::GetInstance()->getSampleRate(soundId, &sampleRate);
                if (valid != 0)
                {
                    // sampleRate is stored in local_4 but not passed to callback
                }
            }

            // Apply instance-specific pitch multiplier
            finalPitch = *(float*)(this + 0x4c) * finalPitch;  // +0x4c: pitch multiplier

            // Call callback to apply the pitch (e.g., set pitch in underlying stream)
            (**(code**)(this + 0x34))(pSoundData, this, &finalPitch);  // +0x34: function pointer to apply pitch callback
        }
    }
    return;
}