//FUNC_NAME: TargetingManager::isTargetValid
bool __thiscall TargetingManager::isTargetValid(int param_1)
{
    uint uVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    int iVar5;
    byte bVar6;
    int *thisPtr; // in_EAX
    char *pcVar7;
    uint uVar8;
    uint uVar9;
    uint uVar10;
    int *piVar11;
    bool bVar12;

    iVar4 = param_1;
    // Check if the manager is active (field at +0x1C? Actually in_EAX[7] is offset 28)
    bVar12 = thisPtr[7] == 0; // +0x1C? Wait: in_EAX is int*, so in_EAX[7] is offset 28 bytes
    if (bVar12) {
        return bVar12;
    }
    // Traverse linked list starting from param_1+0xC (next pointer)
    iVar5 = *(int *)(param_1 + 0xc); // param_1->next
    iVar3 = param_1;
    while (iVar2 = iVar5, iVar2 != 0) {
        iVar3 = iVar2;
        iVar5 = *(int *)(iVar2 + 0xc);
    }
    // Virtual call: get vtable from this, offset 0x70, then +0x14, then +4
    // Returns a char* (probably a debug string or target name)
    pcVar7 = (char *)(**(code **)(*(int *)(*(int *)(*thisPtr + 0x70) + 0x14) + 4))
                             (&param_1, thisPtr[2], iVar3);
    if (*pcVar7 != '\0') {
        uVar1 = thisPtr[6]; // +0x18? field at offset 24
        if ((1 < uVar1) && (uVar8 = FUN_005566a0(iVar3, *(undefined4 *)(iVar4 + 4)), uVar8 != 0)) {
            uVar8 = FUN_005413f0(uVar8 >> 2 | 0x80000000);
            bVar6 = FUN_00541470(*(undefined4 *)(iVar3 + 0x1c));
            uVar10 = 1;
            if (1 < uVar1) {
                piVar11 = thisPtr + 3; // +0xC? array of pointers?
                do {
                    uVar9 = FUN_005414c0(*(undefined4 *)(*piVar11 + 0x24));
                    if (((1 << (bVar6 & 0x1f) & uVar9) != 0) && (uVar9 = FUN_00541430(), (uVar8 & uVar9) == 0)) {
                        return false;
                    }
                    uVar10 = uVar10 + 1;
                    piVar11 = piVar11 + 1;
                } while (uVar10 < uVar1);
            }
        }
        return true;
    }
    return bVar12;
}