// FUNC_NAME: CommandSerializer::buildCommand
// function at 0x005c69d0 - builds a command packet with parameters (two variants based on global flag)
void CommandSerializer::buildCommand(int param_1, int param_2, int param_3, int param_4)
{
    uint *puVar2;
    int *piVar3;
    int *puVar4;

    if (DAT_0119d0ac == 1) { // global flag: possibly "isDon" or "isMultiplayer"
        if (1 < DAT_01205684) { // some thread safety / recursion guard
            puVar2 = (uint *)(DAT_01206880 + 0x14);
            **(void ***)(DAT_01206880 + 0x14) = &PTR_LAB_01126c08; // write type descriptor
            *puVar2 = *puVar2 + 4;
            *(char *)*puVar2 = 0; // write zero byte
            *puVar2 = *puVar2 + 4 & 0xfffffffc; // align to 4 bytes
        }
        int iVar1 = DAT_01206880;
        **(void ***)(DAT_01206880 + 0x14) = &PTR_LAB_01126bb8; // write another type descriptor
        *(int *)(iVar1 + 0x14) = *(int *)(iVar1 + 0x14) + 4;
        **(int **)(iVar1 + 0x14) = 8; // write length 8
        *(int *)(iVar1 + 0x14) = *(int *)(iVar1 + 0x14) + 4;
        piVar3 = (int *)(DAT_01206880 + 0x14);
        **(void ***)(DAT_01206880 + 0x14) = &PTR_LAB_01126b18; // write a third type descriptor
        *piVar3 = *piVar3 + 4;
        puVar4 = (int *)(*piVar3 + 3U & 0xfffffffc); // align
        *piVar3 = (int)puVar4;
        *puVar4 = 1; // write value 1
        puVar4 = (int *)(*piVar3 + 7U & 0xfffffffc); // align to 8
        *piVar3 = (int)puVar4;
        *puVar4 = 1; // write value 1
        puVar4 = (int *)(*piVar3 + 7U & 0xfffffffc); // another align
        *piVar3 = (int)puVar4;
        *puVar4 = 5; // command id 5
        *piVar3 = *piVar3 + 4;
        FUN_005c6b60(param_1, param_4); // finalize or send

        if (1 < DAT_01205684) {
            puVar2 = (uint *)(DAT_01206880 + 0x14);
            **(void ***)(DAT_01206880 + 0x14) = &PTR_LAB_01126c08;
            *puVar2 = *puVar2 + 4;
            *(char *)*puVar2 = 1; // write 1 byte
            *puVar2 = *puVar2 + 4 & 0xfffffffc;
        }
        iVar1 = DAT_01206880;
        **(void ***)(DAT_01206880 + 0x14) = &PTR_LAB_01126bb8;
        *(int *)(iVar1 + 0x14) = *(int *)(iVar1 + 0x14) + 4;
        **(int **)(iVar1 + 0x14) = 7; // length 7
        *(int *)(iVar1 + 0x14) = *(int *)(iVar1 + 0x14) + 4;
        piVar3 = (int *)(DAT_01206880 + 0x14);
        **(void ***)(DAT_01206880 + 0x14) = &PTR_LAB_01126b18;
        *piVar3 = *piVar3 + 4;
        puVar4 = (int *)(*piVar3 + 3U & 0xfffffffc);
        *piVar3 = (int)puVar4;
        *puVar4 = 1; // value 1
        puVar4 = (int *)(*piVar3 + 7U & 0xfffffffc);
        *piVar3 = (int)puVar4;
        *puVar4 = 7; // command id 7
        puVar4 = (int *)(*piVar3 + 7U & 0xfffffffc);
        *piVar3 = (int)puVar4;
        *puVar4 = 8; // command id 8
        *piVar3 = *piVar3 + 4;
        FUN_005c6b60(param_1, param_4);
        return;
    }
    FUN_005c6b60(param_1, param_4); // default branch: just finalize without additional data
    return;
}