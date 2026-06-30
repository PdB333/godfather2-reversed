// FUNC_NAME: Math::AccumulateTransformation
void __fastcall Math_AccumulateTransformation(float* pOut, const float* pIn)
{
    // pOut (in_EAX) is the destination array, pIn (param_1) is the source array
    // Global scale factor (likely time step or blend weight)
    const float fScale = DAT_00e2b1a4;

    // Blend rotation components (indices 0-3) - typically quaternion part
    // +0x00: quaternion x
    // +0x04: quaternion y
    // +0x08: quaternion z
    // +0x0C: quaternion w
    pOut[0] = fScale * pIn[0] + pOut[0];
    pOut[1] = fScale * pIn[1] + pOut[1];
    pOut[2] = fScale * pIn[2] + pOut[2];
    pOut[3] = fScale * pIn[3] + pOut[3];

    // Add translation components directly (unscaled)
    // +0x10: translation x
    // +0x14: translation y
    // Note: pIn[6] and pIn[7] are ignored (possibly translation z and unused)
    pOut[4] = pIn[4] + pOut[4];
    pOut[5] = pIn[5] + pOut[5];

    // Accumulate time/parameter at index 8 (e.g., animation timer)
    // +0x20: scalar field (e.g., time accumulator or weight)
    pOut[8] = pOut[8] + fScale;
}