// FUNC_NAME: packScaledFloatVec3ToUint
// Function at 0x00522b00 converts three floats (clamped, scaled, offset) to a packed 24-bit integer.
// Uses SSE minps/maxps for clamping to [vectorMin, vectorMax] then scales with scaleFactor and adds addOffset,
// rounds to nearest integer, and packs into uint32 (byte0: first float, byte1: second float, byte2: third float).

#include <xmmintrin.h>  // SSE intrinsics

// Global constants (from data at 0x00e38310, 0x00e38320, 0x00e38330, etc.)
// Assuming they are __m128 constants.
extern const __m128 g_clampMin;    // _DAT_00e38310
extern const __m128 g_clampMax;    // _DAT_00e38320
extern const float g_scaleAndAdd;  // _DAT_00e38330 (used for first component)
// For second and third components, there are likely separate scale+add at 0x00e38334 and 0x00e38338
extern const float g_scaleAndAdd2; // _UNK_00e38334
extern const float g_scaleAndAdd3; // _UNK_00e38338

// Note: The constants may be identical or different. The decompile shows _DAT_00e38330 used twice for first component
// (multiply and add), and _UNK_00e38334 and _UNK_00e38338 for second and third. We treat them as separate.

uint32_t packScaledFloatVec3ToUint(const float* inVec) {
    // Load input 4 floats (we only use first three)
    __m128 v = _mm_loadu_ps(inVec);

    // Clamp to [g_clampMin, g_clampMax]
    __m128 clamped = _mm_min_ps(v, g_clampMax);
    clamped = _mm_max_ps(clamped, g_clampMin);

    // Extract components
    float f0 = _mm_cvtss_f32(clamped); // first
    // For second and third, use shuffle
    __m128 tmp1 = _mm_shuffle_ps(clamped, clamped, _MM_SHUFFLE(1,1,1,1));
    float f1 = _mm_cvtss_f32(tmp1);
    __m128 tmp2 = _mm_shuffle_ps(clamped, clamped, _MM_SHUFFLE(2,2,2,2));
    float f2 = _mm_cvtss_f32(tmp2);

    // Scale and add for each component
    float s0 = f0 * g_scaleAndAdd + g_scaleAndAdd; // same constant used twice (maybe scale and bias)
    float s1 = f1 * g_scaleAndAdd2 + g_scaleAndAdd2;
    float s2 = f2 * g_scaleAndAdd3 + g_scaleAndAdd3;

    // Round to nearest integer
    int i0 = (int)(s0 + 0.5f);  // assume floor+0.5 for round to nearest
    int i1 = (int)(s1 + 0.5f);
    int i2 = (int)(s2 + 0.5f);

    // Clamp to byte range (0-255) – implied by rounding and scaling?
    // Ghidra decompile shows ROUND (which is floor? Actually ROUND with longlong, likely _mm_cvtss_si32 with rounding mode)
    // We'll use _mm_cvtss_si32 with default rounding (round to nearest even). Use (int)(x + 0.5f) as approximation.
    // But to match exactly, we could use _mm_cvtss_si32 (round to nearest even).
    // However, Ghidra shows ROUND which might be _mm_cvtss_si32. We'll use that.
    // Actually the decompile shows (longlong)ROUND(...). That's likely SSE intrinsic _mm_cvtss_si32.
    // We'll compute with SSE for exactness.

    // Re-do with SSE to match exactly:
    __m128 scaled = _mm_set_ps(0.0f, s2, s1, s0); // order: w=0, z=s2, y=s1, x=s0
    __m128i rounded = _mm_cvtps_epi32(scaled); // round to nearest even

    // Extract bytes (low 8 bits of each component)
    int r0 = _mm_extract_epi16(rounded, 0) & 0xFF;  // lower 16 bits of x, we take low byte
    int r1 = _mm_extract_epi16(rounded, 1) & 0xFF;  // lower 16 bits of y
    int r2 = _mm_extract_epi16(rounded, 2) & 0xFF;  // lower 16 bits of z

    // Pack into uint: byte0 (lowest) = r0, byte1 = r1, byte2 = r2, byte3 = 0
    return (uint32_t)( (r2 << 16) | (r1 << 8) | r0 );
}