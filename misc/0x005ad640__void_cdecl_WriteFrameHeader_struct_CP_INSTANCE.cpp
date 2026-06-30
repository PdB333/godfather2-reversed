// Xbox PDB: void __cdecl WriteFrameHeader(struct CP_INSTANCE *)
// FUNC_NAME: AptActionInterpreter::executeAction
uint* AptActionInterpreter::executeAction(int param_2, void* param_1) // Address: 0x005ad640
{
    code* pcVar1;
    char cVar2;
    uint uVar3;
    uint* puVar4;
    int* piVar5;
    undefined4 uVar6;
    uint uVar7;
    int iVar8;
    int iVar9;
    int iVar10;
    int unaff_FS_OFFSET;
    bool bVar11;
    undefined4 in_XMM0_Da;
    int iStack_1c;
    char* local_14;
    char* local_10;
    undefined4 local_c;
    int local_8;
    undefined1* local_4;

    iVar8 = 2;
    if (param_2 < 2) {
        local_14 = "nParams >= 2";
        local_10 = "..\\source\\Apt\\AptActionInterpreter.cpp";
        local_c = 0x323; // Line 803
        local_8 = 2;
        local_4 = &DAT_01128fe6;
        if (DAT_01128fe6 != '\0') {
            piVar5 = *(int**)(**(int**)(unaff_FS_OFFSET + 0x2c) + 0x30);
            uVar3 = 1;
            if (((piVar5 == (int*)0x0) ||
                (uVar3 = (**(code**)(*piVar5 + 8))(&local_14, "nParams >= 2"),
                    local_4 != (undefined1*)0x0)) && ((uVar3 & 2) != 0)) {
                *local_4 = 0;
            }
            if (((piVar5 != (int*)0x0) || (local_8 != 4)) &&
                (((uVar3 & 1) != 0 || ((local_8 == 0 || (local_8 == 1)))))) {
                pcVar1 = (code*)swi(3);
                puVar4 = (uint*)(*pcVar1)();
                return puVar4;
            }
        }
    }
    uVar3 = 0;
    puVar4 = (uint*)FUN_005a0d00(0); // GetActionValue(0) - first parameter
    FUN_005a0d00(1); // GetActionValue(1) - second parameter (likely action type)
    iVar10 = DAT_0119a9cc; // gInterpreter
    iStack_1c = 2;
    if ((~(byte)(*puVar4 >> 0xf) & 1) == 0) {
        piVar5 = (int*)(DAT_0119a9cc + 0x2518); // gInterpreter->actionSlots (array of 64, each 0x2c bytes)
        do {
            if (*piVar5 == 0) {
                *(int*)(DAT_0119a9cc + 0x3018) = *(int*)(DAT_0119a9cc + 0x3018) + 1; // gInterpreter->activeActionCount++
                iVar9 = uVar3 * 0x2c;
                *(undefined4*)(iVar10 + 0x2518 + iVar9) = 1; // Mark slot as active
                cVar2 = FUN_005a3dc0(); // IsActionDefined?
                if (cVar2 == '\0') {
                    cVar2 = FUN_005a81b0(); // IsSpriteDefined?
                    if (cVar2 == '\0') {
                        FUN_0059c3b0(); // CreateSprite
                        cVar2 = FUN_005a3fc0(); // IsSpriteReady?
                        if (cVar2 == '\0') goto LAB_005ad7e6;
                    }
                    FUN_005a0d00(2); // GetActionValue(2)
                    cVar2 = FUN_005a81b0(); // IsSpriteDefined?
                    if (cVar2 == '\0') {
                        iVar8 = FUN_005a0d00(1); // GetActionValue(1)
                        puVar4 = (uint*)FUN_005bc230(*(undefined4*)(iVar8 + 0xc)); // GetMovieClip from sprite
                    }
                    else {
                        FUN_005a0d00(1); // GetActionValue(1)
                        puVar4 = (uint*)FUN_005bb150(puVar4 + 1); // GetSprite from action value
                    }
                    iStack_1c = 3;
                    iVar8 = 3;
                }
LAB_005ad7e6:
                bVar11 = puVar4 != DAT_0119cbbc; // isSpriteValid?
                *(uint**)(DAT_0119a9cc + 0x251c + iVar9) = puVar4; // Store sprite pointer in action slot
                if (bVar11) {
                    uVar7 = *puVar4 & 0x7fff;
                    if ((uVar7 != 0x19) &&
                        (((~(byte)(*puVar4 >> 0xf) & 1) != 0 ||
                            (((uVar7 != 0xb && (uVar7 != 0x18)) && (uVar7 != 0x17)))))) {
                        FUN_0059c230(puVar4); // AddReference (increment sprite ref count)
                    }
                }
                FUN_005a9040(); // ProcessAction?
                iVar10 = DAT_0119a9cc;
                *(undefined4*)((uVar3 + 0xd8) * 0x2c + DAT_0119a9cc) = in_XMM0_Da; // Store float value in slot (likely duration)
                *(undefined4*)(iVar10 + 0x2524 + iVar9) = in_XMM0_Da; // Also store in action target
                if (iVar8 < param_2) {
                    iVar10 = 0;
                    if (0 < param_2 - iVar8) {
                        do {
                            uVar6 = FUN_005a0d00(iVar10 + iStack_1c);
                            FUN_005b1a70(uVar6); // Push parameter onto stack
                            iVar10 = iVar10 + 1;
                        } while (iVar10 < param_2 - iVar8);
                    }
                }
                break;
            }
            uVar3 = uVar3 + 1;
            piVar5 = piVar5 + 0xb;
        } while ((int)uVar3 < 0x40);
        if (uVar3 == 0x40) {
            local_14 = "i != 64";
            local_10 = "..\\source\\Apt\\AptActionInterpreter.cpp";
            local_c = 0x35b; // Line 859
            local_8 = 2;
            local_4 = &DAT_01128fe7;
            if (DAT_01128fe7 != '\0') {
                piVar5 = *(int**)(**(int**)(unaff_FS_OFFSET + 0x2c) + 0x30);
                uVar7 = 1;
                if (((piVar5 == (int*)0x0) ||
                    (uVar7 = (**(code**)(*piVar5 + 8))(&local_14, "i != 64"), local_4 != (undefined1*)0x0))
                    && ((uVar7 & 2) != 0)) {
                    *local_4 = 0;
                }
                if (((piVar5 != (int*)0x0) || (local_8 != 4)) &&
                    (((uVar7 & 1) != 0 || ((local_8 == 0 || (local_8 == 1)))))) {
                    pcVar1 = (code*)swi(3);
                    puVar4 = (uint*)(*pcVar1)();
                    return puVar4;
                }
            }
        }
        // Create action result value (positive, with action ID)
        puVar4 = (uint*)(*DAT_0119caf0)(8, 0); // AllocateValue(8, 0)
        if (puVar4 != (uint*)0x0) {
            *puVar4 = *puVar4 & 0xffff8007 | 7; // Set type to Action (7)
            *(undefined2*)((int)puVar4 + 2) = 0;
            puVar4[1] = uVar3; // Store action slot index
            *puVar4 = *puVar4 | 0x8000; // Mark as valid
            return puVar4;
        }
    }
    else {
        // Invalid action, return error value (zero slot)
        puVar4 = (uint*)(*DAT_0119caf0)(8, 0); // AllocateValue(8, 0)
        if (puVar4 != (uint*)0x0) {
            *puVar4 = *puVar4 & 0xffff8007 | 7; // Set type to Action (7)
            *(undefined2*)((int)puVar4 + 2) = 0;
            puVar4[1] = 0; // Slot index 0 (invalid)
            *puVar4 = *puVar4 | 0x8000; // Mark as valid
            return puVar4;
        }
    }
    return (uint*)0x0; // Failed to allocate value
}