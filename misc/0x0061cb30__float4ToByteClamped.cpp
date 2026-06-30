// FUNC_NAME: float4ToByteClamped
// Function address: 0x0061cb30
// Converts a 4‑element float vector (passed via EAX) to a 4‑byte array (out param)
// with scaling, offset, and clamping to [0, kClampMax]. Uses SSE intrinsics.

#include <xmmintrin.h>  // SSE intrinsics

// Global constants (addresses from Ghidra analysis)
extern float kClampMax;       // 0x00e44584 – upper clamp bound
extern float kOffset;         // 0x00e44724 – added after scaling
extern float kThresholdMask;  // 0x00e44680 – bitmask for conditional test
extern float kFallbackValue;  // 0x00e2b1a4 – fallback for fVar6
extern float kDivThreshold;   // 0x00e2e084 – threshold for conditional
extern float kDivide;         // 0x00e2b1a4 – numerator in scale factor

void __fastcall float4ToByteClamped(float* inVec, char* outBytes, float extraFloat)
{
    // Load input vector (4 floats)
    __m128 vec = _mm_load_ps(inVec);

    // Determine fVar6: either extraFloat or kFallbackValue based on bitwise test
    float fVar6 = extraFloat;
    if ((*reinterpret_cast<uint32_t*>(&extraFloat) & *reinterpret_cast<const uint32_t*>(&kThresholdMask)) <=
        *reinterpret_cast<const uint32_t*>(&kDivThreshold))
    {
        fVar6 = kFallbackValue;
    }

    // Compute scale factor: (kDivide / fVar6) * kClampMax
    float scale = (kDivide / fVar6) * kClampMax;

    // Scale all four elements
    __m128 scaled = _mm_mul_ps(vec, _mm_set1_ps(scale));

    // Overwrite first element with extraFloat * kClampMax (as per original code)
    float* temp = reinterpret_cast<float*>(&scaled);
    temp[0] = extraFloat * kClampMax;

    // Add offset to every element
    __m128 withOffset = _mm_add_ps(scaled, _mm_set1_ps(kOffset));

    // Clamp to [0, kClampMax]
    __m128 clamped = _mm_min_ps(withOffset, _mm_set1_ps(kClampMax));
    clamped = _mm_max_ps(clamped, _mm_setzero_ps());

    // Truncate floats to integers and store as bytes
    const float* result = reinterpret_cast<const float*>(&clamped);
    outBytes[0] = static_cast<char>(static_cast<int>(result[0]));
    outBytes[1] = static_cast<char>(static_cast<int>(result[1]));
    outBytes[2] = static_cast<char>(static_cast<int>(result[2]));
    outBytes[3] = static_cast<char>(static_cast<int>(result[3]));
}