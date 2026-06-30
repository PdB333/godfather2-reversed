// FUNC_NAME: AudioManager::setAudioContext
// Address: 0x0060a460
// Purpose: Activates a sound/music context by index. Reads from a global audio context array (0x10-byte entries).
// If the context is marked as non-active (music), it plays the bank and updates the current music bank.
// If active (sound effect), it plays the bank and optionally a secondary bank.

struct AudioContext {
    int bankId;           // +0x00
    int unknown04;        // +0x04
    int secondaryBankId;  // +0x08
    bool isSoundEffect;   // +0x0C (0 = music, 1 = sound effect)
};

// Global audio manager object (singleton)
extern AudioManager* gAudioManager; // 0x01205750

// Array of AudioContext entries (0x10 bytes each), base at 0x011eb8f0
extern AudioContext* gAudioContextArray; // DAT_011eb8f0

// Currently active bank IDs
extern int gCurrentMusicBankId;      // 0x01205834
extern int gCurrentSoundBankId;      // 0x01205830
extern int gCurrentSecondaryBankId;  // 0x01205838
extern int gCurrentMusicContextIndex; // 0x00f15a60

void AudioManager::setAudioContext(int contextIndex) {
    int offset = contextIndex * 0x10;
    int bankId = gAudioContextArray[contextIndex].bankId; // +0x00

    if (!gAudioContextArray[contextIndex].isSoundEffect) {
        // Music context
        if (gCurrentMusicBankId != bankId) {
            // vtable offset 0x1ac = playMusicBank
            (*(*(code**)gAudioManager + 0x1ac))(gAudioManager, bankId);
            gCurrentMusicBankId = bankId;
            gCurrentMusicContextIndex = contextIndex;
        }
    } else {
        // Sound effect context
        if (gCurrentSoundBankId != bankId) {
            // vtable offset 0x170 = playSoundBank
            (*(*(code**)gAudioManager + 0x170))(gAudioManager, bankId);
            gCurrentSoundBankId = bankId;
        }

        int secondaryBankId = gAudioContextArray[contextIndex].secondaryBankId; // +0x08
        if (secondaryBankId != 0 && gCurrentSecondaryBankId != secondaryBankId) {
            // vtable offset 0x15c = playSecondaryBank
            (*(*(code**)gAudioManager + 0x15c))(gAudioManager, secondaryBankId);
            gCurrentSecondaryBankId = secondaryBankId;
        }
    }
}