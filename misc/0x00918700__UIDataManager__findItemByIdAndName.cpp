// FUNC_NAME: UIDataManager::findItemByIdAndName
// Function at 0x00918700 - searches through a table of items by numeric ID and wide-string name, returns index or -1 (0xFFFFFFFF)
// Uses global game mode at DAT_01130044 + 0xB8 to select which table to search.
// Tables are arrays of structs, each containing a pointer to a wide string (first field) and a numeric ID at varying offsets.
uint __thiscall UIDataManager::findItemByIdAndName(int param_2, byte* param_3)
{
    byte bVar1;
    char cVar2;
    byte* pbVar3;
    int iVar4;
    byte* pbVar5;
    int extraout_EDX;
    uint uVar6;
    undefined4* puVar7;
    bool bVar8;
    uint local_4;

    // Get global game mode
    iVar4 = *(int*)(DAT_01130044 + 0xb8);

    // Initialize return index to -1
    local_4 = 0xffffffff;

    // Mode 10, 11, 12 -> table at +0x4c, size at +0x50, struct id at offset 0xa
    if (((iVar4 == 10) || (iVar4 == 0xb)) || (iVar4 == 0xc)) {
        uVar6 = 0;
        if (*(uint*)(param_1 + 0x50) != 0) {
            puVar7 = *(undefined4**)(param_1 + 0x4c);
            while (local_4 = uVar6, ((undefined4*)*puVar7)[10] != param_2) {
                pbVar3 = *(byte**)*puVar7;
                pbVar5 = param_3;
                if (pbVar3 == (byte*)0x0) {
                    pbVar3 = &DAT_0120546e; // default empty string
                }
                // Wide-string comparison (two-byte characters)
                do {
                    bVar1 = *pbVar3;
                    bVar8 = bVar1 < *pbVar5;
                    if (bVar1 != *pbVar5) {
                        iVar4 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
                        goto LAB_00918780;
                    }
                    if (bVar1 == 0) break;
                    bVar1 = pbVar3[1];
                    bVar8 = bVar1 < pbVar5[1];
                    if (bVar1 != pbVar5[1]) goto LAB_00918780;
                    pbVar3 = pbVar3 + 2;
                    pbVar5 = pbVar5 + 2;
                } while (bVar1 != 0);
                iVar4 = 0;
                LAB_00918780:
                if (iVar4 == 0) {
                    return uVar6; // found by name
                }
                uVar6 = uVar6 + 1;
                puVar7 = puVar7 + 1;
                if (*(uint*)(param_1 + 0x50) <= uVar6) {
                    return local_4; // not found, return last-assigned index (may be valid or -1)
                }
            }
        }
    }
    // Mode 0x19 (25) -> table at +0x58, size at +0x5c, struct id at offset 0xb
    else if (iVar4 == 0x19) {
        uVar6 = 0;
        if (*(uint*)(param_1 + 0x5c) != 0) {
            puVar7 = *(undefined4**)(param_1 + 0x58);
            while (local_4 = uVar6, ((undefined4*)*puVar7)[0xb] != param_2) {
                pbVar3 = *(byte**)*puVar7;
                pbVar5 = param_3;
                if (pbVar3 == (byte*)0x0) {
                    pbVar3 = &DAT_0120546e;
                }
                do {
                    bVar1 = *pbVar3;
                    bVar8 = bVar1 < *pbVar5;
                    if (bVar1 != *pbVar5) {
                        iVar4 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
                        goto LAB_00918800;
                    }
                    if (bVar1 == 0) break;
                    bVar1 = pbVar3[1];
                    bVar8 = bVar1 < pbVar5[1];
                    if (bVar1 != pbVar5[1]) goto LAB_00918800;
                    pbVar3 = pbVar3 + 2;
                    pbVar5 = pbVar5 + 2;
                } while (bVar1 != 0);
                iVar4 = 0;
                LAB_00918800:
                if (iVar4 == 0) {
                    return uVar6;
                }
                uVar6 = uVar6 + 1;
                puVar7 = puVar7 + 1;
                if (*(uint*)(param_1 + 0x5c) <= uVar6) {
                    return local_4;
                }
            }
        }
    }
    // Mode 13, 14, 15, 16, 17 -> table at +0x64 (100 decimal), size at +0x68, struct id at offset 0xb
    else if (((iVar4 == 0xd) || (iVar4 == 0xe)) ||
             ((iVar4 == 0xf || ((iVar4 == 0x10 || (iVar4 == 0x11)))))) {
        uVar6 = 0;
        if (*(uint*)(param_1 + 0x68) != 0) {
            puVar7 = *(undefined4**)(param_1 + 100); // offset 0x64
            while (local_4 = uVar6, ((undefined4*)*puVar7)[0xb] != param_2) {
                pbVar3 = *(byte**)*puVar7;
                pbVar5 = param_3;
                if (pbVar3 == (byte*)0x0) {
                    pbVar3 = &DAT_0120546e;
                }
                do {
                    bVar1 = *pbVar3;
                    bVar8 = bVar1 < *pbVar5;
                    if (bVar1 != *pbVar5) {
                        iVar4 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
                        goto LAB_00918890;
                    }
                    if (bVar1 == 0) break;
                    bVar1 = pbVar3[1];
                    bVar8 = bVar1 < pbVar5[1];
                    if (bVar1 != pbVar5[1]) goto LAB_00918890;
                    pbVar3 = pbVar3 + 2;
                    pbVar5 = pbVar5 + 2;
                } while (bVar1 != 0);
                iVar4 = 0;
                LAB_00918890:
                if (iVar4 == 0) {
                    return uVar6;
                }
                uVar6 = uVar6 + 1;
                puVar7 = puVar7 + 1;
                if (*(uint*)(param_1 + 0x68) <= uVar6) {
                    return local_4;
                }
            }
        }
    }
    // All other modes -> attempt to use a secondary data manager obtained from FUN_00917060()
    else {
        cVar2 = FUN_00917060();
        if (cVar2 != '\0') {
            uVar6 = 0;
            if (*(uint*)(extraout_EDX + 0x74) != 0) {
                puVar7 = *(undefined4**)(extraout_EDX + 0x70);
                while (local_4 = uVar6, ((undefined4*)*puVar7)[6] != param_2) {
                    pbVar3 = *(byte**)*puVar7;
                    pbVar5 = param_3;
                    if (pbVar3 == (byte*)0x0) {
                        pbVar3 = &DAT_0120546e;
                    }
                    do {
                        bVar1 = *pbVar3;
                        bVar8 = bVar1 < *pbVar5;
                        if (bVar1 != *pbVar5) {
                            iVar4 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
                            goto LAB_00918908;
                        }
                        if (bVar1 == 0) break;
                        bVar1 = pbVar3[1];
                        bVar8 = bVar1 < pbVar5[1];
                        if (bVar1 != pbVar5[1]) goto LAB_00918908;
                        pbVar3 = pbVar3 + 2;
                        pbVar5 = pbVar5 + 2;
                    } while (bVar1 != 0);
                    iVar4 = 0;
                    LAB_00918908:
                    if (iVar4 == 0) {
                        return uVar6;
                    }
                    uVar6 = uVar6 + 1;
                    puVar7 = puVar7 + 1;
                    if (*(uint*)(extraout_EDX + 0x74) <= uVar6) {
                        return local_4;
                    }
                }
            }
        }
    }
    return local_4; // fallback
}