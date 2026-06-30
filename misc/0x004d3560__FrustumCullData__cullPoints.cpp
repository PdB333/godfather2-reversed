// FUNC_NAME: FrustumCullData::cullPoints
#include <xmmintrin.h>

// Global constant referenced at 0x00e2b1a4
static float s_globalConstant = 0.0f; // Placeholder, actual value unknown

void FrustumCullData::cullPoints(const float* points, uint8* outMasks, int numPoints)
{
    // this pointer layout (offsets relative to this):
    // +0x00: float m_projectionMatrix[16]; // 4x4 matrix (used as shared base for frustum planes)
    // +0x20: float m_frustumPlanes[7][16]; // Actually each frustum uses 24 floats (6 planes) but stored with overlap? See code.
    // +0x60, +0x120, ... : uint8 m_frustumMask[7]; // per-frustum output mask bits
    // Note: offsets are from decompiled, not fully verified.

    float* localPlanePtr; // Reused pointer
    uint32 uVar10, uVar11;
    uint8 shapeMask; // from local_38 array
    uint8 resultBit;

    // Array of mask bytes for each frustum shape, read from object memory
    uint8 shapeMasks[7];
    shapeMasks[0] = *(uint8*)(this + 0x60);
    shapeMasks[1] = *(uint8*)(this + 0x120);
    shapeMasks[2] = *(uint8*)(this + 0x1e0);
    shapeMasks[3] = *(uint8*)(this + 0x2a0);
    shapeMasks[4] = *(uint8*)(this + 0x360);
    shapeMasks[5] = *(uint8*)(this + 0x420);
    shapeMasks[6] = *(uint8*)(this + 0x4e0);

    // Iterate over each input point
    for (int pointIdx = 0; pointIdx < numPoints; pointIdx++)
    {
        const float* pt = &points[pointIdx * 4];
        float x = pt[0];
        float y = pt[1];
        float z = pt[2];
        float w = pt[3];

        // accumulate result mask for this point
        uint8 finalMask = 0;

        // Inner loop over 7 frustum shapes
        for (int shapeIdx = 0; shapeIdx < 7; shapeIdx++)
        {
            // Base pointer for this shape's plane data (offset +0x20 + shapeIdx*0x30)
            float* pf = (float*)(this + 0x20 + shapeIdx * 0x30);

            // Compute dot products with rows of the 4x4 matrix? (actual indices from decompiled)
            // fVar14 = pf[11] * fVar7 + pf[10] * fVar3;  // indices 10,11
            float temp1 = pf[11] * s_globalConstant + pf[10] * z;
            // fVar15 = pf[9] * fVar2 + pf[8] * fVar1;    // indices 8,9
            float temp2 = pf[9] * y + pf[8] * x;
            // fVar16 = pf[15] * fVar7 + pf[14] * fVar3;  // indices 14,15
            float temp3 = pf[15] * s_globalConstant + pf[14] * z;
            // fVar17 = pf[13] * fVar2 + pf[12] * fVar1;  // indices 12,13
            float temp4 = pf[13] * y + pf[12] * x;

            // Four plane tests using negative indices (first two planes)
            __m128 cmp1;
            cmp1.m128_f32[0] = (float)(w < (pf[-3]*y + pf[-4]*x + pf[-1]*s_globalConstant + pf[-2]*z));
            cmp1.m128_f32[1] = (float)(w < (pf[-7]*y + pf[-8]*x + pf[-5]*s_globalConstant + pf[-6]*z));
            cmp1.m128_f32[2] = (float)(w < (pf[5]*y + pf[4]*x + pf[7]*s_globalConstant + pf[6]*z));
            cmp1.m128_f32[3] = (float)(w < (pf[1]*y + pf[0]*x + pf[3]*s_globalConstant + pf[2]*z));
            uVar11 = _mm_movemask_ps(cmp1);

            // Two additional plane tests (likely near/far or combined)
            __m128 cmp2;
            cmp2.m128_f32[0] = (float)(w < (temp4 + temp3));
            cmp2.m128_f32[1] = (float)(w < (temp2 + temp1));
            cmp2.m128_f32[2] = (float)(w < (temp4 + temp3));
            cmp2.m128_f32[3] = (float)(w < (temp2 + temp1));
            uVar10 = _mm_movemask_ps(cmp2);

            // Combine masks: if any bit from uVar11 or uVar10 is set, use shapeMask, else 0
            shapeMask = shapeMasks[shapeIdx];
            resultBit = (( (int)(uVar10 | uVar11) > 0 ) ? shapeMask : 0);
            finalMask |= resultBit;
        }

        // Store the final mask for this point
        outMasks[pointIdx] = finalMask;
    }
}