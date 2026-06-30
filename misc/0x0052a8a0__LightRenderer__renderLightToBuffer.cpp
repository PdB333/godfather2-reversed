// FUNC_NAME: LightRenderer::renderLightToBuffer
void __thiscall LightRenderer::renderLightToBuffer(LightRenderer* thisPtr, Camera* camera)
{
    byte* frameBufferByte;
    uint uVar2;
    uint uVar3;
    uint uVar4;
    uint uVar5;
    int iVar6;
    int iVar7;
    uint uVar8;
    int iVar9;
    uint uVar10;
    int iVar11;
    int iVar12;
    int iVar13;
    int unaff_FS_OFFSET;
    float fVar14;
    float fVar15;
    float fVar16;
    float fVar17;
    float fVar18;
    double dVar19;
    float fVar20;
    float fVar21;
    float fVar22;
    float fVar23;
    float fVar24;
    float fVar25;
    float fVar26;
    float fVar27;
    float fVar28;
    float local_4c;

    // +0x8: pointer to a byte 'flag' that controls early exit?
    frameBufferByte = (byte*)(*(int*)(**(int**)(unaff_FS_OFFSET + 0x2c) + 8) + *(int*)(thisPtr + 8));
    // light type (from LightInfo at this+0x10) and a global flag
    if (((*frameBufferByte & 1) == 0) || (**(char**)(thisPtr + 0x10) != '\x04')) {
        // LightInfo structure
        LightInfo* lightInfo = *(LightInfo**)(thisPtr + 0x10);
        fVar24 = lightInfo->position.x;   // +0x14
        fVar14 = lightInfo->position.y;   // +0x18
        fVar15 = lightInfo->position.z;   // +0x1c

        // Transform light position by world matrix (stored in frameBufferByte at offsets 0x50 etc.)
        fVar20 = fVar14 * *(float*)(frameBufferByte + 0x60) + fVar24 * *(float*)(frameBufferByte + 0x50) +
                 fVar15 * *(float*)(frameBufferByte + 0x70) + DAT_00e2b1a4 * *(float*)(frameBufferByte + 0x80);
        fVar22 = fVar14 * *(float*)(frameBufferByte + 100) + fVar24 * *(float*)(frameBufferByte + 0x54) +
                 fVar15 * *(float*)(frameBufferByte + 0x74) + DAT_00e2b1a4 * *(float*)(frameBufferByte + 0x84);
        fVar23 = fVar14 * *(float*)(frameBufferByte + 0x68) + fVar24 * *(float*)(frameBufferByte + 0x58) +
                 fVar15 * *(float*)(frameBufferByte + 0x78) + DAT_00e2b1a4 * *(float*)(frameBufferByte + 0x88);
        fVar24 = fVar14 * *(float*)(frameBufferByte + 0x6c) + fVar24 * *(float*)(frameBufferByte + 0x5c) +
                 fVar15 * *(float*)(frameBufferByte + 0x7c) + DAT_00e2b1a4 * *(float*)(frameBufferByte + 0x8c);

        // Project light position to clip space using view-projection matrix (global)
        local_4c = fVar22 * fRam01218e18 + fVar20 * fRam01218e08 + fVar23 * fRam01218e28 +
                   fVar24 * fRam01218e38;

        // Check if within camera's near/far plane
        if ((*(float*)(camera + 0x144) <= local_4c) &&
            (local_4c < *(float*)(camera + 0x148) || local_4c == *(float*)(camera + 0x148))) {

            // Perspective divide
            fVar14 = DAT_00e2b1a4 / (fVar22 * fRam01218e1c + fVar20 * fRam01218e0c +
                                      fVar23 * fRam01218e2c + fVar24 * fRam01218e3c);

            // Compute screen coordinates (NDC to pixel)
            fVar15 = fVar14 * (fVar22 * fRam01218e14 + fVar20 * fRam01218e04 +
                               fVar23 * fRam01218e24 + fVar24 * fRam01218e34) * DAT_00e44718 + DAT_00e2cd54;
            fVar24 = fVar14 * (fVar22 * _DAT_01218e10 + fVar20 * _DAT_01218e00 +
                               fVar23 * _DAT_01218e20 + fVar24 * _DAT_01218e30) * DAT_00e2cd54 + DAT_00e2cd54;

            // Adjust w if not a point light (flag 0x8)
            if ((*(uint*)(lightInfo + 4) & 8) == 0) {
                fVar14 = DAT_00e2b1a4 / local_4c;
            } else {
                local_4c = DAT_00e2b1a4;
                fVar14 = DAT_00e2b1a4;
            }

            fVar20 = *(float*)(thisPtr + 0x20) * fVar14;

            // Check if light is within screen bounds (x and y within [0,1] range)
            if ((((0.0 < fVar20 + fVar24) && (0.0 < fVar20 + fVar15)) &&
                 (fVar24 - fVar20 < DAT_00e2b1a4)) &&
                (fVar15 - fVar20 < DAT_00e2b1a4)) {

                fVar23 = fVar20 * fVar20 + fVar20 * fVar20; // squared half-width?
                fVar22 = *(float*)(thisPtr + 0x18);

                // Flag 0x10: scale radius by something
                if ((*(uint*)(lightInfo + 4) & 0x10) == 0) {
                    fVar22 = *(float*)(thisPtr + 0x24) * fVar22 * fVar14;
                }

                // Minimum threshold for light contribution
                if ((DAT_00e2e210 < fVar22) && (DAT_00e2e210 < fVar23)) {

                    // Compute pixel grid bounds (32x32)
                    uVar2 = (uint)(((fVar24 - fVar20) - DAT_00e2b1a4) * DAT_00e446f0);
                    uVar5 = (uint)((fVar20 + fVar24 + DAT_00e2b1a4) * DAT_00e446f0);
                    uVar3 = (int)(uVar5 - 0x20) >> 0x1f;
                    uVar8 = (uint)(((fVar15 - fVar20) - DAT_00e2b1a4) * DAT_00e446f0);
                    uVar10 = (uint)((fVar20 + fVar15 + DAT_00e2b1a4) * DAT_00e446f0);
                    uVar4 = (int)(uVar10 - 0x20) >> 0x1f;

                    fVar20 = lightInfo->someFloat;   // +0x44
                    iVar9 = (uVar4 & uVar10 | ~uVar4 & 0x1f) - 1;
                    iVar12 = (~((int)uVar2 >> 0x1f) & uVar2) + 1;
                    iVar13 = (uVar3 & uVar5 | ~uVar3 & 0x1f) - 1;
                    iVar6 = (~((int)uVar8 >> 0x1f) & uVar8) + 1;

                    // Global flag: enable light?
                    DAT_012054fd = 1;

                    // Flag 0x4: attenuate by distance
                    if ((*(byte*)(lightInfo + 4) & 4) == 0) {
                        fVar20 = fVar20 * fVar14;
                    }

                    fVar14 = fVar23 - fVar20 * fVar20 * DAT_00e2b04c;

                    // Loop over rows
                    if (iVar6 <= iVar9) {
                        fVar27 = 0.0;
                        iVar7 = iVar6 * 0x20;
                        fVar20 = DAT_00e2b1a4;
                        fVar26 = fVar14;
                        fVar28 = fVar23;
                        do {
                            // Y distance from light center (in pixel coords)
                            fVar16 = (float)iVar6 * DAT_00e2d848 - fVar15;
                            if (iVar12 <= iVar13) {
                                iVar11 = iVar12;
                                do {
                                    // X distance
                                    fVar21 = (float)iVar11 * DAT_00e2d848 - fVar24;
                                    fVar25 = fVar21 * fVar21 + fVar16 * fVar16;
                                    if (fVar25 < fVar28) {
                                        fVar17 = fVar25 / fVar28;
                                        fVar18 = fVar17;
                                        switch (**(byte**)(thisPtr + 0x10)) {
                                        case 0: // Point light (inverse square)
                                            fVar18 = fVar27;
                                            if (fVar26 < fVar25) {
                                                fVar17 = fVar20 - fVar17;
                                                dVar19 = (double)(*(float*)(lightInfo + 0x48) *
                                                                  *(float*)(thisPtr + 0x14) +
                                                                 *(float*)(lightInfo + 0x50) * fVar17);
                                                FUN_00b99fcb(); // might be sqrt or noise
                                                fVar27 = 0.0;
                                                fVar20 = DAT_00e2b1a4;
                                                fVar26 = fVar14;
                                                fVar28 = fVar23;
                                                fVar18 = (float)dVar19 * fVar17;
                                            }
                                            break;
                                        case 1: // Spot light (cosine falloff)
                                            fVar18 = fVar20 - (DAT_00e445ac - fVar17 * DAT_00e2b04c) * fVar17 * fVar17;
                                            break;
                                        case 2: // Unknown (squared distance)
                                            fVar18 = fVar27;
                                            if (fVar26 < fVar25) {
                                                fVar21 = (fVar20 - (fVar20 - fVar17)) * (fVar20 - fVar17) * DAT_00e2d99c;
                                                fVar18 = fVar21 * fVar21;
                                            }
                                            break;
                                        case 3: // Area light?
                                            fVar20 = *(float*)(thisPtr + 0x14);
                                            dVar19 = (double)(*(float*)(lightInfo + 0x50) * fVar21 * local_4c +
                                                               *(float*)(lightInfo + 0x48) * fVar20);
                                            FUN_00b99fcb();
                                            dVar19 = (double)((float)dVar19 * *(float*)(lightInfo + 0x44) +
                                                             (fVar16 * local_4c + fVar20) *
                                                             *(float*)(lightInfo + 0x4c));
                                            FUN_00b99fcb();
                                            fVar27 = 0.0;
                                            fVar20 = DAT_00e2b1a4;
                                            fVar26 = fVar14;
                                            fVar28 = fVar23;
                                            fVar18 = (float)dVar19 * (DAT_00e2b1a4 - fVar17);
                                            break;
                                        case 4: // Random dither?
                                            fVar18 = fVar27;
                                            if (fVar26 < fVar25) {
                                                uVar2 = FUN_004e9200(); // random?
                                                fVar18 = ((float)(uVar2 >> 8 | 0x3f800000) - fVar20) * (fVar20 - fVar17);
                                            }
                                        }
                                        // Accumulate into pixel buffer (32x32 grid)
                                        (&DAT_01197da0)[iVar7 + iVar11] =
                                             fVar18 * fVar22 * *(float*)(&DAT_01198da0 + iVar11 * 4) *
                                             *(float*)(&DAT_01198da0 + iVar6 * 4) +
                                             (float)(&DAT_01197da0)[iVar7 + iVar11];
                                    }
                                    iVar11 = iVar11 + 1;
                                } while (iVar11 <= iVar13);
                            }
                            iVar6 = iVar6 + 1;
                            iVar7 = iVar7 + 0x20;
                        } while (iVar6 <= iVar9);
                    }
                    // If flag 0x20 set, apply post-process
                    if ((*(byte*)(lightInfo + 4) & 0x20) != 0) {
                        FUN_0052b390(*(undefined4*)(thisPtr + 0x1c));
                    }
                }
            }
        }
    }
    return;
}