// FUNC_NAME: Random::getRandomInt
// This function returns a pseudo-random integer in the range [0, param_1 - 1] using a precomputed float table.
// It uses a sequence counter (gRandCounter) that is masked to index into the table of floats.
// The table entries are presumably uniform in [0, 1).
// param_1: the exclusive upper bound (must be > 0 for valid results)

// Global state
extern uint32_t gRandCounter;        // DAT_012054b4 - monotonic counter
extern uint32_t gRandMask;           // DAT_010c2678 - mask applied to counter to get table index
extern float gRandTable[];           // DAT_010c2680 - array of floats (size = gRandMask + 1)
extern float gNegAdjust;             // DAT_00e44578 - large float adjustment for negative input (likely 4294967296.0f)

int32_t __fastcall Random_GetRandomInt(int32_t param_1)
{
    uint32_t index = gRandMask & gRandCounter;
    gRandCounter++;

    float fBase = static_cast<float>(param_1 - 1);
    if (param_1 - 1 < 0)
    {
        // If param_1 <= 0, adjust the base to avoid negative float rounding artifacts
        fBase += gNegAdjust;
    }

    // Generate random float from table, multiply by (param_1-1), round to nearest integer
    float randomFactor = gRandTable[index];
    float scaled = fBase * randomFactor;
    int32_t result = static_cast<int32_t>(lroundf(scaled)); // ROUND in decompiler = round to nearest, ties away? using lroundf

    return result;
}