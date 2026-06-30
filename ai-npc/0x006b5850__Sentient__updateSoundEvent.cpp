// FUNC_NAME: Sentient::updateSoundEvent
void __fastcall Sentient::updateSoundEvent(void) {
    int entityPtr;

    // Check if a sound event is already active
    if (m_pSoundEvent == nullptr) {
        // No active sound event: decide if we need to start one
        // Check if the entity is not dead (bit 0 of m_flags) and has a valid entity pointer
        if (((m_flags & 1) == 0) && (m_pEntity != nullptr)) {
            entityPtr = static_cast<int>(EntityManager::getEntity(m_pEntity));
            if ((entityPtr != 0) && ((*(uint32_t*)(entityPtr + 0x84) >> 5) & 1) == 0) {
                // Entity is alive and not in a suppressed state (bit 5 clear) -> start sound
                AudioManager::playSound();
                return;
            }
        }
    } else {
        // A sound event is active: check if we should stop it
        if (((m_flags & 1) == 0) && (m_pEntity != nullptr)) {
            entityPtr = static_cast<int>(EntityManager::getEntity(m_pEntity));
            if ((entityPtr != 0) && ((*(uint32_t*)(entityPtr + 0x84) >> 5) & 1) == 0) {
                // Entity still valid and not suppressed -> keep sound playing (do nothing)
                return;
            }
        }
        // Entity is dead, missing, or suppressed: stop the sound event
        if (m_pSoundEvent != nullptr) {
            AudioManager::stopSound(m_pSoundEvent);
            m_pSoundEvent = nullptr;
        }
    }
}