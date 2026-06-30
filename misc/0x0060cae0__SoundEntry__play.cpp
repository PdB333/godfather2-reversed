// FUNC_NAME: SoundEntry::play
// Address: 0x0060cae0
// Role: Plays a sound entry from a bank, handling bank switching and range calculation.

// Assumed global pointers (from EARS engine)
extern AudioDataManager* gAudioDataManager; // DAT_01205750
extern int gCurrentBankId; // DAT_0120583c

// Forward declarations of helper functions
void AudioDataManager::lock(); // FUN_006102c0
uint AudioDataManager::getCurrentTime(); // FUN_0060c9d0

// SoundEntry class (partial, offsets based on decompilation)
class SoundEntry {
public:
    int bankId;          // +0x00
    ushort startIndex;   // +0x04
    // ... padding ...
    ushort endIndex;     // +0x12
    // ... other fields ...

    void play(int soundId, uint extraData) {
        // Map special sound ID
        if (soundId == 0xd) {
            soundId = 6;
        }

        // Get range from this entry
        uint rangeEnd = (uint)this->endIndex;
        ushort rangeStart = this->startIndex;
        uint rangeCount = (rangeEnd - (uint)rangeStart) + 1;

        // Switch bank if needed
        if (gCurrentBankId != this->bankId) {
            // Call virtual function at vtable+0x1a0 (likely setCurrentBank)
            (**(code**)(*(int*)gAudioDataManager + 0x1a0))(gAudioDataManager, this->bankId);
            gCurrentBankId = this->bankId;
        }

        // Lock audio manager (prevent concurrent access)
        gAudioDataManager->lock();

        // Get current time for scheduling
        uint currentTime = gAudioDataManager->getCurrentTime();

        // Call virtual function at vtable+0x148 (likely playStream)
        // Parameters: soundId, 0 (flags?), rangeStart, rangeCount, extraData, currentTime
        (**(code**)(*(int*)gAudioDataManager + 0x148))
            (gAudioDataManager, soundId, 0, (uint)rangeStart, rangeCount, extraData, currentTime);
    }
};