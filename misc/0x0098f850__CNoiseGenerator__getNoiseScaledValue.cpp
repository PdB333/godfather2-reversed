// FUNC_NAME: CNoiseGenerator::getNoiseScaledValue
// Function address: 0x0098f850
// Role: Computes a noise-scaled integer from a seed (this+0x48) by combining it with a global noise table and counter.
// See also: 0x0098f710 (base noise shape function)

#include <cmath>  // for lrintf

// Global noise engine state (set during render/update)
extern uint gNoiseMask;        // Typically 0xFF or mask for table size; DAT_010c2678
extern int  gNoiseCounter;     // Incremented per call; DAT_012054b4
extern float gNoiseTable[];    // Precomputed float array; &DAT_010c2680
extern float gNoiseFloatAdjust;// Constant added for negative seed conversion; DAT_00e44578

// Forward declaration of the underlying noise shape function
uint FUN_0098f710(int intParam, undefined4 param2);

// -------------------------------------------------------------------
// unsigned int __thiscall CNoiseGenerator::getNoiseScaledValue(int param2)
// -------------------------------------------------------------------
uint __thiscall CNoiseGenerator::getNoiseScaledValue(undefined4 param2)
{
    int seed = *(int*)(this + 0x48);  // +0x48: seed/time value driving the noise

    if (seed == 0) {
        // Note: Original code uses the value of EAX when seed==0, which is likely an
        // unused path (all callers guarantee non-zero seed). Defaulting to 0 for clarity.
        return 0;
    }

    // Compute index from the current counter
    uint index = gNoiseMask & gNoiseCounter;
    gNoiseCounter++;

    // Convert seed to float, with special handling for negative values
    float fSeed = static_cast<float>(seed);
    if (seed < 0) {
        fSeed += gNoiseFloatAdjust;  // Shifts negative values into a specific range
    }

    // Scale by the noise table and round to nearest integer
    int scaled = lrintf(fSeed * gNoiseTable[index]);

    // Pass the rounded value to the base noise shape function
    return FUN_0098f710(scaled, param2);
}