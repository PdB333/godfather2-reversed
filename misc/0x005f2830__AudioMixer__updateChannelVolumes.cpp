// FUNC_NAME: AudioMixer::updateChannelVolumes

// Address: 0x005f2830
// Purpose: Updates audio channel volumes and panning for a stereo mixer, alternating between left/right channels

#include <cstdint>

// Forward declarations of helper functions (not defined here)
extern void FUN_005f2680();
extern void FUN_005dbc10(int leftVol, int rightVol, double pan, double volumeScale, double masterFade);
extern int FUN_005f37b0();
extern void FUN_005f1400(int param);

// Constants (likely from global data)
extern float DAT_0112750c; // default pan value (e.g., 0.5f)
extern float DAT_00e44564; // max pan value (e.g., 1.0f)

// Forward declaration of AudioMixer class
class AudioMixer;

// Default audio configuration data (pointed to by AudioMixer::pDefaultConfig at +0x08)
struct DefaultAudioConfig {
    uint8_t unknown1[8];          // +0x00
    uint8_t flags;                // +0x08 (bit 1 = 0x02 -> use custom pan value)
    uint8_t unknown2[27];         // +0x09 to +0x23
    float customPan;              // +0x24 (custom pan value, used if flags bit 1 set)
};

// Individual audio channel data (pointed to by AudioMixer::channels array)
struct AudioChannel {
    uint32_t unknown1[2];         // +0x00
    uint8_t settingsFlags;        // +0x08 (bit 1 = 0x02 used? Actually checked as byte)
    uint8_t unknown2[3];          // +0x09
    uint32_t someId;              // +0x0c (set from context+4)
    uint16_t channelFlags;        // +0x10 (bit 0x100 = active/muted flag)
    uint8_t unknown3[10];         // +0x12 to +0x1b
    uint8_t volume;               // +0x1c (byte, scaled by input)
    uint8_t dirty;                // +0x1d (set to 1 when channel flag cleared)
};

// Audio mixer manager
class AudioMixer {
public:
    uint8_t unknown1[8];                     // +0x00
    DefaultAudioConfig* pDefaultConfig;      // +0x08
    AudioChannel* channels[];                // +0x0c (array of pointers, size at channelCount)
    // ... layout continues ...
    float masterFade;                        // +0x54 (used in volume calculation)
    uint8_t unknown2[23];                    // +0x58 to +0x6e (includes some flags)
    uint8_t mixerFlags;                      // +0x6c (bit 2 = 0x04 used)
    uint8_t channelCount;                    // +0x6f (number of entries in channels array)

    // Main entry point
    int updateChannelVolumes(void* pContext, float* volumeScale);
};

int AudioMixer::updateChannelVolumes(void* pContext, float* volumeScale) {
    // Validate inputs
    if (pContext == nullptr || this == nullptr || this->pDefaultConfig == nullptr) {
        return 0;
    }

    // Determine default pan value
    float panBase = DAT_0112750c;
    if (this->pDefaultConfig->flags & 0x02) {
        panBase = this->pDefaultConfig->customPan;
    }

    uint32_t count = this->channelCount; // number of slots
    AudioChannel** ppChannel = this->channels; // pointer to first slot

    bool toggle = false;
    const float maxPan = DAT_00e44564; // usually 1.0f

    for (uint32_t i = 0; i < count; i++) {
        AudioChannel* pChannel = ppChannel[i];
        if (pChannel == nullptr) continue;

        // Scale channel volume by input scale factor
        short scaledVolume = static_cast<short>(static_cast<float>(pChannel->volume) * (*volumeScale));

        // Acquire some lock/semaphore
        FUN_005f2680();

        float pan;
        if (toggle) {
            pan = panBase;
            // If mixer flag 0x04 set and channel has 0x100 flag, clear it and mark dirty
            if ((this->mixerFlags & 0x04) && (pChannel->channelFlags & 0x100)) {
                pChannel->channelFlags &= ~0x100;
                pChannel->dirty = 1;
            }
        } else {
            pan = maxPan - panBase;
            // If mixer flag 0x04 is NOT set and channel has 0x100 flag, clear it and mark dirty
            if (!(this->mixerFlags & 0x04) && (pChannel->channelFlags & 0x100)) {
                pChannel->channelFlags &= ~0x100;
                pChannel->dirty = 1;
            }
        }

        // Apply volume, pan, scale, and master fade to the channel
        FUN_005dbc10(
            static_cast<int>(scaledVolume),  // left volume (same as right in this call)
            static_cast<int>(scaledVolume),  // right volume
            static_cast<double>(pan),        // pan position
            static_cast<double>(*volumeScale),  // overall scale
            static_cast<double>(this->masterFade) // master fade
        );

        // Store context-related ID
        pChannel->someId = *reinterpret_cast<int*>(static_cast<char*>(pContext) + 4);

        // Finalize update and release lock
        int result = FUN_005f37b0();
        FUN_005f1400(result);

        // Toggle for next channel (alternates left/right assignment)
        toggle = !toggle;
    }

    return 1;
}