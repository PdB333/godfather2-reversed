// FUNC_NAME: TNLConnection::sendPacket
int * __thiscall TNLConnection::sendPacket(int thisPtr, undefined4 param_2, uint param_3, uint param_4, uint param_5)
{
    uint uVar1;
    undefined4 *puVar2;
    int *piVar3;
    int *piVar4;
    uint *puVar5;
    bool bVar6;
    int *local_4;

    piVar4 = (int *)0x1;
    if (*(int *)(thisPtr + 0x40) != 0) {
        puVar2 = (undefined4 *)(*(int *)(thisPtr + 0x3c) + 4);
        piVar3 = (int *)0x1;
        do {
            piVar4 = piVar3;
            if (piVar3 < *(int **)*puVar2) break;
            piVar4 = (int *)((int)piVar3 + 1);
            puVar2 = puVar2 + 2;
            bVar6 = piVar3 < *(int **)(thisPtr + 0x40);
            piVar3 = piVar4;
        } while (bVar6);
    }
    local_4 = piVar4;
    local_4 = (int *)FUN_0098f800(&local_4);
    if ((*(int *)(thisPtr + 0x38) == 0) &&
       ((*(int *)(thisPtr + 0x34) == 0 || ((*(byte *)(thisPtr + 0x28) & 1) == 0)))) {
        FUN_004de190();
    }
    puVar5 = *(uint **)(thisPtr + 0x38);
    if (puVar5 != (uint *)0x0) {
        uVar1 = *puVar5;
        *(int *)(thisPtr + 0x14) = *(int *)(thisPtr + 0x14) + 1;
        *(int *)(thisPtr + 0x10) = *(int *)(thisPtr + 0x10) + -1;
        *(uint *)(thisPtr + 0x38) = uVar1;
        if (puVar5 != (uint *)0x0) {
            puVar5[1] = param_3;
            puVar5[3] = param_5;
            *puVar5 = (uint)piVar4;
            puVar5[2] = param_4;
            FUN_004d3bc0(param_2);
            goto LAB_0098f9bd;
        }
    }
    puVar5 = (uint *)0x0;
LAB_0098f9bd:
    *local_4 = (int)puVar5;
    *(int *)(thisPtr + 0x48) = *(int *)(thisPtr + 0x48) + param_4;
    return piVar4;
}