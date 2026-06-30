// FUNC_NAME: SoundManager::updateChannel
// Address: 0x005ebbe0
// Role: Updates a single sound channel, processing event queue or looping playback depending on channel type.
// The channel index is passed in the low 16 bits of EAX (likely from caller's loop index).
// The class 'SoundManager' holds an array of SoundChannel structures starting at offset 0x5A0.
// Each SoundChannel is 0xF8 bytes and contains timing, event data, and state.

#include <cstdint>

// Forward declarations for called functions (assumed to be audio system helpers)
extern int __cdecl FUN_005e9d10(); // Might be AudioSystem::getSoundObject() or similar
extern void __cdecl FUN_00c9cbe0(void* audioSystem, void* soundObject, int param, double* outDouble); // PlaySound?
extern void __cdecl FUN_00c9eac0(); // AudioSystem::pushParams
extern void __cdecl FUN_00c9cd40(int param, double* volume); // SetVolume?
extern void __cdecl FUN_00c9eae0(); // AudioSystem::popParams
extern int __cdecl FUN_00c9eb20(); // GetCurrentPosition?
extern void __cdecl FUN_005efb60(); // ResetChannel?

// Global constant used to clamp volume
extern float DAT_00e2b1a4;

// Structure for a single sound channel element (0xF8 bytes)
struct SoundChannel {
    /* +0x00-0x1F: possibly other fields */
    /* +0x20 */ float    timeOffset;            // Start offset or blend
    /* +0x24 */ float    eventTimes[?];          // Array of pairs (time/duration?) each 8 bytes (2 floats)
    /*         actually used with iVar1*8, so at +0x24 + index*8 */
    /* +0xA4 */ float    loopThreshold;          // Threshold for looping type (if flag != 0)
    /* +0xA8 */ int32_t  eventCount;             // Number of events in the array
    /* +0xAC */ int32_t  currentEventIndex;      // Current index into event array
    /* +0xB0 */ double   lastTime;               // Last time the channel was triggered
    /* +0xB8 */ uint8_t  typeFlag;               // 0 = layered/event, non0 = looping
    /* +0xBC-0xDB: padding? */
    /* +0xDC */ int32_t  reserved1;
    /* +0xE0 */ int32_t  currentSoundHandle;     // Handle of currently playing sound
    /* +0xE4 */ int32_t  reserved2;
};

// The main class (this)
class SoundManager {
public:
    // Assumed offset 0x580: pointer to audio system with a double at +8 (current time)
    void* audioSystem; // at +0x580? Actually pointer stored at this+0x580

    // Array of SoundChannel elements starting at offset 0x5A0
    // SoundChannel channels[]; // at +0x5A0

    int updateChannel(uint16_t channelIndex);
};

int SoundManager::updateChannel(uint16_t channelIndex) {
    // Calculate pointer to the specific channel
    uint32_t elementOffset = channelIndex * 0xF8;
    SoundChannel* channel = reinterpret_cast<SoundChannel*>(
        reinterpret_cast<char*>(this) + 0x5A0 + elementOffset);

    // Get current time from the audio system
    void* audioSys = *reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 0x580);
    double currentTime = *reinterpret_cast<double*>(static_cast<char*>(audioSys) + 8);

    if (channel->typeFlag == 0) {
        // Layered/event-driven channel
        int32_t currentIdx = channel->currentEventIndex;
        int32_t maxIdx = channel->eventCount - 1;

        if (currentIdx < maxIdx) {
            double elapsed = currentTime - channel->lastTime;
            int32_t nextIdx = currentIdx + 1;

            // Check if it's time to play the next event
            if (channel->eventTimes[currentIdx] <= static_cast<float>(elapsed)) {
                // Get a sound object or resource
                int soundObject = FUN_005e9d10();
                if (soundObject != 0) {
                    double volumeParams; // local_20
                    // Play sound with given parameters
                    FUN_00c9cbe0(audioSys, *reinterpret_cast<void**>(soundObject + 0x10), 0, &volumeParams);

                    // Prepare volume/pan data
                    float volume = 0.0f; // local_10
                    float nextEventTime = channel->eventTimes[nextIdx]; // local_18 low part?
                    // Note: eventTimes array stores pairs: first float at +0x24+nextIdx*8
                    // Second float at +0x20? Actually in code: local_18 = *(undefined4 *)(iVar2 + 0x24 + iVar1 * 8);
                    // And fVar3 = *(float *)(iVar2 + 0x20 + iVar1 * 8);
                    // So at +0x20+nextIdx*8 is a float (maybe duration or end time)
                    float duration = *reinterpret_cast<float*>(reinterpret_cast<char*>(channel) + 0x20 + nextIdx * 8);

                    if (duration > 0.0f) {
                        volume = duration;
                        if (DAT_00e2b1a4 < duration) {
                            volume = DAT_00e2b1a4;
                        }
                    }

                    // Set volume (via some container)
                    volumeParams = currentTime; // local_20 = currentTime
                    // local_8 was 0, local_18 was nextEventTime, local_10=volume, local_20=currentTime
                    FUN_00c9eac0(); // push
                    FUN_00c9cd40(0, &volumeParams); // apply volume?
                    FUN_00c9eae0(); // pop

                    // Update channel state
                    channel->lastTime = *reinterpret_cast<double*>(&volumeParams); // probably currentTime stored
                    channel->currentEventIndex = nextIdx;
                    return 1;
                }
            }
        }
    } else {
        // Looping channel
        if (channel->currentSoundHandle == 0) {
            double elapsed = currentTime - channel->lastTime;
            if (static_cast<float>(elapsed) >= channel->loopThreshold) {
                int soundObject = FUN_005e9d10();
                if (soundObject != 0) {
                    FUN_00c9eac0(); // push
                    FUN_00c9cd40(1, 0); // set some parameter
                    int soundHandle = FUN_00c9eb20(); // get current sound handle (maybe start new sound)
                    channel->currentSoundHandle = soundHandle;
                    FUN_00c9eae0(); // pop
                    FUN_005efb60(); // reset channel?
                    channel->reserved1 = 0;
                    channel->currentSoundHandle = 0;
                    channel->reserved2 = 0;
                }
            }
        }
    }
    return 1; // Always returns 1 (success)
}