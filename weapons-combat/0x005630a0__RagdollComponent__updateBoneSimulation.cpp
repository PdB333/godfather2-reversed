// FUNC_NAME: RagdollComponent::updateBoneSimulation
void __thiscall RagdollComponent::updateBoneSimulation(int *thisPtr, uint boneIndex, Context* context, float* outBoneData)
{
    float *pfVar1;
    float fVar2, fVar3, fVar6, fVar9, fVar10, fVar11, fVar12, fVar13;
    char cVar4;
    int iVar5, iVar8;
    float fStack_b4, fStack_b0, fStack_ac, fStack_a8, fStack_a0;
    float fStack_94, fStack_90, fStack_8c;
    uint boneLoopIndex;
    int *boneNodeArray = (int *)thisPtr;
    int *vtable = (int *)*thisPtr;
    int contextBoneCountAddr;
    int boneDataOffset;
    int somePointer;
    float fStack_20, fStack_34;
    float fStack_a4;

    // Call vtable function at offset 0x28 – likely preUpdate or reset
    ((void (*)(Context*))vtable[0x28 / 4])(context);

    boneLoopIndex = 0;
    fStack_84 = DAT_00e2b1a4;  // timestep or scalar

    contextBoneCountAddr = *(int *)(context + 0x1c);
    int boneCount = *(char *)(contextBoneCountAddr + 0x20);
    if (boneCount > 0) {
        do {
            iVar5 = (char)boneLoopIndex;
            boneDataOffset = iVar5 * 0xC0 + *(int *)(context + 0x48); // per-bone data array
            int *boneData = (int *)boneDataOffset;

            // Local arrays/structs
            int *someArray = (int *)0; // uStack_54
            int someInt = 0; // iStack_44
            uint someUint = 0xffffffff; // uStack_80
            float afStack_74[8]; // unknown float array

            // Virtual call at offset 0x24 – maybe getBoneState?
            float *fStackPtr = &fStack_94;
            ((void (*)(int *, Context*, float*)) (*(int *)*boneNodeArray + 0x24))(boneData, context, fStackPtr);

            // Read some velocity/position from context
            float fVar10 = *(float *)(*(int *)(*(int *)(context + 0x34) + 8) + 0x20 + iVar5 * 0x30);
            float fVar11 = *(float *)(*(int *)(contextBoneCountAddr + 0x8c) + iVar5 * 0x28);
            float fVar6 = 0.0f;

            float *outRow = outBoneData + iVar5 * 0x10; // 0x40 = 16 floats

            if (someInt == 0) {
                // First pass: initialize output
                outRow[0xb] = fVar10;
                fVar6 = DAT_00e44564;  // likely 0.0f
                outRow[9] = 0.0f;
                outRow[0xc] = 0.0f;
                outRow[0] = *(float *)(boneDataOffset + 0x40);
                outRow[1] = *(float *)(boneDataOffset + 0x44);
                outRow[2] = *(float *)(boneDataOffset + 0x48);
                outRow[3] = *(float *)(boneDataOffset + 0x4c);
                fVar10 = *(float *)(boneDataOffset + 100);
                fVar11 = *(float *)(boneDataOffset + 0x68);
                outRow[4] = fVar6 - *(float *)(boneDataOffset + 0x60);
                fStack_84 = DAT_00e2b1a4;
                outRow[5] = fVar6 - fVar10;
                outRow[6] = fVar6 - fVar11;
                outRow[8] = 0.0f;
            } else {
                // Subsequent passes: integrate
                outRow[4] = fStack_94;
                outRow[5] = fStack_90;
                outRow[6] = fStack_8c;

                // Process afStack_74 array
                iVar5 = 0;
                do {
                    pfVar1 = afStack_74 + iVar5;
                    if (*pfVar1 == -FLT_MAX) break;
                    iVar5++;
                    outRow[10] = *pfVar1;
                } while (iVar5 < 8);

                // Check some flag from someInt structure
                if (*(char *)(someInt + 0x18) == 1) {
                    fVar6 = (float)(*(char *)(someInt + 0x10) + someInt); // suspicious: pointer addition
                }
                outRow[9] = fVar6;

                float fVar9 = (fVar11 + fVar10) * fStack_84;
                outRow[0xb] = fVar9 - fVar11;

                // Read more bone data for position computation
                fVar10 = *(float *)(boneDataOffset + 100);
                fVar11 = *(float *)(boneDataOffset + 0x68);
                fVar12 = *(float *)(boneDataOffset + 0x6c);
                fVar13 = *(float *)(boneDataOffset + 0x34);
                float fVar2 = *(float *)(boneDataOffset + 0x38);
                float fVar3 = *(float *)(boneDataOffset + 0x3c);

                // New position = integration
                outRow[0] = *(float *)(boneDataOffset + 0x60) * fVar9 + *(float *)(boneDataOffset + 0x30);
                outRow[1] = fVar10 * fVar9 + fVar13;
                outRow[2] = fVar11 * fVar9 + fVar2;
                outRow[3] = fVar12 * fVar9 + fVar3;

                // Virtual call at offset 0x20 – maybe getWorldTransform?
                boneNodeArray = *(int **)((int)fVar6 + 0x84);
                ((void (*)(Context*, uint, float*, int**)) (*(int *)*boneNodeArray + 0x20))(context, boneLoopIndex, &fStack_94, &boneNodeArray);

                fStack_ac = outRow[1];
                fStack_b4 = outRow[2];
                outRow[8] = (float)boneNodeArray;

                // Use some context fields for velocity damping
                iVar5 = *(int *)(context + 0x18);
                fVar10 = *(float *)(boneDataOffset + 0x68) * outRow[6] +
                         *(float *)(boneDataOffset + 100) * outRow[5] +
                         *(float *)(boneDataOffset + 0x60) * outRow[4];
                fStack_b0 = *(float *)(iVar5 + 0x1b4);
                fStack_20 = fStack_ac - *(float *)(iVar5 + 0x134);
                fVar13 = fStack_b4 - *(float *)(iVar5 + 0x138);
                fStack_34 = (fStack_b0 * fVar13 - *(float *)(iVar5 + 0x1b8) * fStack_20) +
                            *(float *)(iVar5 + 0x1a0);
                fVar12 = outRow[0] - *(float *)(iVar5 + 0x130);
                fStack_a4 = outRow[0] - *(float *)((int)fVar6 + 0x130);
                fStack_a0 = fStack_ac - *(float *)((int)fVar6 + 0x134);
                fVar11 = fStack_b4 - *(float *)((int)fVar6 + 0x138);
                fStack_a8 = *(float *)((int)fVar6 + 0x1b4);

                if (fVar10 < DAT_00e44564 - *(float *)(*(int *)(context + 0x1c) + 0x84)) {
                    fVar10 = DAT_00e2eff4 / fVar10;
                    outRow[0xc] = fVar10 * (outRow[6] * 
                        ((*(float *)(iVar5 + 0x1a8) +
                          (*(float *)(iVar5 + 0x1b0) * fStack_20 - fStack_b0 * fVar12)) -
                         (*(float *)((int)fVar6 + 0x1a8) +
                          (*(float *)((int)fVar6 + 0x1b0) * fStack_a0 - fStack_a8 * fStack_a4))) +
                        outRow[5] *
                        ((*(float *)(iVar5 + 0x1a4) +
                          (*(float *)(iVar5 + 0x1b8) * fVar12 - *(float *)(iVar5 + 0x1b0) * fVar13)) -
                         (*(float *)((int)fVar6 + 0x1a4) +
                          (*(float *)((int)fVar6 + 0x1b8) * fStack_a4 - *(float *)((int)fVar6 + 0x1b0) * fVar11))) +
                        outRow[4] *
                        (fStack_34 -
                         ((fStack_a8 * fVar11 - *(float *)((int)fVar6 + 0x1b8) * fStack_a0) +
                          *(float *)((int)fVar6 + 0x1a0))));
                    fStack_84 = DAT_00e2b1a4;
                    outRow[0xd] = fVar10;
                } else {
                    outRow[0xc] = 0.0f;
                    fStack_84 = DAT_00e2b1a4;
                    outRow[0xd] = DAT_00e2b1a4 / *(float *)(*(int *)(context + 0x1c) + 0x84);
                }
            }

            outRow[0xd] = fStack_84;

            cVar4 = (char)boneLoopIndex + 1;
            boneLoopIndex = ((boneLoopIndex & 0xffffff00) | (cVar4 & 0xff));
        } while (cVar4 < *(char *)(*(int *)(context + 0x1c) + 0x20));
    }
    return;
}