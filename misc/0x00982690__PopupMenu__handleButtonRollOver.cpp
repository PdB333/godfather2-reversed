// FUNC_NAME: PopupMenu::handleButtonRollOver
bool __thiscall PopupMenu::handleButtonRollOver(int this, byte *buttonPath)
{
    byte bVar1;
    byte *pbVar2;
    int iVar3;
    int iVar4;
    byte *pbVar5;
    uint uVar6;
    bool bVar7;
    bool bVar8;
    undefined4 local_4c;
    undefined4 local_48;
    undefined1 local_44;
    byte local_40 [64]; // Path string buffer
    
    // Check if the button is the default "button" (RollOverDefaultButton)
    iVar4 = 0x14;
    bVar8 = true;
    pbVar2 = (byte *)"/ppop/button/button";
    pbVar5 = buttonPath;
    do {
        if (iVar4 == 0) break;
        iVar4 = iVar4 + -1;
        bVar8 = *pbVar2 == *pbVar5;
        pbVar2 = pbVar2 + 1;
        pbVar5 = pbVar5 + 1;
    } while (bVar8);
    if (bVar8) {
        // Matched default button path - trigger RollOverDefaultButton event
        FUN_005a04a0("RollOverDefaultButton", 0, &DAT_00d90628, 0);
        local_4c = DAT_01130228;
        local_48 = 0;
        local_44 = 0;
        FUN_00408a00(&local_4c, 0);
    }
    uVar6 = 0;
    if (!bVar8) {
        // Check against popup buttons: /ppop/popup_root/popup_%d/button_%d/button
        while (uVar6 < 4) {
            FUN_00910160(local_40, "/ppop/popup_root/popup_%d/button_%d/button",
                         *(int *)(this + 0x6c) + -1, uVar6); // +0x6c = currentPopupIndex
            pbVar2 = local_40;
            pbVar5 = buttonPath;
            do {
                bVar1 = *pbVar2;
                bVar7 = bVar1 < *pbVar5;
                if (bVar1 != *pbVar5) {
LAB_00982740:
                    iVar4 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
                    goto LAB_00982745;
                }
                if (bVar1 == 0) break;
                bVar1 = pbVar2[1];
                bVar7 = bVar1 < pbVar5[1];
                if (bVar1 != pbVar5[1]) goto LAB_00982740;
                pbVar2 = pbVar2 + 2;
                pbVar5 = pbVar5 + 2;
            } while (bVar1 != 0);
            iVar4 = 0;
LAB_00982745:
            if (iVar4 == 0) {
                // Matched a popup button - trigger RollOverButton event
                FUN_00910160(local_40, &DAT_00e3266c, uVar6);
                FUN_005a04a0("RollOverButton", 0, &DAT_00d90628, 1, local_40);
                bVar8 = true;
                local_4c = DAT_01130228;
                local_48 = 0;
                local_44 = 0;
                FUN_00408a00(&local_4c, 0);
            }
            uVar6 = uVar6 + 1;
            if (bVar8 != false) {
                return bVar8;
            }
        }
        if (bVar8 == false) {
            // Check against options items: /ppop/popup_root/popup_%d/options/item_%d/option
            iVar4 = *(int *)(this + 0x4c + *(int *)(this + 0x6c) * 4); // +0x4c = popupArray[popupIndex]
            uVar6 = 0;
            do {
                if (*(uint *)(iVar4 + 4) <= uVar6) { // +0x04 = itemCount
                    return bVar8;
                }
                FUN_00910160(local_40, "/ppop/popup_root/popup_%d/options/item_%d/option",
                             *(int *)(this + 0x6c) + -1, uVar6);
                pbVar2 = local_40;
                pbVar5 = buttonPath;
                do {
                    bVar1 = *pbVar2;
                    bVar7 = bVar1 < *pbVar5;
                    if (bVar1 != *pbVar5) {
LAB_00982800:
                        iVar3 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
                        goto LAB_00982805;
                    }
                    if (bVar1 == 0) break;
                    bVar1 = pbVar2[1];
                    bVar7 = bVar1 < pbVar5[1];
                    if (bVar1 != pbVar5[1]) goto LAB_00982800;
                    pbVar2 = pbVar2 + 2;
                    pbVar5 = pbVar5 + 2;
                } while (bVar1 != 0);
                iVar3 = 0;
LAB_00982805:
                if (iVar3 == 0) {
                    // Matched an option item - trigger selection (index adjusted by scroll offset)
                    FUN_00982100(uVar6 - *(int *)(this + 0x70)); // +0x70 = scrollOffset
                    bVar8 = true;
                }
                uVar6 = uVar6 + 1;
            } while (bVar8 == false);
        }
    }
    return bVar8;
}