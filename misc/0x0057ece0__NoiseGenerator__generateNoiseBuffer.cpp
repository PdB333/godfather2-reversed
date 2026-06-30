// FUNC_NAME: NoiseGenerator::generateNoiseBuffer
// Address: 0x0057ece0
// Reconstructed C++ for noise generation function.
// Uses bitmask to check if a specific noise channel is active,
// then updates internal RNG state (NoiseState) and fills an 8-float output buffer.
// The number of state updates per active channel depends on a config value (low/high count).
// The final output is filled with zeros and a constant (likely 0.0f).

#include <cstdint>

// External noise RNG functions
extern void NoiseStateUpdate(NoiseState* state);           // FUN_0057d3a0: updates state
extern float NoiseStep(NoiseState* state, float input);   // FUN_0057dc70: returns next value

// Noise state structure (12 bytes)
struct NoiseState {
    uint32_t s0; // +0x00
    uint32_t s1; // +0x04
    uint32_t s2; // +0x08
};

// Configuration for noise generation
struct NoiseConfig {
    uint8_t noiseType;     // +0x04 (compared to 10)
    uint8_t _pad1[0x1C];  // padding to reach +0x20
    int32_t lowCount;      // +0x20 (used if noiseType < 10)
    float   lowValue;      // +0x24
    int32_t highCount;     // +0x28 (used if noiseType >= 10)
    float   highValue;     // +0x2C
};

// Main class
class NoiseGenerator {
public:
    float*     outputBuffer; // +0x00
    int32_t    _unknown04;   // +0x04 (not used in this function)
    NoiseConfig* config;     // +0x08
    int32_t*   bitmask;      // +0x0C (array of ints for bit testing)
    float      initialValue; // +0x10
    int32_t    channelIndex; // +0x14 (bit index)

    // Method at 0x0057ece0
    int32_t generateNoiseBuffer();
};

int32_t NoiseGenerator::generateNoiseBuffer() {
    int32_t* bitmaskPtr = bitmask;
    int32_t index = channelIndex;
    // Check if the bit for channelIndex is set in the bitmask
    if ((bitmaskPtr[index >> 5] & (1 << (index & 0x1F))) != 0) {
        NoiseState state;
        NoiseConfig* cfg = config;
        int32_t count;

        // Initialize state based on config type
        if ((cfg->noiseType & 0xFF) < 10) {
            state.s0 = *(uint32_t*)(cfg->lowValue); // Actually lowValue is float, but stored as int
            count = cfg->lowCount;
        } else {
            state.s0 = *(uint32_t*)(cfg->highValue);
            count = cfg->highCount;
        }
        state.s1 = 0;
        state.s2 = 0;

        // Update state multiple times for each active bit up to channelIndex
        // Count can be negative (7 calls) or non-negative (10 calls)
        if (count < 0) {
            for (int32_t i = 0; i < index; i++) {
                if ((bitmaskPtr[i >> 5] & (1 << (i & 0x1F))) != 0) {
                    NoiseStateUpdate(&state);
                    NoiseStateUpdate(&state);
                    NoiseStateUpdate(&state);
                    NoiseStateUpdate(&state);
                    NoiseStateUpdate(&state);
                    NoiseStateUpdate(&state);
                    NoiseStateUpdate(&state); // 7 times
                }
            }
        } else {
            for (int32_t i = 0; i < index; i++) {
                if ((bitmaskPtr[i >> 5] & (1 << (i & 0x1F))) != 0) {
                    NoiseStateUpdate(&state);
                    NoiseStateUpdate(&state);
                    NoiseStateUpdate(&state);
                    NoiseStateUpdate(&state);
                    NoiseStateUpdate(&state);
                    NoiseStateUpdate(&state);
                    NoiseStateUpdate(&state);
                    NoiseStateUpdate(&state);
                    NoiseStateUpdate(&state);
                    NoiseStateUpdate(&state); // 10 times
                }
            }
        }

        // Generate 8 output values (decompiled shows zeros, but likely intended to fill from sequence)
        float val = (float)initialValue;
        float* out = outputBuffer;
        const float constVal = 0.0f; // Replaces DAT_00e2b1a4

        out[0] = constVal;
        val = NoiseStep(&state, val);
        out[1] = constVal;
        val = NoiseStep(&state, val);
        out[2] = constVal;
        val = NoiseStep(&state, val);
        out[3] = constVal;
        val = NoiseStep(&state, val);
        out[4] = constVal;
        val = NoiseStep(&state, val);
        out[5] = constVal;
        val = NoiseStep(&state, val); // Last call result not stored in decompiled
        out[7] = constVal;
        out[6] = constVal;

        return 1;
    }

    // If bit not active, clear output and return
    float* out = outputBuffer;
    out[0] = 0.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
    out[3] = 0.0f;
    out[4] = 0.0f;
    out[5] = 0.0f;
    out[6] = 0.0f;
    out[7] = 0.0f;
    return 1;
}