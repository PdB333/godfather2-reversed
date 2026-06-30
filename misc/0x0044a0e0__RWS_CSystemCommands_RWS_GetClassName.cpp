// Xbox PDB: RWS::CSystemCommands::RWS_GetClassName
// FUNC_NAME: EARSConnection::buildReliablePacket

void EARSConnection::buildReliablePacket(void)
{
    int *piVar1;
    undefined8 uVar2;
    undefined8 uVar3;
    char cVar4;
    int iVar5;
    undefined4 *puVar6;
    int iVar7;
    int *piVar8;
    char *pcVar9;
    int *piVar10;
    undefined4 uVar11;
    undefined4 *puVar12;
    undefined4 *puVar13;
    undefined1 uStack_51d;
    undefined4 *puStack_51c;
    uint uStack_518;
    int iStack_514;
    undefined4 *puStack_510;
    undefined4 uStack_50c;
    undefined4 uStack_508;
    undefined4 uStack_504;
    undefined4 uStack_500;
    uint uStack_4fc;
    uint uStack_4f8;
    int iStack_4f4;
    int iStack_4f0;
    int iStack_4ec;
    int iStack_4e8;
    undefined4 uStack_4e4;
    int aiStack_4e0[3];
    undefined4 uStack_4d4;
    undefined4 uStack_4c4;
    undefined4 uStack_4b4;
    undefined4 uStack_4a4;
    int aiStack_4a0[3];
    undefined4 uStack_494;
    undefined4 uStack_484;
    undefined4 uStack_474;
    undefined4 uStack_464;
    undefined1 auStack_454[4];
    undefined4 auStack_450[15];
    undefined1 auStack_414[4];
    undefined1 auStack_410[16];
    undefined1 auStack_400[16];
    int aiStack_3f0[251];

    DAT_012053f0 = this; // reentrancy guard
    iVar5 = (**(code **)(**(int **)(*(int *)(this + 8) + 8) + 0x1c))(); // get some object size/info
    uStack_50c = *(undefined4 *)(iVar5 + 0x20);
    uStack_508 = *(undefined4 *)(iVar5 + 0x24);
    uStack_504 = *(undefined4 *)(iVar5 + 0x28);
    uStack_500 = *(undefined4 *)(iVar5 + 0x2c);
    uStack_4fc = *(uint *)(iVar5 + 0x1c);
    if (uStack_4fc == 0) {
        DAT_012053f0 = 0;
        return;
    }
    puStack_51c = *(undefined4 **)(this + 4); // pointer to command list structure
    auStack_400._0_12_ = SUB1612((undefined1 [16])0x0, 0);
    auStack_400[0xc] = 4;
    auStack_410 = ZEXT416(uStack_4fc) << 0x40;
    auStack_400 = ZEXT516(auStack_400._8_5_) << 0x40;
    puVar6 = (undefined4 *)FUN_00449be0(*(undefined2 *)(this + 0x18)); // get packet type info
    iStack_4ec = puVar6[1];
    iStack_4e8 = puVar6[2];
    uVar11 = *puVar6;
    uStack_4e4 = puVar6[3];
    iVar5 = FUN_0043b610(); // get current write offset in temporary buffer
    if ((undefined4 *)((int)aiStack_3f0 + iVar5) != (undefined4 *)0x0) {
        *(undefined4 *)((int)aiStack_3f0 + iVar5) = 0x18; // header size: 24 bytes
        *(undefined4 *)((int)aiStack_3f0 + iVar5 + 4) = 0x40000000; // flags? type?
        *(undefined4 *)((int)aiStack_3f0 + iVar5 + 8) = uVar11; // first part of object reference
        *(int *)((int)aiStack_3f0 + iVar5 + 0xc) = iStack_4ec;
        *(int *)((int)aiStack_3f0 + iVar5 + 0x10) = iStack_4e8;
        *(undefined4 *)((int)aiStack_3f0 + iVar5 + 0x14) = uStack_4e4;
    }
    puVar12 = (undefined4 *)((int)aiStack_3f0 + iVar5 + 0x18); // current write pointer after header
    puStack_510 = (undefined4 *)(**(code **)(**(int **)(*(int *)(this + 8) + 8) + 4))(); // get packet data start? copy 0x40 bytes
    puVar6 = puStack_510;
    puVar13 = auStack_450;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar13 = *puVar6;
        puVar6 = puVar6 + 1;
        puVar13 = puVar13 + 1;
    }
    uStack_4f8 = (uint)*(ushort *)(puStack_51c + 8); // number of commands
    iStack_514 = 0;
    uStack_518 = 0;
    if (uStack_4f8 != 0) {
        do {
            piVar8 = *(int **)(puStack_51c[7] + uStack_518 * 4); // command pointer array at offset 0x1c? (+7*4=0x1c of struct)
            iVar5 = piVar8[2]; // command data size?
            uVar11 = 0;
            if (iStack_514 != iVar5) {
                iVar7 = FUN_0043b5d0(); // align buffer
                puVar12 = (undefined4 *)((int)puVar12 + iVar7);
                iStack_514 = iVar5;
            }
            iVar5 = piVar8[5]; // type field
            iVar7 = piVar8[3]; // group/channel
            if (iVar5 < 0x11) {
                if (iVar5 != 0x10) {
                    switch(iVar5) {
                    case 1: // byte
                        uStack_51d = (char)*piVar8 != '\0';
                        piVar10 = (int *)&uStack_51d;
                        break;
                    case 2: // short int? (falls through to 0x40)
                        goto switchD_0044a272_caseD_2;
                    default:
                        goto switchD_0044a272_caseD_3;
                    case 4: // int32
                        iStack_4f4 = *piVar8;
                        piVar10 = &iStack_4f4;
                        break;
                    case 8: // string (null-terminated)
                        piVar10 = (int *)*piVar8;
                        piVar8 = piVar10;
                        do {
                            iVar5 = *piVar8;
                            piVar8 = (int *)((int)piVar8 + 1);
                        } while ((char)iVar5 != '\0');
                        // piVar10 points to string, piVar8 ends after null
                    }
                    goto LAB_0044a44c;
                }
                // case 0x10: compound data (3 QWORDs)
                iVar5 = *piVar8;
                uStack_50c = *(undefined4 *)(iVar5 + 0xc);
                uStack_508 = *(undefined4 *)(iVar5 + 0x10);
                uVar2 = *(undefined8 *)(iVar5 + 0xc);
                uStack_504 = *(undefined4 *)(iVar5 + 0x14);
                uStack_500 = *(undefined4 *)(iVar5 + 0x18);
                uVar3 = *(undefined8 *)(iVar5 + 0x14);
                if (puVar12 != (undefined4 *)0x0) {
                    *puVar12 = 0x18; // size of this entry
                    puVar12[1] = iVar7; // group
                    *(undefined8 *)(puVar12 + 2) = uVar2; // first QWORD
                    *(undefined8 *)(puVar12 + 4) = uVar3; // second QWORD
                }
                puVar12 = puVar12 + 6; // advance by 6 dwords (24 bytes)
                goto switchD_0044a272_caseD_3;
            }
            switch(iVar5) {
            case 0x20:
                FUN_004a36a0(aiStack_4e0);
                uStack_464 = DAT_00e2b1a4;
                uStack_494 = uVar11;
                uStack_484 = uVar11;
                uStack_474 = uVar11;
                FUN_00449da0(aiStack_4a0, aiStack_4e0);
                if (piVar8[4] != -0x2aaf9774) { // magic number check
                    piVar10 = aiStack_4a0;
                    if (piVar8[4] == -0x221046b2) { // another magic
                        uStack_4d4 = 0;
                        uStack_4c4 = 0;
                        uStack_4b4 = 0;
                        uStack_4a4 = DAT_00e2b1a4;
                        FUN_00424540(aiStack_4e0, piVar10, puStack_510);
                        piVar10 = aiStack_4e0;
                    }
                    goto LAB_0044a44c;
                }
                FUN_00417560();
                break;
            case 0x40: // int32 command
switchD_0044a272_caseD_2:
                iVar5 = *piVar8; // value
                if (puVar12 != (undefined4 *)0x0) {
                    *puVar12 = 0xc; // size: 12 bytes
                    puVar12[1] = iVar7; // group
                    puVar12[2] = iVar5; // value
                }
                puVar12 = puVar12 + 3;
                break;
            case 0x80: // three int32s
                piVar8 = (int *)*piVar8;
                iStack_4f0 = *piVar8;
                iStack_4ec = piVar8[1];
                iStack_4e8 = piVar8[2];
                piVar10 = &iStack_4f0;
                goto LAB_0044a44c;
            case 0x100: // pointer to raw data
                piVar10 = (int *)*piVar8;
LAB_0044a44c:
                iVar5 = FUN_0043b650(iVar7, piVar10); // serialize with alignment
                puVar12 = (undefined4 *)((int)puVar12 + iVar5);
            }
switchD_0044a272_caseD_3:
            uStack_518 = uStack_518 + 1;
        } while (uStack_518 < uStack_4f8);
    }
    puVar6 = puStack_51c;
    piVar8 = (int *)(**(code **)(**(int **)(*(int *)(this + 8) + 8) + 0x20))(); // get some object
    cVar4 = (**(code **)(*piVar8 + 0x5c))(*puVar6); // check if light should be appended
    if (cVar4 != '\0') {
        if (puVar12 != (undefined4 *)0x0) {
            pcVar9 = "EARSLight";
            *puVar12 = 0x24; // size 36? 0x24=36
            puVar12[1] = 0x80000000; // flag
            do {
                cVar4 = *pcVar9;
                pcVar9[(int)(puVar12 + -0x38c489)] = cVar4; // copy string (offset trick)
                pcVar9 = pcVar9 + 1;
            } while (cVar4 != '\0');
        }
        if (puVar12 + 9 != (undefined4 *)0x0) {
            puVar12[9] = 0xc; // size 12
            puVar12[10] = 0x12; // ? group?
            puVar12[0xb] = puVar6 + 3; // pointer to data? offset 12 in struct?
        }
        puVar12 = puVar12 + 0xc; // advance 12 dwords (48 bytes)
    }
    if (puVar12 != (undefined4 *)0x0) {
        pcVar9 = "CSystemCommands";
        *puVar12 = 0x30; // size 48? 0x30=48
        puVar12[1] = 0x80000000;
        do {
            cVar4 = *pcVar9;
            pcVar9[(int)(puVar12 + -0x38c3b5)] = cVar4;
            pcVar9 = pcVar9 + 1;
        } while (cVar4 != '\0');
    }
    if (puVar12 + 0xc != (undefined4 *)0x0) {
        puVar12[0xc] = 0x48; // size 72
        puVar12[0xd] = 1; // count?
        _memcpy(puVar12 + 0xe, auStack_454, 0x40); // copy 0x40 bytes from some saved data
    }
    if (puVar12 + 0x1e != (undefined4 *)0x0) {
        puVar12[0x1e] = 0; // null terminator?
    }
    DAT_01205478 = DAT_01205478 + 1; // increment global counter
    *(undefined4 *)(&DAT_01163fec + DAT_01205478 * 4) = *(undefined4 *)(this + 0x1c); // save some pointer
    DAT_0120547c = DAT_0120547c + 1;
    *(undefined4 *)(&DAT_01163ffc + DAT_0120547c * 4) = *(undefined4 *)(this + 8); // save another pointer
    iVar5 = FUN_00446340(auStack_414, uStack_500, 0); // get something from stack
    piVar8 = (int *)(this + 0xc);
    if (iVar5 == 0) {
        iVar5 = 0;
    }
    else {
        iVar5 = iVar5 + 0x48; // add 72 (size of node)
    }
    iVar7 = *piVar8;
    if (iVar7 != iVar5) {
        if (iVar7 != 0) {
            piVar10 = *(int **)(iVar7 + 4);
            if (piVar10 == piVar8) {
                *(undefined4 *)(iVar7 + 4) = *(undefined4 *)(this + 0x10);
            }
            else {
                piVar1 = (int *)piVar10[1];
                while (piVar1 != piVar8) {
                    piVar10 = (int *)piVar10[1];
                    piVar1 = (int *)piVar10[1];
                }
                piVar10[1] = *(int *)(this + 0x10);
            }
        }
        *piVar8 = iVar5;
        if (iVar5 != 0) {
            *(undefined4 *)(this + 0x10) = *(undefined4 *)(iVar5 + 4);
            *(int **)(iVar5 + 4) = piVar8;
        }
    }
    if ((*piVar8 == 0) || (*piVar8 == 0x48)) {
        *(ushort *)(this + 0x1a) = *(ushort *)(this + 0x1a) | 1;
    }
    else {
        if (DAT_0120547c == 0) {
            uVar11 = 0;
        }
        else {
            uVar11 = *(undefined4 *)(&DAT_01163ffc + DAT_0120547c * 4);
        }
        if (*piVar8 == 0) {
            iVar5 = 0;
        }
        else {
            iVar5 = *piVar8 + -0x48;
        }
        *(undefined4 *)(iVar5 + 0x144) = uVar11;
        piVar10 = (int *)(**(code **)(**(int **)(*(int *)(this + 8) + 8) + 0x20))();
        if (*piVar8 == 0) {
            piVar8 = (int *)0x0;
        }
        else {
            piVar8 = (int *)(*piVar8 + -0x48);
        }
        iVar5 = *piVar8;
        uVar11 = (**(code **)(*piVar10 + 0x24))();
        (**(code **)(iVar5 + 0x114))(uVar11);
    }
    FUN_0044a8e0(); // finalize packet sending?
    DAT_0120547c = DAT_0120547c + -1;
    DAT_01205478 = DAT_01205478 + -1;
    DAT_012053f0 = 0;
    return;
}