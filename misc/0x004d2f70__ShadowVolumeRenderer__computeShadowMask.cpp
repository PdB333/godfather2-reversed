// FUNC_NAME: ShadowVolumeRenderer::computeShadowMask
void __fastcall ShadowVolumeRenderer::computeShadowMask(
    undefined4 param_1, 
    undefined4 param_2, 
    int lightData,          // param_3 - pointer to light data array
    uint shadowMask,        // param_4 - output shadow mask buffer
    int numSamples          // param_5 - number of samples to process
)
{
    float fVar1, fVar2, fVar3, fVar4;
    float fVar7;
    float *pfVar8, *pfVar13;
    uint uVar9, uVar10, uVar11;
    int iVar12;
    float fVar14, fVar15, fVar16, fVar17;
    byte local_3c[4];       // shadow bias values for each cascade
    int local_38;           // sample counter

    fVar7 = DAT_00e2b1a4;   // global shadow map resolution or depth bias

    // Load shadow bias values from the shadow volume object (+0x60, +0x120, +0x1e0)
    local_3c[0] = *(byte *)(in_EAX + 0x60);   // cascade 0 bias
    local_3c[1] = *(byte *)(in_EAX + 0x120);  // cascade 1 bias
    local_3c[2] = *(byte *)(in_EAX + 0x1e0);  // cascade 2 bias
    local_38 = 0;

    if (0 < numSamples) {
        pfVar13 = (float *)(lightData + 8);  // skip first 2 floats (light position?)
        uVar10 = CONCAT31((int3)((uint)param_2 >> 8), *(undefined1 *)(in_EAX + 0x120));

        do {
            // Load sample position (x, y, z, w)
            fVar1 = pfVar13[-2];  // sample x
            fVar2 = pfVar13[-1];  // sample y
            fVar3 = *pfVar13;     // sample z
            fVar4 = pfVar13[1];   // sample w (depth comparison value)

            uVar9 = 0;
            iVar12 = 0;
            pfVar8 = (float *)(in_EAX + 0x20);  // pointer to shadow map projection matrices

            do {
                // Transform sample position by shadow map projection matrix
                // Each cascade has a 4x4 matrix stored at +0x20, +0x50, +0x80
                fVar14 = pfVar8[0xb] * fVar7 + pfVar8[10] * fVar3;
                fVar15 = pfVar8[9] * fVar2 + pfVar8[8] * fVar1;
                fVar16 = pfVar8[0xf] * fVar7 + pfVar8[0xe] * fVar3;
                fVar17 = pfVar8[0xd] * fVar2 + pfVar8[0xc] * fVar1;

                // Perform shadow map comparison using SSE-style operations
                // Compare depth value against shadow map samples
                auVar5._4_4_ = -(uint)(fVar4 < pfVar8[-7] * fVar2 + pfVar8[-8] * fVar1 +
                                       pfVar8[-5] * fVar7 + pfVar8[-6] * fVar3);
                auVar5._0_4_ = -(uint)(fVar4 < pfVar8[-3] * fVar2 + pfVar8[-4] * fVar1 +
                                       pfVar8[-1] * fVar7 + pfVar8[-2] * fVar3);
                auVar5._8_4_ = -(uint)(fVar4 < pfVar8[5] * fVar2 + pfVar8[4] * fVar1 +
                                       pfVar8[7] * fVar7 + pfVar8[6] * fVar3);
                auVar5._12_4_ = -(uint)(fVar4 < *pfVar8 * fVar1 + pfVar8[1] * fVar2 +
                                        pfVar8[3] * fVar7 + pfVar8[2] * fVar3);

                uVar11 = movmskps(unaff_EBX, auVar5);  // extract comparison results

                // Additional depth comparison for cascade boundaries
                auVar6._4_4_ = -(uint)(fVar4 < fVar15 + fVar14);
                auVar6._0_4_ = -(uint)(fVar4 < fVar17 + fVar16);
                auVar6._8_4_ = -(uint)(fVar4 < fVar17 + fVar16);
                auVar6._12_4_ = -(uint)(fVar4 < fVar15 + fVar14);
                uVar10 = movmskps(uVar10, auVar6);

                unaff_EBX = (uint)local_3c[iVar12];  // load cascade bias
                iVar12 = iVar12 + 1;
                pfVar8 = pfVar8 + 0x30;  // advance to next cascade matrix

                // Combine results and apply bias
                uVar10 = (0 < (int)(uVar10 | uVar11)) - 1 & unaff_EBX;
                uVar9 = uVar9 | uVar10;
            } while (iVar12 < 3);  // process 3 shadow map cascades

            // Store shadow mask result (1 byte per sample)
            *(char *)(local_38 + shadowMask) = (char)uVar9;
            local_38 = local_38 + 1;
            pfVar13 = pfVar13 + 4;  // advance to next sample
            uVar10 = shadowMask;
        } while (local_38 < numSamples);
    }
    return;
}