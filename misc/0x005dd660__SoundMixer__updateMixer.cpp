// FUNC_NAME: SoundMixer::updateMixer
// Function at 0x005dd660 - Updates audio mixer parameters from layers and global settings
// Object layout (offsets from this):
// +0x0c: array of 5 Layer structures (each 0x68 bytes)
// +0x38: pointer into first layer (offset 0x2c within layer)
// +0x214: current state flag (-1 = default)
// +0x240: base volume multiplier
// +0x244: default volume
// +0x254: default sample rate
// +0x27c: volume scale factor
// +0x284: left volume (output)
// +0x288: right volume (output)
// +0x28c: left volume (final)
// +0x290: right volume (final)
// +0x294: sample rate (output, capped at 96000)
// +0x298: flag (0 = use multipliers, 1 = zero left volume)
// +0x29c: additional volume multiplier
// +0x700: random layer index (written from global table)

#include <cstdint>

// Forward declarations
bool FUN_005e73f0(uint32_t* outValue, int param); // Random/hash generator
bool FUN_005dd340(); // Check if layer processing is active

// Layer structure (0x68 bytes)
struct MixerLayer {
    float activeFlag;           // +0x00: -NAN if disabled
    char unknown1[0x14];        // +0x04 to +0x13
    char useSeparatePan;        // +0x14: if 0, apply to both L/R; if non-zero, separate
    char flag1;                 // +0x15
    char flag2;                 // +0x16
    char flag3;                 // +0x17
    char unknown2[0x14];        // +0x18 to +0x2b
    float volumeL;              // +0x2c
    float volumeR;              // +0x30
    char unknown3[0x10];        // +0x34 to +0x3f
    float sampleRateMod;        // +0x40
    // rest 0x28 bytes
};

// Global data
extern uint32_t DAT_01223504; // Pointer to global config table
extern float DAT_00e2e780;    // Default left volume
extern float DAT_00e2b1a4;    // Default right volume

uint32_t SoundMixer::updateMixer() {
    uint32_t local_4 = 0;
    char cVar1;
    int iVar2;
    float* pfVar3;
    float fVar4 = 0.0f;

    // Get a random/hash value and use it to select a layer index from global table
    cVar1 = FUN_005e73f0(&local_4, 0);
    if (cVar1 && ((local_4 ^ 0xad103100) < (uint32_t)(*(uint8_t*)(DAT_01223504 + 0x1c)))) {
        // Write to +0x700: index into layer table at DAT_01223504+4, offset 0x68
        *(uint32_t*)(this + 0x700) = *(uint32_t*)(*(int*)(DAT_01223504 + 4 + ((local_4 ^ 0xad103100) & 0xff) * 4) + 0x68);
    }

    // Determine base volumes based on state
    if (*(int*)(this + 0x214) == -1) {
        // Default state: use global defaults
        *(float*)(this + 0x284) = DAT_00e2e780;
        *(float*)(this + 0x288) = DAT_00e2b1a4;
    } else {
        // Active state: check layer processing
        FUN_005dd340();
        if (*(char*)(this + 0x298) == '\0') {
            // Normal mode: compute left volume from multipliers
            *(float*)(this + 0x288) = *(float*)(this + 0x244);
            *(float*)(this + 0x284) = *(float*)(this + 0x29c) * *(float*)(this + 0x27c) * *(float*)(this + 0x240);
        } else {
            // Special mode: zero left volume, right from default
            *(float*)(this + 0x284) = fVar4;
            *(float*)(this + 0x288) = *(float*)(this + 0x244);
        }
    }

    // Copy initial volumes to final outputs
    *(float*)(this + 0x28c) = *(float*)(this + 0x284);
    *(float*)(this + 0x294) = *(float*)(this + 0x254);
    *(float*)(this + 0x290) = *(float*)(this + 0x288);

    // Process each of the 5 layers
    pfVar3 = (float*)(this + 0x38); // Points to offset 0x2c within first layer
    iVar2 = 5;
    do {
        MixerLayer* layer = (MixerLayer*)((uint8_t*)pfVar3 - 0x2c); // Recover layer start
        if (layer->activeFlag != -NAN) {
            cVar1 = FUN_005dd340();
            if (cVar1) {
                if (layer->useSeparatePan == '\0') {
                    // Apply volume multipliers to both channels
                    *(float*)(this + 0x284) = layer->volumeL * *(float*)(this + 0x284);
                    *(float*)(this + 0x28c) = *(float*)(this + 0x28c) * layer->volumeL;
                    *(float*)(this + 0x288) = *(float*)(this + 0x288) * layer->volumeR;
                    *(float*)(this + 0x290) = *(float*)(this + 0x290) * layer->volumeR;
                } else {
                    // Separate pan: only modify final volumes and sample rate
                    *(float*)(this + 0x28c) = *(float*)(this + 0x28c) * layer->volumeL;
                    *(float*)(this + 0x290) = layer->volumeR * *(float*)(this + 0x290);
                    *(float*)(this + 0x294) = layer->sampleRateMod;
                }
                // Check flags for special behaviors
                if (layer->flag3 != '\0') {
                    if (layer->flag2 == '\0') {
                        if (layer->flag1 != '\0') {
                            // Zero right volume
                            *(float*)(this + 0x288) = fVar4;
                        }
                    } else {
                        // Disable this layer by setting activeFlag to -NAN
                        layer->activeFlag = -NAN;
                    }
                }
            }
        }
        pfVar3 += 0x1a; // Move to next layer (0x68 bytes)
        iVar2--;
    } while (iVar2 != 0);

    // Clamp volumes to zero if negative
    if (*(float*)(this + 0x284) <= fVar4 && fVar4 != *(float*)(this + 0x284)) {
        *(float*)(this + 0x284) = fVar4;
    }
    if (*(float*)(this + 0x288) <= fVar4 && fVar4 != *(float*)(this + 0x288)) {
        *(float*)(this + 0x288) = fVar4;
    }
    if (*(float*)(this + 0x28c) <= fVar4 && fVar4 != *(float*)(this + 0x28c)) {
        *(float*)(this + 0x28c) = fVar4;
    }
    if (*(float*)(this + 0x290) <= fVar4 && fVar4 != *(float*)(this + 0x290)) {
        *(float*)(this + 0x290) = fVar4;
    }

    // Cap sample rate at 96000
    if (96000 < *(uint32_t*)(this + 0x294)) {
        *(uint32_t*)(this + 0x294) = 96000;
    }

    return 0x17701; // Success code (96001)
}