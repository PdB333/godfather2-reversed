// FUNC_NAME: Entity::stopSoundComponent
void Entity::stopSoundComponent()
{
    SoundComponent* pSound = reinterpret_cast<SoundComponent*>(this->m_pSound); // +0x14
    if (pSound == nullptr) {
        return;
    }

    // Check if the global audio manager is initialized
    if (AudioManager::isInitialized(&g_audioManager) != 0) {
        int oldState = pSound->m_state; // +0x170
        pSound->m_state = 0; // Reset state to idle/stopped

        // If the sound was playing and a looping flag is set, reset timer
        if ((oldState == 2) && (pSound->m_flags != 0)) { // +0x14c for flags
            AudioManager::stopSound(&g_audioManager); // 0x00ab4e70
            pSound->resetTimer(0, 0, 0); // 0x00458110, pass pointer to timer member at +0x148
            return;
        }

        // Otherwise just stop the sound
        AudioManager::stopSound(&g_audioManager);
    }
}