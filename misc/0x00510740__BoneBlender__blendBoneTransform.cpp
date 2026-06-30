// FUNC_NAME: BoneBlender::blendBoneTransform
// Reconstructed from function at 0x00510740
// This function computes the final bone transformation matrix for a given bone,
// blending between animation frames or applying IK constraints.
void BoneBlender::blendBoneTransform(int param_2, int param_3, BoneMatrix& outMatrix)
{
    int localThreadData = *(int*)(__readfsdword(0x2C));  // FS:0x2C - likely current thread struct
    // Possibly get current time or context
    FUN_00414aa0();  // likely time update or profiling
    FUN_00414aa0();

    AnimState* animState = *(AnimState**)(this + 0x24);
    bool bUseIK = false;

    if ((*(uint*)(animState + 0x108) & 0x4000) == 0)
    {
        if ((*(uint*)(animState + 0x10C) & 0x80000) == 0)
            goto LAB_0051088e;  // no special mode, go to standard blend

        // IK mode: get target rotation/quaternion from some source
        int ikData = FUN_004e9fa0();
        int ikSlot = (int)(*(int*)(localThreadData + 0x34) != 0) * 0x98 + 0xC + ikData;
        float* ikQuat = (float*)(*(int*)(ikSlot + 0x60));
        m_quatResult.x = ikQuat[0];       // +0x60
        m_quatResult.y = *(float*)(ikSlot + 100); // +0x64
        m_quatResult.z = *(float*)(ikSlot + 0x68);
        m_quatResult.w = *(float*)(ikSlot + 0x6C);
    }
    else
    {
        // No IK, compute direction from local velocity/direction vectors
        // local_68, local_6c, local_70 represent a direction vector (likely from previous blend or movement)
        float dirLength = local_68 * local_68 + (float)local_70 * (float)local_70 + (float)local_6c * (float)local_6c;
        if (dirLength <= DAT_00e2cbe0)
        {
            m_quatResult.y = 0.0f;
            dirLength = 0.0f;
        }
        else
        {
            dirLength = sqrtf(dirLength);
            float invLen = 1.0f / dirLength;  // puVar26 is actually a float? The decompiler shows puVar26 = DAT_00e2b1a4 (a float pointer), likely a global scalar. We assume it's a float constant 1.0f.
            m_quatResult.x = (float)local_70 * invLen;
            m_quatResult.z = local_68 * invLen;
            m_quatResult.y = invLen * (float)local_6c;
        }

        m_quatResult.w = 0.0f;

        if (dirLength < *(float*)PTR_FUN_00e4462c)  // some threshold
        {
            m_quatResult.x = 0.0f;
            m_quatResult.z = 0.0f;
            m_quatResult.y = 0.0f;
            // Set one component based on bone index
            char boneIdx = *(char*)(animState + 0x157);
            ((float*)&m_quatResult)[boneIdx] = 1.0f;
        }
    }

    bUseIK = true;

LAB_0051088e:
    // Prepare output transform
    FUN_0050a940(param_2);  // likely setup rendering context

    if (bUseIK)
    {
        // Build a quaternion from the computed direction/IK data
        float tempQuat[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
        double angle = (double)(float)m_quatResult.x;
        tempQuat[0] = (float)angle;  // Actually this is confusing: the code sets fStack_4c = (float)dVar24 after FUN_00b99fcb and then later uses local_50 as (float)dVar24. Might be a time value.
        // Let's follow the decompiled logic more closely:
        // The original code:
        // fStack_4c = 0.0; ... local_40 = 0.0; etc.
        // Then dVar24 = (double)(float)in_XMM0_Da;
        // local_50 = puVar26;  // likely 1.0f
        // FUN_00b99fcb(); -> get some time
        // fStack_4c = (float)dVar24;  // assign time to fStack_4c
        // dVar24 = (double)(float)in_XMM0_Da;
        // FUN_00b99e20(); -> get another time
        // local_40 = DAT_00e44564 - fStack_4c;  // difference
        // local_50 = (float)dVar24;  // second time
        // Then local_70 = 0, local_6c = DAT_00e2b1a4 (1.0f?), local_68 = 0.
        // This seems to be setting up a quaternion/transform for output.
        // The exact logic is messy with decompiler inlining. We'll simplify: compute a quaternion from direction/IK and then call FUN_0056c6b0 to blend.
        // For readability, we'll assume the function builds a final transform and writes it to outMatrix.
        // Actually the code calls FUN_0056c6b0(&local_80, &local_70, param_4) and FUN_0056b230.
        // We'll keep the function structure but rename.

        // For brevity and clarity, I'll represent the core logic:
        float blendTime1 = 0.0f, blendTime2 = 0.0f;
        blendTime1 = getBlendTime1();  // FUN_00b99fcb
        blendTime2 = getBlendTime2();  // FUN_00b99e20
        float blendAlpha = DAT_00e44564 - blendTime1;  // maybe 1 - time1

        // Construct a quaternion from the processed direction/IK
        Quaternion outQuat;
        outQuat.x = m_quatResult.x;
        outQuat.y = m_quatResult.y;
        outQuat.z = m_quatResult.z;
        outQuat.w = m_quatResult.w;  // from uStack_74, which was set earlier

        // Call blend functions
        FUN_0056c6b0(&outQuat, &someVec, &outMatrix);  // possibly a quaternion blend
        FUN_0056b230(&outQuat, &outMatrix, &outMatrix, 3);  // matrix multiply or copy

        // Zero out some parts?
        *(float*)(&outMatrix + 0xC) = 0.0f;
        *(float*)(&outMatrix + 0x1C) = 0.0f;
        *(float*)(&outMatrix + 0x2C) = 0.0f;

        // Additional blending under a flag
        if (*(byte*)(animState + 0x104) & 2)
        {
            // Blend with another transform from some slot
            int slotBase = *(int*)(this + 0x10) + 0x50 + *(int*)(localThreadData + 8);
            FUN_0056b230(&outMatrix, slotBase, &outMatrix, 3);
            *(float*)(&outMatrix + 0xC) = 0.0f;
            *(float*)(&outMatrix + 0x1C) = 0.0f;
            *(float*)(&outMatrix + 0x2C) = 0.0f;
        }
    }
    else
    {
        // Standard bone blending without IK
        char boneIdx = *(char*)(animState + 0x157);
        uint slot1 = (0x21 >> (boneIdx * 4) & 0x1F) & 0xF;
        uint slot2 = (0x21 >> ((char)slot1 * 4) & 0x1F) & 0xF;

        if ((*(byte*)(animState + 0x104) & 2) == 0)
        {
            // Single animation frame (no blending)
            FUN_0056bf40(/*some context*/);
        }
        else
        {
            // Blend between two animation frames
            float blendWeight1 = getBlendWeight1(); // FUN_00b99fcb returns a float
            float blendWeight2 = getBlendWeight2(); // FUN_00b99e20 returns a float

            float* source1 = (float*)(*(int*)(this + 0x10) + (boneIdx + 5) * 16 + *(int*)(localThreadData + 8));
            float* source2 = (float*)(*(int*)(this + 0x10) + (slot1 + 5) * 16 + *(int*)(localThreadData + 8));
            float* dest = (float*)(&outMatrix) + boneIdx * 4;  // Actually outMatrix is a flat array

            // Copy first source
            float src1[4] = { source1[0], source1[1], source1[2], source1[3] };
            dest[0] = src1[0];
            dest[1] = src1[1];
            dest[2] = src1[2];
            dest[3] = src1[3];

            // Blend from second slot for slot1
            float* source3 = (float*)(*(int*)(this + 0x10) + (slot1 + 5) * 16 + *(int*)(localThreadData + 8));
            float* dest2 = (float*)(&outMatrix) + slot1 * 4;
            dest2[0] = blendWeight1 * source3[0];
            dest2[1] = blendWeight1 * source3[1];
            dest2[2] = blendWeight1 * source3[2];
            dest2[3] = blendWeight1 * source3[3];

            float blendAlpha = DAT_00e44564 - blendWeight1; // 1 - weight1

            // Accumulate from second slot for slot1
            float* source4 = (float*)(*(int*)(this + 0x10) + (slot1 + 5) * 16 + *(int*)(localThreadData + 8));
            dest2[0] = source4[0] * blendAlpha + dest2[0];
            dest2[1] = source4[1] * blendAlpha + dest2[1];
            dest2[2] = source4[2] * blendAlpha + dest2[2];
            dest2[3] = source4[3] * blendAlpha + dest2[3];

            // Blend from first slot for slot2
            float* source5 = (float*)(*(int*)(this + 0x10) + (slot2 + 5) * 16 + *(int*)(localThreadData + 8));
            float* dest3 = (float*)(&outMatrix) + slot2 * 4;
            dest3[0] = source5[0] * blendWeight2;
            dest3[1] = source5[1] * blendWeight2;
            dest3[2] = source5[2] * blendWeight2;
            dest3[3] = source5[3] * blendWeight2;

            // Accumulate from second slot for slot2
            float* source6 = (float*)(*(int*)(this + 0x10) + (slot2 + 5) * 16 + *(int*)(localThreadData + 8));
            dest3[0] = (DAT_00e44564 - blendWeight1) * source6[0] + dest3[0];
            dest3[1] = (DAT_00e44564 - blendWeight1) * source6[1] + dest3[1];
            dest3[2] = (DAT_00e44564 - blendWeight1) * source6[2] + dest3[2];
            dest3[3] = (DAT_00e44564 - blendWeight1) * source6[3] + dest3[3];
        }
    }

    // Final matrix copy
    byte* flags = (byte*)(*(int*)(this + 0x10) + *(int*)(localThreadData + 8));
    if (*flags & 4)
    {
        FUN_0056b420(flags + 0x50, local_60, &outMatrix + 0x30);  // copy extra matrix
        return;
    }
    *(Matrix4*)(&outMatrix + 0x30) = local_60;  // local_60 is a 4x4 matrix
    return;
}