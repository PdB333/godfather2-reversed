// FUNC_NAME: TNLConnection::processPacketBuffer
void TNLConnection::processPacketBuffer(int param_1, int *param_2) // 0x00548440
{
    undefined4 *puVar1;
    undefined4 **ppuVar2;
    uint uVar3;
    uint uVar4;
    int iVar5;
    int iVar6;
    int this;
    bool bVar7;
    char isResend; // cStack_64
    int packetCount; // iStack_60
    undefined4 *packetData; // puStack_5c
    uint currentSequence; // uStack_58
    uint totalSequences; // uStack_54
    undefined4 *entryData; // puStack_50
    undefined2 uStack_4c;
    undefined4 uStack_48;
    undefined4 **ppuStack_8;

    // Call virtual function at vtable+0x220 (likely getPacketCount or similar)
    (**(code **)(*param_2 + 0x220))();
    // Call some initialization function
    FUN_0043aff0(param_1, 0x1464034a);
    while( true ) {
        if (isResend == '\0') {
            bVar7 = ppuStack_8 == (undefined4 *)0x0;
        }
        else {
            bVar7 = currentSequence == totalSequences;
        }
        if (bVar7) break;
        ppuVar2 = &entryData;
        if (isResend == '\0') {
            ppuVar2 = ppuStack_8;
        }
        if (*(short *)((int)ppuVar2 + 6) == 0x25e3) {
            puVar1 = (undefined4 *)(uint)*(ushort *)(ppuVar2 + 1);
        }
        else {
            puVar1 = ppuVar2[1];
        }
        switch(puVar1) {
        case (undefined4 *)0x0: // packet type 0
            uVar4 = (**(code **)(*param_2 + 0x228))(0); // get sequence count
            uVar3 = 0;
            if (3 < (int)uVar4) {
                iVar5 = (uVar4 - 4 >> 2) + 1;
                uVar3 = iVar5 * 4;
                iVar6 = 0;
                do {
                    ppuVar2 = &entryData;
                    if (isResend == '\0') {
                        ppuVar2 = ppuStack_8;
                    }
                    // Write data to buffer at offset +0x00 per slot
                    *(undefined4 **)(iVar6 + *(int *)(this + 8)) = ppuVar2[2];
                    ppuVar2 = &entryData;
                    if (isResend == '\0') {
                        ppuVar2 = ppuStack_8;
                    }
                    // Write to +0x0C per slot
                    *(undefined4 **)(*(int *)(this + 8) + 0xc + iVar6) = ppuVar2[2];
                    ppuVar2 = &entryData;
                    if (isResend == '\0') {
                        ppuVar2 = ppuStack_8;
                    }
                    // Write to +0x18 per slot
                    *(undefined4 **)(*(int *)(this + 8) + 0x18 + iVar6) = ppuVar2[2];
                    ppuVar2 = &entryData;
                    if (isResend == '\0') {
                        ppuVar2 = ppuStack_8;
                    }
                    // Write to +0x24 per slot
                    *(undefined4 **)(iVar6 + 0x24 + *(int *)(this + 8)) = ppuVar2[2];
                    iVar6 = iVar6 + 0x30; // 0x30 = 48 bytes per slot (4 * 12)
                    iVar5 = iVar5 + -1;
                } while (iVar5 != 0);
            }
            if (uVar3 < uVar4) {
                iVar6 = uVar3 * 0xc;
                iVar5 = uVar4 - uVar3;
                do {
                    ppuVar2 = &entryData;
                    if (isResend == '\0') {
                        ppuVar2 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar6 + *(int *)(this + 8)) = ppuVar2[2];
                    iVar6 = iVar6 + 0xc;
                    iVar5 = iVar5 + -1;
                } while (iVar5 != 0);
            }
            break;
        case (undefined4 *)0x1: // packet type 1
            uVar3 = (**(code **)(*param_2 + 0x228))(0); // get start sequence
            uVar4 = (**(code **)(*param_2 + 0x220))(); // get end sequence
            if (3 < (int)(uVar4 - uVar3)) {
                iVar6 = uVar3 * 0xc;
                iVar5 = ((uVar4 - uVar3) - 4 >> 2) + 1;
                uVar3 = uVar3 + iVar5 * 4;
                do {
                    ppuVar2 = &entryData;
                    if (isResend == '\0') {
                        ppuVar2 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar6 + *(int *)(this + 8)) = ppuVar2[2];
                    ppuVar2 = &entryData;
                    if (isResend == '\0') {
                        ppuVar2 = ppuStack_8;
                    }
                    *(undefined4 **)(*(int *)(this + 8) + 0xc + iVar6) = ppuVar2[2];
                    ppuVar2 = &entryData;
                    if (isResend == '\0') {
                        ppuVar2 = ppuStack_8;
                    }
                    *(undefined4 **)(*(int *)(this + 8) + 0x18 + iVar6) = ppuVar2[2];
                    ppuVar2 = &entryData;
                    if (isResend == '\0') {
                        ppuVar2 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar6 + 0x24 + *(int *)(this + 8)) = ppuVar2[2];
                    iVar6 = iVar6 + 0x30;
                    iVar5 = iVar5 + -1;
                } while (iVar5 != 0);
            }
            if (uVar3 < uVar4) {
                iVar6 = uVar3 * 0xc;
                iVar5 = uVar4 - uVar3;
                do {
                    ppuVar2 = &entryData;
                    if (isResend == '\0') {
                        ppuVar2 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar6 + *(int *)(this + 8)) = ppuVar2[2];
                    iVar6 = iVar6 + 0xc;
                    iVar5 = iVar5 + -1;
                } while (iVar5 != 0);
            }
            break;
        case (undefined4 *)0x2: // packet type 2
            uVar4 = (**(code **)(*param_2 + 0x228))(0);
            uVar3 = 0;
            if (3 < (int)uVar4) {
                iVar6 = 0;
                iVar5 = (uVar4 - 4 >> 2) + 1;
                uVar3 = iVar5 * 4;
                do {
                    ppuVar2 = &entryData;
                    if (isResend == '\0') {
                        ppuVar2 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar6 + 4 + *(int *)(this + 8)) = ppuVar2[2];
                    ppuVar2 = &entryData;
                    if (isResend == '\0') {
                        ppuVar2 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar6 + 0x10 + *(int *)(this + 8)) = ppuVar2[2];
                    ppuVar2 = &entryData;
                    if (isResend == '\0') {
                        ppuVar2 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar6 + 0x1c + *(int *)(this + 8)) = ppuVar2[2];
                    ppuVar2 = &entryData;
                    if (isResend == '\0') {
                        ppuVar2 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar6 + 0x28 + *(int *)(this + 8)) = ppuVar2[2];
                    iVar6 = iVar6 + 0x30;
                    iVar5 = iVar5 + -1;
                } while (iVar5 != 0);
            }
            if (uVar3 < uVar4) {
                iVar6 = uVar3 * 0xc;
                iVar5 = uVar4 - uVar3;
                do {
                    ppuVar2 = &entryData;
                    if (isResend == '\0') {
                        ppuVar2 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar6 + 4 + *(int *)(this + 8)) = ppuVar2[2];
                    iVar6 = iVar6 + 0xc;
                    iVar5 = iVar5 + -1;
                } while (iVar5 != 0);
            }
            break;
        case (undefined4 *)0x3: // packet type 3
            uVar3 = (**(code **)(*param_2 + 0x228))(0);
            uVar4 = (**(code **)(*param_2 + 0x220))();
            if (3 < (int)(uVar4 - uVar3)) {
                iVar6 = uVar3 * 0xc;
                iVar5 = ((uVar4 - uVar3) - 4 >> 2) + 1;
                uVar3 = uVar3 + iVar5 * 4;
                do {
                    ppuVar2 = &entryData;
                    if (isResend == '\0') {
                        ppuVar2 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar6 + 4 + *(int *)(this + 8)) = ppuVar2[2];
                    ppuVar2 = &entryData;
                    if (isResend == '\0') {
                        ppuVar2 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar6 + 0x10 + *(int *)(this + 8)) = ppuVar2[2];
                    ppuVar2 = &entryData;
                    if (isResend == '\0') {
                        ppuVar2 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar6 + 0x1c + *(int *)(this + 8)) = ppuVar2[2];
                    ppuVar2 = &entryData;
                    if (isResend == '\0') {
                        ppuVar2 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar6 + 0x28 + *(int *)(this + 8)) = ppuVar2[2];
                    iVar6 = iVar6 + 0x30;
                    iVar5 = iVar5 + -1;
                } while (iVar5 != 0);
            }
            if (uVar3 < uVar4) {
                iVar6 = uVar3 * 0xc;
                iVar5 = uVar4 - uVar3;
                do {
                    ppuVar2 = &entryData;
                    if (isResend == '\0') {
                        ppuVar2 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar6 + 4 + *(int *)(this + 8)) = ppuVar2[2];
                    iVar6 = iVar6 + 0xc;
                    iVar5 = iVar5 + -1;
                } while (iVar5 != 0);
            }
            break;
        case (undefined4 *)0x4: // packet type 4
            ppuVar2 = &entryData;
            if (isResend == '\0') {
                ppuVar2 = ppuStack_8;
            }
            *(undefined4 **)(this + 0x14) = ppuVar2[2]; // store at offset +0x14
            break;
        case (undefined4 *)0x5: // packet type 5
            ppuVar2 = &entryData;
            if (isResend == '\0') {
                ppuVar2 = ppuStack_8;
            }
            puVar1 = ppuVar2[2];
            iVar6 = (**(code **)(*param_2 + 0x228))(0);
            if (iVar6 != 0) {
                iVar5 = 0;
                do {
                    // Set boolean at +0x08 per slot
                    *(bool *)(iVar5 + 8 + *(int *)(this + 8)) = puVar1 != (undefined4 *)0x0;
                    iVar5 = iVar5 + 0xc;
                    iVar6 = iVar6 + -1;
                } while (iVar6 != 0);
            }
            break;
        case (undefined4 *)0x6: // packet type 6
            ppuVar2 = &entryData;
            if (isResend == '\0') {
                ppuVar2 = ppuStack_8;
            }
            puVar1 = ppuVar2[2];
            uVar3 = (**(code **)(*param_2 + 0x228))(0);
            uVar4 = (**(code **)(*param_2 + 0x220))();
            if (uVar3 < uVar4) {
                iVar6 = uVar3 * 0xc;
                iVar5 = uVar4 - uVar3;
                do {
                    *(bool *)(iVar6 + 8 + *(int *)(this + 8)) = puVar1 != (undefined4 *)0x0;
                    iVar6 = iVar6 + 0xc;
                    iVar5 = iVar5 + -1;
                } while (iVar5 != 0);
            }
        }
        // Advance to next packet entry
        if (isResend == '\0') {
            if ((int)currentSequence < 0) {
                ppuStack_8 = (undefined4 **)((int)ppuStack_8 + (int)*ppuStack_8);
                FUN_0043b140();
            }
            else if ((int)currentSequence < (int)(totalSequences - 1)) {
                currentSequence = currentSequence + 1;
                ppuStack_8 = (undefined4 **)((int)ppuStack_8 + (int)*ppuStack_8);
            }
            else {
                ppuStack_8 = (undefined4 **)&DAT_01163cf8;
            }
        }
        else {
            currentSequence = currentSequence + 1;
            if (currentSequence != totalSequences) {
                uStack_4c = (short)currentSequence;
                if ((*(byte *)((currentSequence >> 3) + packetCount) & (byte)(1 << ((byte)currentSequence & 7))) == 0) {
                    entryData = packetData;
                    uStack_48 = *packetData;
                    packetData = packetData + 1;
                }
                else {
                    entryData = (undefined4 *)0x0;
                    uStack_48 = 0;
                }
            }
        }
    }
    return;
}