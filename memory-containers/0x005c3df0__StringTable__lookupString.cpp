// FUNC_NAME: StringTable::lookupString
int* StringTable::lookupString(int param_1, char* in_EAX) {
    char cVar1;
    char cVar2;
    char cVar3;
    char cVar4;
    uint uVar5;
    int* piVar6;
    char* in_EAX;
    int iVar7;
    int iVar8;
    uint uVar9;

    if ((in_EAX == (char *)0x0) || (*in_EAX == '\0')) {
        return (int *)0x0;
    }
    
    // Compute hash from the four first bytes of the string
    uVar5 = *(uint *)(param_1 + 0xc); // Hash table size (number of slots)
    uVar9 = *(int *)(&DAT_00f17684 + in_EAX[3] * 4) + (&DAT_00f17680)[in_EAX[2]] + (&DAT_00f17680)[*in_EAX] + (&DAT_00f17680)[in_EAX[1]];
    
    if (uVar9 < uVar5) {
        piVar6 = *(int **)(*(int *)(param_1 + 8) + uVar9 * 4); // Get entry from hash table
        if (*(char *)(param_1 + 0xc0) != '\0') { // If checking is disabled (e.g., no need to compare CRC)
            return piVar6;
        }
        if (piVar6 != (int *)0x0) {
            iVar7 = (**(code **)(*piVar6 + 4))(); // Get CRC of the string
            iVar8 = FUN_005bff40(); // Compute CRC of input string
            if (iVar7 == iVar8) {
                return piVar6;
            }
        }
    }
    
    if (*(char *)(param_1 + 0xc0) == '\0') { // Need to do CRC comparison
        cVar1 = *in_EAX;
        cVar2 = in_EAX[1];
        cVar3 = in_EAX[2];
        cVar4 = in_EAX[3];
        
        // Linear probing for collision chain
        while (uVar9 = uVar9 + 1, uVar9 < uVar5) {
            piVar6 = *(int **)(*(int *)(param_1 + 8) + uVar9 * 4);
            if ((piVar6 != (int *)0x0) && 
                (iVar7 = (**(code **)(*piVar6 + 4))(), // Get CRC of entry
                 iVar7 == ((cVar1 * 0x100 + (int)cVar2) * 0x100 + (int)cVar3) * 0x100 + (int)cVar4)) {
                return piVar6;
            }
        }
    }
    
    return (int *)0x0;
}