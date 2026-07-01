// FUNC_NAME: CrimeScene::updateObjectiveDistances

void __fastcall CrimeScene::updateObjectiveDistances(CrimeScene* thisPtr)
{
    byte* pbVar1;
    float fVar2;
    byte bVar3;
    int iVar4;
    int iVar5;
    uint uVar6;
    uint uVar7;
    int iVar8;
    uint uVar9;
    undefined4 local_4;
    
    // Find first non-null objective group slot (up to 3 slots at offset +0xB0)
    uVar6 = 0;
    do {
        uVar7 = uVar6;
        if (*(int*)(thisPtr + 0xB0 + uVar6 * 4) != 0) break;
        bVar3 = (byte)(uVar6 + 1);
        uVar6 = (uint)bVar3;
        uVar7 = 0;
    } while (bVar3 < 3);
    
    iVar4 = *(int*)(thisPtr + 0xB0 + uVar7 * 4);
    if ((iVar4 != 0) &&
        (uVar6 = (uint)*(byte*)(iVar4 + 0x82) + (uint)*(byte*)(iVar4 + 0x81) +
                 (uint)*(byte*)(iVar4 + 0x80), uVar6 != 0)) {
        uVar9 = 0;
        *(char*)(thisPtr + 0xCC) = (char)uVar7;  // store selected slot index
        
        if (uVar6 != 0) {
            do {
                // Read objective ID from group's array at +0x68
                local_4 = *(undefined4*)
                          (*(int*)(*(int*)(thisPtr + 0xB0 + (uint)*(byte*)(thisPtr + 0xCC) * 4) + 0x68)
                          + uVar9 * 4);
                
                iVar4 = FUN_00889ee0(&local_4);  // get objective object by ID
                if (iVar4 != 0) {
                    iVar5 = FUN_0088e1e0(uVar9);  // get category (0,1,2) for this index
                    if (iVar5 == 0) {
                        iVar8 = (uVar6 - uVar9) + 900;  // base distance for category 0
                        fVar2 = (float)iVar8;
                        if (iVar8 < 0) {
                            *(float*)(iVar4 + 0xC) = fVar2 + DAT_00e44578;  // adjust negative
                        }
                        else {
LAB_0088a8a0:
                            *(float*)(iVar4 + 0xC) = fVar2;
                        }
                    }
                    else {
                        if (iVar5 == 1) {
                            iVar8 = (uVar6 - uVar9) + 800;  // base distance for category 1
                            fVar2 = (float)iVar8;
                            if (iVar8 < 0) {
                                fVar2 = fVar2 + DAT_00e44578;
                            }
                            goto LAB_0088a8a0;
                        }
                        if (iVar5 == 2) {
                            *(undefined4*)(iVar4 + 0xC) = 0;  // category 2: distance zero
                        }
                    }
                    // Set flag bit 1 (0x2) in objective flags at +0x10
                    *(ushort*)(iVar4 + 0x10) = *(ushort*)(iVar4 + 0x10) | 2;
                    
                    if (iVar5 == 2) {
                        // Clear bit 4 of byte at +0x51 in the pointer at +0x14
                        pbVar1 = (byte*)(*(int*)(iVar4 + 0x14) + 0x51);
                        *pbVar1 = *pbVar1 & 0xEF;
                    }
                    else {
                        // Set bit 4 of byte at +0x51 in the pointer at +0x14
                        pbVar1 = (byte*)(*(int*)(iVar4 + 0x14) + 0x51);
                        *pbVar1 = *pbVar1 | 0x10;
                    }
                }
                uVar9 = uVar9 + 1;
            } while (uVar9 < uVar6);
        }
    }
    return;
}