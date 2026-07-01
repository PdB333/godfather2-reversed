// FUNC_NAME: HashTable::resolveEntry
void __thiscall HashTable::resolveEntry(int thisPtr, int index, uint quality, uint hashValue)
{
    int iVar1;
    uint uVar2;
    uint uVar3;
    uint *puVar4;
    int iVar5;
    uint local_50[20];
    
    // index is multiplied by 4 to get offset into an array at this+0x28
    int *arrayBase = *(int **)(thisPtr + 0x28);
    int entryPtr = arrayBase[index]; // each entry is a pointer
    
    if (hashValue == 0) {
        uVar3 = *(uint *)(entryPtr + 0x20); // retrieve existing hash
    } else {
        *(uint *)(entryPtr + 0x20) = hashValue; // set new hash
        uVar3 = hashValue;
    }
    
    uVar2 = _DAT_0112f6f8 & 1; // static initialization flag
    *(uint *)(entryPtr + 0x3c) = quality; // store quality
    
    if (uVar2 == 0) {
        // First call: initialize global hash arrays
        _DAT_0112f6f8 = _DAT_0112f6f8 | 1;
        FUN_004da550("XATZ0273XX_C8F7646_BC623AE_v3");
        FUN_004da7e0(&DAT_0112f5b8);
        FUN_004da550("XATZ0273XX_C8F7646_570DF4C_v3");
        FUN_004da7e0(&DAT_0112f5c8);
        FUN_004da550("XATZ0273XX_C8F7647_BDBAE52_v3");
        FUN_004da7e0(&DAT_0112f5d8);
        FUN_004da550("XATZ0273XX_C8F7647_7E66394_v3");
        FUN_004da7e0(&DAT_0112f5e8);
        FUN_004da550("XATZ0273XX_C8F7647_3325C18_v3");
        FUN_004da7e0(&DAT_0112f5f8);
        FUN_004da550("XATZ0273XX_C8F7646_BC623AD_v3");
        FUN_004da7e0(&DAT_0112f608);
        FUN_004da550("XATZ0273XX_C8F7646_56E7CF0_v3");
        FUN_004da7e0(&DAT_0112f618);
        FUN_004da550("XATZ0273XX_C8F7647_BDBAE51_v3");
        FUN_004da7e0(&DAT_0112f628);
        FUN_004da550("XATZ0273XX_C8F7647_7E19EDC_v3");
        FUN_004da7e0(&DAT_0112f638);
        FUN_004da550("XATZ0273XX_C8F7647_334BE75_v3");
        FUN_004da7e0(&DAT_0112f648);
        FUN_004da550("XATZ0273XX_C8F7646_BC88608_v3");
        FUN_004da7e0(&DAT_0112f658);
        FUN_004da550("XATZ0273XX_C8F7646_56E7CF1_v3");
        FUN_004da7e0(&DAT_0112f668);
        FUN_004da550("XATZ0273XX_C8F7647_BD94BF4_v3");
        FUN_004da7e0(&DAT_0112f678);
        FUN_004da550("XATZ0273XX_C8F7647_7E40138_v3");
        FUN_004da7e0(&DAT_0112f688);
        FUN_004da550("XATZ0273XX_C8F7647_334BE74_v3");
        FUN_004da7e0(&DAT_0112f698);
        FUN_004da550("XATZ0273XX_C8F7646_BC623AC_v3");
        FUN_004da7e0(&DAT_0112f6a8);
        FUN_004da550("XATZ0273XX_C8F7646_56E7CF2_v3");
        FUN_004da7e0(&DAT_0112f6b8);
        FUN_004da550("XATZ0273XX_C8F7647_BDBAE50_v3");
        FUN_004da7e0(&DAT_0112f6c8);
        FUN_004da550("XATZ0273XX_C8F7647_7E40139_v3");
        FUN_004da7e0(&DAT_0112f6d8);
        FUN_004da550("XATZ0273XX_C8F7647_3325C19_v3");
        FUN_004da7e0(&DAT_0112f6e8);
    }
    
    // Precomputed hash table for quality levels (4 rows, 5 columns)
    local_50[0] = 0xa868f5c1;
    local_50[1] = 0x299fa77d;
    local_50[2] = 0x6ff44caf;
    local_50[3] = 0x89dc556a;
    local_50[4] = 0xa10c586c;
    local_50[5] = 0x59bfb800;
    local_50[6] = 0xdaf669bc;
    local_50[7] = 0x214b0eee;
    local_50[8] = 0x3b3317a9;
    local_50[9] = 0x52631aab;
    local_50[10] = 0xb167a3f;
    local_50[11] = 0x8c4d2bfb;
    local_50[12] = 0xd2a1d12d;
    local_50[13] = 0xec89d9e8;
    local_50[14] = 0x3b9dcea;
    local_50[15] = 0xbc6d3c7e;
    local_50[16] = 0x3da3ee3a;
    local_50[17] = 0x83f8936c;
    local_50[18] = 0x9de09c27;
    local_50[19] = 0xb5109f29;
    
    // Clamp quality to valid range [1,4]
    if (quality < 2) {
        quality = 1;
    } else if (3 < quality) {
        quality = 4;
    }
    
    // Clamp hash value to range [0x14, 0x18]
    if (uVar3 < 0x15) {
        uVar3 = 0x14;
    } else if (0x17 < uVar3) {
        uVar3 = 0x18;
    }
    
    iVar5 = quality - 1; // row index (0..3)
    if (iVar5 != 0) {
        puVar4 = local_50 + (uVar3 - 0x14) + iVar5 * 5; // start at last row
        do {
            uint temp = 0;
            FUN_008934e0(*puVar4, &temp); // compute some value from hash
            if (DAT_00e44598 < (float)(temp & DAT_00e44680)) break;
            iVar5 = iVar5 + -1;
            puVar4 = puVar4 + -5; // move to previous row
        } while (iVar5 != 0);
    }
    
    // Write the selected four values into the entry structure
    int selectedEntry = arrayBase[index];
    int selectedIndex = (uVar3 - 0x14) + iVar5 * 5; // final column+row
    *(uint *)(selectedEntry + 0x10) = (&DAT_0112f5b8)[selectedIndex * 4];
    *(uint *)(selectedEntry + 0x14) = (&DAT_0112f5bc)[selectedIndex * 4];
    *(uint *)(selectedEntry + 0x18) = (&DAT_0112f5c0)[selectedIndex * 4];
    *(uint *)(selectedEntry + 0x1c) = (&DAT_0112f5c4)[selectedIndex * 4];
    return;
}