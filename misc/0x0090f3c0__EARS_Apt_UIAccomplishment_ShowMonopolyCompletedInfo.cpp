// Xbox PDB: EARS_Apt_UIAccomplishment_ShowMonopolyCompletedInfo
// FUNC_NAME: MonopolyManager::showSummaryScreen
void __fastcall MonopolyManager::showSummaryScreen(int this)
{
    char cVar1;
    undefined4 *puVar2;
    undefined4 *puVar3;
    undefined1 *puVar4;
    undefined4 uVar5;
    undefined1 *puVar6;
    undefined1 *puVar7;
    undefined1 *local_30;
    undefined4 local_2c;
    undefined4 local_28;
    code *local_24;
    undefined1 *local_20;
    undefined4 local_1c;
    undefined4 local_18;
    code *local_14;
    undefined1 *local_10;
    undefined4 local_c;
    undefined4 local_8;
    code *local_4;
    
    puVar2 = (undefined4 *)FUN_0084aea0(*(undefined4 *)(this + 0x80)); // +0x80: currentMonopolyData
    if (puVar2 != (undefined4 *)0x0) {
        local_10 = (undefined1 *)0x0;
        local_c = 0;
        local_8 = 0;
        local_4 = (code *)0x0;
        local_20 = (undefined1 *)0x0;
        local_1c = 0;
        local_18 = 0;
        local_14 = (code *)0x0;
        puVar3 = (undefined4 *)FUN_0084a4b0(); // getFamilyName
        puVar4 = (undefined1 *)*puVar3;
        if (puVar4 == (undefined1 *)0x0) {
            puVar4 = &DAT_0120546e; // empty string
        }
        FUN_004d4ad0(&local_10, "{m:%s}{$summary_screen_monopoly}", puVar4); // format message
        uVar5 = FUN_0084a150(); // getPlayerId
        FUN_004d4ad0(&local_20, "{#%u}", uVar5);
        puVar4 = local_20;
        if (local_20 == (undefined1 *)0x0) {
            puVar4 = &DAT_0120546e;
        }
        puVar3 = (undefined4 *)FUN_0084a4e0(); // getPlayerName
        puVar7 = (undefined1 *)*puVar3;
        if (puVar7 == (undefined1 *)0x0) {
            puVar7 = &DAT_0120546e;
        }
        puVar6 = local_10;
        if (local_10 == (undefined1 *)0x0) {
            puVar6 = &DAT_0120546e;
        }
        FUN_005a04a0("ShowMessage", 0, &DAT_00d83810, 3, puVar6, puVar7, puVar4); // show summary screen message
        local_30 = (undefined1 *)0x0;
        local_2c = 0;
        local_28 = 0;
        local_24 = (code *)0x0;
        FUN_004d4ad0(&local_30, "mono_%d", *(undefined4 *)*puVar2); // format image name
        puVar4 = local_30;
        if (local_30 == (undefined1 *)0x0) {
            puVar4 = &DAT_0120546e;
        }
        cVar1 = FUN_005bd670(puVar4); // hasImage
        if (cVar1 != '\0') {
            FUN_005a04a0("SetImage", 0, &DAT_00d83810, 1, puVar4); // set summary screen image
        }
        if (local_30 != (undefined1 *)0x0) {
            (*local_24)(local_30); // free string
        }
        if (local_20 != (undefined1 *)0x0) {
            (*local_14)(local_20); // free string
        }
        if (local_10 != (undefined1 *)0x0) {
            (*local_4)(local_10); // free string
        }
    }
    return;
}