// FUNC_NAME: AudioEffect::calculateCoefficients
// Function at 0x00614440: Computes audio effect coefficients (likely reverb or equalizer) from input parameters and per-channel state.
// Inputs: param1 (frequency/angle), param2 (gain), param3, param4 (frequency range endpoints)
// Outputs: outCoeffs[16] (filter coefficients), outGains[16] (optional gain scaling factors)

#include <cstdint>
#include <cmath>

// --- Global constants ---
// DAT_00e2cd54: Scale factor for param1
static const float g_scaleFactor = *reinterpret_cast<const float*>(0x00e2cd54);
// DAT_00e2b1a4: Constant A (base gain/coefficient)
static const float g_constantA = *reinterpret_cast<const float*>(0x00e2b1a4);
// DAT_00e44564: Constant B (offset/max value)
static const float g_constantB = *reinterpret_cast<const float*>(0x00e44564);

// --- Per-channel arrays ---
// DAT_011f6be8: Active channel index array (int per thread/channel)
static int* g_channelActive = reinterpret_cast<int*>(0x011f6be8);
// DAT_011f6bb8: Channel coefficient set A (float, stride 3 per channel)
static float* g_channelCoeffA = reinterpret_cast<float*>(0x011f6bb8);
// DAT_011f6bbc: Channel coefficient set B (float, stride 3 per channel)
static float* g_channelCoeffB = reinterpret_cast<float*>(0x011f6bbc);

// --------------------------------------------------------------------

// Thread-local storage access: FS:[0x2c] points to a per-thread struct,
// offset +0x34 holds a boolean flag (0 or 1) indicating which channel slot is active.
static inline uint32_t GetThreadChannelFlag() {
    // Placeholder: actual implementation would use __readfsdword(0x2c) and dereference twice.
    // Assuming return value is 0 or 1.
    return 0; // stubbed
}

// The two functions called with a double on the FP stack are assumed to be sin and cos.
// If not, replace with the actual math functions.

void __cdecl AudioEffect::calculateCoefficients(
    float param1,    // Frequency input (scaled by g_scaleFactor)
    float param2,    // Gain factor
    float param3,    // Lower frequency endpoint
    float param4,    // Upper frequency endpoint
    float* outCoeffs, // Output coefficient array (16 floats)
    float* outGains  // Optional output gain array (16 floats)
) {
    float scaledParam1 = param1 * g_scaleFactor;
    double dVar4 = static_cast<double>(scaledParam1);
    double sinVal = sin(dVar4);   // FUN_00b99e20: sine of scaled angle
    double dVar5 = static_cast<double>(scaledParam1);
    double cosVal = cos(dVar5);   // FUN_00b99fcb: cosine of scaled angle

    float fVar1 = g_constantA;
    uint32_t channelFlag = GetThreadChannelFlag(); // uVar2: 0 or 1

    float fVar3 = 0.0f;
    float fVar6 = g_constantA;

    if (g_channelActive[channelFlag] != -1) {
        int index = g_channelActive[channelFlag];
        // Each channel has 3 coefficients; we use the first of each set.
        fVar3 = g_channelCoeffA[index * 3];     // DAT_011f6bb8[index*3]
        fVar6 = g_channelCoeffB[index * 3];     // DAT_011f6bbc[index*3]
    }

    // Interpolation between fVar3 and fVar6 over the frequency range [param3, param4]
    fVar6 = (fVar6 * param4 - fVar3 * param3) * (g_constantA / (param4 - param3));

    // Ratio of sine/cosine (tan?), subtracted from constant B
    float fVar7 = g_constantB - static_cast<float>(sinVal / cosVal);

    // --- Fill output coefficient array (outCoeffs[0..15]) ---
    outCoeffs[10] = fVar6;                  // +0x28: interpolated coefficient
    outCoeffs[0]  = fVar7;                  // +0x00: offset/attenuation
    outCoeffs[1]  = 0.0f;
    outCoeffs[2]  = 0.0f;
    outCoeffs[3]  = 0.0f;
    outCoeffs[4]  = 0.0f;
    outCoeffs[5]  = static_cast<float>(sinVal / cosVal) * param2; // +0x14: modulated gain
    outCoeffs[6]  = 0.0f;
    outCoeffs[7]  = 0.0f;
    outCoeffs[8]  = 0.0f;
    outCoeffs[9]  = 0.0f;
    outCoeffs[11] = fVar1;                  // +0x2c: constant A
    outCoeffs[12] = 0.0f;
    outCoeffs[13] = 0.0f;
    outCoeffs[14] = fVar3 * param3 - fVar6 * param3; // +0x38: frequency-dependent offset
    outCoeffs[15] = 0.0f;

    // --- Optional gain scaling array (outGains[0..15]) ---
    if (outGains != nullptr) {
        outGains[1]  = 0.0f;
        outGains[2]  = 0.0f;
        outGains[3]  = 0.0f;
        outGains[4]  = 0.0f;
        outGains[0]  = g_constantA / fVar7;             // +0x00: gain for channel 0
        outGains[5]  = g_constantA / outCoeffs[5];      // +0x14: gain for channel 5
        outGains[6]  = 0.0f;
        outGains[7]  = 0.0f;
        outGains[8]  = 0.0f;
        outGains[9]  = 0.0f;
        outGains[10] = 0.0f;

        float fVar3b = outCoeffs[14];                  // reuse fVar3
        outGains[12] = 0.0f;
        outGains[13] = 0.0f;
        outGains[11] = g_constantA / fVar3b;           // +0x2c: gain for channel 11
        outGains[14] = g_constantA;                    // +0x38: constant gain
        outGains[15] = g_constantB - (outCoeffs[10] / outCoeffs[14]); // +0x3c: modulation
    }
}