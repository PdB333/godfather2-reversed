// FUNC_NAME: TriggerRegion::selectRandomSpawnPoint
int __thiscall TriggerRegion::selectRandomSpawnPoint(void)
{
    float fVar1;
    int *piVar2;
    bool bVar3;
    int iVar4;
    int iVar5;
    int iVar6;
    int iVar7;
    float fVar8;
    float fVar9;
    int candidateNodes [30];
    
    fVar9 = 0.0;
    iVar7 = 0;
    fVar8 = 0.0;
    if (gSpawnPointListHead != 0) {
        iVar5 = this->field_0C; // +0x0C (maybe sub-type)
        iVar4 = this->field_08; // +0x08 (maybe type)
        iVar6 = gSpawnPointListHead;
        do {
            piVar2 = *(int **)(iVar6 + 0x28); // pointer to SpawnPointData struct
            // Check if this spawn point matches the trigger region's criteria
            if ((((iVar4 == piVar2[2]) && (iVar5 == piVar2[3])) && (*(int *)this == *piVar2)) &&
               ((*(int *)((int)this + 4) == piVar2[1] && (fVar1 = (float)piVar2[4], 0.0 < fVar1)))) {
                if (0x1d < iVar7) break;
                candidateNodes[iVar7] = iVar6;
                fVar8 = fVar1 + fVar8;
                iVar7 = iVar7 + 1;
            }
            iVar6 = *(int *)(iVar6 + 0x24); // next node in linked list
        } while (iVar6 != 0);
        if (iVar7 != 0) {
            // Update global RNG state
            iVar4 = gRandomStateIndex + -1;
            iVar5 = gRandomStateIndex + 2;
            if (iVar4 < 0) {
                iVar4 = 0x13;
            }
            else if (0x13 < iVar5) {
                iVar5 = gRandomStateIndex + -0x12;
            }
            gRandomStateTable[iVar4] = gRandomStateTable[iVar4] + gRandomStateTable[iVar5];
            gRandomStateIndex = iVar4;
            iVar5 = 0;
            // Convert mantissa bits to float and scale totalWeight
            fVar8 = ((float)((gRandomStateTable[iVar4] & 0x7fffff | 0x3f800000) - 1.0f)) * fVar8;
            if (0 < iVar7) {
                do {
                    bVar3 = fVar9 <= fVar8;
                    fVar9 = *(float *)(*(int *)(candidateNodes[iVar5] + 0x28) + 0x10) + fVar9; // accumulate weight
                    if ((bVar3) && (fVar8 < fVar9)) {
                        return candidateNodes[iVar5];
                    }
                    iVar5 = iVar5 + 1;
                } while (iVar5 < iVar7);
            }
        }
    }
    return 0;
}