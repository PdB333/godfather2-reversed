// FUNC_NAME: ControllerAxisState::updateDampening
// Address: 0x005e5b00
// This function appears to compute a damped output value for a controller axis state.
// It takes two extra float parameters in XMM3 and XMM4 (likely input vector components).
// Global constants used: g_dt (DAT_00e44564), g_maxValue (DAT_00e2b1a4),
// g_dampingThreshold (DAT_00e44598), g_dampingMultiplier (DAT_00e39f98).
// Per-instance state (0x18 bytes each) stored in global arrays at DAT_00e2afc8, etc.

struct ControllerAxisState {
    float m_currentValue;       // +0x00
    float m_maxDelta;           // +0x04
    float m_padding1;           // +0x08 (unused directly)
    float m_springLimit;        // +0x0C (pfVar1[3])
    float m_dampingFactor;      // +0x10 (pfVar1[4])
    float m_otherFactor;        // +0x14 (pfVar1[5])
};

// Global constants (addresses from Ghidra)
extern const float g_dt;                // 0x00e44564
extern const float g_maxValue;          // 0x00e2b1a4
extern const float g_dampingThreshold;  // 0x00e44598
extern const float g_dampingMultiplier; // 0x00e39f98

void __thiscall ControllerAxisState::updateDampening(int instanceIndex, float param2, float param3, float param4,
                                                      float inputX, float inputY)
{
    // instanceIndex is param_1, treated as index into global arrays.
    // inputX and inputY are passed in XMM3 and XMM4 registers (in_XMM3_Da, in_XMM4_Da)
    // The decompiler mapped them as locals, but they are extra register args.

    float diff = inputY - inputX;
    ControllerAxisState* state;
    float fVar2; // computed damped value
    float fVar3; // intermediate
    float fVar4; // time-adjusted clamp

    if (diff < 0.0f)
    {
        // Branch for negative difference
        param4 = inputX - param4;   // param4 is overwritten as a local
        fVar2 = 0.0f;
        fVar4 = g_dt - diff;        // diff is negative, so this becomes g_dt + |diff|
        if (param4 <= 0.0f || fVar4 <= 0.0f)
            return;

        state = (ControllerAxisState*)(&g_axisStates[instanceIndex]); // base offset 0x00e2afc8
        float maxDelta = state->m_maxDelta;       // field at +0x04
        fVar3 = g_maxValue;

        if (g_dampingThreshold < param4)
            fVar3 = g_dampingMultiplier / param4;

        fVar3 *= fVar4;

        if (fVar3 <= maxDelta)
        {
            if (state->m_currentValue < fVar3)
            {
                // Apply damping from current value
                fVar2 = g_dt - (fVar3 - state->m_currentValue) * state->m_dampingFactor;
            }
            goto LAB_005e5c32;
        }
    }
    else
    {
        // Branch for positive or zero difference
        param3 = param3 - param2;
        if (param3 <= 0.0f || inputY - param2 <= 0.0f)
            return;

        state = (ControllerAxisState*)(&g_axisStates[instanceIndex]);
        float maxDelta = state->m_maxDelta;
        fVar3 = g_maxValue;

        if (g_dampingThreshold < param3)
            fVar3 = g_dampingMultiplier / param3;

        fVar3 *= (inputY - param2);

        if (fVar3 <= maxDelta)
        {
            fVar2 = g_maxValue;
            if (state->m_currentValue < fVar3)
            {
                fVar2 = g_maxValue - (fVar3 - state->m_currentValue) * state->m_dampingFactor;
            }
            goto LAB_005e5c32;
        }
    }

    // If fVar3 exceeded maxDelta, clamp via spring-like formula
    fVar2 = state->m_springLimit - (fVar3 - maxDelta) * state->m_otherFactor;
    if (fVar2 < 0.0f)
        fVar2 = 0.0f;

LAB_005e5c32:
    // Special handling for controller index 3 (likely 4th controller)
    if (instanceIndex == 3)
    {
        float residue = g_maxValue - fVar2;
        if (residue <= 0.0f || g_maxValue <= residue)
            return;
    }

    // The computed fVar2 is not written back to memory in this function.
    // Possibly it's returned via a global or used in caller inline.
    return;
}