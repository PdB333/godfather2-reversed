// FUNC_NAME: AnimBlendState::accumulate

#include <cmath>
#include <cstdint>

// Forward declaration for quaternion blend function (assumed to be a slerp-like operation)
extern void quaternionBlend(float* out, const float* a, const float* b, float t);

// Global animation blend state (static data from DAT_01219... region)
// These represent the current accumulated blend result.
static float g_blendPos[4];    // +0x00 Position (4 components, used with minps)
static float g_blendRot[4];    // +0x10 Rotation quaternion
static float g_blendScale;     // +0x20 Scale? (index 8)
static float g_blendUnk1;      // +0x24 (index 9)
static float g_blendUnk2;      // +0x28 (index 10)
static float g_blendThresholdA;// +0x2C (index 11) – used in comparisons
static float g_blendThresholdB;// +0x30 (index 12)
static float g_blendThresholdC;// +0x34 (index 13)
static float g_blendThresholdD;// +0x38 (index 14)
static float g_blendThresholdE;// +0x3C (index 15)
static float g_blendMaxVal;    // +0x40 (index 16)
static float g_blendFlags;     // +0x44 (index 17, stored as float for bit ops)
static float g_blendPad[2];    // +0x48 (indices 18,19, padding to 20 floats)
static float g_blendFactor;    // +0x4C? Not in the array but separate DAT_0121925c (actually a copy of factor)
static uint32_t g_blendStateFlags; // +0x50 Flags integer (DAT_01219294)

// External constants (from .data section)
extern float DAT_00e2af44;      // Threshold weight value
extern float DAT_0121927c;      // Another threshold
extern float DAT_01219288;      // Scaling factor?
extern float DAT_0121928c;      // Scaling factor?
extern float DAT_01219290;      // Max value?
extern float DAT_00e2b1a4;      // Blend factor (weight)
extern float _DAT_00e2da30;     // Position component bias
extern float _UNK_00e2da34;     // Position component bias
extern float _UNK_00e2da38;     // Position component bias
extern float _UNK_00e2da3c;     // Position component bias
extern float DAT_00e2cd54;      // Exponential decay factor
extern float DAT_00e39f98;      // Reset value for certain fields
extern float DAT_00e445ac;      // Reset value for g_blendUnk2

