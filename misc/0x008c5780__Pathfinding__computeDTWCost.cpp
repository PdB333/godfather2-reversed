// FUNC_NAME: Pathfinding::computeDTWCost
float computeDTWCost(int* sequenceA, int* sequenceB, int costType)
{
    int iVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    char cVar5;
    int iVar6;
    int iVar7;
    float fVar8;
    float fVar9;
    int local_58;
    undefined4 local_54;
    undefined4 local_50;
    int local_4c;
    undefined4 local_48;
    undefined4 local_44;
    int local_40;
    int local_3c;
    int local_34;
    int local_30;
    float local_28;
    float local_24;
    int local_20 [3];
    int local_14 [3];
    float local_8;
    float local_4;
    
    local_4c = 0;
    local_48 = 0;
    local_44 = 0;
    local_58 = 0;
    local_54 = 0;
    local_50 = 0;
    // Build cost matrix from sequences
    buildCostMatrix(&local_4c, &local_58, sequenceA, sequenceB, costType);
    // Initialize DTW accumulation arrays
    initDTWArrays(local_20, &local_4c, &local_58, *(undefined4 *)(sequenceB + 0x68), sequenceB, costType);
    // Clear arrays
    clearArray(local_20);
    clearArray(local_14);
    
    sequenceB = 0;
    sequenceA = 100;
    iVar1 = local_40;
    iVar7 = local_3c;
    iVar2 = local_34;
    iVar6 = local_30;
    fVar8 = local_8;
    local_28 = local_8;
    fVar9 = local_4;
    local_24 = local_4;
    
    do {
        while ((iVar4 = local_34, iVar3 = local_40, local_40 = iVar1, local_34 = iVar2, iVar7 != 0 &&
               (iVar6 != 0))) {
            cVar5 = compareCosts(local_28, local_24);
            iVar1 = local_40;
            iVar2 = local_34;
            if (cVar5 == '\0') {
                fVar8 = fVar8 - *(float *)(iVar3 + -4 + iVar7 * 4);
                iVar7 = iVar7 + -1;
                local_28 = fVar8;
                local_34 = iVar4;
                local_40 = iVar3;
            }
            else {
                fVar9 = fVar9 - *(float *)(iVar4 + -4 + iVar6 * 4);
                iVar6 = iVar6 + -1;
                local_24 = fVar9;
                local_34 = iVar4;
                local_40 = iVar3;
            }
        }
        if (iVar6 == 0) {
            sequenceB = sequenceB + 1;
        }
        local_3c = iVar7;
        local_30 = iVar6;
        resetArray(local_20);
        resetArray(local_14);
        sequenceA = sequenceA + -1;
        local_28 = local_8;
        local_24 = local_4;
        iVar1 = local_40;
        iVar7 = local_3c;
        iVar2 = local_34;
        iVar6 = local_30;
        fVar8 = local_8;
        fVar9 = local_4;
    } while (sequenceA != 0);
    
    if ((costType != 1) && (costType != 2)) {
        sequenceB = 100 - sequenceB;
    }
    fVar8 = (float)sequenceB;
    if (sequenceB < 0) {
        fVar8 = fVar8 + DAT_00e44578;
    }
    fVar8 = fVar8 * DAT_00d5ef84;
    
    if (local_34 != 0) {
        freeMemory(local_34);
    }
    if (local_40 != 0) {
        freeMemory(local_40);
    }
    if (local_14[0] != 0) {
        freeMemory(local_14[0]);
    }
    if (local_20[0] != 0) {
        freeMemory(local_20[0]);
    }
    if (local_58 != 0) {
        freeMemory(local_58);
    }
    if (local_4c != 0) {
        freeMemory(local_4c);
    }
    return (float10)fVar8;
}