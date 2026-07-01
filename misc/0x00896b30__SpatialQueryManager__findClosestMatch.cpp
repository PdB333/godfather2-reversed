// FUNC_NAME: SpatialQueryManager::findClosestMatch
char* __thiscall SpatialQueryManager::findClosestMatch(int this, uint typeMask, uint entityTypeMask, float maxDistSq, float minDotProduct, int queryType, char checkActive)
{
    uint uVar2 = DAT_01205220;
    float bestDistSq = DAT_00d5f6f0;
    char* bestMatch = (char*)0x0;
    double dVar9 = (double)minDotProduct;
    FUN_00b99e20(); // likely some frame/update function
    int iVar3 = FUN_00471610(); // get camera/player position
    float fVar10 = DAT_00e44564 - *(float*)(iVar3 + 0x20);
    float fVar11 = DAT_00e44564 - *(float*)(iVar3 + 0x24);
    float fVar8 = DAT_00e44564 - *(float*)(iVar3 + 0x28);
    uint uVar6 = 0;
    if (*(int*)(this + 0xc) == 0) {
        return (char*)0x0;
    }
    int iVar3 = 0;
    int local_30 = 0;
    do {
        if (((((*(uint*)(local_30 + *(int*)(this + 4)) & typeMask) != 0) &&
             (((pcVar7 = (char*)(*(int*)(this + 8) + iVar3),
               uVar2 <= (uint)(*(int*)(*(int*)(this + 8) + 0x28 + iVar3) + *(int*)(this + 0x14)
                              ) || (checkActive != '\0')) && (*pcVar7 != '\0')))) &&
            (*(float*)(pcVar7 + 0x14) < bestDistSq)) &&
           (((entityTypeMask == 0 ||
             ((*(int*)(pcVar7 + 0x24) != 0 && ((*(uint*)(*(int*)(pcVar7 + 0x24) + 4) & entityTypeMask) != 0)
              ))) && ((maxDistSq <= 0.0 || (*(float*)(pcVar7 + 0x14) <= maxDistSq * maxDistSq)))))) {
            if (0.0 < minDotProduct) {
                if (queryType == 0x80) {
                    pfVar4 = (float*)FUN_00471610();
                    local_18 = DAT_00e44564 - *pfVar4;
                    fStack_14 = DAT_00e44564 - pfVar4[1];
                    local_10 = DAT_00e44564 - pfVar4[2];
                }
                else {
                    if (queryType == 8) {
                        puVar5 = (undefined8*)FUN_00471610();
                        uVar1 = *puVar5;
                        local_10 = *(float*)(puVar5 + 1);
                    }
                    else {
                        uVar1 = CONCAT44(fVar11,fVar10);
                        local_10 = fVar8;
                    }
                    local_18 = (float)uVar1;
                    fStack_14 = (float)((ulonglong)uVar1 >> 0x20);
                }
                if (*(float*)(pcVar7 + 0x1c) * fStack_14 + *(float*)(pcVar7 + 0x18) * local_18 +
                    *(float*)(pcVar7 + 0x20) * local_10 < (float)dVar9) goto LAB_00896d23;
            }
            bestDistSq = *(float*)(pcVar7 + 0x14);
            bestMatch = pcVar7;
        }
LAB_00896d23:
        local_30 = local_30 + 0x10;
        uVar6 = uVar6 + 1;
        iVar3 = iVar3 + 0x2c;
        if (*(uint*)(this + 0xc) <= uVar6) {
            return bestMatch;
        }
    } while( true );
}