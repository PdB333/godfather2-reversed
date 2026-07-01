// FUNC_NAME: FamilyManager::updateFamilyMemberCounts
void __fastcall FamilyManager::updateFamilyMemberCounts(int this)
{
    uint *puVar1;
    char cVar2;
    int iVar3;
    int iVar4;
    uint uVar5;
    uint uVar6;
    int familyCounts[5]; // local_28, local_24, local_1c, local_14, local_c, local_4
    ulonglong local_24;
    undefined8 local_1c;
    ulonglong local_14;
    undefined8 local_c;
    undefined4 local_4;
    
    // Get total number of entities from global data
    uVar5 = *(uint *)(DAT_0112a558 + 0x38); // +0x38: entity count
    familyCounts[0] = 0;
    familyCounts[1] = 0;
    familyCounts[2] = 0;
    familyCounts[3] = 0;
    familyCounts[4] = 0;
    
    if (uVar5 != 0) {
        uVar6 = 0;
        do {
            iVar3 = FUN_006b0770(uVar6); // Get entity by index
            if (((iVar3 != 0) && (cVar2 = FUN_006b4440(), cVar2 != '\0')) && // Check if entity is a family member
               (cVar2 = FUN_00849ea0(*(undefined4 *)(iVar3 + 0x48)), cVar2 != '\0')) { // Check if entity is alive
                familyCounts[*(int *)(iVar3 + 0xc4)] = familyCounts[*(int *)(iVar3 + 0xc4)] + 1; // +0xc4: family ID
            }
            uVar6 = uVar6 + 1;
        } while (uVar6 < uVar5);
    }
    
    // Clear high bits of counts (only keep low 32 bits per family)
    familyCounts[1] = familyCounts[1] & 0xffffffff00000000;
    familyCounts[3] = familyCounts[3] & 0xffffffff;
    familyCounts[4] = 0;
    
    // Find the currently selected family member index
    if (*(uint *)(this + 0x78) < *(uint *)(this + 0x5c)) { // +0x78: current selection index, +0x5c: array size
        uVar5 = *(uint *)(*(int *)(this + 0x58) + *(uint *)(this + 0x78) * 4); // +0x58: family member array
    } else {
        uVar5 = 0xffffffff;
    }
    
    iVar3 = -1;
    *(undefined4 *)(this + 0x5c) = 0; // Reset array size
    FUN_009c8f10(*(undefined4 *)(this + 0x58)); // Free old array
    *(int *)(this + 0x58) = 0; // Clear array pointer
    *(undefined4 *)(this + 0x60) = 0; // +0x60: array capacity
    
    // Build new array of family IDs that have members
    uVar6 = 0;
    do {
        if (familyCounts[uVar6] != 0) {
            iVar4 = *(int *)(this + 0x60);
            if (*(int *)(this + 0x5c) == iVar4) {
                if (iVar4 == 0) {
                    iVar4 = 1;
                } else {
                    iVar4 = iVar4 * 2;
                }
                FUN_00951230(iVar4); // Resize array
            }
            puVar1 = (uint *)(*(int *)(this + 0x58) + *(int *)(this + 0x5c) * 4);
            *(int *)(this + 0x5c) = *(int *)(this + 0x5c) + 1;
            if (puVar1 != (uint *)0x0) {
                *puVar1 = uVar6; // Store family ID
            }
            if (uVar6 == uVar5) {
                iVar3 = *(int *)(this + 0x5c) + -1; // Track new index of previously selected family
            }
        }
        uVar6 = uVar6 + 1;
    } while (uVar6 < 10); // Max 10 families
    
    // If previously selected family still exists, keep its index; otherwise select first
    if ((iVar3 == -1) && (*(int *)(this + 0x5c) != 0)) {
        iVar3 = 0;
    }
    
    FUN_00952030(iVar3); // Update selection
    return;
}