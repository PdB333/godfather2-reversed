// FUNC_NAME: Camera::updateViewProjection
void __thiscall Camera::updateViewProjection(float *viewMatrix, float fov) {
    float *camera = this;
    float *viewM[16]; // Interpreted from param_1
    float *cameraM = (float *)camera; // Camera's embedded matrix at offset 0
    float fVar1, fVar2, fVar3, fVar4, fVar5, fVar6, fVar7, fVar8, fVar9;
    float fVar10, fVar11, fVar12, fVar13, fVar14, fVar15, fVar16;
    float fVar17, fVar18, fVar20, fVar21, fVar22, fVar23;
    float temp0, temp1, temp2, temp3, temp4, temp5, temp6, temp7;
    float local_60[4], local_30[4], local_50[4], local_40[4], local_20[4];
    float local_5c, local_54, local_4c, local_3c, local_34, local_2c, local_24, local_1c, local_18, local_14;
    undefined4 local_58, local_48, local_44, local_38, local_28;

    // Store input parameters into camera fields
    *(float **)(camera + 0x128) = camera; // Back-pointer
    *(float **)(camera + 0x12C) = viewMatrix;
    *(float  *)(camera + 0x130) = fov;

    // Condition: only for main camera and if renderer state > 1
    extern Camera *g_mainCamera; // DAT_012058e8
    if (g_mainCamera == camera && *(unsigned int *)(camera + 0x134) > 1) {
        // Extract view matrix rows
        fVar1  = viewMatrix[8];
        fVar2  = viewMatrix[9];
        fVar3  = viewMatrix[0];
        fVar4  = viewMatrix[3];
        fVar5  = viewMatrix[2];
        fVar6  = viewMatrix[10];
        fVar7  = viewMatrix[12];
        fVar8  = viewMatrix[13];
        fVar9  = viewMatrix[14];
        fVar10 = viewMatrix[11];
        fVar11 = viewMatrix[1];
        fVar12 = viewMatrix[4];
        fVar13 = viewMatrix[5];
        fVar14 = viewMatrix[6];
        fVar15 = viewMatrix[15];
        fVar16 = viewMatrix[7];
        fVar17 = cameraM[5];
        fVar18 = cameraM[1];

        // Compute combined matrix components
        // local_40 = dot product of view row with camera column for perspective components
        local_40[0] = fVar4 * cameraM[15] + fVar5 * cameraM[11] + fVar11 * cameraM[7] + fVar3 * cameraM[3];
        local_3c[0] = fVar16 * cameraM[15] + fVar14 * cameraM[11] + fVar13 * cameraM[7] + fVar12 * cameraM[3];
        local_14[0] = fVar10 * cameraM[15] + fVar6 * cameraM[11] + fVar2 * cameraM[7] + fVar1 * cameraM[3];

        // Compute perspective divisor
        float invFov = 1.0f / fov; // DAT_00e2b1a4 is likely 1.0f
        // Actually the code: param_2 = DAT_00e2b1a4 / param_2; so param_2 becomes 1/fov
        fov = 1.0f / fov;

        // Accumulate diagonal terms
        fVar20 = fVar7 * cameraM[3];
        fVar21 = fVar8 * cameraM[7];
        fVar22 = fVar9 * cameraM[11];
        fVar23 = fVar15 * cameraM[15];

        // First set of combined vectors
        local_60[0] = ((((fVar4 * cameraM[12] + fVar5 * cameraM[8] + fVar11 * cameraM[4] + fVar3 * cameraM[0]) - fVar20) - fVar21) - fVar22) - fVar23;
        local_5c = fVar16 * cameraM[12] + fVar14 * cameraM[8] + fVar13 * cameraM[4] + fVar12 * cameraM[0];
        local_58 = 0;
        local_54 = fVar15 * cameraM[12] + fVar9 * cameraM[8] + fVar8 * cameraM[4] + fVar7 * cameraM[0];

        // Second set of combined vectors
        local_30[0] = fVar4 * cameraM[13] + fVar5 * cameraM[9] + fVar11 * fVar17 + fVar3 * fVar18;
        float *cameraM_9 = &cameraM[9]; // Ghidra used in_EAX[9] - local variable fVar3 reused? Actually it's a pointer offset
        // The decompiler used fVar3 again but it's actually cameraM[9]. We'll compute directly.
        local_2c = ((((fVar16 * cameraM[13] + fVar14 * cameraM[9] + fVar13 * fVar17 + fVar12 * fVar18) - fVar20) - fVar21) - fVar22) - fVar23;
        local_24 = fVar15 * cameraM[13] + fVar9 * cameraM[9] + fVar8 * fVar17 + fVar7 * fVar18;

        // 1 - from some constant (DAT_00e44564 likely 1.0f)
        local_4c = 1.0f - local_3c[0];
        local_50[0] = 1.0f - local_40[0];

        local_34 = (fVar23 + fVar22 + fVar21 + fVar20) * fov;
        local_40[0] = fov * local_40[0];
        local_3c[0] = fov * local_3c[0];

        local_28 = 0;
        local_48 = 0;
        local_44 = 0;
        local_38 = 0;

        local_20[0] = fVar10 * cameraM[12] + fVar6 * cameraM[8] + fVar2 * cameraM[4] + fVar1 * cameraM[0];
        local_1c = fVar10 * cameraM[13] + fVar6 * cameraM[9] + fVar2 * fVar17 + fVar1 * fVar18;
        local_18 = 1.0f - local_14[0];
        local_14[0] = fov * local_14[0];

        // Update shader constants with computed vectors
        extern void setShaderConstant(void *context, unsigned int constantIndex, float *data); // FUN_0060add0

        setShaderConstant(*(void **)(camera + 0x10), *(unsigned int *)(camera + 0x2C4), &local_60);
        setShaderConstant(*(void **)(camera + 0x10), *(unsigned int *)(camera + 0x2C8), &local_30);
        setShaderConstant(*(void **)(camera + 0x10), *(unsigned int *)(camera + 0x2CC), &local_50);
        setShaderConstant(*(void **)(camera + 0x10), *(unsigned int *)(camera + 0x2D0), &local_40);

        int additionalConstantIndex = *(int *)(camera + 0x37C + *(int *)(camera + 0x138) * 4);
        if (additionalConstantIndex != 0) {
            setShaderConstant(*(void **)(camera + 0x14), additionalConstantIndex, &local_20);
        }
    }
    return;
}