// FUN_0045a100: AudioManager::activateSound
// This function looks up a sound event by its ID in a global hash table and activates it,
// stopping any currently active sound and updating the manager's state.

#include <cstdint>

// Forward declarations of sound system functions.
void stopSound(uint32_t soundId);   // FUN_004d24f0
void updateAudioState();             // FUN_004d23f0

// Hash table node – stored in a global array indexed by (soundId & 0x1FFF).
// Offsets:
// +0x00: unknown (maybe padding or extra data)
// +0x04: unknown
// +0x08: dataPtr – pointer to actual sound data
// +0x0C: id      – the sound ID used for matching
// +0x10: next    – next node in the bucket chain
struct SoundHashNode {
    char gap00[0x08];     // +0x00..0x07
    void* dataPtr;        // +0x08
    uint32_t id;          // +0x0C
    SoundHashNode* next;  // +0x10
};

extern SoundHashNode* g_soundHashTable[8192]; // DAT_012054ac – 8192 entries (0x2000)

// AudioManager class (partial)
class AudioManager {
public:
    // Offsets relative to this:
    // +0x08: uint32_t flags
    // +0x0C: uint32_t currentSoundId
    // +0x54: void* currentSoundData

    uint32_t flags;            // +0x08
    uint32_t currentSoundId;   // +0x0C
    void* currentSoundData;    // +0x54

    int32_t activateSound(uint32_t soundId);
};

int32_t AudioManager::activateSound(uint32_t soundId) {
    // Sound ID of 0 is invalid.
    if (soundId == 0)
        return 0;

    // Look up the hash bucket.
    SoundHashNode* node = g_soundHashTable[soundId & 0x1FFF];
    if (node == nullptr)
        return 0;

    // Walk the chain to find the exact sound ID.
    while (node->id != soundId) {
        node = node->next;
        if (node == nullptr)
            return 0;
    }

    // Node found; check if it has valid data.
    void* dataPtr = node->dataPtr;
    if (dataPtr != nullptr) {
        // Stop the currently active sound (pass its ID).
        stopSound(this->currentSoundId);
        updateAudioState();

        // Mark the manager as active and store the new sound.
        this->flags |= 0x80;
        this->currentSoundId = soundId;
        this->currentSoundData = dataPtr;
    }
    return reinterpret_cast<int32_t>(dataPtr);
}