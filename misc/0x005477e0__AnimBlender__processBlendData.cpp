// FUNC_NAME: AnimBlender::processBlendData
void __thiscall AnimBlender::processBlendData(void *thisPtr, int *stream) {
    float *pfVar1;
    float fVar2;
    int numElements;
    undefined4 *puVar4;
    uint uVar5;
    uint uVar6;
    undefined4 **ppuVar7;
    int iVar8;
    char cVar9;
    int iVar10;
    int iVar11;
    int unaff_EDI; // "this" pointer
    bool bVar12;
    char isBitStream;
    int baseArrayOffset; // iStack_60
    undefined4 *puStack_5c;
    uint currentIndex;
    uint endIndex;
    undefined4 *puStack_50;
    undefined2 uStack_4c;
    undefined4 uStack_48;
    undefined4 **ppuStack_8;

    // Get the number of elements to process from a vtable method (offset 0x220)
    numElements = (**(code **)(*stream + 0x220))();
    // Call a hash function to identify the data type? (hash 0xe97cfb79)
    FUN_0043aff0(thisPtr, 0xe97cfb79);
    while (true) {
        if (isBitStream == '\0') {
            bVar12 = *ppuStack_8 == (undefined4 *)0x0;
        } else {
            bVar12 = currentIndex == endIndex;
        }
        if (bVar12) break;
        ppuVar7 = &puStack_50;
        if (isBitStream == '\0') {
            ppuVar7 = ppuStack_8;
        }
        // Read control word (type)
        if (*(short *)((int)ppuVar7 + 6) == 0x25e3) {
            puVar4 = (undefined4 *)(uint)*(ushort *)(ppuVar7 + 1);
        } else {
            puVar4 = ppuVar7[1];
        }
        switch ((int)puVar4) {
        case 0x0:
            // Write to offset 0x0 in each element
            cVar9 = '\0';
            if (0 < numElements) {
                iVar11 = 0;
                do {
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    cVar9 = cVar9 + '\x01';
                    *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + iVar11 * 0x28) = ppuVar7[2];
                    iVar11 = (int)cVar9;
                } while (iVar11 < numElements);
            }
            break;
        case 0x1:
            // Write to offset 0x4
            cVar9 = '\0';
            if (0 < numElements) {
                iVar11 = 0;
                do {
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    cVar9 = cVar9 + '\x01';
                    *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 8 + iVar11 * 0x28) = ppuVar7[2];
                    iVar11 = (int)cVar9;
                } while (iVar11 < numElements);
            }
            break;
        case 0x2:
            // Write to offset 0x8
            cVar9 = '\0';
            if (0 < numElements) {
                iVar11 = 0;
                do {
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    cVar9 = cVar9 + '\x01';
                    *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 4 + iVar11 * 0x28) = ppuVar7[2];
                    iVar11 = (int)cVar9;
                } while (iVar11 < numElements);
            }
            break;
        case 0x3:
            // Write to offsets 0xc, 0x34, 0x5c, 0x84 for groups of 4 elements (stride 0xa0)
            uVar6 = (**(code **)(*stream + 0x228))(0);
            uVar5 = 0;
            if (3 < (int)uVar6) {
                iVar11 = 0;
                iVar8 = (uVar6 - 4 >> 2) + 1;
                uVar5 = iVar8 * 4;
                do {
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar11 + 0xc + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2];
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar11 + 0x34 + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2];
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar11 + 0x5c + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2];
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar11 + 0x84 + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2];
                    iVar11 = iVar11 + 0xa0;
                    iVar8 = iVar8 + -1;
                } while (iVar8 != 0);
            }
            if (uVar5 < uVar6) {
                iVar11 = uVar5 * 0x28;
                iVar8 = uVar6 - uVar5;
                do {
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar11 + 0xc + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2];
                    iVar11 = iVar11 + 0x28;
                    iVar8 = iVar8 + -1;
                } while (iVar8 != 0);
            }
            break;
        case 0x4:
            // Write to offsets 0xc, 0x34, 0x5c, 0x84 for a range starting at uVar5 (getNumElements)
            uVar5 = (**(code **)(*stream + 0x228))(0);
            uVar6 = (**(code **)(*stream + 0x220))();
            if (3 < (int)(uVar6 - uVar5)) {
                iVar11 = uVar5 * 0x28;
                iVar8 = ((uVar6 - uVar5) - 4 >> 2) + 1;
                uVar5 = uVar5 + iVar8 * 4;
                do {
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar11 + 0xc + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2];
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar11 + 0x34 + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2];
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar11 + 0x5c + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2];
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar11 + 0x84 + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2];
                    iVar11 = iVar11 + 0xa0;
                    iVar8 = iVar8 + -1;
                } while (iVar8 != 0);
            }
            if (uVar5 < uVar6) {
                iVar11 = uVar5 * 0x28;
                iVar8 = uVar6 - uVar5;
                do {
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar11 + 0xc + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2];
                    iVar11 = iVar11 + 0x28;
                    iVar8 = iVar8 + -1;
                } while (iVar8 != 0);
            }
            break;
        case 0x5:
            // Write to offsets 0x10, 0x38, 0x60, 0x88
            uVar6 = (**(code **)(*stream + 0x228))(0);
            uVar5 = 0;
            if (3 < (int)uVar6) {
                iVar11 = 0;
                iVar8 = (uVar6 - 4 >> 2) + 1;
                uVar5 = iVar8 * 4;
                do {
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar11 + 0x10 + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2];
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar11 + 0x38 + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2];
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar11 + 0x60 + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2];
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar11 + 0x88 + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2];
                    iVar11 = iVar11 + 0xa0;
                    iVar8 = iVar8 + -1;
                } while (iVar8 != 0);
            }
            if (uVar5 < uVar6) {
                iVar11 = uVar5 * 0x28;
                iVar8 = uVar6 - uVar5;
                do {
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar11 + 0x10 + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2];
                    iVar11 = iVar11 + 0x28;
                    iVar8 = iVar8 + -1;
                } while (iVar8 != 0);
            }
            break;
        case 0x6:
            // Write to offsets 0x10, 0x38, 0x60, 0x88 for a range
            uVar5 = (**(code **)(*stream + 0x228))(0);
            uVar6 = (**(code **)(*stream + 0x220))();
            if (3 < (int)(uVar6 - uVar5)) {
                iVar11 = uVar5 * 0x28;
                iVar8 = ((uVar6 - uVar5) - 4 >> 2) + 1;
                uVar5 = uVar5 + iVar8 * 4;
                do {
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar11 + 0x10 + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2];
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar11 + 0x38 + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2];
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar11 + 0x60 + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2];
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(iVar11 + 0x88 + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2];
                    iVar11 = iVar11 + 0xa0;
                    iVar8 = iVar8 + -1;
                } while (iVar8 != 0);
            }
            if (uVar5 < uVar6) {
                iVar11 = uVar5 * 0x28;
                iVar8 = uVar6 - uVar5;
                do {
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x10 + iVar11) = ppuVar7[2];
                    iVar11 = iVar11 + 0x28;
                    iVar8 = iVar8 + -1;
                } while (iVar8 != 0);
            }
            break;
        case 0x7:
            // Write to offsets 0x14, 0x3c, 0x64, 0x8c
            uVar6 = (**(code **)(*stream + 0x228))(0);
            uVar5 = 0;
            if (3 < (int)uVar6) {
                iVar11 = 0;
                iVar8 = (uVar6 - 4 >> 2) + 1;
                uVar5 = iVar8 * 4;
                do {
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x14 + iVar11) = ppuVar7[2];
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x3c + iVar11) = ppuVar7[2];
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 100 + iVar11) = ppuVar7[2];
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x8c + iVar11) = ppuVar7[2];
                    iVar11 = iVar11 + 0xa0;
                    iVar8 = iVar8 + -1;
                } while (iVar8 != 0);
            }
            if (uVar5 < uVar6) {
                iVar11 = uVar5 * 0x28;
                iVar8 = uVar6 - uVar5;
                do {
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x14 + iVar11) = ppuVar7[2];
                    iVar11 = iVar11 + 0x28;
                    iVar8 = iVar8 + -1;
                } while (iVar8 != 0);
            }
            break;
        case 0x8:
            // Write to offsets 0x14, 0x3c, 0x64, 0x8c for a range
            uVar5 = (**(code **)(*stream + 0x228))(0);
            uVar6 = (**(code **)(*stream + 0x220))();
            if (3 < (int)(uVar6 - uVar5)) {
                iVar11 = uVar5 * 0x28;
                iVar8 = ((uVar6 - uVar5) - 4 >> 2) + 1;
                uVar5 = uVar5 + iVar8 * 4;
                do {
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x14 + iVar11) = ppuVar7[2];
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x3c + iVar11) = ppuVar7[2];
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 100 + iVar11) = ppuVar7[2];
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x8c + iVar11) = ppuVar7[2];
                    iVar11 = iVar11 + 0xa0;
                    iVar8 = iVar8 + -1;
                } while (iVar8 != 0);
            }
            if (uVar5 < uVar6) {
                iVar11 = uVar5 * 0x28;
                iVar8 = uVar6 - uVar5;
                do {
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x14 + iVar11) = ppuVar7[2];
                    iVar11 = iVar11 + 0x28;
                    iVar8 = iVar8 + -1;
                } while (iVar8 != 0);
            }
            break;
        case 0x9:
            // Write to offsets 0x1c, 0x44, 0x6c, 0x94
            uVar6 = (**(code **)(*stream + 0x228))(0);
            uVar5 = 0;
            if (3 < (int)uVar6) {
                iVar11 = 0;
                iVar8 = (uVar6 - 4 >> 2) + 1;
                uVar5 = iVar8 * 4;
                do {
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x1c + iVar11) = ppuVar7[2];
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x44 + iVar11) = ppuVar7[2];
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x6c + iVar11) = ppuVar7[2];
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x94 + iVar11) = ppuVar7[2];
                    iVar11 = iVar11 + 0xa0;
                    iVar8 = iVar8 + -1;
                } while (iVar8 != 0);
            }
            if (uVar5 < uVar6) {
                iVar11 = uVar5 * 0x28;
                iVar8 = uVar6 - uVar5;
                do {
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x1c + iVar11) = ppuVar7[2];
                    iVar11 = iVar11 + 0x28;
                    iVar8 = iVar8 + -1;
                } while (iVar8 != 0);
            }
            break;
        case 0xa:
            // Write to offsets 0x1c, 0x44, 0x6c, 0x94 for a range
            uVar5 = (**(code **)(*stream + 0x228))(0);
            uVar6 = (**(code **)(*stream + 0x220))();
            if (3 < (int)(uVar6 - uVar5)) {
                iVar11 = uVar5 * 0x28;
                iVar8 = ((uVar6 - uVar5) - 4 >> 2) + 1;
                uVar5 = uVar5 + iVar8 * 4;
                do {
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x1c + iVar11) = ppuVar7[2];
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x44 + iVar11) = ppuVar7[2];
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x6c + iVar11) = ppuVar7[2];
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x94 + iVar11) = ppuVar7[2];
                    iVar11 = iVar11 + 0xa0;
                    iVar8 = iVar8 + -1;
                } while (iVar8 != 0);
            }
            if (uVar5 < uVar6) {
                iVar11 = uVar5 * 0x28;
                iVar8 = uVar6 - uVar5;
                do {
                    ppuVar7 = &puStack_50;
                    if (isBitStream == '\0') {
                        ppuVar7 = ppuStack_8;
                    }
                    *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x1c + iVar11) = ppuVar7[2];
                    iVar11 = iVar11 + 0x28;
                    iVar8 = iVar8 + -1;
                } while (iVar8 != 0);
            }
        }
        // Advance the stream pointer
        if (isBitStream == '\0') {
            if ((int)currentIndex < 0) {
                ppuStack_8 = (undefined4 **)((int)ppuStack_8 + (int)*ppuStack_8);
                FUN_0043b140(); // Advance to next block
            } else if ((int)currentIndex < (int)(endIndex - 1)) {
                currentIndex = currentIndex + 1;
                ppuStack_8 = (undefined4 **)((int)ppuStack_8 + (int)*ppuStack_8);
            } else {
                ppuStack_8 = (undefined4 **)&DAT_01163cf8; // End marker
            }
        } else {
            currentIndex = currentIndex + 1;
            if (currentIndex != endIndex) {
                uStack_4c = (short)currentIndex;
                if ((*(byte *)((currentIndex >> 3) + baseArrayOffset) & (byte)(1 << ((byte)currentIndex & 7))) == 0) {
                    puStack_50 = puStack_5c;
                    uStack_48 = *puStack_5c;
                    puStack_5c = puStack_5c + 1;
                } else {
                    puStack_50 = (undefined4 *)0x0;
                    uStack_48 = 0;
                }
            }
        }
    }
    // Clamp interpolated values: for the first 4-element groups
    iVar11 = 0;
    if (3 < numElements) {
        iVar8 = 0;
        iVar10 = (numElements - 4U >> 2) + 1;
        iVar11 = iVar10 * 4;
        do {
            // Compare and clamp (keep the smaller) between offset+0xc and +0x14
            fVar2 = *(float *)(*(int *)(unaff_EDI + 0x8c) + 0xc + iVar8);
            pfVar1 = (float *)(*(int *)(unaff_EDI + 0x8c) + iVar8 + 0x14);
            if (*pfVar1 <= fVar2 && fVar2 != *pfVar1) {
                *(undefined4 *)(*(int *)(unaff_EDI + 0x8c) + iVar8 + 0xc) = *(undefined4 *)(*(int *)(unaff_EDI + 0x8c) + 0x14 + iVar8);
            }
            // Compare and clamp between offset+0x34 and +0x3c
            fVar2 = *(float *)(*(int *)(unaff_EDI + 0x8c) + 0x34 + iVar8);
            pfVar1 = (float *)(*(int *)(unaff_EDI + 0x8c) + iVar8 + 0x3c);
            if (*pfVar1 <= fVar2 && fVar2 != *pfVar1) {
                *(undefined4 *)(*(int *)(unaff_EDI + 0x8c) + iVar8 + 0x34) = *(undefined4 *)(*(int *)(unaff_EDI + 0x8c) + 0x3c + iVar8);
            }
            // Compare and clamp between offset+0x5c and +0x64
            fVar2 = *(float *)(*(int *)(unaff_EDI + 0x8c) + 0x5c + iVar8);
            pfVar1 = (float *)(*(int *)(unaff_EDI + 0x8c) + iVar8 + 100);
            if (*pfVar1 <= fVar2 && fVar2 != *pfVar1) {
                *(undefined4 *)(*(int *)(unaff_EDI + 0x8c) + iVar8 + 0x5c) = *(undefined4 *)(*(int *)(unaff_EDI + 0x8c) + 100 + iVar8);
            }
            // Compare and clamp between offset+0x84 and +0x8c
            fVar2 = *(float *)(*(int *)(unaff_EDI + 0x8c) + 0x84 + iVar8);
            pfVar1 = (float *)(*(int *)(unaff_EDI + 0x8c) + iVar8 + 0x8c);
            if (*pfVar1 <= fVar2 && fVar2 != *pfVar1) {
                *(undefined4 *)(*(int *)(unaff_EDI + 0x8c) + iVar8 + 0x84) = *(undefined4 *)(*(int *)(unaff_EDI + 0x8c) + 0x8c + iVar8);
            }
            iVar8 = iVar8 + 0xa0;
            iVar10 = iVar10 + -1;
        } while (iVar10 != 0);
    }
    // Clamp remaining individual elements
    if (iVar11 < numElements) {
        iVar8 = iVar11 * 0x28;
        numElements = numElements - iVar11;
        do {
            fVar2 = *(float *)(*(int *)(unaff_EDI + 0x8c) + 0xc + iVar8);
            pfVar1 = (float *)(*(int *)(unaff_EDI + 0x8c) + iVar8 + 0x14);
            if (*pfVar1 <= fVar2 && fVar2 != *pfVar1) {
                *(undefined4 *)(*(int *)(unaff_EDI + 0x8c) + iVar8 + 0xc) = *(undefined4 *)(*(int *)(unaff_EDI + 0x8c) + 0x14 + iVar8);
            }
            iVar8 = iVar8 + 0x28;
            numElements = numElements + -1;
        } while (numElements != 0);
    }
    return;
}