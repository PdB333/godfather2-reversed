// FUNC_NAME: AudioChannel::updatePlayback
void __thiscall AudioChannel::updatePlayback(float currentTime)
{
    Stream* pStream = m_pStream;            // +0x10
    SoundInstance* pInstance = m_pSoundInstance; // +0x18

    // Check if audio system is globally enabled
    if (AudioSystem::isAudioEnabled())
    {
        // Check if enough time has passed since last play (cooldown)
        if ((currentTime <= m_lastPlayTime + g_fMinPlayInterval) && 
            (pStream != nullptr) && 
            (pInstance != nullptr))
        {
            goto PLAY_EXISTING;
        }

        // If stream is not busy, load a new sound and prepare it
        if (!StreamManager::isStreamActive())
        {
            SoundHandle newHandle = AudioManager::createSoundInstance(
                m_resourceId,                    // +0x0c
                g_pPrimarySoundBank,             // DAT_00d61b40
                0, 0, 
                0xF                              // priority
            );
            setActiveSound(newHandle);           // FUN_0071ab70
            m_lastPlayTime = currentTime;        // +0x48
        }
    }

    // If no instance is present, nothing to do
    if (pInstance == nullptr)
        return;

PLAY_EXISTING:
    // Check if the resource is valid and the instance is ready to play
    if (AudioManager::isSoundValid(m_resourceId) && 
        SoundInstance::isReadyToPlay(pInstance))
    {
        // Mark as playing
        m_flags |= 0x2;                          // +0x3c, bit 2 = PLAYING

        // Start playback on the instance
        pInstance->play();                       // FUN_0071b450

        // If this instance is the currently active one, clear the resource
        if (m_pCurrentSound == pInstance)        // +0x20
        {
            setActiveSound(nullptr);              // FUN_0071ab70(0)
        }
    }
}