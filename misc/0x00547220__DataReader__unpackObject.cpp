// FUNC_NAME: DataReader::unpackObject
void DataReader::unpackObject(void* thisPtr, int outputObj, int* funcTable)
{
    float fVar1;
    undefined4* puVar2;
    undefined4** ppuVar3;
    uint uVar4;
    uint uVar5;
    uint uVar6;
    byte bVar7;
    undefined4** ppuVar8;
    bool bVar9;
    char cStack_64;
    int iStack_60;
    undefined4* puStack_5c;
    uint uStack_58;
    uint uStack_54;
    undefined4* puStack_50;
    undefined2 uStack_4c;
    undefined4 uStack_48;
    undefined4** ppuStack_8;

    // Call a function from the vtable (offset 0x220) - likely a reset/init
    (**(code**)(*funcTable + 0x220))();

    // Check a hash/identifier (0xe9613cc5) against thisPtr
    FUN_0043aff0(thisPtr, 0xe9613cc5);

    ppuVar8 = ppuStack_8;
    while (true) {
        if (cStack_64 == '\0') {
            bVar9 = *ppuVar8 == (undefined4*)0x0;
        } else {
            bVar9 = uStack_58 == uStack_54;
        }
        if (bVar9) break;

        ppuVar3 = &puStack_50;
        if (cStack_64 == '\0') {
            ppuVar3 = ppuVar8;
        }

        // Determine the type field (2 bytes at offset 6 of the element)
        if (*(short*)((int)ppuVar3 + 6) == 0x25e3) {
            puVar2 = (undefined4*)(uint)*(ushort*)(ppuVar3 + 1);
        } else {
            puVar2 = ppuVar3[1];
        }

        switch (puVar2) {
        case (undefined4*)0x0:
            ppuVar3 = &puStack_50;
            if (cStack_64 == '\0') {
                ppuVar3 = ppuVar8;
            }
            *(undefined4**)(outputObj + 8) = ppuVar3[2]; // +0x08
            break;
        case (undefined4*)0x1:
            ppuVar3 = &puStack_50;
            if (cStack_64 == '\0') {
                ppuVar3 = ppuVar8;
            }
            *(undefined4**)(outputObj + 0xc) = ppuVar3[2]; // +0x0C
            break;
        case (undefined4*)0x2:
            ppuVar3 = &puStack_50;
            if (cStack_64 == '\0') {
                ppuVar3 = ppuVar8;
            }
            *(undefined4**)(outputObj + 0x14) = ppuVar3[2]; // +0x14
            break;
        case (undefined4*)0x3:
            ppuVar3 = &puStack_50;
            if (cStack_64 == '\0') {
                ppuVar3 = ppuVar8;
            }
            *(undefined4**)(outputObj + 0x10) = ppuVar3[2]; // +0x10
            break;
        case (undefined4*)0x4:
            ppuVar3 = &puStack_50;
            if (cStack_64 == '\0') {
                ppuVar3 = ppuVar8;
            }
            **(int**)(outputObj + 0x1c) = (int)ppuVar3[2]; // +0x1c -> first field
            break;
        case (undefined4*)0x5:
            ppuVar3 = &puStack_50;
            if (cStack_64 == '\0') {
                ppuVar3 = ppuVar8;
            }
            *(undefined4**)(*(int*)(outputObj + 0x1c) + 4) = ppuVar3[2]; // +0x1c+4
            break;
        case (undefined4*)0x6:
            ppuVar3 = &puStack_50;
            if (cStack_64 == '\0') {
                ppuVar3 = ppuVar8;
            }
            *(undefined4**)(*(int*)(outputObj + 0x1c) + 8) = ppuVar3[2]; // +0x1c+8
            break;
        case (undefined4*)0x7:
            ppuVar3 = &puStack_50;
            if (cStack_64 == '\0') {
                ppuVar3 = ppuVar8;
            }
            *(undefined4**)(*(int*)(outputObj + 0x1c) + 0xc) = ppuVar3[2]; // +0x1c+0xC
            break;
        case (undefined4*)0x8:
            ppuVar3 = &puStack_50;
            if (cStack_64 == '\0') {
                ppuVar3 = ppuVar8;
            }
            *(undefined4**)(outputObj + 0x18) = ppuVar3[2]; // +0x18
            break;
        case (undefined4*)0x9:
            ppuVar3 = &puStack_50;
            if (cStack_64 == '\0') {
                ppuVar3 = ppuVar8;
            }
            puVar2 = ppuVar3[2]; // value for interpolation
            uVar4 = (**(code**)(*funcTable + 0x220))(); // get total count
            uVar5 = (**(code**)(*funcTable + 0x228))(0); // get start index
            fVar1 = (float)(int)uVar5;
            if ((int)uVar5 < 0) {
                fVar1 = fVar1 + DAT_00e44578; // 2^32? likely a constant for unsigned conversion
            }
            bVar7 = 0;
            if (uVar5 != 0) {
                uVar6 = 0;
                do {
                    bVar7 = bVar7 + 1;
                    // Fill first part of array with decreasing values
                    *(float*)(*(int*)(outputObj + 0x28) + uVar6 * 4) = (1.0 - (float)puVar2) / fVar1;
                    uVar6 = (uint)bVar7;
                } while (uVar6 < uVar5);
            }
            fVar1 = (float)(int)(uVar4 - uVar5);
            if ((int)(uVar4 - uVar5) < 0) {
                fVar1 = fVar1 + DAT_00e44578;
            }
            // Fill remaining part with increasing values
            for (uVar5 = uVar5 & 0xff; uVar5 < uVar4; uVar5 = (uint)(byte)((char)uVar5 + 1)) {
                *(float*)(*(int*)(outputObj + 0x28) + uVar5 * 4) = (float)puVar2 / fVar1;
            }
        }

        // Advance to next element
        if (cStack_64 == '\0') {
            if ((int)uStack_58 < 0) {
                ppuStack_8 = (undefined4**)((int)ppuVar8 + (int)*ppuVar8);
                FUN_0043b140(); // likely a cleanup/advance function
                ppuVar8 = ppuStack_8;
            } else if ((int)uStack_58 < (int)(uStack_54 - 1)) {
                uStack_58 = uStack_58 + 1;
                ppuStack_8 = (undefined4**)((int)ppuVar8 + (int)*ppuVar8);
                ppuVar8 = (undefined4**)((int)ppuVar8 + (int)*ppuVar8);
            } else {
                ppuStack_8 = (undefined4**)&DAT_01163cf8; // sentinel
                ppuVar8 = (undefined4**)&DAT_01163cf8;
            }
        } else {
            uStack_58 = uStack_58 + 1;
            if (uStack_58 != uStack_54) {
                uStack_4c = (short)uStack_58;
                // Check bitmask to decide if value is present
                if ((*(byte*)((uStack_58 >> 3) + iStack_60) & (byte)(1 << ((byte)uStack_58 & 7))) == 0) {
                    puStack_50 = puStack_5c;
                    uStack_48 = *puStack_5c;
                    puStack_5c = puStack_5c + 1;
                } else {
                    puStack_50 = (undefined4*)0x0;
                    uStack_48 = 0;
                }
            }
        }
    }
    return;
}