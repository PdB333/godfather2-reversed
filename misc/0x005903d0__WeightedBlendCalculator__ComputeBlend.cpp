// FUNC_NAME: WeightedBlendCalculator::ComputeBlend
// Address: 0x005903d0
// Role: Computes a blended value from a weighted structure and an implicit float input (XMM0).
// Calls a random state refresh (FUN_00591160) twice before accessing weights.
// The data structure at +0x01 holds a quality level; if < 2, returns 1.0.
// Offset +0x04 is a pointer to a BlendWeights struct: float a (+0x00), b (+0x04), pad (+0x08), totalWeight (+0x0C).
// Returns a + max(b, inputValue) when totalWeight != 0, otherwise a + b + inputValue.

// Helper: likely updates internal random state
void RefreshRandomState(); // FUN_00591160

struct BlendWeights {
    float a;            // +0x00
    float b;            // +0x04
    float pad;          // +0x08 (unused)
    float totalWeight;  // +0x0C
};

struct WeightedBlendData {
    char _pad0;                 // +0x00
    char qualityLevel;          // +0x01
    // +0x02-0x03 alignment
    BlendWeights* pWeights;    // +0x04
};

// __thiscall: param_1 is this (unused), param_2 is pData
// float inputValue is passed in XMM0 register (in_XMM0_Da)
float __thiscall WeightedBlendCalculator::ComputeBlend(int unusedThis, WeightedBlendData* pData)
{
    float inputValue; // from XMM0 – not a standard parameter

    if (pData->qualityLevel < 2) {
        return 1.0f;
    }

    RefreshRandomState();
    BlendWeights* pWeights = pData->pWeights;
    RefreshRandomState();

    float bVal = pWeights->b;
    if (pWeights->totalWeight == 1.4013e-45f) { // effectively zero
        return pWeights->a + bVal + inputValue;
    }

    if (inputValue < bVal) {
        return pWeights->a + bVal;
    } else {
        return pWeights->a + inputValue;
    }
}