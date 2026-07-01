// FUNC_NAME: MenuStateMachine::handleMenuCommand
void __fastcall MenuStateMachine::handleMenuCommand(int this)
{
    char cVar1;
    int* piVar5;
    int* piVar6;
    int iVar7;
    uint uVar8;
    int iVar9;
    char* pcVar10;
    undefined4* puVar11;
    char* pcVar12;
    undefined2* puVar13;
    char* pcVar14;
    bool bVar15;
    undefined4 uStackY_130;
    char* pcStackY_12c;
    char local_110 [256]; // Buffer for concatenating strings
    undefined4* local_10;
    undefined4 local_c;
    int local_8;
  
    local_c = DAT_011298a0;
    local_110[0] = '\0';
    pcStackY_12c = (char *)0x959344; // Return address for error handling
    local_8 = this;
    _memset(local_110 + 1,0,0xff);
    
    // Get string from vtable pointer at offset +0x84 (likely "currentMenu")
    pcVar4 = (char *)(*(code *)**(undefined4 **)(this + 0x84))();
    pcVar10 = local_110;
    do {
        cVar1 = *pcVar4;
        *pcVar10 = cVar1;
        pcVar4 = pcVar4 + 1;
        pcVar10 = pcVar10 + 1;
    } while (cVar1 != '\0');
    
    // Get string from vtable pointer at offset +0x108 (likely "command")
    pcVar4 = (char *)(*(code *)**(undefined4 **)(this + 0x108))();
    pcVar10 = pcVar4 + 1;
    do {
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    
    if (pcVar4 != pcVar10) {
        puVar13 = (undefined2 *)&stack0xfffffeef;
        do {
            pcVar10 = (char *)((int)puVar13 + 1);
            puVar13 = (undefined2 *)((int)puVar13 + 1);
        } while (*pcVar10 != '\0');
        pcVar2 = (code *)**(undefined4 **)(this + 0x108);
        *puVar13 = DAT_00e3ed40; // Separator character
        pcVar4 = (char *)(*pcVar2)();
        pcVar10 = pcVar4;
        do {
            cVar1 = *pcVar10;
            pcVar10 = pcVar10 + 1;
        } while (cVar1 != '\0');
        pcVar14 = &stack0xfffffeef;
        do {
            pcVar12 = pcVar14 + 1;
            pcVar14 = pcVar14 + 1;
        } while (*pcVar12 != '\0');
        pcVar12 = pcVar4;
        for (uVar8 = (uint)((int)pcVar10 - (int)pcVar4) >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
            *(undefined4 *)pcVar14 = *(undefined4 *)pcVar12;
            pcVar12 = pcVar12 + 4;
            pcVar14 = pcVar14 + 4;
        }
        for (uVar8 = (int)pcVar10 - (int)pcVar4 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
            *pcVar14 = *pcVar12;
            pcVar12 = pcVar12 + 1;
            pcVar14 = pcVar14 + 1;
        }
        
        // Get string from vtable at offset +0x18c (likely "screenName")
        puVar11 = (undefined4 *)(local_8 + 0x18c);
        pcVar4 = (char *)(*(code *)**(undefined4 **)(local_8 + 0x18c))();
        pcVar10 = pcVar4 + 1;
        do {
            cVar1 = *pcVar4;
            pcVar4 = pcVar4 + 1;
        } while (cVar1 != '\0');
        this = local_8;
        if (pcVar4 != pcVar10) {
            puVar13 = (undefined2 *)&stack0xfffffeef;
            do {
                pcVar10 = (char *)((int)puVar13 + 1);
                puVar13 = (undefined2 *)((int)puVar13 + 1);
            } while (*pcVar10 != '\0');
            pcVar2 = *(code **)*puVar11;
            *puVar13 = DAT_00e3ed40;
            pcVar4 = (char *)(*pcVar2)();
            pcVar10 = pcVar4;
            do {
                cVar1 = *pcVar10;
                pcVar10 = pcVar10 + 1;
            } while (cVar1 != '\0');
            pcVar14 = &stack0xfffffeef;
            do {
                pcVar12 = pcVar14 + 1;
                pcVar14 = pcVar14 + 1;
            } while (*pcVar12 != '\0');
            pcVar12 = pcVar4;
            for (uVar8 = (uint)((int)pcVar10 - (int)pcVar4) >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
                *(undefined4 *)pcVar14 = *(undefined4 *)pcVar12;
                pcVar12 = pcVar12 + 4;
                pcVar14 = pcVar14 + 4;
            }
            for (uVar8 = (int)pcVar10 - (int)pcVar4 & 3; this = local_8, uVar8 != 0; uVar8 = uVar8 - 1)
            {
                *pcVar14 = *pcVar12;
                pcVar12 = pcVar12 + 1;
                pcVar14 = pcVar14 + 1;
            }
        }
    }
    
    // Get global state from FUN_009bbd30 (likely getGameStateManager)
    piVar5 = (int *)FUN_009bbd30();
    local_10 = (undefined4 *)(this + 0x210); // +0x210: VTable pointer for menu type
    
    // Get string from vtable at this+0x210 (likely "menuType")
    pcVar10 = (char *)(*(code *)**(undefined4 **)(this + 0x210))();
    iVar9 = 0xc;
    bVar15 = true;
    pcVar4 = "onentermenu";
    do {
        if (iVar9 == 0) break;
        iVar9 = iVar9 + -1;
        bVar15 = *pcVar10 == *pcVar4;
        pcVar10 = pcVar10 + 1;
        pcVar4 = pcVar4 + 1;
    } while (bVar15);
    
    if (bVar15) {
        // Handle "onentermenu" command
        if (piVar5 != (int *)0x0) {
            if ((((*piVar5 == 1) && (piVar6 = (int *)FUN_009c0e10(), piVar6 != (int *)0x0)) &&
                (*piVar6 == 0)) && (iVar9 = FUN_009bf470(), iVar9 == 7)) {
                piVar5 = piVar6;
            }
            if (*piVar5 == 0) {
                FUN_009582c0(); // Possibly closeMenu or showMenu
                FUN_00958810(); // Possibly updateUI or refresh
            }
        }
        FUN_009bdfc0(); // executeOnEnterMenu callback
        return;
    }
    
    if (piVar5 != (int *)0x0) {
        iVar7 = FUN_009bf470(); // getMenuState
        iVar9 = local_8;
        if (iVar7 == 2) {
            // Menu state: "active" or "shown"
            (**(code **)*local_10)();
            pcStackY_12c = (char *)0x959655;
            FUN_009be1b0(); // executeCommand
        }
        else {
            if (iVar7 == 3) {
                // Menu state: "hidden" or "closed"
                pcVar4 = *(char **)(piVar5[1] + 0x10);
                pcVar10 = pcVar4 + 1;
                pcVar14 = pcVar4;
                do {
                    cVar1 = *pcVar14;
                    pcVar14 = pcVar14 + 1;
                } while (cVar1 != '\0');
                cVar1 = pcVar4[(int)(pcVar14 + (-1 - (int)pcVar10))];
                if (cVar1 == 'l') {
                    if (cVar1 != 'r') {
                        pcStackY_12c = local_110;
                        uStackY_130 = 0x95962c;
                        FUN_009bd370(); // log or setState
                        return;
                    }
                }
                else if (cVar1 != 'r') {
                    return;
                }
                pcStackY_12c = local_110;
                uStackY_130 = 0x9595b1;
                FUN_009bd370(); // log or setState
                iVar7 = -(int)(pcVar14 + (1 - (int)pcVar10));
                pcVar4 = local_110;
                iVar3 = iVar7 - (int)pcVar4;
                do {
                    cVar1 = *pcVar4;
                    pcVar4[(int)(local_110 + iVar3 + -0x10)] = cVar1;
                    pcVar4 = pcVar4 + 1;
                } while (cVar1 != '\0');
                pcVar14[(int)(local_110 + (iVar7 - (int)pcVar10) + -0x11)] = 'l';
                *(undefined4 *)(local_110 + iVar7 + -0x14) = *(undefined4 *)(iVar9 + 0x2a0);
                *(undefined4 *)(local_110 + iVar7 + -0x18) = *(undefined4 *)(iVar9 + 0x29c);
                *(char **)((int)&pcStackY_12c + iVar7) = local_110 + iVar7 + -0x10;
                *(undefined4 *)((int)&uStackY_130 + iVar7) = 0x9595f7;
                FUN_009bd370(); // log or setState
                return;
            }
            if (iVar7 == 6) {
                // Menu state: "transitioning" or "error"
                pcStackY_12c = (char *)0x959549;
                FUN_009be2d0(); // handleTransition
                return;
            }
        }
    }
    return;
}