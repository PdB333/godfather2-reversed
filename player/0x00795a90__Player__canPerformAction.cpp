// FUNC_NAME: Player::canPerformAction
bool __thiscall Player::canPerformAction(int thisPtr, int *actionData, char param3)
{
    uint flags;
    bool isBusy;
    char cVar3;
    int iVar4;
    int *piVar5;
    bool bVar6;
    
    piVar5 = actionData;
    if (actionData == (int *)0x0) {
        actionData = (int *)0x0;
    }
    else {
        iVar4 = *actionData;
        actionData = (int *)0x0;
        cVar3 = (**(code **)(iVar4 + 0x10))(0x383225a1, &actionData);
        actionData = (int *)CONCAT31(actionData._1_3_, (-(uint)(cVar3 != '\0') & (uint)actionData) != 0);
    }
    
    // Check if player is busy (bit 0 of flags at +0x2BC)
    bVar6 = (*(byte *)(thisPtr + 700) & 1) != 0;
    flags = *(uint *)(thisPtr + 700);
    
    // Check various state flags: bit 6 (in combat?), bit 29 (driving?), bit 27 (falling?)
    if ((((flags >> 6 & 1) == 0) && ((flags >> 0x1d & 1) == 0)) && ((flags >> 0x1b & 1) == 0)) {
        bVar2 = false;
    }
    else {
        bVar2 = true;
    }
    
    if (bVar6) {
        return bVar6;
    }
    
    if (bVar2) {
        bVar6 = (bool)(char)actionData == bVar6;
        if (bVar6) {
            return bVar6;
        }
    }
    
    // Check if any of the 4 action slots (+0x40C to +0x418) are occupied
    if (((((*(int *)(thisPtr + 0x40c) != 0) || (*(int *)(thisPtr + 0x410) != 0)) ||
         ((*(int *)(thisPtr + 0x414) != 0 || (*(int *)(thisPtr + 0x418) != 0)))) && (param3 != '\0'))
        && ((iVar4 = FUN_00405a80(thisPtr + 0x40c), iVar4 == 0 ||
            (cVar3 = FUN_00411720(iVar4), cVar3 == '\0')))) {
        return true;
    }
    
    flags = *(uint *)(thisPtr + 700);
    // Check bit 9 (aiming?) and bit 19 (sprinting?)
    if (((((flags >> 9 & 1) == 0) || ((char)actionData == '\0')) ||
        (bVar6 = (bool)((byte)(flags >> 0x13) & 1), (flags >> 0x13 & 1) == 0)) &&
       (((flags >> 9 & 1) != 0 && ((flags >> 0x13 & 1) != 0)))) {
        if (piVar5 == (int *)0x0) {
            piVar5 = (int *)0x0;
        }
        else {
            piVar5 = (int *)FUN_0043b870(DAT_01131040);
        }
        // Check bit 18 (crouching?)
        if ((*(uint *)(thisPtr + 700) >> 0x12 & 1) == 0) {
            return true;
        }
        if (piVar5 == (int *)0x0) {
            return true;
        }
        cVar3 = (**(code **)(*piVar5 + 0x1c))(0x100);
        if (cVar3 == '\0') {
            return true;
        }
    }
    
    return bVar6;
}