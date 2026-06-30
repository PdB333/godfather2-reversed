// FUNC_NAME: audioResamplerGenerateKernel
// Address: 0x0061c8f0
// Generates a windowed resampling kernel for sample rate conversion.
// Computes a set of weights for input samples contributing to one output sample.
// Weights are normalized to sum to 1.0.

void audioResamplerGenerateKernel(
    int srcInteger,          // param_1: integer part of source sample index
    float srcFraction,       // float passed in XMM2 (missing from decompiled signature): fractional part of source sample index [0..1)
    float dstRatio,          // param_2: output/input sample rate ratio
    int dstLength,           // param_3: length of output buffer (used to clamp indices)
    float windowScale,       // param_4: reciprocal of half-window width (e.g., 1.0/halfWidth)
    int filterType,          // param_5: 0=nearest, 1=linear, 2=quadratic? 3=cubic? (see FUN_0061c7c0)
    int* outStart,           // param_6: [out] start index into input buffer
    int* outEnd,             // param_7: [out] end index (exclusive)
    float* outWeights        // param_8: [out] array of filter weights (size = outEnd - outStart)
)
{
    const float half = 0.5f;     // DAT_00e2cd54
    const float one  = 1.0f;     // DAT_00e2b1a4
    const float epsilon = 0.0f;  // DAT_00e44718 (likely zero)

    // Center position in output sample units: (srcInteger + 0.5) * dstRatio + srcFraction
    float center = ((float)srcInteger + half) * dstRatio;

    // Compute window bounds in output sample indices
    float startF = (center - srcFraction) + half;
    if (startF < 0.0f) startF = 0.0f;
    int startIdx = (int)startF;

    float endF = center + srcFraction + half;
    if ((float)dstLength < endF) endF = (float)dstLength;
    int endIdx = (int)endF;

    int count = endIdx - startIdx;
    float weightSum = 0.0f;

    int i = startIdx;
    float* weightPtr = outWeights;
    float currentHalf = half;
    float currentOne = one;

    do {
        if (endIdx <= i) {
            // Normalize weights
            if (weightSum != 0.0f) {
                currentOne = currentOne / weightSum;
            }

            // Apply normalization to all weights
            int idx = 0;
            if (count > 3) {
                float* p = outWeights + 2;  // start of third element (two behind)
                int loopCount = ((count - 4) >> 2) + 1;  // unroll 4x
                idx = loopCount * 4;
                do {
                    p[-2] = p[-2] * currentOne;
                    p[-1] = p[-1] * currentOne;
                    p[0]  = p[0]  * currentOne;
                    p[1]  = p[1]  * currentOne;
                    p += 4;
                    loopCount--;
                } while (loopCount != 0);
            }
            for (; idx < count; idx++) {
                outWeights[idx] = outWeights[idx] * currentOne;
            }

            *outStart = startIdx;
            *outEnd   = endIdx;
            return;
        }

        // Compute distance from current input sample to output position (in scaled units)
        float distance = (((float)i - center) + currentHalf) * windowScale;
        float weight = 0.0f;

        // Select filter kernel based on type
        if (filterType < 1) {
            // Nearest neighbor? (always zero, but later normalization might fix)
            weight = 0.0f;
        }
        else if (filterType < 3) {
            // Linear or triangular? Actually checks if distance < epsilon or half <= distance -> 0, else 1.
            // This is a box of width half (scale matters). Might be a simplified linear step?
            if ((distance < epsilon) || (currentHalf <= distance)) {
                weight = 0.0f;
            } else {
                weight = currentOne;
            }
            // Note: the original code sets fVar9 = currentOne in the else branch, then jumps to store.
        }
        else if (filterType == 3) {
            // Cubic interpolation (calls FUN_0061c7c0)
            // FUN_0061c7c0 modifies distance in place (likely returns cubic coefficient)
            FUN_0061c7c0(distance);
            weight = distance;
            // Re-read constants after call (they might be modified)
            currentHalf = half;
            currentOne = one;
        }
        // else: zero (default)

        *weightPtr = weight;
        i++;
        weightSum += weight;
        weightPtr++;
    } while (true);
}