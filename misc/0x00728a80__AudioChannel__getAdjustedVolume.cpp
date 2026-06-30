// FUNC_NAME: AudioChannel::getAdjustedVolume

#include <cstdint>

// External global volume scaling factor (e.g., master volume)
extern float g_masterVolumeScale; // 0x00d5780c

// Forward declaration of a processing function that modifies volume based on fade data
void applyAudioProcessing(float* volume, void* fadeParams); // FUN_00729fd0

// Structure representing fade parameters (offset layout inferred)
struct FadeParams {
    uint32_t unknown_0x00; // +0x00
    uint32_t unknown_0x04; // +0x04
    uint32_t unknown_0x08; // +0x08
    float    fadeTime;     // +0x0c
    float    fadeDuration; // +0x10
};

class AudioChannel {
public:
    // Offsets in this class:
    // +0x5c: uint8_t flags (bit 0 = bUseFade)
    // +0x6c: float volumes[]  (per-channel base volumes)
    // +0x9c: uint32_t processingMode (0 = none, 0x48 = bypass)

    float getAdjustedVolume(int slotIndex, FadeParams* fadeParams) {
        // Read the base volume for the given slot
        float volume = this->volumes[slotIndex];

        if (fadeParams != nullptr) {
            // Apply DSP processing if mode is not 0 or 0x48 (bypass)
            uint32_t procMode = this->processingMode;
            if (procMode != 0 && procMode != 0x48) {
                applyAudioProcessing(&volume, fadeParams);
            }

            // Apply fade-out if the flag is set
            if (this->flags & 0x01) {
                float time = fadeParams->fadeTime;
                float duration = fadeParams->fadeDuration;

                // Clamp time to [0, duration]
                if (time > 0.0f) {
                    if (duration <= time) {
                        time = duration;
                    }
                } else {
                    time = 0.0f;
                }

                // Linear fade factor: 1.0 -> 0.0 over duration
                float fadeFactor = g_masterVolumeScale - (time / duration);
                volume = fadeFactor * volume;
            }
        }

        return volume;
    }

private:
    // Layout of member variables (offsets are speculative based on Ghidra analysis)
    uint8_t  flags;          // +0x5c
    uint8_t  padding[0x6c - 0x5c - 1]; // alignment
    float    volumes[];      // +0x6c (variable-length array)
    uint32_t processingMode; // +0x9c
};