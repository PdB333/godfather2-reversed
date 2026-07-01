// FUNC_NAME: CoverSystem::sampleCoverPositions

uint __thiscall CoverSystem::sampleCoverPositions(CoverSystem* this, uint param_2, CoverSamplePoint* outPoints, uint maxPoints) {
    float* pfVar1;
    float fVar2;
    char cVar3;
    uint uVar4;
    int iVar5;
    uint uVar6;
    uint uVar7;
    uint uVar8;
    float fVar9;
    int iVar10;
    undefined4* puVar11;
    float* pfVar12;
    float10 fVar13;
    float fVar14;
    uint hintCount;
    uint randomHintIndex;
    float radiusMargin;
    uint childIndex;
    uint randomChildIndex;
    int numSteps;
    uint local_10c8;
    int local_10c4;
    uint* local_10c0;
    float stepSizeInverse;
    undefined4 local_10b8;
    float fStackLocal;
    undefined4 local_10b0;
    undefined4 local_10ac;
    undefined4 local_10a8;
    uint local_10a4;
    float vecDiffX;
    float vecDiffY;
    float vecDiffZ;
    undefined4 padding;
    float fVar15;
    float fVar16;
    float fVar17;
    undefined4 padding2;
    float fStackL;
    float fStackL1;
    float fStackL2;
    float fStackL3;
    float fStackL4;
    float fStackL5;
    int childList[2];
    float* childListNode;
    undefined1 rayInfo[12];
    undefined1 coverQueryInput[12];
    undefined1 coverQueryOutput[4];
    uint hintNodeCount;
    undefined4 local_1014;
    float hintNodeData[768];  // 256 entries * 3 floats (positions/pointers)
    undefined4 hintNodeIds[255];
    undefined4 local_14;

    local_14 = 0x83d5b0;
    // Compute ray parameters from cover system context
    computeRayInfo((undefined4*)&local_10a8, (undefined4*)&local_10b0, (undefined4*)&local_10b8, (undefined4*)&local_10ac, rayInfo, coverQueryInput);
    // Initialize cover sampling: sets up the ray/sampling context
    initCoverSampling(this, this->unkField_0x15, local_10a8, local_10b0, local_10b8, local_10ac, rayInfo);
    // Query the cover node spatial index: returns number of relevant nodes and fills hintNodeData/hintNodeIds
    hintNodeCount = queryCoverNodes(coverQueryInput, coverQueryOutput, local_1014);
    if (hintNodeCount != 0) {
        if (hintNodeCount < 2) {
            randomHintIndex = 0;
        }
        else {
            randomHintIndex = rand();
            randomHintIndex = randomHintIndex % hintNodeCount;
        }
        hintCount = 0;
        local_10a4 = randomHintIndex;
        do {
            fVar2 = hintNodeData[randomHintIndex * 3];  // first field: usually a node kind or flag
            if (fVar2 == 0.0) {
                pfVar12 = (float*)0x0;
            }
            else {
                pfVar12 = (float*)hintNodeData[randomHintIndex * 3 + 2];  // third field: pointer to node position
            }
            // Check if we are in complex sampling mode (bit 10 of this->flags at +0xA8)
            if (((uint)this->field_0xa8 >> 10 & 1) == 0) {
                // Simple mode: just copy the node's position as a sample point
                pfVar1 = (float*)((int)outPoints + hintCount * 0x18);
                fVar13 = (float10)(**(code**)(*this + 0x40))(hintNodeIds[randomHintIndex], pfVar12);
                hintCount = hintCount + 1;
                *pfVar1 = (float)fVar13;  // distance from source? Or sample weight
                *(undefined8*)(pfVar1 + 1) = *(undefined8*)pfVar12;  // copy x,y
                pfVar1[3] = pfVar12[2];  // z
                pfVar1[4] = (float)pfVar12;  // pointer stored as float? Actually stores the node pointer in the sample
                pfVar1[5] = fVar2;  // node flag
            }
            else {
                // Complex sampling mode: perform detailed line-of-sight tests between children of this node
                local_10c4 = 0;
                local_10c0 = (uint*)0x0;
                radiusMargin = 0.0;
                cVar3 = getTerrainFlag(*(undefined2*)((int)pfVar12 + 0x12), 0x48043505, &local_10c4);
                if (cVar3 != '\0') {
                    uVar4 = 0;
                    if (((local_10c0 != (uint*)0x0) && (local_10c4 != 0)) &&
                        (*(char*)(local_10c4 + 6) == '\x02')) {
                        uVar4 = *local_10c0;
                    }
                    if ((uVar4 & 2) != 0) {
                        radiusMargin = DAT_00d5779c;  // some constant radius margin
                    }
                }
                uVar4 = (uint)*(byte*)(pfVar12 + 5);  // number of direct children (first set)
                if (uVar4 != 0) {
                    if (uVar4 < 2) {
                        childIndex = 0;
                    }
                    else {
                        childIndex = rand();
                        childIndex = childIndex % uVar4;
                    }
                    local_10e4 = childIndex;
                    randomChildIndex = childIndex;
                    do {
                        iVar5 = (uint)(ushort)(*(short*)(pfVar12 + 4) + (short)local_10e4) * 0x10 +
                                *(int*)((int)fVar2 + 0x24);
                        pfVar1 = (float*)(*(int*)((int)fVar2 + 0x20) + (uint)*(ushort*)(iVar5 + 4) * 0x24);
                        cVar3 = (**(code**)(*this + 0x30))(fVar2, iVar5);
                        if ((cVar3 != '\0') &&
                            (cVar3 = lineOfSightCheck(fVar2, pfVar12, fVar2, pfVar1, hintNodeData, randomHintIndex),
                             cVar3 != '\0')) {
                            vecDiffX = *pfVar1 - *pfVar12;
                            vecDiffY = pfVar1[1] - pfVar12[1];
                            vecDiffZ = pfVar1[2] - pfVar12[2];
                            padding = 0;
                            fVar13 = (float10)vectorLength(&vecDiffX, &vecDiffX);
                            fVar14 = (float)(fVar13 - (float10)radiusMargin);
                            cVar3 = getTerrainFlag(*(undefined2*)((int)pfVar1 + 0x12), 0x48043505, &local_10c4);
                            if (cVar3 != '\0') {
                                uVar6 = 0;
                                if (((local_10c0 != (uint*)0x0) && (local_10c4 != 0)) &&
                                    (*(char*)(local_10c4 + 6) == '\x02')) {
                                    uVar6 = *local_10c0;
                                }
                                if ((uVar6 & 2) != 0) {
                                    fVar14 = fVar14 - DAT_00d5779c;
                                }
                            }
                            if (radiusMargin < fVar14) {
                                stepSize = (int)(longlong)ROUND((1.0 / (float)this->field_0x14) * (fVar14 - radiusMargin));
                                uVar6 = stepSize + 1;
                                fVar9 = radiusMargin;
                                if (1 < uVar6) {
                                    uVar7 = rand();
                                    fVar9 = (float)(int)(uVar7 % uVar6);
                                    if ((int)(uVar7 % uVar6) < 0) {
                                        fVar9 = fVar9 + DAT_00e44578;
                                    }
                                    fVar9 = fVar9 * (float)this->field_0x14 + radiusMargin;
                                }
                                local_10f0 = 0;
                                puVar11 = (undefined4*)((int)outPoints + hintCount * 0x18 + 0x10);
                                fStack_10b4 = fVar9;
                                do {
                                    fStack_1074 = vecDiffX * fStack_10b4 + *pfVar12;
                                    fStack_1070 = vecDiffY * fStack_10b4 + pfVar12[1];
                                    fStack_106c = vecDiffZ * fStack_10b4 + pfVar12[2];
                                    fVar9 = fVar2;
                                    if (fStack_10b4 != _DAT_00d577a0) {
                                        fVar9 = 0.0;
                                    }
                                    iVar5 = (**(code**)(*this + 0x20))(fVar9, pfVar12, &fStack_1074, rayInfo, local_10a8, local_10b0, local_10b8, local_10ac);
                                    if (iVar5 != 3) {
                                        fVar13 = (float10)(**(code**)(*this + 0x40))(iVar5, pfVar12);
                                        puVar11[-4] = (float)fVar13;
                                        hintCount = hintCount + 1;
                                        *(ulonglong*)(puVar11 + -3) = CONCAT44(fStack_1070, fStack_1074);
                                        puVar11[-1] = fStack_106c;
                                        *puVar11 = pfVar12;
                                        puVar11[1] = fVar2;
                                        puVar11 = puVar11 + 6;
                                    }
                                    fStack_10b4 = (float)this->field_0x14 + fStack_10b4;
                                    if (fVar14 < fStack_10b4) {
                                        fStack_10b4 = radiusMargin;
                                    }
                                    local_10f0 = local_10f0 + 1;
                                } while ((local_10f0 < uVar6) && (hintCount < maxPoints));
                            }
                        }
                        local_10e4 = local_10e4 + 1;
                        if (uVar4 <= local_10e4) {
                            local_10e4 = 0;
                        }
                    } while ((local_10e4 != randomChildIndex) && (hintCount < maxPoints));
                }
                // Second set of children (offset +7 and +0x15 in pfVar12)
                uVar4 = (uint)*(byte*)(pfVar12 + 7) + (uint)*(byte*)((int)pfVar12 + 0x15);
                if (uVar4 != 0) {
                    if (uVar4 < 2) {
                        local_10e4 = 0;
                        uVar6 = local_10e4;
                    }
                    else {
                        local_10e4 = rand();
                        local_10e4 = local_10e4 % uVar4;
                        uVar6 = local_10e4;
                    }
                    do {
                        iVar10 = (uint)(ushort)(*(short*)((int)pfVar12 + 0x16) + (short)local_10e4) * 0x10 +
                                 *(int*)((int)fVar2 + 0x30);
                        getDirectChildList(childList, iVar10);
                        pfVar1 = childListNode;
                        iVar5 = childList[0];
                        if (((childList[0] != 0) &&
                            (cVar3 = (**(code**)(*this + 0x34))(fVar2, iVar10), cVar3 != '\0')) &&
                            (cVar3 = lineOfSightCheck(fVar2, pfVar12, iVar5, pfVar1, hintNodeData, randomHintIndex),
                             cVar3 != '\0')) {
                            vecDiffX = *pfVar1 - *pfVar12;
                            vecDiffY = pfVar1[1] - pfVar12[1];
                            vecDiffZ = pfVar1[2] - pfVar12[2];
                            padding2 = 0;
                            fVar13 = (float10)vectorLength(&vecDiffX, &vecDiffX);
                            fVar14 = (float)(fVar13 - (float10)radiusMargin);
                            cVar3 = getTerrainFlag(*(undefined2*)((int)pfVar1 + 0x12), 0x48043505, &local_10c4);
                            if (cVar3 != '\0') {
                                uVar7 = 0;
                                if (((local_10c0 != (uint*)0x0) && (local_10c4 != 0)) &&
                                    (*(char*)(local_10c4 + 6) == '\x02')) {
                                    uVar7 = *local_10c0;
                                }
                                if ((uVar7 & 2) != 0) {
                                    fVar14 = fVar14 - DAT_00d5779c;
                                }
                            }
                            if (radiusMargin < fVar14) {
                                stepSize = (int)(longlong)ROUND((1.0 / (float)this->field_0x14) * (fVar14 - radiusMargin));
                                uVar7 = stepSize + 1;
                                fVar9 = radiusMargin;
                                if (1 < uVar7) {
                                    uVar8 = rand();
                                    fVar9 = (float)(int)(uVar8 % uVar7);
                                    if ((int)(uVar8 % uVar7) < 0) {
                                        fVar9 = fVar9 + DAT_00e44578;
                                    }
                                    fVar9 = fVar9 * (float)this->field_0x14 + radiusMargin;
                                }
                                local_10dc = 0;
                                puVar11 = (undefined4*)((int)outPoints + hintCount * 0x18 + 0x10);
                                fStack_10bc = fVar9;
                                do {
                                    fStack_1068 = vecDiffX * fStack_10bc + *pfVar12;
                                    fStack_1064 = vecDiffY * fStack_10bc + pfVar12[1];
                                    fStack_1060 = vecDiffZ * fStack_10bc + pfVar12[2];
                                    fVar9 = fVar2;
                                    if (fStack_10bc != _DAT_00d577a0) {
                                        fVar9 = 0.0;
                                    }
                                    iVar5 = (**(code**)(*this + 0x20))(fVar9, pfVar12, &fStack_1068, rayInfo, local_10a8, local_10b0, local_10b8, local_10ac);
                                    if (iVar5 != 3) {
                                        fVar13 = (float10)(**(code**)(*this + 0x40))(iVar5, pfVar12);
                                        puVar11[-4] = (float)fVar13;
                                        hintCount = hintCount + 1;
                                        *(ulonglong*)(puVar11 + -3) = CONCAT44(fStack_1064, fStack_1068);
                                        puVar11[-1] = fStack_1060;
                                        *puVar11 = pfVar12;
                                        puVar11[1] = fVar2;
                                        puVar11 = puVar11 + 6;
                                    }
                                    fStack_10bc = (float)this->field_0x14 + fStack_10bc;
                                    if (fVar14 < fStack_10bc) {
                                        fStack_10bc = radiusMargin;
                                    }
                                    local_10dc = local_10dc + 1;
                                } while ((local_10dc < uVar7) && (hintCount < maxPoints));
                            }
                        }
                        local_10e4 = local_10e4 + 1;
                        if (uVar4 <= local_10e4) {
                            local_10e4 = 0;
                        }
                        if (childList[0] != 0) {
                            releaseChildList(childList);
                        }
                    } while ((local_10e4 != uVar6) && (hintCount < maxPoints));
                }
            }
            randomHintIndex = randomHintIndex + 1;
            if (hintNodeCount <= randomHintIndex) {
                randomHintIndex = 0;
            }
        } while ((randomHintIndex != local_10a4) && (hintCount < maxPoints));
        qsort(outPoints, hintCount, 0x18, (_PtFuncCompare*)&LAB_0083b4c0);
        cleanupCoverSampling();
        return hintCount;
    }
    cleanupCoverSampling();
    return 0;
}