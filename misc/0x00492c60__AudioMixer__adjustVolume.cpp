// FUNC_NAME: AudioMixer::adjustVolume
void __thiscall AudioMixer::adjustVolume(float delta, int newValue)
{
    // Offset field definitions (from this structure)
    // +0x10: int m_currentVolumeIndex
    // +0x50: int m_outputState
    // +0x1b8: char m_volumeLocked
    // +0x1bc: int m_lockedVolume
    // +0x1e0: int m_audioParamA
    // +0x1e4: int m_audioParamB
    // +0x1e8: float m_volumeDeltaAccum

    // Global constants (likely defined elsewhere)
    extern float g_masterVolume;
    extern int kVolumeLevelHigh;
    extern int kVolumeLevelDefault;
    extern int kVolumeLevelLow;
    extern int kVolumeStateOff;
    extern int kVolumeStateOn;
    extern AudioMixer* g_currentMixer;  // singleton instance

    this->m_volumeDeltaAccum = g_masterVolume - delta;

    if (delta < 0.0f)
    {
        // Volume decreasing
        this->m_audioParamB = 0;

        if (this->m_volumeLocked == 0)
        {
            kVolumeLevelDefault = kVolumeLevelLow;  // Use low level when not locked
        }

        if (kVolumeLevelDefault != this->m_currentVolumeIndex)
        {
            this->m_currentVolumeIndex = kVolumeLevelDefault;
            int volumeToRestore = (this->m_volumeLocked == 0) ? this->m_lockedVolume : 0;
            this->m_outputState = volumeToRestore;

            if (g_currentMixer == this)
            {
                setVolumeLevel(kVolumeLevelDefault);  // Apply new volume level
            }
        }

        this->m_outputState = kVolumeStateOff;
        return;
    }
    else
    {
        // Volume increasing or staying
        if (this->m_volumeLocked == 0)
        {
            bool stateChanged = (this->m_currentVolumeIndex != kVolumeLevelHigh);
            this->m_audioParamB = newValue;

            if (stateChanged)
            {
                this->m_currentVolumeIndex = kVolumeLevelHigh;
                setVolumeLevel(kVolumeLevelHigh);
            }

            if (g_currentMixer == this)
            {
                updateMixerState(kVolumeLevelHigh, this->m_audioParamA, this->m_audioParamB);
            }

            this->m_outputState = kVolumeStateOn;
        }
    }
}