// FUNC_NAME: PauseMenuManager::handleButtonRollover

bool __thiscall PauseMenuManager::handleButtonRollover(int this, byte *buttonPath)
{
    byte bVar1;
    byte *pbVar2;
    int iVar3;
    byte *pbVar4;
    uint i;
    bool bVar6;
    bool bVar7;
    int *itemEntries;
    undefined4 local_70;
    undefined4 local_6c;
    undefined1 local_68;
    byte formattedPath[100];

    iVar3 = 0x1e;
    bVar7 = true;
    pbVar2 = (byte *)"/onsl/buttons/button_2/button";
    pbVar4 = buttonPath;
    do {
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        bVar7 = *pbVar2 == *pbVar4;
        pbVar2 = pbVar2 + 1;
        pbVar4 = pbVar4 + 1;
    } while (bVar7);

    if (bVar7) {
        // Match on the main back button path
        sendMessage("RollOverButton", 0, &g_uiFocusManager, 1, &DAT_00d796d4);
        local_70 = DAT_011302b0;
        local_6c = 0;
        local_68 = 0;
        unknownFunction(&local_70, 0);
    }

    i = 0;
    if (!bVar7) {
        // Iterate through menu item entries
        itemEntries = &g_menuItemEntries; // DAT_00e574d0
        do {
            if (this->numItems <= i) { // +0x50
                return bVar7;
            }
            formatString(formattedPath, 
                         "/onsl/pause_mc/menu_items_anim/menu_stub/menu_%d/shared_menu_item/item",
                         i);
            pbVar2 = formattedPath;
            pbVar4 = buttonPath;
            do {
                bVar1 = *pbVar2;
                bVar6 = bVar1 < *pbVar4;
                if (bVar1 != *pbVar4) {
                    iVar3 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
                    goto LAB_009744e5;
                }
                if (bVar1 == 0) break;
                bVar1 = pbVar2[1];
                bVar6 = bVar1 < pbVar4[1];
                if (bVar1 != pbVar4[1]) goto LAB_009744e0;
                pbVar2 = pbVar2 + 2;
                pbVar4 = pbVar4 + 2;
            } while (bVar1 != 0);
            iVar3 = 0;
LAB_009744e5:
            if ((iVar3 == 0) && (itemEntries[0] == 0)) { // first field of struct is used flag?
                this->selectedItemIndex = i; // +0x60
                sendMessage("RollOverSelection", 0, &g_uiFocusManager, 0);
                local_70 = DAT_011302b0;
                local_6c = 0;
                local_68 = 0;
                unknownFunction(&local_70, 0);
                bVar7 = true;
            }
            itemEntries += 3; // each entry is 12 bytes (3 ints?)
            i++;
        } while (!bVar7);
    }
    return bVar7;
}