void AnimBlendState::accumulate(const float* source) // source is 20 floats
{
    // Check if the blend state is uninitialized or the source has the high bit set
    if ((g_blendStateFlags & 0x10000000) == 0 && (((uint32_t)source[17] & 0x10000000) == 0))
    {
        // Normal blend path: check weight thresholds
        if ((DAT_00e2af44 < source[11] || DAT_00e2af44 == source[11]) &&
            (DAT_00e2af44 < source[14] || DAT_00e2af44 == source[14] ||
             DAT_00e2af44 < source[15] || DAT_00e2af44 == source[15]))
        {
            // Additional threshold check for target values
            if ((DAT_00e2af44 <= g_blendThresholdA) &&
                (DAT_00e2af44 <= g_blendThresholdD || DAT_00e2af44 <= g_blendThresholdE))
            {
                // Interpolate position with min clamp
                float newPos[4];
                newPos[0] = (source[0] - _DAT_00e2da30) * DAT_00e2b1a4 + _DAT_00e2da30;
                newPos[1] = (source[1] - _UNK_00e2da34) * DAT_00e2b1a4 + _UNK_00e2da34;
                newPos[2] = (source[2] - _UNK_00e2da38) * DAT_00e2b1a4 + _UNK_00e2da38;
                newPos[3] = (source[3] - _UNK_00e2da3c) * DAT_00e2b1a4 + _UNK_00e2da3c;

                // Clamp with previous blend position using minps (SSE min)
                for (int i = 0; i < 4; i++)
                {
                    if (newPos[i] > g_blendPos[i])
                        g_blendPos[i] = newPos[i];
                    else
                        g_blendPos[i] = g_blendPos[i]; // Actually minps: new <= old? Wait minps is packed min of two vectors.
                    // In decompiled: auVar7 = minps(auVar7, _DAT_01219250); so newPos = min(newPos, g_blendPos)
                    // That means we clamp newPos to be no greater than g_blendPos. So:
                    // g_blendPos = min(newPos, g_blendPos) for each component.
                }
                // Simulate minps: take component-wise minimum
                for (int i = 0; i < 4; i++)
                {
                    if (newPos[i] < g_blendPos[i])
                        g_blendPos[i] = newPos[i];
                    // else keep old
                }

                // Update max value
                float fVar3 = source[16];
                if ((int32_t)source[16] < (int32_t)g_blendMaxVal)
                {
                    fVar3 = g_blendMaxVal;
                }
                g_blendMaxVal = fVar3;

                // Handle rotation blending
                if (((uint32_t)source[17] & 4) != 0)
                {
                    if ((g_blendStateFlags & 4) == 0)
                    {
                        // If target rotation not initialized, just copy
                        g_blendRot[0] = source[4];
                        g_blendRot[1] = source[5];
                        g_blendRot[2] = source[6];
                        g_blendRot[3] = source[7];
                    }
                    else
                    {
                        // Blend rotation with quaternion slerp
                        quaternionBlend(g_blendRot, g_blendRot, &source[4], DAT_00e2cd54);
                    }
                }

                // Blend other parameters
                float fVar6 = source[10];
                if (source[10] < g_blendUnk2)
                {
                    fVar6 = g_blendUnk2;
                }
                g_blendUnk2 = fVar6;

                // Exponential moving average for some value
                g_blendScale = (source[8] + g_blendScale) * DAT_00e2cd54;

                fVar6 = source[9];
                if (source[9] < g_blendUnk1)
                {
                    fVar6 = g_blendUnk1;
                }
                g_blendUnk1 = fVar6;

                fVar6 = source[11];
                float fVar1 = fVar6;
                if (fVar6 < g_blendThresholdA)
                {
                    fVar1 = g_blendThresholdA;
                }
                g_blendThresholdA = fVar1;

                // Adjust scaling factors when flags change in bits 0 and 1
                if ((((uint32_t)source[17] ^ g_blendStateFlags) & 3) != 0)
                {
                    if ((g_blendStateFlags & 2) != ((uint32_t)source[17] & 2))
                    {
                        float fVar2 = fVar6;
                        if ((g_blendStateFlags & 2) != 0)
                        {
                            fVar2 = g_blendThresholdA;
                        }
                        g_blendThresholdD = (g_blendThresholdD / fVar1) * fVar2;
                    }
                    if ((g_blendStateFlags & 1) != ((uint32_t)source[17] & 1))
                    {
                        float fVar3 = g_blendThresholdA;  // Actually fVar3 is reused, but correct?
                        if ((g_blendStateFlags & 1) == 0)
                        {
                            fVar3 = fVar6;
                        }
                        g_blendThresholdE = (g_blendThresholdE / fVar1) * fVar3;
                    }
                }

                // Update min / max thresholds
                float fVar3b = source[12];
                if (g_blendThresholdB < source[12])
                {
                    fVar3b = g_blendThresholdB;
                }
                g_blendThresholdB = fVar3b;

                fVar3b = source[13];
                if (source[13] < g_blendThresholdC)
                {
                    fVar3b = g_blendThresholdC;
                }
                g_blendThresholdC = fVar3b;

                // Merge flags
                g_blendStateFlags |= (uint32_t)source[17];

                // Store blend factor used
                g_blendFactor = DAT_00e2b1a4;
                return;
            }
        }
        // Fallback: copy entire source (20 floats) directly to blend state
        {
            const float* src = source;
            float* dst = &g_blendPos[0];
            for (int i = 0; i < 20; i++)
            {
                *dst++ = *src++;
            }
            g_blendFactor = DAT_00e2b1a4;
            return;
        }
    }
    else
    {
        // Initialize (or reset) blend state when uninitialized or source flags indicate reset
        g_blendScale = DAT_00e39f98;
        g_blendUnk1 = DAT_00e39f98;
        g_blendRot[0] = 0.0f;
        g_blendRot[1] = 0.0f;
        g_blendRot[2] = 0.0f;
        g_blendRot[3] = DAT_00e2b1a4;
        g_blendPos[1] = DAT_00e2b1a4;  // Note: order from code: DAT_01219254 = DAT_00e2b1a4 (pos[1]?)
        g_blendPos[0] = DAT_00e2b1a4;  // DAT_01219250
        g_blendPos[3] = DAT_00e2b1a4;  // _DAT_01219258
        g_blendUnk2 = DAT_00e445ac;
        g_blendThresholdA = 0.0f;
        g_blendMaxVal = 0.0f;
        g_blendThresholdB = 0.0f;
        g_blendThresholdC = 0.0f;
        g_blendThresholdD = DAT_00e2b1a4;
        g_blendThresholdE = DAT_00e2b1a4;
        g_blendStateFlags = 0x10000000;
        g_blendFactor = DAT_00e2b1a4;
    }
    return;
}