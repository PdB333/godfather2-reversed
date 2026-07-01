// FUNC_NAME: FamilyViewScreen::populateCategoryRows
void __thiscall FamilyViewScreen::populateCategoryRows(int thisPtr, uint startIndex)
{
    int mode;
    int iVar1;
    int iVar2;
    char cVar4;
    undefined4 uVar5;
    uint uVar6;

    // Global UI manager singleton (likely a screen manager or list manager)
    int gUIMgr = DAT_01130044;
    mode = *(int *)(gUIMgr + 0xb8); // +0xB8: current category/mode ID

    // Overall stats category (modes 10, 11, 12)
    if (((mode == 10) || (mode == 11)) || (mode == 12)) {
        uVar5 = FUN_009185a0(); // getCurrentScreen?
        *(undefined4 *)(gUIMgr + 0xec) = uVar5;
        FUN_005a04a0("InitScroll", 0, &DAT_00d8510c, 0); // initialize scroll list
        uVar6 = 0;
        if (startIndex < *(uint *)(thisPtr + 0x50)) { // +0x50: overall stat count
            while (uVar6 < 10) {
                FUN_0095c670(*(undefined4 *)(gUIMgr + 0xc4), 0x80); // add overall row icon
                FUN_0095d0c0(*(undefined4 *)(gUIMgr + 0xf0), 0x80); // add stat column 1
                FUN_0095d130(*(undefined4 *)(gUIMgr + 0xf4), 0x80); // add stat column 2
                FUN_0095d280(*(undefined4 *)(gUIMgr + 0xf8), 0x80); // add stat column 3
                FUN_0095d1a0(*(undefined4 *)(gUIMgr + 0xfc), 0x80); // add stat column 4
                FUN_0095d210(*(undefined4 *)(gUIMgr + 0x100), 0x80); // add stat column 5
                FUN_005a04a0("AddOverallRow", 0, &DAT_00d8510c, 0); // commit row
                startIndex = startIndex + 1;
                uVar6 = uVar6 + 1;
                if (*(uint *)(thisPtr + 0x50) <= startIndex) {
                    return;
                }
            }
        }
    }
    // Combat stats category (mode 0x19 = 25)
    else if (mode == 0x19) {
        uVar5 = FUN_009185a0();
        *(undefined4 *)(gUIMgr + 0xec) = uVar5;
        FUN_005a04a0("InitScroll", 0, &DAT_00d8510c, 0);
        uVar6 = 0;
        if (startIndex < *(uint *)(thisPtr + 0x5c)) { // +0x5C: combat stat count
            while (uVar6 < 10) {
                FUN_0095c6a0(*(undefined4 *)(gUIMgr + 0xc4), 0x80); // add combat row icon
                FUN_0095d310(*(undefined4 *)(gUIMgr + 0xf0), 0x80); // add combat stat 1
                FUN_0095d380(*(undefined4 *)(gUIMgr + 0xf4), 0x80); // add combat stat 2
                FUN_0095d3f0(*(undefined4 *)(gUIMgr + 0xf8), 0x80); // add combat stat 3
                FUN_0095d4a0(*(undefined4 *)(gUIMgr + 0xfc), 0x80); // add combat stat 4
                FUN_0095d510(*(undefined4 *)(gUIMgr + 0x100), 0x80); // add combat stat 5
                FUN_0095d580(*(undefined4 *)(gUIMgr + 0x104), 0x80); // add combat stat 6
                FUN_0095d5f0(*(undefined4 *)(gUIMgr + 0x108), 0x80); // add combat stat 7
                FUN_005a04a0("AddCombatRow", 0, &DAT_00d8510c, 0);
                startIndex = startIndex + 1;
                uVar6 = uVar6 + 1;
                if (*(uint *)(thisPtr + 0x5c) <= startIndex) {
                    return;
                }
            }
        }
    }
    // Game modes category (modes 13-17)
    else if (((mode == 0xd) || (mode == 0xe)) ||
             ((mode == 0xf || ((mode == 0x10 || (mode == 0x11)))))) {
        uVar5 = FUN_009185a0();
        *(undefined4 *)(gUIMgr + 0xec) = uVar5;
        FUN_005a04a0("InitScroll", 0, &DAT_00d8510c, 0);
        uVar6 = 0;
        if (startIndex < *(uint *)(thisPtr + 0x68)) { // +0x68: game mode count
            while (uVar6 < 10) {
                FUN_0095c6d0(*(undefined4 *)(gUIMgr + 0xc4), 0x80); // add game mode row icon
                if (*(int *)(gUIMgr + 0xb8) == 0x11) {
                    // Special case for mode 17: 4 columns
                    FUN_0095d740(*(undefined4 *)(gUIMgr + 0xf0),
                                 *(undefined4 *)(gUIMgr + 0xf4),
                                 *(undefined4 *)(gUIMgr + 0xf8),
                                 *(undefined4 *)(gUIMgr + 0xfc), 0x80);
                }
                else {
                    // Normal: 3 columns
                    FUN_0095d660(*(undefined4 *)(gUIMgr + 0xf0),
                                 *(undefined4 *)(gUIMgr + 0xf4),
                                 *(undefined4 *)(gUIMgr + 0xf8), 0x80);
                }
                FUN_005a04a0("AddGameModesRow", 0, &DAT_00d8510c, 0);
                startIndex = startIndex + 1;
                uVar6 = uVar6 + 1;
                if (*(uint *)(thisPtr + 0x68) <= startIndex) {
                    return;
                }
            }
        }
    }
    // Specialties category (modes 18-24)
    else {
        cVar4 = FUN_00917060(); // isVisible?
        if (cVar4 != '\0') {
            iVar1 = gUIMgr + 0xec;
            FUN_00919980(iVar1); // clear current list?
            iVar2 = *(int *)(gUIMgr + 0xb8);
            if (iVar2 == 0x12) { // mode 18
                uVar6 = 0;
                if (startIndex < *(uint *)(thisPtr + 0x74)) { // +0x74: specialty count
                    while (uVar6 < 10) {
                        FUN_0095c700(*(undefined4 *)(gUIMgr + 0xc4), 0x80); // add specialty row icon
                        FUN_0095d9d0(gUIMgr + 0xd8,
                                     *(undefined4 *)(gUIMgr + 0xf0),
                                     *(undefined4 *)(gUIMgr + 0xf4),
                                     *(undefined4 *)(gUIMgr + 0xf8),
                                     *(undefined4 *)(gUIMgr + 0xfc), 0x80);
                        FUN_005a04a0("AddSpecialtyRow", 0, &DAT_00d8510c, 0);
                        startIndex = startIndex + 1;
                        uVar6 = uVar6 + 1;
                        if (*(uint *)(thisPtr + 0x74) <= startIndex) {
                            return;
                        }
                    }
                }
            }
            else if (iVar2 == 0x13) { // mode 19
                uVar6 = 0;
                if (startIndex < *(uint *)(thisPtr + 0x74)) {
                    while (uVar6 < 10) {
                        FUN_0095c700(*(undefined4 *)(gUIMgr + 0xc4), 0x80);
                        FUN_0095daf0(*(undefined4 *)(gUIMgr + 0xf0),
                                     *(undefined4 *)(gUIMgr + 0xf4),
                                     *(undefined4 *)(gUIMgr + 0xf8), 0x80);
                        FUN_005a04a0("AddSpecialtyRow", 0, &DAT_00d8510c, 0);
                        startIndex = startIndex + 1;
                        uVar6 = uVar6 + 1;
                        if (*(uint *)(thisPtr + 0x74) <= startIndex) {
                            return;
                        }
                    }
                }
            }
            else if (iVar2 == 0x14) { // mode 20
                FUN_00919980(iVar1);
                uVar6 = 0;
                if (startIndex < *(uint *)(thisPtr + 0x74)) {
                    while (uVar6 < 10) {
                        FUN_0095c700(*(undefined4 *)(gUIMgr + 0xc4), 0x80);
                        FUN_0095dbd0(*(undefined4 *)(gUIMgr + 0xf0),
                                     *(undefined4 *)(gUIMgr + 0xf4), 0x80);
                        FUN_005a04a0("AddSpecialtyRow", 0, &DAT_00d8510c, 0);
                        startIndex = startIndex + 1;
                        uVar6 = uVar6 + 1;
                        if (*(uint *)(thisPtr + 0x74) <= startIndex) {
                            return;
                        }
                    }
                }
            }
            else if (iVar2 == 0x15) { // mode 21
                FUN_00919980(iVar1);
                uVar6 = 0;
                if (startIndex < *(uint *)(thisPtr + 0x74)) {
                    while (uVar6 < 10) {
                        FUN_0095c700(*(undefined4 *)(gUIMgr + 0xc4), 0x80);
                        FUN_0095df20(*(undefined4 *)(gUIMgr + 0xf0),
                                     *(undefined4 *)(gUIMgr + 0xf4), 0x80);
                        FUN_005a04a0("AddSpecialtyRow", 0, &DAT_00d8510c, 0);
                        startIndex = startIndex + 1;
                        uVar6 = uVar6 + 1;
                        if (*(uint *)(thisPtr + 0x74) <= startIndex) {
                            return;
                        }
                    }
                }
            }
            else if (iVar2 == 0x16) { // mode 22
                FUN_00919980(iVar1);
                uVar6 = 0;
                if (startIndex < *(uint *)(thisPtr + 0x74)) {
                    while (uVar6 < 10) {
                        FUN_0095c700(*(undefined4 *)(gUIMgr + 0xc4), 0x80);
                        FUN_0095dd60(*(undefined4 *)(gUIMgr + 0xf0),
                                     *(undefined4 *)(gUIMgr + 0xf4),
                                     *(undefined4 *)(gUIMgr + 0xf8), 0x80);
                        FUN_005a04a0("AddSpecialtyRow", 0, &DAT_00d8510c, 0);
                        startIndex = startIndex + 1;
                        uVar6 = uVar6 + 1;
                        if (*(uint *)(thisPtr + 0x74) <= startIndex) {
                            return;
                        }
                    }
                }
            }
            else if (iVar2 == 0x17) { // mode 23
                FUN_00919980(iVar1);
                uVar6 = 0;
                if (startIndex < *(uint *)(thisPtr + 0x74)) {
                    while (uVar6 < 10) {
                        FUN_0095c700(*(undefined4 *)(gUIMgr + 0xc4), 0x80);
                        FUN_0095dc80(*(undefined4 *)(gUIMgr + 0xf0),
                                     *(undefined4 *)(gUIMgr + 0xf4),
                                     *(undefined4 *)(gUIMgr + 0xf8), 0x80);
                        FUN_005a04a0("AddSpecialtyRow", 0, &DAT_00d8510c, 0);
                        startIndex = startIndex + 1;
                        uVar6 = uVar6 + 1;
                        if (*(uint *)(thisPtr + 0x74) <= startIndex) {
                            return;
                        }
                    }
                }
            }
            else if (iVar2 == 0x18) { // mode 24
                FUN_00919980(iVar1);
                uVar6 = 0;
                if (startIndex < *(uint *)(thisPtr + 0x74)) {
                    do {
                        if (9 < uVar6) {
                            return;
                        }
                        FUN_0095c700(*(undefined4 *)(gUIMgr + 0xc4), 0x80);
                        FUN_0095de40(*(undefined4 *)(gUIMgr + 0xf0),
                                     *(undefined4 *)(gUIMgr + 0xf4),
                                     *(undefined4 *)(gUIMgr + 0xf8), 0x80);
                        FUN_005a04a0("AddSpecialtyRow", 0, &DAT_00d8510c, 0);
                        startIndex = startIndex + 1;
                        uVar6 = uVar6 + 1;
                    } while (startIndex < *(uint *)(thisPtr + 0x74));
                }
            }
        }
    }
    return;
}