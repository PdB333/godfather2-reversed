// FUNC_NAME: DebugManager::displayDebugItems
undefined1 DebugManager::displayDebugItems(undefined4 param_1, undefined4 param_2, undefined4 *param_3) {
    char cVar1;
    undefined1 uVar2;
    int iVar3;
    int *piVar4;
    undefined1 *puVar5;
    undefined1 *puStack_40;
    int iStack_3c;
    code *pcStack_34;
    undefined **local_30;
    int local_2c;
    undefined4 local_28;
    undefined4 local_24;
    char local_20;
    undefined4 local_1c;
    uint local_18;
    undefined4 local_14;
    undefined4 local_10;
    code *local_c;

    iVar3 = FUN_0068f700(param_1);
    if (iVar3 == 0) {
        return 0;
    }
    local_24 = *(undefined4 *)(iVar3 + 4); // +0x04: maybe item type or flags
    local_28 = 7; // default text color?
    if ((*(char *)(DAT_012233b4 + 0x568) == '\x12') || (*(int *)(iVar3 + 0xc) == 0)) {
        local_28 = 3; // change color if condition met
    }
    local_2c = 0;
    local_30 = &PTR_FUN_00d5c878; // global debug item vtable
    local_20 = '\0';
    local_1c = 0xffffffff;
    local_18 = 0;
    local_14 = 0;
    local_10 = 0;
    local_c = (code *)0x0;
    FUN_00495960(); // begin enumeration
    cVar1 = FUN_00495980(); // hasMoreItems
    while (cVar1 != '\0') {
        piVar4 = (int *)FUN_004959c0(); // getNextItem
        (**(code **)(*piVar4 + 0x14))(&local_30); // call virtual method at vtable+0x14
        cVar1 = FUN_00495980();
    }
    if (local_2c != 4) {
        cVar1 = FUN_0068e3b0(*(undefined4 *)(iVar3 + 8), param_2, param_3); // print with format string from +0x08
        if (cVar1 == '\0') {
            if (local_20 == '\0') {
                if (local_18 == 0) {
                    return 0;
                }
                (*local_c)(local_18); // call callback with data
                return 0;
            }
            if ((char)param_2 != '\0') {
                _memset((void *)*param_3, 0, param_3[2]);
            }
            FUN_004d3b50(&local_18); // release string?
            if (puStack_40 != (undefined1 *)0x0) {
                (*pcStack_34)(puStack_40);
            }
            if (iStack_3c != 0) {
                FUN_0068e0a0("[c=CUSTOM1]"); // set custom color
                FUN_004d3b50(&local_18); // release again?
                puVar5 = puStack_40;
                if (puStack_40 == (undefined1 *)0x0) {
                    puVar5 = &DAT_0120546e;
                }
                FUN_0068e0a0(puVar5); // print additional string
                if (puStack_40 != (undefined1 *)0x0) {
                    (*pcStack_34)(puStack_40);
                }
                FUN_0068e0a0("[c=RESET]"); // reset color
            }
        }
        if (local_18 != 0) {
            (*local_c)(local_18);
        }
        return 1;
    }
    uVar2 = FUN_0068e3b0(*(undefined4 *)(iVar3 + 0xc), param_2, param_3); // alternative format for type 4
    if (local_18 != 0) {
        (*local_c)(local_18);
    }
    return uVar2;
}