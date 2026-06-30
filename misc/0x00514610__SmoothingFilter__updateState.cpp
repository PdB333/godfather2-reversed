// FUNC_NAME: SmoothingFilter::updateState
// Address: 0x00514610
// This function processes a 21-float input buffer and updates internal smoothing/envelope state.
// Input is a float* passed in EAX (16-byte aligned?).
// The function applies exponential smoothing (with factor DAT_00e2b1a4), min/max accumulation, and clamping.
// If input[0x14] has bit 0x10000000 set, state is reset.

#include <cstdint>
#include <xmmintrin.h> // SSE

// Global constants (inferred from known addresses)
static constexpr float kLeakFactor = 0.0f; // Actually from DAT_00e2b1a4, unknown so leave comment
static constexpr float kResetMinClamp = 0.0f; // from DAT_00e2eb58, unknown
// These would be defined elsewhere in the binary; we use placeholder values.

//------------------------------------------------------------------------------
// Static smoothing state (addresses 0x012191e0 - 0x01219230)
//------------------------------------------------------------------------------
static struct SmoothingState {
    // Accumulated leaky buffer (8 floats)
    float leakyBuffer[8];    // offset +0x00: _DAT_012191e0.._012191fc

    // Min-accumulated vector (4 floats, SSE)
    __m128 minAccum;         // offset +0x20: _DAT_01219200

    // Max-accumulated vector (4 floats, SSE)
    __m128 maxAccum;         // offset +0x30: _DAT_01219210

    // Clamp bounds
    float clampLo[2];        // offset +0x40: DAT_01219220, DAT_01219224 (lower/upper for first two?)
    float clampHi[2];        // offset +0x48: DAT_01219228, DAT_0121922c (lower/upper for next two?)

    // Flags
    uint32_t flags;          // offset +0x50: DAT_01219230

    // Additional reset state
    float resetMin;          // offset +0x24: DAT_01219204 (initial min value for minAccum)
    float resetMax;          // offset +0x28: DAT_01219208 (initial max value for minAccum? actually used in reset)
    uint32_t resetDummy;     // offset +0x2c: _DAT_0121920c

    SmoothingState() {
        // Initialization would be elsewhere; we just declare for reconstruction.
    }
} g_smoothingState; // Actually the globals are at fixed addresses, we reference them directly.

// Helper constants from the binary (these are likely float constants at known addresses)
#define DAT_00e2b1a4 (*(const float*)0x00e2b1a4)      // scaling/leak factor
#define DAT_00e2da50 (*(const float*)0x00e2da50)      // baseline for elements 8-11
#define DAT_00e2da54 (*(const float*)0x00e2da54)
#define DAT_00e2da58 (*(const float*)0x00e2da58)
#define DAT_00e2da5c (*(const float*)0x00e2da5c)
#define DAT_00e2eb58 (*(const float*)0x00e2eb58)      // default upper clamp value

// Direct memory-mapped globals for simplicity
static float& s_leaky0  = *(float*)0x012191e0;
static float& s_leaky1  = *(float*)0x012191e4;
static float& s_leaky2  = *(float*)0x012191e8;
static float& s_leaky3  = *(float*)0x012191ec;
static float& s_leaky4  = *(float*)0x012191f0;
static float& s_leaky5  = *(float*)0x012191f4;
static float& s_leaky6  = *(float*)0x012191f8;
static float& s_leaky7  = *(float*)0x012191fc;

static __m128& s_minAccum  = *(__m128*)0x01219200;
static __m128& s_maxAccum  = *(__m128*)0x01219210;

static float& s_clampMin0 = *(float*)0x01219220; // lower clamp for input[16]
static float& s_clampMin1 = *(float*)0x01219224; // lower clamp for input[17]? Actually acts as upper? See logic
static float& s_clampMax0 = *(float*)0x01219228; // upper clamp for input[18]? Actually logic: if s_clampMax0 < input[18] then use s_clampMax0 (i.e., min clamp)
static float& s_clampMax1 = *(float*)0x0121922c; // upper clamp for input[19]? Actually lower clamp for this? See code: if input[19] < s_clampMax1 then use s_clampMax1 (lower clamp)

static uint32_t& s_flags  = *(uint32_t*)0x01219230;

// Additional reset-related globals (used only in reset)
static float& s_resetMinAccumVal = *(float*)0x01219204; // initial min value (set to DAT_00e2b1a4)
static float& s_resetMaxAccumVal = *(float*)0x01219208; // initial max value (set to DAT_00e2b1a4)
static uint32_t& s_resetDummy    = *(uint32_t*)0x0121920c;

