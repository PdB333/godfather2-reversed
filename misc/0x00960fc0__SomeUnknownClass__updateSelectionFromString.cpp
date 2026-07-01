// FUNC_NAME: SomeUnknownClass::updateSelectionFromString
bool __thiscall updateSelectionFromString(int this, byte *stringPtr)
{
    byte bVar1;
    byte *pbVar2;
    int iVar3;
    byte *pbVar4;
    bool bVar5;
    undefined4 local_c;
    undefined4 local_8;
    undefined1 local_4;
    
    // Check if a flag at +0xa08 is already set, if so clear it and return true
    if (*(char *)(this + 0xa08) != '\0') {
        *(undefined1 *)(this + 0xa08) = 0;
        return true;
    }
    
    // Compare the string at this+4 with the input string
    pbVar2 = (byte *)(this + 4);
    pbVar4 = stringPtr;
    do {
        bVar1 = *pbVar2;
        bVar5 = bVar1 < *pbVar4;
        if (bVar1 != *pbVar4) {
LAB_00961010:
            iVar3 = (1 - (uint)bVar5) - (uint)(bVar5 != 0);
            goto LAB_00961015;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar2[1];
        bVar5 = bVar1 < pbVar4[1];
        if (bVar1 != pbVar4[1]) goto LAB_00961010;
        pbVar2 = pbVar2 + 2;
        pbVar4 = pbVar4 + 2;
    } while (bVar1 != 0);
    iVar3 = 0;
LAB_00961015:
    bVar5 = iVar3 == 0;
    if (!bVar5) {
        // Compare the string at this+0x204
        pbVar2 = (byte *)(this + 0x204);
        pbVar4 = stringPtr;
        do {
            bVar1 = *pbVar2;
            bVar5 = bVar1 < *pbVar4;
            if (bVar1 != *pbVar4) {
LAB_00961050:
                iVar3 = (1 - (uint)bVar5) - (uint)(bVar5 != 0);
                goto LAB_00961055;
            }
            if (bVar1 == 0) break;
            bVar1 = pbVar2[1];
            bVar5 = bVar1 < pbVar4[1];
            if (bVar1 != pbVar4[1]) goto LAB_00961050;
            pbVar2 = pbVar2 + 2;
            pbVar4 = pbVar4 + 2;
        } while (bVar1 != 0);
        iVar3 = 0;
LAB_00961055:
        bVar5 = iVar3 == 0;
        if (!bVar5) {
            // Compare the string at this+0x404
            pbVar2 = (byte *)(this + 0x404);
            pbVar4 = stringPtr;
            do {
                bVar1 = *pbVar2;
                bVar5 = bVar1 < *pbVar4;
                if (bVar1 != *pbVar4) {
LAB_00961090:
                    iVar3 = (1 - (uint)bVar5) - (uint)(bVar5 != 0);
                    goto LAB_00961095;
                }
                if (bVar1 == 0) break;
                bVar1 = pbVar2[1];
                bVar5 = bVar1 < pbVar4[1];
                if (bVar1 != pbVar4[1]) goto LAB_00961090;
                pbVar2 = pbVar2 + 2;
                pbVar4 = pbVar4 + 2;
            } while (bVar1 != 0);
            iVar3 = 0;
LAB_00961095:
            bVar5 = iVar3 == 0;
            if (!bVar5) {
                // Compare the string at this+0x604
                pbVar2 = (byte *)(this + 0x604);
                pbVar4 = stringPtr;
                do {
                    bVar1 = *pbVar2;
                    bVar5 = bVar1 < *pbVar4;
                    if (bVar1 != *pbVar4) {
LAB_009610d0:
                        iVar3 = (1 - (uint)bVar5) - (uint)(bVar5 != 0);
                        goto LAB_009610d5;
                    }
                    if (bVar1 == 0) break;
                    bVar1 = pbVar2[1];
                    bVar5 = bVar1 < pbVar4[1];
                    if (bVar1 != pbVar4[1]) goto LAB_009610d0;
                    pbVar2 = pbVar2 + 2;
                    pbVar4 = pbVar4 + 2;
                } while (bVar1 != 0);
                iVar3 = 0;
LAB_009610d5:
                bVar5 = iVar3 == 0;
                if (!bVar5) {
                    // All four string comparisons failed, check if string is valid
                    iVar3 = FUN_00960c50(stringPtr);
                    if (-1 < iVar3) {
                        FUN_005a04a0("UpdateSelection",0,&DAT_00d8d668,0);
                        local_c = DAT_01130448;
                        local_8 = 0;
                        local_4 = bVar5;
                        FUN_00408a00(&local_c,0);
                        FUN_00960ac0();
                    }
                    local_c = DAT_01130310;
                    local_8 = 0;
                    local_4 = 0;
                    FUN_00408a00(&local_c,0);
                    FUN_00960ac0();
                }
            }
        }
    }
    return bVar5;
}