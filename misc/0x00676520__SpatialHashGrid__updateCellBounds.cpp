// FUNC_NAME: SpatialHashGrid::updateCellBounds
void SpatialHashGrid::updateCellBounds(int this)
{
    int *piVar1;
    int *piVar2;
    int *piVar3;
    int iVar4;
    int iVar5;
    undefined4 *puVar6;
    int iVar7;
    int minX;
    int maxX;
    int local_8;
    int local_4;
    
    iVar5 = *(int *)(this + 0xd4); // +0xD4: firstActiveCellX
    iVar4 = *(int *)(this + 0xd8); // +0xD8: lastActiveCellX
    local_8 = 0x7fffffff;
    minX = 0x7fffffff;
    piVar2 = (int *)0x0;
    local_4 = -0x7fffffff;
    maxX = -0x7fffffff;
    
    if (iVar4 < iVar5) goto LAB_00676615;
    
    piVar3 = (int *)(*(int *)(this + 0xcc) + iVar5 * 4); // +0xCC: cellArray
    do {
        piVar2 = (int *)*piVar3;
        if (piVar2 != (int *)0x0) {
            iVar7 = iVar5 * 0x40 + 0x20; // cell center X = cellIndex * 64 + 32
            if (iVar7 < 0x7fffffff) {
                minX = iVar7;
            }
            if (iVar4 < iVar5) goto LAB_006765a5;
            piVar3 = (int *)(*(int *)(this + 0xcc) + iVar4 * 4);
            goto LAB_00676593;
        }
        iVar5 = iVar5 + 1;
        piVar3 = piVar3 + 1;
    } while (iVar5 <= iVar4);
    goto LAB_006765b9;
    
LAB_006765a5:
    iVar7 = iVar4 * 0x40 + 0x20;
    if (-0x7fffffff < iVar7) {
        maxX = iVar7;
    }
    goto LAB_006765b9;
    
    while( true ) {
        iVar4 = iVar4 + -1;
        piVar3 = piVar3 + -1;
        if (iVar4 < iVar5) break;
LAB_00676593:
        piVar2 = (int *)*piVar3;
        if (piVar2 != (int *)0x0) goto LAB_006765a5;
    }
    
LAB_006765b9:
    if (iVar5 <= iVar4) {
        piVar3 = (int *)(*(int *)(this + 0xcc) + iVar5 * 4);
        iVar7 = (iVar4 - iVar5) + 1;
        do {
            piVar2 = (int *)*piVar3;
            if (piVar2 != (int *)0x0) {
                if (*piVar2 >> 1 < minX) {
                    minX = *piVar2 >> 1;
                }
                for (piVar1 = (int *)piVar2[1]; piVar1 != (int *)0x0; piVar1 = (int *)piVar1[1]) {
                    piVar2 = piVar1;
                }
                if (maxX < *piVar2 >> 1) {
                    maxX = *piVar2 >> 1;
                }
            }
            piVar3 = piVar3 + 1;
            iVar7 = iVar7 + -1;
        } while (iVar7 != 0);
    }
    
LAB_00676615:
    *(int *)(this + 0xd4) = iVar5; // +0xD4: firstActiveCellX
    *(int *)(this + 0xd8) = iVar4; // +0xD8: lastActiveCellX
    
    if (*(char *)(this + 0x2209) != '\0') { // +0x2209: hasSecondaryGrid
        iVar5 = *(int *)(this + 0x164); // +0x164: firstActiveCellY
        iVar4 = *(int *)(this + 0x168); // +0x168: lastActiveCellY
        if (iVar4 < iVar5) {
            if (piVar2 != (int *)0x0) {
LAB_0067665d:
                iVar7 = iVar5 * 0x40 + 0x20;
                if (iVar7 < minX) {
                    minX = iVar7;
                }
            }
            if (iVar4 < iVar5) {
                if (piVar2 != (int *)0x0) {
LAB_00676694:
                    iVar7 = iVar4 * 0x40 + 0x20;
                    if (maxX < iVar7) {
                        maxX = iVar7;
                    }
                }
            }
            else {
                piVar2 = (int *)(*(int *)(this + 0x15c) + iVar4 * 4); // +0x15C: cellArrayY
                do {
                    if (*piVar2 != 0) goto LAB_00676694;
                    iVar4 = iVar4 + -1;
                    piVar2 = piVar2 + -1;
                } while (iVar5 <= iVar4);
            }
        }
        else {
            puVar6 = (undefined4 *)(*(int *)(this + 0x15c) + iVar5 * 4);
            do {
                piVar2 = (int *)*puVar6;
                if (piVar2 != (int *)0x0) goto LAB_0067665d;
                iVar5 = iVar5 + 1;
                puVar6 = puVar6 + 1;
            } while (iVar5 <= iVar4);
        }
        *(int *)(this + 0x164) = iVar5; // +0x164: firstActiveCellY
        *(int *)(this + 0x168) = iVar4; // +0x168: lastActiveCellY
        
        if (iVar5 <= iVar4) {
            piVar2 = (int *)(*(int *)(this + 0x15c) + iVar5 * 4);
            iVar5 = (iVar4 - iVar5) + 1;
            do {
                piVar3 = (int *)*piVar2;
                if (piVar3 != (int *)0x0) {
                    if (*piVar3 >> 1 < local_8) {
                        local_8 = *piVar3 >> 1;
                    }
                    for (piVar1 = (int *)piVar3[1]; piVar1 != (int *)0x0; piVar1 = (int *)piVar1[1]) {
                        piVar3 = piVar1;
                    }
                    if (local_4 < *piVar3 >> 1) {
                        local_4 = *piVar3 >> 1;
                    }
                }
                piVar2 = piVar2 + 1;
                iVar5 = iVar5 + -1;
            } while (iVar5 != 0);
        }
    }
    
    if (maxX < minX) {
        maxX = 0;
        minX = 0;
    }
    if (local_4 < local_8) {
        local_4 = 0;
        local_8 = 0;
    }
    
    *(int *)(this + 0x28) = minX;   // +0x28: boundsMinX
    *(int *)(this + 0x2c) = maxX;   // +0x2C: boundsMaxX
    *(int *)(this + 0x30) = local_8; // +0x30: boundsMinY
    *(int *)(this + 0x34) = local_4; // +0x34: boundsMaxY
    *(undefined4 *)(this + 0x24) = 1; // +0x24: boundsDirty = false
    
    return;
}