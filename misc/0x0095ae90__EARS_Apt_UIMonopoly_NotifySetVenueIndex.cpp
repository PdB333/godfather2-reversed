// Xbox PDB: EARS_Apt_UIMonopoly_NotifySetVenueIndex
// FUNC_NAME: CityStatusPanel::updateTooltip
void __fastcall CityStatusPanel::updateTooltip(int thisPtr)
{
    uint businessIndex;
    float fVar2;
    char cVar3;
    int businessPtr;
    undefined4 *puVar5;
    undefined1 *puVar6;
    undefined4 uVar7;
    int iVar8;
    int iVar9;
    undefined1 **ppuVar10;
    undefined4 uVar11;
    char *pcVar12;
    undefined1 *local_1040;
    undefined4 local_103c;
    undefined4 local_1038;
    code *local_1034;
    longlong local_1030;
    undefined4 local_1028;
    undefined1 *local_1024;
    undefined4 local_1020;
    undefined4 local_101c;
    code *local_1018;
    undefined1 local_1014 [4112];
    undefined4 uStack_4;

    uStack_4 = 0x95ae9a;
    // Get current business index (or invalid sentinel)
    businessIndex = *(uint *)(thisPtr + 0x94);
    iVar9 = 0;
    if ((businessIndex != 0xffffffff) && (businessIndex < *(uint *)(thisPtr + 0x68))) {
        // Look up the business pointer from array at +0x64
        iVar9 = FUN_006b0ee0(*(undefined4 *)(*(int *)(thisPtr + 100) + businessIndex * 4));
    }
    // Clear tooltip flags
    *(undefined1 *)(thisPtr + 0xbf) = 0;
    *(undefined1 *)(thisPtr + 0xbe) = 0;
    *(undefined1 *)(thisPtr + 0xbd) = 0;
    *(undefined1 *)(thisPtr + 0xbc) = 0;
    if (iVar9 == 0) {
        // No business selected; reset all fields
        *(undefined4 *)(thisPtr + 0x90) = 0;
        *(undefined4 *)(thisPtr + 0x94) = 0xffffffff;
        **(undefined1 **)(thisPtr + 0x98) = 0;
        **(undefined1 **)(thisPtr + 0x9c) = 0;
        **(undefined1 **)(thisPtr + 0xa0) = 0;
        **(undefined1 **)(thisPtr + 0xa4) = 0;
        **(undefined1 **)(thisPtr + 0xa8) = 0;
        **(undefined1 **)(thisPtr + 0xac) = 0;
        *(undefined4 *)(thisPtr + 0xb4) = 0;
        *(undefined4 *)(thisPtr + 0xb8) = 0;
        *(undefined1 *)(thisPtr + 0xb0) = 0;
        return;
    }
    // Get business name (global string from some manager)
    iVar4 = FUN_006b2160();
    uVar7 = *(undefined4 *)(iVar4 + 4);
    puVar5 = (undefined4 *)FUN_006b2160();
    puVar6 = (undefined1 *)*puVar5;
    if (puVar6 == (undefined1 *)0x0) {
        puVar6 = &DAT_0120546e; // empty string?
    }
    FUN_005c4660(*(undefined4 *)(thisPtr + 0x98), puVar6, 0x80, uVar7); // copy business name to buffer
    // Get business status (e.g., closed, open, bombed)
    uVar7 = FUN_0095a800(iVar9);
    *(undefined4 *)(thisPtr + 0xb4) = uVar7;
    *(undefined4 *)(thisPtr + 0xb8) = *(undefined4 *)(iVar9 + 0x68); // some other status value
    // Get owner (family) info
    iVar4 = FUN_00849cf0(*(undefined4 *)(iVar9 + 0x48));
    if (iVar4 == 0) {
        **(undefined1 **)(thisPtr + 0x9c) = 0;
        *(undefined1 *)(thisPtr + 0xb0) = 0;
    } else {
        iVar8 = FUN_00849530();
        uVar7 = *(undefined4 *)(iVar8 + 4);
        puVar5 = (undefined4 *)FUN_00849530();
        puVar6 = (undefined1 *)*puVar5;
        if (puVar6 == (undefined1 *)0x0) {
            puVar6 = &DAT_0120546e;
        }
        FUN_005c4660(*(undefined4 *)(thisPtr + 0x9c), puVar6, 0x20, uVar7); // copy owner name
        cVar3 = FUN_006b4440(); // check something (e.g., bombed status?)
        if ((cVar3 == '\0') || ((~*(byte *)(iVar4 + 0x58) & 1) == 0)) {
            *(undefined1 *)(thisPtr + 0xb0) = 0;
        } else {
            *(undefined1 *)(thisPtr + 0xb0) = 1;
        }
    }
    // Get building info (e.g., building name, tooltip)
    iVar4 = FUN_008c74d0(*(undefined4 *)(iVar9 + 0x40));
    if (iVar4 == 0) {
        **(undefined1 **)(thisPtr + 0xa0) = 0;
        **(undefined1 **)(thisPtr + 0xa4) = 0;
    } else {
        iVar8 = FUN_008be2d0();
        uVar7 = *(undefined4 *)(iVar8 + 4);
        puVar5 = (undefined4 *)FUN_008be2d0();
        puVar6 = (undefined1 *)*puVar5;
        if (puVar6 == (undefined1 *)0x0) {
            puVar6 = &DAT_0120546e;
        }
        FUN_005c4660(*(undefined4 *)(thisPtr + 0xa0), puVar6, 0x20, uVar7); // copy building name
        puVar6 = *(undefined1 **)(iVar4 + 0x8c);
        if (puVar6 == (undefined1 *)0x0) {
            puVar6 = &DAT_0120546e;
        }
        FUN_005c4660(*(undefined4 *)(thisPtr + 0xa4), puVar6, 0x20, *(undefined4 *)(iVar4 + 0x90)); // copy another string
        if (*(char *)(thisPtr + 0xb0) != '\0') {
            *(undefined4 *)(thisPtr + 0xbc) = *(undefined4 *)(iVar4 + 0xf8); // copy some data if flag set
        }
    }
    // Get localized tooltip string for business status (e.g., "opening soon", "bombed")
    uVar11 = 1;
    ppuVar10 = &local_1040;
    local_1040 = (undefined1 *)0x0;
    local_103c = 0;
    local_1038 = 0;
    local_1034 = (code *)0x0;
    local_1028 = DAT_012234a4;
    uVar7 = FUN_006b1a20(ppuVar10, 1); // get string from resource
    FUN_00604000(uVar7, ppuVar10, uVar11); // format with arguments
    puVar6 = local_1040;
    if (local_1040 == (undefined1 *)0x0) {
        puVar6 = &DAT_0120546e;
    }
    FUN_005c4660(*(undefined4 *)(thisPtr + 0xa8), puVar6, 0x20, local_103c); // copy formatted string
    **(undefined1 **)(thisPtr + 0xac) = 0; // clear tooltip text initially
    // Check if we need to show a timer or special tooltip
    iVar4 = FUN_006b4860();
    if (iVar4 == 0) goto LAB_0095b20f;
    // Begin debug output for timer display
    FUN_00604be0();
    local_1024 = (undefined1 *)0x0;
    local_1020 = 0;
    local_101c = 0;
    local_1018 = (code *)0x0;
    iVar8 = FUN_006b27f0(); // get current game time (seconds?)
    uVar7 = local_1028;
    fVar2 = (float)iVar8;
    if (iVar8 < 0) {
        fVar2 = fVar2 + DAT_00e44578;
    }
    local_1030 = (longlong)ROUND(fVar2 * *(float *)(DAT_0112a53c + 0x70)); // convert to some time unit
    FUN_006042a0((uint)local_1030 / 0xe10, ((uint)local_1030 % 0xe10) / 0x3c, &local_1024); // format hours:minutes
    puVar6 = local_1024;
    if (local_1024 == (undefined1 *)0x0) {
        puVar6 = &DAT_0120546e;
    }
    FUN_00604c10(0x6e, puVar6); // debug print with ID 0x6e
    if (((*(int *)(iVar9 + 0x16c) != 1) && (*(int *)(iVar9 + 0x16c) != 2)) ||
       (0.0 < *(float *)(iVar9 + 0x170))) {
        if (((iVar4 == 2) || (iVar4 == 3)) || (iVar4 == 4)) {
            pcVar12 = "$pause_city_tooltip_bombed";
            goto LAB_0095b1c4;
        }
        if (iVar4 == 1) {
            pcVar12 = "$pause_city_tooltip_closed";
            goto LAB_0095b1c4;
        }
    } else {
        pcVar12 = "$pause_city_tooltip_openingsoon";
LAB_0095b1c4:
        FUN_006038a0(uVar7, local_1014, &local_1040, pcVar12); // format localized string
    }
    puVar6 = local_1040;
    if (local_1040 == (undefined1 *)0x0) {
        puVar6 = &DAT_0120546e;
    }
    FUN_005c4660(*(undefined4 *)(thisPtr + 0xac), puVar6, 0x80, local_103c); // copy final tooltip text
    if (local_1024 != (undefined1 *)0x0) {
        (*local_1018)(local_1024);
    }
    FUN_00604c00(); // end debug output
LAB_0095b20f:
    if (local_1040 == (undefined1 *)0x0) {
        return;
    }
    (*local_1034)(local_1040); // release allocated string
    return;
}