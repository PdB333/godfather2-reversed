// FUNC_NAME: Player::updateControllerState
void __fastcall Player::updateControllerState(int this)
{
    char cVar1;
    undefined1 *puVar2;
    char *pcVar3;
    int iVar4;
    char *pcVar5;
    uint uVar6;
    uint uVar7;
    int iVar8;
    undefined1 local_3d;
    int local_3c;
    uint local_38;
    uint local_34;
    undefined1 *local_30;
    undefined4 local_2c;
    undefined4 local_28;
    code *local_24;
    int local_20;
    uint local_1c;
    code *local_14;
    undefined1 *local_10;
    code *pcStack_4;

    local_3c = this;
    // Check if bit 14 of field at +0x10 is set (some flag)
    if ((*(uint *)(this + 0x10) >> 0xe & 1) == 0) {
        // Allocate memory for controller state (0xf0 bytes)
        iVar4 = FUN_009c8e50(0xf0);
        if (iVar4 == 0) {
            local_38 = 0;
        }
        else {
            local_38 = FUN_00982280(0);
        }
        uVar6 = local_38;
        local_34 = 0;
        // Initialize controller state
        FUN_006039d0(0xd80c083d, &local_34, &local_3d);
        FUN_004d3bc0(local_34);
        puVar2 = local_10;
        if (local_10 == (undefined1 *)0x0) {
            puVar2 = &DAT_0120546e;
        }
        FUN_00981eb0(puVar2);
        local_34 = 0;
        // Iterate through controller slots (each 0x558 bytes)
        if (*(int *)(this + 0x2048) != 0) {
            pcVar5 = (char *)(this + 0x78);
            do {
                pcVar3 = pcVar5;
                do {
                    cVar1 = *pcVar3;
                    pcVar3 = pcVar3 + 1;
                } while (cVar1 != '\0');
                FUN_004dba80(pcVar5, (int)pcVar3 - (int)(pcVar5 + 1));
                uVar6 = local_1c;
                uVar7 = 0;
                local_30 = (undefined1 *)0x0;
                local_2c = 0;
                local_28 = 0;
                local_24 = (code *)0x0;
                if (local_1c != 0) {
                    do {
                        FUN_004d44b0(*(undefined2 *)(local_20 + uVar7 * 2));
                        uVar7 = uVar7 + 1;
                    } while (uVar7 < uVar6);
                }
                uVar6 = local_34;
                puVar2 = local_30;
                if (local_30 == (undefined1 *)0x0) {
                    puVar2 = &DAT_0120546e;
                }
                FUN_00981e70(puVar2, local_34 == 0, 0);
                if (local_30 != (undefined1 *)0x0) {
                    (*local_24)(local_30);
                }
                if (local_20 != 0) {
                    (*local_14)(local_20);
                }
                local_34 = uVar6 + 1;
                pcVar5 = pcVar5 + 0x558;
                uVar6 = local_38;
            } while (local_34 < *(uint *)(local_3c + 0x2048));
        }
        // Set controller update function pointer
        *(code **)(uVar6 + 0x14) = FUN_008f4d70;
        FUN_00982400(0);
        FUN_00982e10();
        FUN_0068c590(1);
        if (local_10 != (undefined1 *)0x0) {
            (*pcStack_4)(local_10);
        }
        return;
    }
    // If flag is set, handle controller disconnection
    if (*(int *)(this + 0x2048) != 0) {
        uVar6 = 1;
        local_38 = 0;
        if (1 < *(uint *)(this + 0x2048)) {
            iVar4 = 0;
            iVar8 = 0x558;
            do {
                cVar1 = FUN_00acc870(local_3c + 0x180 + iVar4);
                if (cVar1 != '\0') {
                    iVar4 = iVar8;
                    local_38 = uVar6;
                }
                uVar6 = uVar6 + 1;
                iVar8 = iVar8 + 0x558;
            } while (uVar6 < *(uint *)(local_3c + 0x2048));
        }
        FUN_008f44b0(local_38);
        return;
    }
    // No controllers, handle default state
    FUN_008f3ea0();
    FUN_008f2cf0(2);
    return;
}