// FUNC_NAME: AICharacter::handleMessage

void __thiscall AICharacter::handleMessage(int thisPtr, int *msg)
{
    char cVar1;
    int iVar2;
    int local_c[2];
    
    iVar2 = *msg;
    local_c[0] = thisPtr;
    if (iVar2 == EVENT_DAT_0120e93c) {
        iVar2 = FUN_00445ff0(thisPtr + 0x2c, 0);
        if ((iVar2 != 0) && (cVar1 = FUN_00475660(iVar2, 0x38523fc3, local_c), cVar1 != '\0')) {
            FUN_0044b210(local_c[0]);
        }
        FUN_004086d0(&EVENT_DAT_0120e93c);
        if (DAT_00e44598 < (float)((uint)*(float *)(thisPtr + 0x54) & DAT_00e44680)) {
            if ((*(int *)(thisPtr + 0x3c) == 0) || (*(int *)(thisPtr + 0x3c) == 0x48)) {
                *(uint *)(thisPtr + 0x58) = 3 - (uint)(*(char *)(thisPtr + 0x50) != '\0');
                return;
            }
            if (DAT_00e44598 <= (float)((uint)(*(float *)(thisPtr + 0x54) - DAT_00e2b1a4) & DAT_00e44680))
            {
LAB_0047d854:
                *(undefined4 *)(thisPtr + 0x58) = 3;
                return;
            }
            goto LAB_0047d92f;
        }
    }
    else {
        if (iVar2 == EVENT_DAT_012069f4) {
            (**(code **)(*(int *)(thisPtr + -0x40) + 4))();
            return;
        }
        if (iVar2 == *(int *)(thisPtr + 0x1c)) {
            (**(code **)(*(int *)(thisPtr + -0x40) + 8))();
            return;
        }
        if (iVar2 == *(int *)(thisPtr + 0x14)) {
            (**(code **)(*(int *)(thisPtr + -0x40) + 0xc))();
            return;
        }
        if (iVar2 != *(int *)(thisPtr + 0x24)) {
            return;
        }
        if (msg[1] == 0) {
            return;
        }
        iVar2 = *(int *)(msg[1] + 4);
        if (iVar2 == 0) {
            return;
        }
        iVar2 = iVar2 + -0x48;
        if (iVar2 == 0) {
            return;
        }
        FUN_0044b210(iVar2);
        if (DAT_00e44598 < (float)((uint)*(float *)(thisPtr + 0x54) & DAT_00e44680)) {
            if ((*(int *)(thisPtr + 0x3c) == 0) || (*(int *)(thisPtr + 0x3c) == 0x48)) {
                *(uint *)(thisPtr + 0x58) = 3 - (uint)(*(char *)(thisPtr + 0x50) != '\0');
                return;
            }
            if (DAT_00e44598 <= (float)((uint)(*(float *)(thisPtr + 0x54) - DAT_00e2b1a4) & DAT_00e44680))
                goto LAB_0047d854;
            goto LAB_0047d92f;
        }
    }
    if (*(char *)(thisPtr + 0x50) != '\0') {
        *(undefined4 *)(thisPtr + 0x58) = 2;
        return;
    }
    if ((*(int *)(thisPtr + 0x3c) == 0) || (*(int *)(thisPtr + 0x3c) == 0x48)) {
        *(undefined4 *)(thisPtr + 0x58) = 0;
        return;
    }
LAB_0047d92f:
    *(undefined4 *)(thisPtr + 0x58) = 1;
    return;
}