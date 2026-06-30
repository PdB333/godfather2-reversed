// FUNC_NAME: SoundManager::stopEvent

// Function at 0x006064b0: Stops sound events identified by eventId.
// Handles two global arrays: active sound IDs (20 slots) and channel pairs (5 pairs).
// Global pointer gSoundManager (DAT_01205750) provides virtual stop methods.
// Global flag gVoiceChannelStopped (DAT_01223538) is set when main channel (index 0) is stopped.

#include <cstddef>

// Forward declarations of called functions (likely free functions or static helpers)
extern void FreeSoundId();                     // FUN_00618d40 - originally no arguments, but likely should take eventId
extern int GetCurrentMixState();               // FUN_00609260 - returns some mix/animation state

// Constants
constexpr int MAX_ACTIVE_SOUND_IDS = 20;
constexpr int MAX_CHANNEL_PAIRS = 5;

// Global data (likely static members of SoundManager or external globals)
extern int gActiveSoundIds[MAX_ACTIVE_SOUND_IDS];         // DAT_011d912c
extern int gActiveChannelPairs[MAX_CHANNEL_PAIRS][2];     // DAT_011f38f0 (pair: [soundId, channel])
extern int gVoiceChannelStopped;                           // DAT_01223538

// Global singleton pointer to SoundManager
extern class SoundManager* gSoundManager;                // DAT_01205750

// Hypothetical SoundManager class with virtual methods matching vtable offsets
class SoundManager {
public:
    // vtable+0x94: Stop a specific channel (channel index, flag)
    virtual void StopChannel(int channel, int flag);

    // vtable+0x9c: Stop voice channel (used for index 4)
    virtual void StopVoiceChannel(int flag);
};

// The reconstructed function (likely a static method or free function)
void SoundManager_stopEvent(int eventId, int bStopFromActiveList) {
    if (eventId == 0)
        return;

    // If requested, remove from the active sound IDs list and free
    if (bStopFromActiveList != 0) {
        for (int i = 0; i < MAX_ACTIVE_SOUND_IDS; ++i) {
            if (gActiveSoundIds[i] == eventId) {
                FreeSoundId();               // clear the sound resource
                gActiveSoundIds[i] = 0;
            }
        }
    }

    // Always check the channel pairs array
    for (int i = 0; i < MAX_CHANNEL_PAIRS; ++i) {
        int soundId = gActiveChannelPairs[i][0];
        if (eventId == soundId) {
            int channelInfo = gActiveChannelPairs[i][1];
            // Clear the pair entry
            gActiveChannelPairs[i][0] = 0;
            gActiveChannelPairs[i][1] = 0;

            // Only call the virtual if the entry was previously valid (non-zero)
            if (soundId != 0 || channelInfo != 0) {
                if (i == 4) {
                    // Special channel index 4 (voice channel)
                    gSoundManager->StopVoiceChannel(0);
                } else if (i == 0) {
                    // Main channel (index 0): call with current mix state
                    int mixState = GetCurrentMixState();
                    gSoundManager->StopChannel(0, mixState);
                    gVoiceChannelStopped = 1;
                } else {
                    // Other channels: stop with default flag
                    gSoundManager->StopChannel(i, 0);
                }
            }
        }
    }
}