// FUNC_NAME: NetConnection::queuePacket
void NetConnection::queuePacket(int *param_1, int param_2, undefined4 param_3, int param_4, int param_5, int param_6, int param_7)
{
    int *piVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    int unaff_FS_OFFSET;
    
    iVar2 = **(int **)(unaff_FS_OFFSET + 0x2c);
    iVar3 = *(int *)(iVar2 + 0x34);
    if (((iVar3 != 1) || (*param_1 == 0)) || (iVar4 = 1, param_7 == 2)) {
        piVar1 = param_1 + (uint)(iVar3 != 0) * 0x26 + 1;
        if (iVar3 == 0) {
            if (param_2 == DAT_012054f0) {
                param_5 = 8;
            }
            else {
                param_5 = FUN_004e9d00();
                param_6 = FUN_004e9d40();
            }
        }
        iVar4 = *(int *)(iVar2 + 0x34);
        piVar1[*piVar1 * 4 + 2] = param_2;
        piVar1[*piVar1 * 4 + 3] = param_4;
        piVar1[(*piVar1 + 1) * 4] = param_5;
        piVar1[*piVar1 * 4 + 5] = param_6;
        if ((iVar4 != 0) && (*(int *)(param_2 + 0x178) != 0)) {
            FUN_004e9a30(param_3);
        }
        *piVar1 = *piVar1 + 1;
    }
    if (((iVar4 == 1) && (*param_1 != 0)) || (param_7 == 2)) {
        FUN_004ea470(param_2, param_3, param_4, param_5, param_6, iVar4 != 0);
    }
    return;
}