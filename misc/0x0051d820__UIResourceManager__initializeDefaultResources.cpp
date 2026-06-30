// FUNC_NAME: UIResourceManager::initializeDefaultResources
void UIResourceManager::initializeDefaultResources(void)
{
    // This function initializes a set of predefined UI shape resources (square, cross, line, angle, circle, wave)
    // and builds a hash table for string-based resource lookup from a global list of strings.
    
    int iVar3;
    int iVar5;
    int iVar10;
    int iVar11;
    int iVar13;
    int iVar15;
    uint uVar9;
    byte bVar1;
    byte *pbVar12;
    undefined4 uVar2;
    undefined4 uVar6;
    undefined4 *puVar4;
    undefined4 *puVar7;
    int *piVar8;
    undefined8 uVar14;
    int *piStack_50;
    char *pcStack_44;
    undefined4 uStack_40;
    undefined4 *puStack_3c;
    undefined4 uStack_24;
    undefined4 uStack_20;
    undefined4 uStack_1c;
    undefined4 uStack_18;
    char acStack_14 [8];
    undefined4 local_c;
    undefined4 local_8;
    undefined4 local_4;
    
    // Get the global resource list container (dynamic array)
    iVar3 = DAT_01205510; // pointer to a struct: +0x4 = capacity, +0x8 = count, +0xc = array
    
    // --- Resource 1: "res_square" ---
    puStack_3c = (undefined4 *)0x51d832;
    puVar4 = (undefined4 *)FUN_009c8f80(); // allocate a resource descriptor (size 0xc0? or based on stack params)
    puStack_3c = &local_c;
    local_c = 2;
    local_8 = 0x10;
    local_4 = 0;
    uStack_40 = 0xc0;
    pcStack_44 = (char *)0x51d85b;
    iVar5 = (**(code **)*puVar4)(); // call the allocator with size from stack
    // Initialize resource descriptor fields
    *(undefined4 *)(iVar5 + 0x18) = 0;          // +0x18: some flag
    uVar2 = DAT_00e44718;                       // color1
    uVar6 = DAT_00e2cd54;                       // color2
    *(undefined4 *)(iVar5 + 0x1c) = 5;          // +0x1c: type (5 = square?)
    *(undefined4 *)(iVar5 + 0x20) = uVar2;      // +0x20: color
    *(undefined4 *)(iVar5 + 0x28) = uVar2;      // +0x28: color
    *(undefined2 *)(iVar5 + 0x2c) = 0;          // +0x2c: short
    *(undefined2 *)(iVar5 + 0x4c) = 0;
    *(undefined2 *)(iVar5 + 0x6c) = 0;
    *(undefined2 *)(iVar5 + 0x8c) = 0;
    *(undefined2 *)(iVar5 + 0xac) = 0;
    *(undefined2 *)(iVar5 + 0x5c) = 1;          // +0x5c: short
    *(undefined2 *)(iVar5 + 0x7c) = 2;
    *(undefined2 *)(iVar5 + 0x9c) = 3;
    *(undefined1 *)(iVar5 + 0x2f) = 1;          // +0x2f: byte
    *(undefined1 *)(iVar5 + 0x2e) = 5;
    *(undefined1 *)(iVar5 + 0x4f) = 2;
    *(undefined1 *)(iVar5 + 0x6f) = 2;
    *(undefined1 *)(iVar5 + 0x8f) = 2;
    *(undefined1 *)(iVar5 + 0xaf) = 2;
    *(undefined4 *)(iVar5 + 0x24) = 0;          // +0x24: int
    *(undefined2 *)(iVar5 + 0x3c) = 4;          // +0x3c: short
    *(undefined2 *)(iVar5 + 0xbc) = 4;
    *(undefined4 *)(iVar5 + 0x40) = uVar2;      // +0x40: color
    *(undefined4 *)(iVar5 + 0x44) = 0;
    *(undefined4 *)(iVar5 + 0x48) = uVar6;      // +0x48: color
    *(undefined4 *)(iVar5 + 0x60) = uVar6;
    *(undefined4 *)(iVar5 + 100) = 0;
    *(undefined4 *)(iVar5 + 0x68) = uVar6;
    *(undefined4 *)(iVar5 + 0x88) = uVar2;
    *(undefined4 *)(iVar5 + 0x80) = uVar6;
    *(undefined4 *)(iVar5 + 0x84) = 0;
    *(undefined4 *)(iVar5 + 0xa0) = uVar2;
    *(undefined4 *)(iVar5 + 0xa8) = uVar2;
    uVar6 = DAT_00e2b1a4;                       // color3
    *(undefined4 *)(iVar5 + 0xa4) = 0;
    *(undefined4 *)(iVar5 + 0x30) = 0;
    *(undefined4 *)(iVar5 + 0x34) = uVar6;
    *(undefined4 *)(iVar5 + 0x38) = 0;
    *(undefined4 *)(iVar5 + 0x50) = 0;
    *(undefined4 *)(iVar5 + 0x54) = uVar6;
    *(undefined4 *)(iVar5 + 0x58) = 0;
    *(undefined4 *)(iVar5 + 0x70) = 0;
    *(undefined4 *)(iVar5 + 0x74) = uVar6;
    *(undefined4 *)(iVar5 + 0x78) = 0;
    *(undefined4 *)(iVar5 + 0x90) = 0;
    *(undefined4 *)(iVar5 + 0x94) = uVar6;
    *(undefined4 *)(iVar5 + 0x98) = 0;
    pcStack_44 = "res_square";
    *(undefined4 *)(iVar5 + 0xb0) = 0;
    *(undefined4 *)(iVar5 + 0xb4) = uVar6;
    *(undefined4 *)(iVar5 + 0xb8) = 0;
    FUN_004eacb0(); // register resource name (string)
    *(undefined4 *)(iVar5 + 4) = 0;             // +0x04: some flag
    pcStack_44 = (char *)0x51d9b0;
    uVar6 = FUN_00519140(); // get resource ID and add to global lists
    if (*(int *)(iVar3 + 8) < *(int *)(iVar3 + 4)) {
        *(undefined4 *)(*(int *)(iVar3 + 0xc) + *(int *)(iVar3 + 8) * 4) = uVar6;
        *(int *)(iVar3 + 8) = *(int *)(iVar3 + 8) + 1;
    }
    *(undefined4 *)(&DAT_01194af0 + DAT_01205520 * 4) = uVar6;
    DAT_01205520 = DAT_01205520 + 1;
    
    // --- Resource 2: "res_cross" ---
    pcStack_44 = (char *)0x51d9dd;
    puVar4 = (undefined4 *)FUN_009c8f80();
    pcStack_44 = acStack_14;
    acStack_14[0] = '\x02';
    acStack_14[1] = '\0';
    acStack_14[2] = '\0';
    acStack_14[3] = '\0';
    acStack_14[4] = '\x10';
    acStack_14[5] = '\0';
    acStack_14[6] = '\0';
    acStack_14[7] = '\0';
    local_c = 0;
    iVar5 = (**(code **)*puVar4)(0xa0);
    *(undefined4 *)(iVar5 + 0x1c) = 4;          // type = 4 (cross)
    *(undefined4 *)(iVar5 + 0x18) = 0;
    uVar6 = DAT_00e44718;
    uVar2 = DAT_00e2cd54;
    *(undefined4 *)(iVar5 + 0x20) = DAT_00e44718;
    *(undefined2 *)(iVar5 + 0x2c) = 0;
    *(undefined2 *)(iVar5 + 0x4c) = 0;
    *(undefined2 *)(iVar5 + 0x6c) = 0;
    *(undefined2 *)(iVar5 + 0x8c) = 0;
    *(undefined2 *)(iVar5 + 0x3c) = 2;
    *(undefined2 *)(iVar5 + 0x5c) = 1;
    *(undefined2 *)(iVar5 + 0x7c) = 3;
    *(undefined2 *)(iVar5 + 0x9c) = 0;
    *(undefined1 *)(iVar5 + 0x2f) = 1;
    *(undefined1 *)(iVar5 + 0x2e) = 2;
    *(undefined1 *)(iVar5 + 0x4f) = 2;
    *(undefined1 *)(iVar5 + 0x6f) = 1;
    *(undefined1 *)(iVar5 + 0x6e) = 2;
    *(undefined1 *)(iVar5 + 0x8f) = 2;
    *(undefined4 *)(iVar5 + 0x24) = 0;
    *(undefined4 *)(iVar5 + 0x28) = 0;
    *(undefined4 *)(iVar5 + 0x40) = uVar2;
    *(undefined4 *)(iVar5 + 0x44) = 0;
    *(undefined4 *)(iVar5 + 0x48) = 0;
    *(undefined4 *)(iVar5 + 0x68) = uVar6;
    uVar6 = DAT_00e2b1a4;
    *(undefined4 *)(iVar5 + 0x60) = 0;
    *(undefined4 *)(iVar5 + 100) = 0;
    *(undefined4 *)(iVar5 + 0x80) = 0;
    *(undefined4 *)(iVar5 + 0x84) = 0;
    *(undefined4 *)(iVar5 + 0x88) = uVar2;
    *(undefined4 *)(iVar5 + 0x30) = 0;
    *(undefined4 *)(iVar5 + 0x34) = uVar6;
    *(undefined4 *)(iVar5 + 0x38) = 0;
    *(undefined4 *)(iVar5 + 0x50) = 0;
    *(undefined4 *)(iVar5 + 0x54) = uVar6;
    *(undefined4 *)(iVar5 + 0x58) = 0;
    *(undefined4 *)(iVar5 + 0x70) = 0;
    *(undefined4 *)(iVar5 + 0x74) = uVar6;
    *(undefined4 *)(iVar5 + 0x78) = 0;
    *(undefined4 *)(iVar5 + 0x90) = 0;
    *(undefined4 *)(iVar5 + 0x94) = uVar6;
    *(undefined4 *)(iVar5 + 0x98) = 0;
    FUN_004eacb0("res_cross");
    *(undefined4 *)(iVar5 + 4) = 0;
    uVar6 = FUN_00519140();
    if (*(int *)(iVar3 + 8) < *(int *)(iVar3 + 4)) {
        *(undefined4 *)(*(int *)(iVar3 + 0xc) + *(int *)(iVar3 + 8) * 4) = uVar6;
        *(int *)(iVar3 + 8) = *(int *)(iVar3 + 8) + 1;
    }
    *(undefined4 *)(&DAT_01194af0 + DAT_01205520 * 4) = uVar6;
    DAT_01205520 = DAT_01205520 + 1;
    
    // --- Resource 3: "res_line" ---
    puVar7 = (undefined4 *)FUN_009c8f80();
    puVar4 = &uStack_1c;
    uStack_1c = 2;
    uStack_18 = 0x10;
    acStack_14[0] = '\0';
    acStack_14[1] = '\0';
    acStack_14[2] = '\0';
    acStack_14[3] = '\0';
    iVar5 = (**(code **)*puVar7)();
    uVar6 = DAT_00e44718;
    *(undefined4 *)(iVar5 + 0x1c) = 2;          // type = 2 (line)
    *(undefined4 *)(iVar5 + 0x18) = 0;
    *(undefined4 *)(iVar5 + 0x20) = uVar6;
    uVar6 = DAT_00e2cd54;
    *(undefined2 *)(iVar5 + 0x2c) = 0;
    *(undefined2 *)(iVar5 + 0x4c) = 0;
    *(undefined1 *)(iVar5 + 0x2e) = 2;
    *(undefined1 *)(iVar5 + 0x4f) = 2;
    *(undefined4 *)(iVar5 + 0x24) = 0;
    *(undefined4 *)(iVar5 + 0x28) = 0;
    *(undefined2 *)(iVar5 + 0x3c) = 1;
    *(undefined2 *)(iVar5 + 0x5c) = 1;
    *(undefined1 *)(iVar5 + 0x2f) = 1;
    *(undefined4 *)(iVar5 + 0x40) = uVar6;
    uVar6 = DAT_00e2b1a4;
    *(undefined4 *)(iVar5 + 0x44) = 0;
    *(undefined4 *)(iVar5 + 0x48) = 0;
    *(undefined4 *)(iVar5 + 0x30) = 0;
    *(undefined4 *)(iVar5 + 0x34) = uVar6;
    *(undefined4 *)(iVar5 + 0x38) = 0;
    *(undefined4 *)(iVar5 + 0x50) = 0;
    *(undefined4 *)(iVar5 + 0x54) = uVar6;
    *(undefined4 *)(iVar5 + 0x58) = 0;
    FUN_004eacb0("res_line");
    *(undefined4 *)(iVar5 + 4) = 0;
    uVar6 = FUN_00519140();
    if (*(int *)(iVar3 + 8) < *(int *)(iVar3 + 4)) {
        *(undefined4 *)(*(int *)(iVar3 + 0xc) + *(int *)(iVar3 + 8) * 4) = uVar6;
        *(int *)(iVar3 + 8) = *(int *)(iVar3 + 8) + 1;
    }
    *(undefined4 *)(&DAT_01194af0 + DAT_01205520 * 4) = uVar6;
    DAT_01205520 = DAT_01205520 + 1;
    
    // --- Resource 4: "res_angle" ---
    puVar7 = (undefined4 *)FUN_009c8f80();
    uStack_24 = 2;
    uStack_20 = 0x10;
    uStack_1c = 0;
    iVar5 = (**(code **)*puVar7)(0x80,&uStack_24);
    uVar6 = DAT_00e44718;
    *(undefined4 *)(iVar5 + 0x1c) = 3;          // type = 3 (angle)
    *(undefined4 *)(iVar5 + 0x18) = 0;
    *(undefined4 *)(iVar5 + 0x20) = uVar6;
    *(undefined4 *)(iVar5 + 0x28) = uVar6;
    *(undefined2 *)(iVar5 + 0x2c) = 0;
    *(undefined2 *)(iVar5 + 0x4c) = 0;
    *(undefined2 *)(iVar5 + 0x6c) = 0;
    *(undefined2 *)(iVar5 + 0x3c) = 2;
    *(undefined2 *)(iVar5 + 0x5c) = 1;
    *(undefined2 *)(iVar5 + 0x7c) = 2;
    *(undefined1 *)(iVar5 + 0x2f) = 1;
    *(undefined1 *)(iVar5 + 0x2e) = 3;
    *(undefined1 *)(iVar5 + 0x4f) = 2;
    *(undefined1 *)(iVar5 + 0x6f) = 2;
    *(undefined4 *)(iVar5 + 0x24) = 0;
    *(undefined4 *)(iVar5 + 0x40) = uVar6;
    uVar6 = DAT_00e2cd54;
    *(undefined4 *)(iVar5 + 0x48) = DAT_00e2cd54;
    *(undefined4 *)(iVar5 + 0x44) = 0;
    *(undefined4 *)(iVar5 + 0x60) = uVar6;
    *(undefined4 *)(iVar5 + 0x68) = uVar6;
    uVar6 = DAT_00e2b1a4;
    *(undefined4 *)(iVar5 + 100) = 0;
    *(undefined4 *)(iVar5 + 0x30) = 0;
    *(undefined4 *)(iVar5 + 0x34) = uVar6;
    *(undefined4 *)(iVar5 + 0x38) = 0;
    *(undefined4 *)(iVar5 + 0x50) = 0;
    *(undefined4 *)(iVar5 + 0x54) = uVar6;
    *(undefined4 *)(iVar5 + 0x58) = 0;
    *(undefined4 *)(iVar5 + 0x70) = 0;
    *(undefined4 *)(iVar5 + 0x74) = uVar6;
    *(undefined4 *)(iVar5 + 0x78) = 0;
    FUN_004eacb0("res_angle");
    *(undefined4 *)(iVar5 + 4) = 0;
    uVar6 = FUN_00519140();
    if (*(int *)(iVar3 + 8) < *(int *)(iVar3 + 4)) {
        *(undefined4 *)(*(int *)(iVar3 + 0xc) + *(int *)(iVar3 + 8) * 4) = uVar6;
        *(int *)(iVar3 + 8) = *(int *)(iVar3 + 8) + 1;
    }
    *(undefined4 *)(&DAT_01194af0 + DAT_01205520 * 4) = uVar6;
    DAT_01205520 = DAT_01205520 + 1;
    
    // --- Resource 5: "res_circle" ---
    puVar7 = (undefined4 *)FUN_009c8f80();
    uStack_24 = 0;
    iVar5 = (**(code **)*puVar7)(0x40,&stack0xffffffd4);
    uVar6 = DAT_00e2b1a4;
    *(undefined4 *)(iVar5 + 0x34) = DAT_00e2cd54在一起的;
    *(undefined4 *)(iVar5 + 0x30) = uVar6;
    *(undefined4 *)(iVar5 + 0x20) = 0;
    *(undefined4 *)(iVar5 + 0x24) = uVar6;
    *(undefined4 *)(iVar5 + 0x28) = 0;
    *(undefined4 *)(iVar5 + 0x2c) = 0;
    FUN_004eacb0("res_circle");
    *(undefined4 *)(iVar5 + 4) = 3;
    uVar6 = FUN_00519140();
    if (*(int *)(iVar3 + 8) < *(int *)(iVar3 + 4)) {
        *(undefined4 *)(*(int *)(iVar3 + 0xc) + *(int *)(iVar3 + 8) * 4) = uVar6;
        *(int *)(iVar3 + 8) = *(int *)(iVar3 + 8) + 1;
    }
    *(undefined4 *)(&DAT_01194af0 + DAT_01205520 * 4) = uVar6;
    DAT_01205520 = DAT_01205520 + 1;
    
    // --- Resource 6: "res_wave" ---
    puVar7 = (undefined4 *)FUN_009c8f80();
    iVar5 = (**(code **)*puVar7)(0x40,&stack0xffffffcc);
    uVar6 = DAT_00e2b1a4;
    *(undefined4 *)(iVar5 + 0x38) = DAT_00e2afac;
    *(undefined4 *)(iVar5 + 0x3c) = DAT_00e2cd54;
    *(undefined4 *)(iVar5 + 0x30) = DAT_00e44750;
    *(undefined4 *)(iVar5 + 0x34) = DAT_00e2b04c;
    *(undefined4 *)(iVar5 + 0x20) = 0;
    *(undefined4 *)(iVar5 + 0x24) = uVar6;
    *(undefined4 *)(iVar5 + 0x28) = 0;
    *(undefined4 *)(iVar5 + 0x2c) = 0;
    FUN_004eacb0("res_wave");
    *(undefined4 *)(iVar5 + 4) = 1;
    uVar14 = FUN_00519140();
    iVar5 = (int)((ulonglong)uVar14 >> 0x20);
    if (*(int *)(iVar3 + 8) < *(int *)(iVar3 + 4)) {
        *(int *)(*(int *)(iVar3 + 0xc) + *(int *)(iVar3 + 8) * 4) = (int)uVar14;
        *(int *)(iVar3 + 8) = *(int *)(iVar3 + 8) + iVar5;
    }
    *(int *)(&DAT_01194af0 + DAT_01205520 * 4) = (int)uVar14;
    DAT_01205520 = DAT_01205520 + iVar5;
    
    // --- Build hash table from global string list ---
    pcStack_44 = DAT_012054cc; // pointer to array of string entries
    uStack_40 = DAT_012054d4;
    if (DAT_012054cc != (char *)0x0) {
        iVar5 = 0;
        if (0 < DAT_012054d0) {
            piVar8 = (int *)(DAT_012054cc + 8);
            iVar10 = DAT_012054d0;
            do {
                iVar11 = *piVar8;
                piVar8 = piVar8 + 3;
                iVar10 = iVar10 + -1;
                iVar5 = iVar5 + 1 + iVar11;
            } while (iVar10 != 0);
        }
        iVar10 = DAT_012054d0;
        puVar7 = (undefined4 *)FUN_009c8f80();
        puStack_3c = (undefined4 *)0x2;
        puVar7 = (undefined4 *)(**(code **)*puVar7)(iVar5 * 4 + 0x20,&puStack_3c);
        iVar11 = 0;
        puVar7[6] = 0x60; // hash table size?
        puVar7[7] = iVar5 + -0x60;
        piVar8 = puVar4 + 2;
        iVar5 = 0x60;
        do {
            puVar7[iVar11 + 8] = *piVar8;
            iVar11 = iVar11 + 1;
            iVar15 = 0;
            if (0 < *piVar8) {
                do {
                    pbVar12 = *(byte **)(piVar8[-1] + iVar15 * 4);
                    iVar13 = 0;
                    if (pbVar12 != (byte *)0x0) {
                        bVar1 = *pbVar12;
                        while (bVar1 != 0) {
                            uVar9 = (uint)bVar1;
                            pbVar12 = pbVar12 + 1;
                            if (uVar9 - 0x41 < 0x1a) {
                                uVar9 = uVar9 + 0x20;
                            }
                            iVar13 = iVar13 * 0x1003f + uVar9;
                            bVar1 = *pbVar12;
                        }
                    }
                    puVar7[iVar11 + 8] = iVar13;
                    iVar15 = iVar15 + 1;
                    iVar11 = iVar11 + 1;
                } while (iVar15 < *piVar8);
            }
            piVar8 = piVar8 + 3;
            iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        FUN_004eacb0(iVar10);
        *puVar7 = &PTR_LAB_00e38220;
        puVar7[1] = 4;
        if (*(int *)(iVar3 + 8) < *(int *)(iVar3 + 4)) {
            *(undefined4 **)(*(int *)(iVar3 + 0xc) + *(int *)(iVar3 + 8) * 4) = puVar7;
            *(int *)(iVar3 + 8) = *(int *)(iVar3 + 8) + 1;
        }
        *(undefined4 **)(&DAT_01194af0 + DAT_01205520 * 4) = puVar7;
        DAT_01205520 = DAT_01205520 + 1;
        
        // Build per-entry hash tables
        piVar8 = puVar4 + 2;
        iVar5 = 0x60;
        do {
            iVar10 = *piVar8;
            puVar4 = (undefined4 *)FUN_009c8f80();
            pcStack_44 = (char *)0x2;
            uStack_40 = 0x10;
            puStack_3c = (undefined4 *)0x0;
            puVar4 = (undefined4 *)(**(code **)*puVar4)(iVar10 * 4 + 0x24,&pcStack_44);
            puVar4[6] = 1;
            puVar4[7] = *piVar8;
            puVar4[8] = *piVar8;
            iVar10 = 0;
            if (0 < *piVar8) {
                piStack_50 = puVar4 + 9;
                do {
                    pbVar12 = *(byte **)(piVar8[-1] + iVar10 * 4);
                    iVar11 = 0;
                    if (pbVar12 != (byte *)0x0) {
                        bVar1 = *pbVar12;
                        while (bVar1 != 0) {
                            uVar9 = (uint)bVar1;
                            pbVar12 = pbVar12 + 1;
                            if (uVar9 - 0x41 < 0x1a) {
                                uVar9 = uVar9 + 0x20;
                            }
                            iVar11 = iVar11 * 0x1003f + uVar9;
                            bVar1 = *pbVar12;
                        }
                    }
                    *piStack_50 = iVar11;
                    iVar10 = iVar10 + 1;
                    piStack_50 = piStack_50 + 1;
                } while (iVar10 < *piVar8);
            }
            FUN_004eacb0(piVar8[-2]);
            *puVar4 = &PTR_LAB_00e38220;
            puVar4[1] = 4;
            if (*(int *)(iVar3 + 8) < *(int *)(iVar3 + 4)) {
                *(undefined4 **)(*(int *)(iVar3 + 0xc) + *(int *)(iVar3 + 8) * 4) = puVar4;
                *(int *)(iVar3 + 8) = *(int *)(iVar3 + 8) + 1;
            }
            *(undefined4 **)(&DAT_01194af0 + DAT_01205520 * 4) = puVar4;
            DAT_01205520 = DAT_01205520 + 1;
            piVar8 = piVar8 + 3;
            iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
    }
    return;
}