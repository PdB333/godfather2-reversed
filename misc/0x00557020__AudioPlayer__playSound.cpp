// FUNC_NAME: AudioPlayer::playSound
// Address: 0x00557020
// This function plays the audio event stored at this+0x40.
// If that event is not valid or not loaded, it falls back to a global default sound.

class AudioPlayer {
public:
    // +0x40: AudioEvent* m_pAudioEvent
    int m_pAudioEvent; // Actually pointer, but decompiled as int

    // Returns true if sound was started/queued, false otherwise.
    bool __thiscall playSound();
};

// Forward declarations of helper functions from the audio system.
// These are likely member functions of some AudioSystem singleton.
extern int* g_pAudioSystem; // DAT_0113dfc8
extern int FUN_00ab06f0(char* buffer, int soundHandle); // Convert sound handle to name/status string
extern int FUN_009e7530(int audioEvent); // Start playing the given audio event
extern int FUN_00556e10(); // Get fallback/global default sound event
extern int FUN_009e71f0(int audioEvent); // Play fallback sound event

bool AudioPlayer::playSound() {
    int audioEvent = this->m_pAudioEvent;

    // First try to play the stored audio event
    if (audioEvent != 0) {
        // Get the audio system singleton and query sound status
        int* audioSystem = (int*)(**(code**)(*g_pAudioSystem + 0x14))(); // e.g., AudioSystem::getInstance()
        int soundHandle = (**(code**)(*audioSystem + 0x10))(audioEvent); // e.g., GetSoundHandle(audioEvent)
        char tempBuffer[1]; // placeholder; actual size unknown
        char* statusStr = (char*)FUN_00ab06f0(tempBuffer, soundHandle); // e.g., GetStatusString
        if (*statusStr != '\0') {
            // Sound is already playing or active? Then skip to fallback
            goto tryFallback;
        }
    }

    // Actually re-evaluate audioEvent, because we might have jumped from above
    audioEvent = this->m_pAudioEvent;
    if (audioEvent != 0) {
        // Check if the audio event is valid/loaded (offset +8 indicates readiness)
        if (*(int*)(audioEvent + 8) == 0) {
            return false; // Not ready to play
        }
        FUN_009e7530(audioEvent); // Play the event
        return true;
    }

tryFallback:
    // Fallback to a globally defined default sound
    int defaultSound = FUN_00556e10();
    if (defaultSound != 0 && *(int*)(defaultSound + 8) != 0) {
        FUN_009e71f0(defaultSound); // Play fallback
        return true;
    }

    return false; // Nothing could be played
}