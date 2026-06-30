// FUNC_NAME: GlobalSmoother::lerpToTarget
// Address: 0x0052d480
// Reconstructed from Ghidra decompilation.
// Role: Interpolates 7 global float parameters towards target values stored in this object.
// The object has target values at offsets +0x10 through +0x28 (7 floats).
// The global array is at 0x01206700 and holds current smoothed values.
// The interpolation factor is passed as a float in XMM1_Da.
// A constant (likely 1.0f) is stored at 0x00e2b1a4.

#include <cstdint>

// Extern globals: actual current smooth values
extern float g_smoothCurrent[7];   // base address 0x01206700
// Constant 1.0f
extern const float g_one;          // address 0x00e2b1a4 (assumed to be 1.0f)

class GlobalSmoother
{
public:
    // Target values stored at offsets:
    // +0x10: m_targetParam0
    // +0x14: m_targetParam1
    // +0x18: m_targetParam2
    // +0x1c: m_targetParam3
    // +0x20: m_targetParam4
    // +0x24: m_targetParam5
    // +0x28: m_targetParam6
    // (Preceding data may exist but not referenced)

    void lerpToTarget(float blend); // blend factor (0..1)
};

void GlobalSmoother::lerpToTarget(float blend)
{
    // First four params: lerp using (target - current) * blend + current
    g_smoothCurrent[0] = (*(float*)((uint8_t*)this + 0x10) - g_smoothCurrent[0]) * blend + g_smoothCurrent[0];
    g_smoothCurrent[1] = (*(float*)((uint8_t*)this + 0x14) - g_smoothCurrent[1]) * blend + g_smoothCurrent[1];
    g_smoothCurrent[2] = (*(float*)((uint8_t*)this + 0x18) - g_smoothCurrent[2]) * blend + g_smoothCurrent[2];
    g_smoothCurrent[3] = (*(float*)((uint8_t*)this + 0x1c) - g_smoothCurrent[3]) * blend + g_smoothCurrent[3];

    // Last three: lerp using (target * blend) + (1 - blend) * current
    float oneMinusBlend = g_one - blend;
    g_smoothCurrent[4] = *(float*)((uint8_t*)this + 0x20) * blend + oneMinusBlend * g_smoothCurrent[4];
    g_smoothCurrent[5] = *(float*)((uint8_t*)this + 0x24) * blend + oneMinusBlend * g_smoothCurrent[5];
    g_smoothCurrent[6] = *(float*)((uint8_t*)this + 0x28) * blend + oneMinusBlend * g_smoothCurrent[6];
}