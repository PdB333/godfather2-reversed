// FUNC_NAME: VarianceProvider::getRandomInRange

// Reconstructed from address 0x007159b0
// Computes a random value within a range defined by per-index base and a multiplier.
// The class holds a pointer to a VarianceData structure at offset +0x8.
// VarianceData layout:
//   +0x68: float rangeMultiplier
//   +0xb0: float baseValues[]  (indexed by param_2)

// External globals (likely scaling factors for rand() to [0,1] range)
extern float g_randScale1;   // DAT_00e44590
extern float g_randScale2;   // DAT_00d5eee4
extern float g_defaultReturn; // DAT_00d5c458 (fallback when mData is null)

class VarianceProvider {
public:
    struct VarianceData {
        // +0x68
        float rangeMultiplier;
        // +0xb0
        float baseValues[1]; // actual size unknown, accessed by index
    };

    // +0x0: vtable (implicit)
    // +0x4: probably another member
    // +0x8: pointer to VarianceData
    VarianceData* mData;

    // Returns a random value in [base - (multiplier*base), base + (multiplier*base)]
    // where base = mData->baseValues[index]
    float getRandomInRange(int index) const {
        if (mData) {
            float base = mData->baseValues[index];                 // from +0xb0
            float range = mData->rangeMultiplier * base;           // from +0x68
            int randInt = rand();
            // offset = randInt * g_randScale1 * range * g_randScale2
            // Intended to produce a uniform random offset in [-range, +range]
            float offset = (float)randInt * g_randScale1 * range * g_randScale2;
            return base - range + offset;
        }
        return g_defaultReturn;
    }
};