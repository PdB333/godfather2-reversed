// FUNC_NAME: AudioManager::updateAudioState

// Function at 0x0060a460
// Updates current audio state (music, ambient, effect) based on state index table.
// Each entry is 16 bytes: { int primaryId, int secondaryId, byte flag, byte padding[3] }
// Flag: 0 = music state, non-zero = ambient+effect state

void AudioManager::updateAudioState(int stateIndex) {
    // Table of audio state entries, 16 bytes each
    // +0x0: primaryId (music or ambient)
    // +0x8: secondaryId (effect, only used for ambient)
    // +0xc: flag (0 = music, 1 = ambient)
    AudioStateEntry* entries = (AudioStateEntry*)0x011eb8f0;
    AudioStateEntry* entry = &entries[stateIndex];

    int primaryId = entry->primaryId;

    if (entry->flag == 0) {
        // Music state update
        if (gCurrentMusicId != primaryId) {
            // Set new music
            gAudioManager->setMusic(primaryId); // vtable+0x1ac
            gCurrentMusicId = primaryId;
            gCurrentStateIndex = stateIndex;
        }
    } else {
        // Ambient + effect state update
        if (gCurrentAmbientId != primaryId) {
            gAudioManager->setAmbient(primaryId); // vtable+0x170
            gCurrentAmbientId = primaryId;

            int effectId = entry->secondaryId;
            if (effectId != 0 && gCurrentEffectId != effectId) {
                gAudioManager->setEffect(effectId); // vtable+0x15c
                gCurrentEffectId = effectId;
            }
        }
    }
}