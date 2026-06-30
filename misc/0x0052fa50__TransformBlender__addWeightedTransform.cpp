// FUNC_NAME: TransformBlender::addWeightedTransform
// Address: 0x0052fa50
// Blends a 4-component quaternion (weighted) and 2-component translation (unweighted) into the internal transform state.
// The global weight DAT_00e2b1a4 is used to scale the quaternion components (x,y,z,w) before adding.
// Translation components (positions in 2D or similar) are added directly without scaling.
// Likely part of animation blending or bone accumulation.

void __thiscall TransformBlender::addWeightedTransform(const float* input)
{
    float fVar1;
    float fVar2;
    float fVar3;
    float weight = g_globalWeight; // DAT_00e2b1a4 - global blend factor

    // Accumulate with weight for the quaternion part (indices 0..3)
    m_transform[0] += weight * input[0];
    m_transform[1] += weight * input[1];
    m_transform[2] += weight * input[2];
    m_transform[3] += weight * input[3];

    // Add translation directly (no scaling) for indices 4 and 5
    m_transform[4] += input[4];
    m_transform[5] += input[5];
}