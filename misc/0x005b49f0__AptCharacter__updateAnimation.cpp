// FUNC_NAME: AptCharacter::updateAnimation
void AptCharacter::updateAnimation(uint *animNodeList)
{
    char *flagsString;
    char flagChar;
    int compareResult;
    int iVar4;
    undefined *unknownPtr;
    bool bVar6;
    int thisEAX;
    int iVar7;
    int iVar8;
    undefined4 uVar9;
    byte *srcStringPtr;
    byte *dstStringPtr;
    uint *puVar12;
    uint uVar13;
    byte *pbVar14;
    uint uVar15;
    char *pcVar16;
    bool bVar17;
    bool bVar18;
    undefined4 local_a8;
    undefined4 local_a4;
    byte *local_a0;
    byte local_9c[16]; // UTF-16 buffer, size 16 bytes = 8 characters
    char *local_8c;
    int local_88;
    char *local_84;
    char *local_80;
    undefined4 local_7c;
    undefined4 local_78;
    undefined *local_74;
    byte *local_70;
    int local_6c;
    undefined4 uStack_68;
    float fStack_64;
    float fStack_60;
    float fStack_5c;
    float fStack_58;
    undefined4 uStack_54;
    undefined4 uStack_50;
    undefined4 uStack_4c;
    undefined4 uStack_40;
    undefined4 uStack_3c;
    undefined4 uStack_38;
    undefined4 uStack_34;
    undefined4 uStack_30;
    undefined4 uStack_2c;
    undefined4 uStack_28;
    undefined4 uStack_24;
    undefined4 uStack_20;
    undefined4 uStack_1c;
    undefined4 uStack_18;
    undefined4 uStack_14;
    byte *pbStack_c;
    uint uStack_8;

    // Retrieve the flags string from the parent animation, if any.
    if (*(int *)(thisEAX + 0x34) == 0) {
        local_8c = (char *)0x0;
    } else {
        local_8c = *(char **)(*(int *)(thisEAX + 0x34) + 0xc);
    }

    iVar7 = getContext(); // FUN_0059c810
    local_a0 = local_9c;
    local_a8 = 0;
    local_a4 = 0;
    memset(local_9c, 0, 16);

    local_88 = *(int *)(iVar7 + 8);
    bVar17 = false;
    if ((*(int *)(iVar7 + 0x10) == 0) || (*(int *)(iVar7 + 0x14) == 0)) {
        bVar17 = true;
    }

    iVar8 = *(int *)(iVar7 + 0x1c);
    iVar4 = *(int *)(iVar7 + 0x18);
    if (((iVar8 == 0) && (iVar4 == 0)) &&
        (pbVar14 = *(byte **)(local_88 + 0x34), *(byte **)(local_88 + 0x34) != (byte *)0x0)) {
        bVar17 = !bVar17;
        goto checkFinish;
    } else {
        // Walk the anim node list to see if it contains specific IDs (0xd or 0x12)
        if (animNodeList != (uint *)0x0) {
            do {
                uVar13 = *animNodeList & 0x7fff;
                if (((*animNodeList & 0x8000) != 0) && ((uVar13 == 0xd || (uVar13 == 0x12)))) break;
                animNodeList = (uint *)animNodeList[0x15];
            } while (animNodeList != (uint *)0x0);
        }

        if (iVar8 == 0) {
            pcVar16 = (char *)0x0;
        } else {
            pcVar16 = *(char **)(iVar8 + 0xc);
        }

        bVar18 = false;
        if (((pcVar16 != (char *)0x0) && (*pcVar16 == 'e')) && (pcVar16[1] == '.')) {
            bVar18 = true; // starts with "e."
        }

        bVar6 = false;
        puVar12 = DAT_0119cbbc; // some known reference object
        if ((!bVar18) && (iVar8 != 0)) {
            if ((DAT_0103af70 == 0) &&
                ((*(int *)(iVar7 + 0x10) != 0 && (iVar8 = getSomeString(), **(char **)(iVar8 + 0xc) != '\0')))) {
                puVar12 = *(uint **)(iVar7 + 0x10);
                bVar6 = true;
            } else {
                puVar12 = (uint *)loadResource(animNodeList, 0, *(undefined4 *)(*(int *)(iVar7 + 0x1c) + 0xc), 1, 1);
            }
        }

        if ((*(int *)(iVar7 + 0x1c) == 0) || ((~(byte)(*puVar12 >> 0xf) & 1) != 0)) {
            if (bVar18) {
                if (!bVar17) {
                    if ((((pcVar16[2] == 'g') && (pcVar16[3] == 'a')) && (pcVar16[4] == 'm')) &&
                        (pcVar16[5] == 'e')) goto LAB_005b4e64;
                    bVar17 = true;
                }
                if ((*(int *)(iVar7 + 0x1c) != 0) &&
                    ((*DAT_0119cb30)(pcVar16 + 2, &local_6c, &local_70), pbVar14 = local_70, local_6c == 1))
                    bVar17 = !bVar17;
            }
LAB_005b4e64:
            if (iVar4 == 0) {
                pbVar14 = *(byte **)(local_88 + 0x34);
            } else {
                if (!bVar17) {
                    if (DAT_0103af70 == 0) goto LAB_005b52b6;
                    buildString(&local_a8);
                    iVar8 = getSomeString();
                    pbVar14 = *(byte **)(iVar8 + 0xc);
                    // String compare (UTF-16) between local_a0 and pbVar14
                    dstStringPtr = local_a0;
                    do {
                        // compare 2-byte characters
                        // ... (omitted for brevity, but logic sets iVar8 to 0 if equal)
                    } while (bVar2 != 0);
                    iVar8 = 0;
                } else {
                    buildString(&local_a8);
                    pbVar14 = local_a0;
                }
                bVar17 = !bVar17;
            }
            goto checkFinish;
        }

        // ... (large block handling the animation blending setup)
        // It seems to process animation flags and create a new animation object.

    }

    // At the end, if pbVar14 is null, assert
    if (pbVar14 == (byte *)0x0) {
        // assertion failure
        local_84 = "pLiteral";
        local_80 = "..\\source\\Apt\\AptCharacter.cpp";
        local_7c = 0x274;
        local_78 = 2;
        local_74 = &DAT_01129125;
        assertFail();
    }

    // Release old animation object at +0x10
    puVar12 = *(uint **)(iVar7 + 0x10);
    if (puVar12 != (uint *)0x0) {
        (*(code **)(&DAT_0103aee0 + (*puVar12 & 0x7fff) * 4))(puVar12); // release via vtable
    }

    // Allocate new animation object with ID 1 and signature 0xbeefceec
    puVar12 = (uint *)(*DAT_0119caf0)(0x24, 0);
    if (puVar12 == (uint *)0x0) {
        puVar12 = (uint *)0x0;
    } else {
        *puVar12 = *puVar12 & 0xffff8001 | 1;
        *(undefined2 *)((int)puVar12 + 2) = 0;
        *puVar12 = *puVar12 | 0x8000;
        FUN_005a0a80();
        puVar12[8] = 0xbeefceec;
    }

    bVar17 = puVar12 != DAT_0119cbbc;
    *(uint **)(iVar7 + 0x10) = puVar12;
    if (bVar17) {
        uVar13 = *puVar12 & 0x7fff;
        if ((uVar13 != 0x19) &&
            (((~(byte)(*puVar12 >> 0xf) & 1) != 0 ||
             (((uVar13 != 0xb && (uVar13 != 0x18)) && (uVar13 != 0x17)))))) {
            FUN_0059c230(puVar12); // some postprocess
        }
    }

    FUN_005b8920(*(undefined4 *)(iVar7 + 0x10));

    // Same pattern for +0x18
    puVar12 = *(uint **)(iVar7 + 0x18);
    if (puVar12 != (uint *)0x0) {
        (*(code **)(&DAT_0103aee0 + (*puVar12 & 0x7fff) * 4))(puVar12);
    }

    puVar12 = (uint *)(*DAT_0119caf0)(0x24, 0);
    if (puVar12 == (uint *)0x0) {
        puVar12 = (uint *)0x0;
    } else {
        *puVar12 = *puVar12 & 0xffff8001 | 1;
        *(undefined2 *)((int)puVar12 + 2) = 0;
        *puVar12 = *puVar12 | 0x8000;
        FUN_005a0a80();
        puVar12[8] = 0xbeefceec;
    }

    bVar17 = puVar12 != DAT_0119cbbc;
    *(uint **)(iVar7 + 0x18) = puVar12;
    if (bVar17) {
        uVar13 = *puVar12 & 0x7fff;
        if ((uVar13 != 0x19) &&
            (((~(byte)(*puVar12 >> 0xf) & 1) != 0 ||
             (((uVar13 != 0xb && (uVar13 != 0x18)) && (uVar13 != 0x17)))))) {
            FUN_0059c230(puVar12);
        }
    }

    FUN_005b8920(*(undefined4 *)(iVar7 + 0x18));

    // Release old animation object at +0x14
    unknownPtr = *(undefined **)(iVar7 + 0x14);
    if ((unknownPtr != (undefined *)0x0) && (unknownPtr != &DAT_0103ae68)) {
        (*DAT_0119cb3c)(unknownPtr);
    }

    iVar8 = getParentAnim(); // FUN_0059c3b0
    iVar8 = *(int *)(*(int *)(*(int *)(iVar8 + 0x58) + 8) + 4);
    if (iVar8 == -8) {
        // assert
        local_84 = "pParentAnim";
        local_80 = "..\\source\\Apt\\AptCharacter.cpp";
        local_7c = 0x289;
        local_78 = 2;
        local_74 = &DAT_01129126;
        assertFail();
    }

    if (*pbVar14 == 0) {
        // Empty string: no animation
        *(undefined **)(iVar7 + 0x14) = &DAT_0103ae68;
        *(undefined4 *)(iVar7 + 0x44) = 0;
        *(undefined4 *)(iVar7 + 0x48) = 0;
    } else {
        // Build parameters for new animation
        uStack_38 = *(undefined4 *)(local_88 + 0x30);
        uStack_3c = *(undefined4 *)(local_88 + 0x2c);
        uStack_18 = *(undefined4 *)(local_88 + 0x24);
        uStack_50 = *(undefined4 *)(iVar7 + 0x40);
        uStack_14 = *(undefined4 *)(iVar7 + 0x2c);
        uStack_54 = *(undefined4 *)(local_88 + 0x1c);
        uStack_34 = *(undefined4 *)(iVar7 + 0x24);

        if (*(int *)(local_88 + 0x18) < 0) {
            uStack_68 = 0;
        } else {
            uStack_68 = *(undefined4 *)(*(int *)(*(int *)(iVar8 + 0x18) + *(int *)(local_88 + 0x18) * 4) + 8);
        }

        fStack_64 = *(float *)(local_88 + 8);
        uStack_30 = *(undefined4 *)(iVar7 + 0x38);
        uStack_28 = *(undefined4 *)(iVar7 + 0x34);
        fStack_5c = (*(float *)(iVar7 + 0x4c) - fStack_64) + fStack_64;
        uStack_24 = *(undefined4 *)(iVar7 + 0x30);
        fStack_60 = *(float *)(local_88 + 0xc);
        uStack_2c = *(undefined4 *)(iVar7 + 0x3c);
        uVar13 = 0;
        fStack_58 = (*(float *)(iVar7 + 0x50) - fStack_60) + fStack_60;
        uStack_8 = 0;

        pcVar16 = local_8c;
        if (local_8c != (char *)0x0) {
            while (*pcVar16 != '\0') {
                switch(*pcVar16) {
                    case 'B':
                        uVar13 |= 0x20;
                        break;
                    default:
                        goto switch_end;
                    case 'L':
                        flagChar = pcVar16[1];
                        pcVar16++;
                        if (flagChar == 'l') uVar13 |= 0x40000;
                        else if (flagChar == 'm') uVar13 |= 0x20000;
                        else if (flagChar == 's') uVar13 |= 0x10000;
                        break;
                    case 'O':
                        if (pcVar16[1] == '2') {
                            pcVar16++;
                            uVar15 = uVar13 & 0xffffff7f | 0x100;
                        } else {
                            uVar15 = uVar13 | 0x80;
                            if (pcVar16[1] == '3') {
                                pcVar16++;
                                uVar15 = uVar13 & 0xffffff7f | 0x80000;
                            }
                        }
                        uVar13 = uVar15;
                        if (pcVar16[1] == 'b') {
                            uVar13 |= 0x800;
                            pcVar16++;
                        } else if (pcVar16[1] == 'w') {
                            uVar13 |= 0x400;
                            pcVar16++;
                        }
                        break;
                    case 'b':
                        uVar13 |= 8;
                        break;
                    case 'o':
                        uVar13 |= 0x1000;
                        break;
                    case 'q':
                        uVar13 |= 0x200000;
                        break;
                    case 'r':
                        pcVar16++;
                        uVar15 = (int)*pcVar16 - 0x30;
                        if ((uVar15 & 1) != 0) uVar13 |= 0x2000;
                        if ((uVar15 & 2) != 0) uVar13 |= 0x4000;
                        if ((uVar15 & 4) != 0) uVar13 |= 0x8000;
                        break;
                    case 's':
                        uVar13 |= 1;
                        break;
                    case 'v':
                        uVar13 |= 0x10;
                }
                if ((pcVar16 == (char *)0x0) || (pcVar16++, pcVar16 == (char *)0x0)) break;
            }
        }
        switch_end:
        uStack_8 = uVar13;

        pbStack_c = pbVar14;
        uVar9 = (*DAT_0119cb38)(&uStack_68);
        *(undefined4 *)(iVar7 + 0x44) = uStack_20;
        *(undefined4 *)(iVar7 + 0x48) = uStack_1c;
        *(undefined4 *)(iVar7 + 0x14) = uVar9;
        *(undefined4 *)(iVar7 + 0x28) = uStack_4c;
        *(undefined4 *)(iVar7 + 0x54) = uStack_40;
    }

LAB_005b52b6:
    if ((local_a0 != local_9c) && (local_a0 != (byte *)0x0)) {
        (*DAT_0119caf4)(local_a0);
    }
    return;
}