//------------------------------------------------------------------------------
// Main update function
//------------------------------------------------------------------------------
void SmoothingFilter_updateState(float* input) // input[21] (EAX)
{
    // 1. Leaky integration of first 8 values (exponential smoothing)
    s_leaky0 = DAT_00e2b1a4 * input[0] + s_leaky0;
    s_leaky1 = DAT_00e2b1a4 * input[1] + s_leaky1;
    s_leaky2 = DAT_00e2b1a4 * input[2] + s_leaky2;
    s_leaky3 = DAT_00e2b1a4 * input[3] + s_leaky3;
    s_leaky4 = DAT_00e2b1a4 * input[4] + s_leaky4;
    s_leaky5 = DAT_00e2b1a4 * input[5] + s_leaky5;
    s_leaky6 = DAT_00e2b1a4 * input[6] + s_leaky6;
    s_leaky7 = DAT_00e2b1a4 * input[7] + s_leaky7;

    // 2. Min accumulation of elements 8..11 (with centering around baseline)
    // Compute centered values: (input - baseline) * leak + baseline
    __m128 centered;
    centered.m128_f32[0] = (input[8]  - DAT_00e2da50) * DAT_00e2b1a4 + DAT_00e2da50;
    centered.m128_f32[1] = (input[9]  - DAT_00e2da54) * DAT_00e2b1a4 + DAT_00e2da54;
    centered.m128_f32[2] = (input[10] - DAT_00e2da58) * DAT_00e2b1a4 + DAT_00e2da58;
    centered.m128_f32[3] = (input[11] - DAT_00e2da5c) * DAT_00e2b1a4 + DAT_00e2da5c;

    // Update min accumulator: s_minAccum = min(s_minAccum, centered)
    s_minAccum = _mm_min_ps(s_minAccum, centered);

    // 3. Max accumulation of elements 12..15 (direct scaling, no baseline)
    __m128 scaled;
    scaled.m128_f32[0] = input[12] * DAT_00e2b1a4;
    scaled.m128_f32[1] = input[13] * DAT_00e2b1a4;
    scaled.m128_f32[2] = input[14] * DAT_00e2b1a4;
    scaled.m128_f32[3] = input[15] * DAT_00e2b1a4;

    // Update max accumulator: s_maxAccum = max(s_maxAccum, scaled)
    s_maxAccum = _mm_max_ps(s_maxAccum, scaled);

    // 4. Clamp individual elements 16..19 against previous bounds
    // Element 16: lower clamp (max with lower bound)
    float temp16 = input[16];
    if (input[16] < s_clampMin0) {
        temp16 = s_clampMin0;
    }
    // Element 19: lower clamp (max with lower bound)
    float temp19 = input[19];
    if (input[19] < s_clampMax1) {
        temp19 = s_clampMax1;
    }
    // Element 17: upper clamp (min with upper bound)
    float temp17 = input[17];
    if (s_clampMin1 < input[17]) {
        temp17 = s_clampMin1;
    }
    // Element 18: upper clamp (min with upper bound)
    float temp18 = input[18];
    if (s_clampMax0 < input[18]) {
        temp18 = s_clampMax0;
    }

    // Update bound state
    s_clampMin0 = temp16;
    s_clampMin1 = temp17;
    s_clampMax0 = temp18;
    s_clampMax1 = temp19;

    // 5. Accumulate flags from input[20] (bitmask)
    s_flags = s_flags | (uint32_t)input[20];

    // 6. If reset flag (bit 28) is set, clear all state
    if ((s_flags & 0x10000000) != 0) {
        // Reset leaky buffer to zero
        s_leaky0 = 0.0f;
        s_leaky1 = 0.0f;
        s_leaky2 = 0.0f;
        s_leaky3 = 0.0f;
        s_leaky4 = 0.0f;
        s_leaky5 = 0.0f;
        s_leaky6 = 0.0f;
        s_leaky7 = 0.0f;

        // Reset max accumulator to zero (all components)
        s_maxAccum = _mm_setzero_ps();

        // Reset clamp bounds
        s_clampMin0 = 0.0f;
        s_clampMax1 = 0.0f;

        // Reset min accumulator to initial values (DAT_00e2b1a4)
        s_resetMinAccumVal = DAT_00e2b1a4; // This is the value for the first component of minAccum? Actually minAccum is reset by setting _DAT_01219204, _DAT_01219200, _DAT_01219208
        s_minAccum = _mm_set1_ps(DAT_00e2b1a4); // Set all four components to leak factor
        s_resetDummy = 0; // ??? Possibly padding

        // Reset upper clamp bounds to DAT_00e2eb58
        s_clampMin1 = DAT_00e2eb58;
        s_clampMax0 = DAT_00e2eb58;

        // Keep only the reset flag
        s_flags = 0x10000000;
    }
}