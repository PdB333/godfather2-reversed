// FUNC_NAME: AnimationMixer::applyBlendedSamples

int AnimationMixer::applyBlendedSamples(SampleSet* srcPose, float weight, byte flags)
{
    float fVar1;
    float fVar2;
    float fVar3;
    int boneCount;
    float* dstTransform;
    float* srcTransform;
    int iVar7;
    uint uVar8;
    int local_34;
    char* boneTypeList;
    int local_28;
    float* local_24;
    float local_20;
    float fStack_1c;
    float* pfStack_18;
    float fStack_14;

    if ((srcPose != 0) && (MixerState* mixer = getMixerState(); mixer != 0)) {
        if ((flags & 4) == 0) {
            beginPoseUpdate();
            setSourcePose(srcPose);

            // Number of bones to process
            local_34 = *(int*)(*(int*)(srcPose + 0x38) + 0xc); // count from bone data
            iVar7 = *(int*)(srcPose + 0x34); // pointer to bone flags

            if (*(int*)(mixer + 0x3c) == 0) {
                // Simple per-bone processing based on type flag
                boneTypeList = (char*)(iVar7 + 0x14);
                if (*(char*)(iVar7 + 0x10) == 0) {
                    // Non-uniform: check each bone type
                    for (; 0 < local_34; local_34--) {
                        if (*boneTypeList == 0x02) { // Additive bone
                            processAdditiveBone(weight);
                        }
                        boneTypeList++;
                    }
                } else {
                    // Uniform: all bones same type
                    for (; 0 < local_34; local_34--) {
                        processAdditiveBone(weight);
                    }
                }
            } else {
                // Complex blend with matrix/scale copy
                boneTypeList = (char*)(iVar7 + 0x14);
                local_28 = *(int*)(srcPose + 0x38) + 0x10; // source transform array
                local_24 = (float*)(*(int*)(srcPose + 0x3c) + 0x10); // extra data
                local_20 = (float)(*(int*)(mixer + 0x34) + 0x14); // destination transform start
                fStack_1c = (float)(*(int*)(mixer + 0x38) + 0x10);
                dstTransform = (float*)(*(int*)(mixer + 0x3c) + 0x10);
                pfStack_18 = dstTransform;

                if (*(char*)(iVar7 + 0x10) == 0) {
                    // Non-uniform: scale each bone individually
                    for (; 0 < local_34; local_34--) {
                        scaleAndCopyBone(&local_20, &boneTypeList, weight);
                        boneTypeList++;
                        local_20 = (float)((int)local_20 + 1);
                        local_28 += 0x20; // sizeof(Matrix4x4)
                        fStack_1c = (float)((int)fStack_1c + 0x20);
                        local_24 += 4;
                        pfStack_18 += 4;
                    }
                } else if (0 < local_34) {
                    // Uniform: all bones scaled identically
                    local_20 = weight;
                    fStack_1c = weight;
                    pfStack_18 = (float*)weight;
                    fStack_14 = weight;
                    do {
                        processAdditiveBone(weight);
                        fVar1 = local_24[1];
                        fVar2 = local_24[2];
                        fVar3 = local_24[3];
                        *dstTransform = *local_24 * local_20;
                        dstTransform[1] = fVar1 * fStack_1c;
                        dstTransform[2] = fVar2 * (float)pfStack_18;
                        dstTransform[3] = fVar3 * fStack_14;
                        local_34--;
                        dstTransform[3] = DAT_00e2b1a4; // 1.0f (identity w component)
                        local_24 += 4;
                        dstTransform += 4;
                    } while (0 < local_34);
                }
            }

            // Process additional matrix array if present
            if (*(int*)(mixer + 0x40) != 0) {
                uVar8 = *(uint*)(*(int*)(mixer + 0x40) + 0xc); // element count * 4
                dstTransform = (float*)(*(int*)(mixer + 0x40) + 0x10);
                float* srcExtra = (float*)(*(int*)(srcPose + 0x40) + 0x10);
                for (iVar7 = (int)uVar8 >> 2; 0 < iVar7; iVar7--) {
                    fVar1 = srcExtra[1];
                    fVar2 = srcExtra[2];
                    fVar3 = srcExtra[3];
                    *dstTransform = *srcExtra * weight;
                    dstTransform[1] = fVar1 * weight;
                    dstTransform[2] = fVar2 * weight;
                    dstTransform[3] = fVar3 * weight;
                    srcExtra += 4;
                    dstTransform += 4;
                }
                uVar8 = uVar8 & 3;
                if (3 < uVar8) {
                    iVar7 = ((uVar8 - 4) >> 2) + 1;
                    uVar8 = uVar8 + iVar7 * -4;
                    do {
                        *dstTransform = *srcExtra * weight;
                        dstTransform[1] = srcExtra[1] * weight;
                        dstTransform[2] = srcExtra[2] * weight;
                        dstTransform[3] = srcExtra[3] * weight;
                        srcExtra += 4;
                        dstTransform += 4;
                        iVar7--;
                    } while (iVar7 != 0);
                }
                for (; 0 < (int)uVar8; uVar8--) {
                    *dstTransform = *srcExtra * weight;
                    srcExtra++;
                    dstTransform++;
                }
            }
        }

        // Handle root motion / translation (if flag bit 3 not set)
        if ((flags & 8) == 0) {
            local_28 = srcPose + 0x10; // root motion data area
            if (*(char*)(srcPose + 0x30) == 0x02) { // root motion type additive
                pfStack_18 = (float*)0x0;
                fStack_1c = 0.0;
                local_20 = 0.0;
                fStack_14 = DAT_00e2b1a4; // 1.0f
                applyTranslationWeight(weight, &local_20, local_28, mixer + 0x10, DAT_00e2e780);
                fVar1 = *(float*)(local_28 + 0x14);
                fVar2 = *(float*)(local_28 + 0x18);
                fVar3 = *(float*)(local_28 + 0x1c);
                *(float*)(mixer + 0x20) = weight * *(float*)(local_28 + 0x10);
                *(float*)(mixer + 0x24) = weight * fVar1;
                *(float*)(mixer + 0x28) = weight * fVar2;
                *(float*)(mixer + 0x2c) = weight * fVar3;
                *(float*)(mixer + 0x2c) = DAT_00e2b1a4; // set w to 1.0
                *(undefined1*)(mixer + 0x30) = 2; // mark as additive
            }
        }
        return mixer;
    }
    return 0;
}