// FUNC_NAME: SkeletalModel::ComputeVertexBoneMask
void __thiscall SkeletalModel::ComputeVertexBoneMask(void* this_ptr, int initialMask, float* vertices, uint8_t* outMasks, int vertexCount)
{
    float globalScale = DAT_00e2b1a4;  // Global scale factor, likely stored externally
    uint8_t boneIndices[3];
    boneIndices[0] = *(uint8_t*)((int)this_ptr + 0x60);   // +0x60: first bone index
    boneIndices[1] = *(uint8_t*)((int)this_ptr + 0x120);  // +0x120: second bone index
    boneIndices[2] = *(uint8_t*)((int)this_ptr + 0x1e0);  // +0x1e0: third bone index
    uint32_t currentMask = (initialMask >> 8) & 0xFFFFFF;  // Use high 24 bits of initialMask; low byte replaced by boneIndices[1]

    int outIndex = 0;
    if (vertexCount > 0) {
        float* vertexIter = vertices + 2;  // skip first two floats (position x,y?) Actually param_3+8 is third float (z)
        do {
            float vx = vertexIter[-2];
            float vy = vertexIter[-1];
            float vz = *vertexIter;
            float vw = vertexIter[1];  // maybe w component

            uint32_t resultMask = 0;
            for (int i = 0; i < 3; i++) {
                float* matrix = (float*)((int)this_ptr + 0x20 + i * 0x30);  // +0x20: array of 3 matrices (3×4? or 4×4 with stride 48?)
                // Plane tests using 8 planes stored relative to matrix pointer (from matrix-8 to matrix+7)
                float plane0_val = matrix[-8]*vx + matrix[-7]*vy + matrix[-5]*vw + matrix[-6]*vz;
                float plane1_val = matrix[-4]*vx + matrix[-3]*vy + matrix[-1]*vw + matrix[-2]*vz;
                float plane2_val = matrix[4]*vx + matrix[5]*vy + matrix[7]*vw + matrix[6]*vz;
                float plane3_val = matrix[0]*vx + matrix[1]*vy + matrix[3]*vw + matrix[2]*vz;

                // Compare against vw (probably the fourth component of vertex)
                uint32_t plane0_sign = (vw < plane0_val) ? 0xFFFFFFFF : 0;
                uint32_t plane1_sign = (vw < plane1_val) ? 0xFFFFFFFF : 0;
                uint32_t plane2_sign = (vw < plane2_val) ? 0xFFFFFFFF : 0;
                uint32_t plane3_sign = (vw < plane3_val) ? 0xFFFFFFFF : 0;

                // Pack signs into a 4-bit mask using movmskps equivalent
                uint32_t planeMask = (plane0_sign & 1) | (plane1_sign & 2) | (plane2_sign & 4) | (plane3_sign & 8);

                // Compute dot products with matrix rows? The second set of comparisons uses matrix[10], [11], [8], [9], [14], [15], [12], [13]
                float row0_dot = matrix[10]*vw + matrix[11]*vz + matrix[8]*vx + matrix[9]*vy;
                float row1_dot = matrix[14]*vw + matrix[15]*vz + matrix[12]*vx + matrix[13]*vy;
                // Reuse same pattern: compare vw against these two dot products (each repeated twice)
                uint32_t row0_sign = (vw < row0_dot) ? 0xFFFFFFFF : 0;
                uint32_t row1_sign = (vw < row1_dot) ? 0xFFFFFFFF : 0;
                uint32_t rowMask = (row0_sign & 5) | (row1_sign & 0xA);  // bits 0 and 2 for row0, bits 1 and 3 for row1
                // Actually the decompiled shows: auVar6 = { sign of fVar4<fVar15+fVar14, sign of fVar4<fVar17+fVar16, sign of fVar4<fVar17+fVar16, sign of fVar4<fVar15+fVar14 }
                // That means bits: 0 and 3 from first comparison, bits 1 and 2 from second. So rowMask = ((row0_sign&1)<<0) | ((row0_sign&1)<<3) | ((row1_sign&1)<<1) | ((row1_sign&1)<<2)
                // Simplify: rowMask = ((row0_sign != 0) ? 0x9 : 0) | ((row1_sign != 0) ? 0x6 : 0)
                uint32_t combinedMask = planeMask | rowMask;

                uint32_t boneMask = combinedMask;  // Actually decomp: uVar10 = (0 < (int)(uVar10 | uVar11)) - 1 & unaff_EBX;
                // Then uVar9 |= uVar10. This seems complex. Let's replicate the logic.
                // The uVar10 is being updated per iteration, starting from a value that includes the boneIndices[1] byte.
                // The final result per vertex: ( (uVar10 | uVar11) > 0 ) ? 0 : (boneIndex[i])
                uint32_t anyInside = (int)(rowMask | planeMask) > 0 ? 1 : 0 ? 0 : -1;  // Actually it's: (0 < (int)(uVar10 | uVar11)) - 1 & unaff_EBX
                // unaff_EBX comes from local_3c[i] = boneIndices[i]
                uint32_t insideMask = (anyInside == 0) ? 0 : boneIndices[i];  // But with subtract 1, it's: if positive then 0 else -1 -> -1 & boneIndex = boneIndex
                // Let's simplify: insideMask = (anyInside > 0) ? 0 : boneIndices[i];
                // Then resultMask |= insideMask;
                resultMask |= ((int)(rowMask | planeMask) > 0) ? 0 : boneIndices[i];
            }

            outMasks[outIndex] = (uint8_t)resultMask;
            outIndex++;
            vertexIter += 4;  // stride 4 floats per vertex
        } while (outIndex < vertexCount);
    }
}