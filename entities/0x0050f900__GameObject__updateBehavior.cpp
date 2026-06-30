// FUNC_NAME: GameObject::updateBehavior
undefined1 GameObject::updateBehavior(int *index, int objSlot)
{
    float *pfVar1;
    int *piVar2;
    float *pfVar3;
    int iVar4;
    uint uVar5;
    undefined4 uVar6;
    undefined4 uVar7;
    int iVar8;
    byte *pbVar9;
    undefined4 uVar10;
    float fVar11;
    int iVar12;
    int extraout_EDX;
    int iVar13;
    int unaff_FS_OFFSET;
    float fVar14;
    float fVar15;
    float fVar16;
    float fVar17;
    float fVar18;
    undefined8 uVar19;
    undefined1 result;
    int stack_local_70; // local_70
    undefined4 stack_local_6c; // local_6c
    undefined4 stack_local_68; // local_68
    float stack_local_60; // local_60
    float fStack_5c;
    float fStack_58;
    float fStack_54;
    undefined1 local_50[48];
    undefined1 local_20[12];
    float local_14;

    // +0x2c is FS segment offset for thread-local storage? Typically used for exception handling.
    iVar4 = **(int **)(unaff_FS_OFFSET + 0x2c);
    iVar13 = objSlot * 0x50; // Each object slot is 0x50 bytes
    iVar12 = *(int *)(iVar4 + 8) + iVar13; // Base pointer to object data
    fVar11 = *(float *)(iVar12 + 0x2c + *index); // Some per-index offset at +0x2c
    pfVar3 = (float *)(iVar12 + 0x20 + *index); // Pointer to structure at +0x20 + index (size 0x30? pfVar3[7] used)
    fVar15 = pfVar3[7]; // pfVar3[7] at +0x20+index+0x1c? Actually pfVar3 is float*, so pfVar3[7] is at +0x20+index+0x1c
    result = 0;
    if (*(int *)(this + 0xa8) != 0) { // Animation array? 
        iVar12 = *(int *)(this + 0x24); // Some global state
        // Use ushort at pfVar3+0x36 as index into animation array (size 0xc per entry)
        pfVar1 = (float *)(*(int *)(this + 0xa8) + (uint)*(ushort *)((int)pfVar3 + 0x36) * 0xc);
        fVar14 = fVar15;
        FUN_004e41b0(); // Probably random number generator or noise
        fVar14 = fVar14 * *(float *)(iVar12 + 0x164) + *(float *)(iVar12 + 0x158);
        *pfVar1 = fVar14;
        FUN_004e41b0();
        fVar14 = fVar14 * *(float *)(iVar12 + 0x168) + *(float *)(iVar12 + 0x15c);
        pfVar1[1] = fVar14;
        FUN_004e41b0();
        pfVar1[2] = fVar14 * *(float *)(iVar12 + 0x16c) + *(float *)(iVar12 + 0x160);
    }
    *(undefined1 *)(*(int *)(iVar4 + 8) + iVar13 + 0x54 + *index) = 0; // Clear flag at +0x54+index
    *(undefined1 *)(*(int *)(iVar4 + 8) + iVar13 + 0x55 + *index) = 0; // Clear flag at +0x55+index
    pfVar3[3] = fVar11; // Update pfVar3[3] (at +0x20+index+0xc)
    pfVar3[7] = fVar15; // Update pfVar3[7] (at +0x20+index+0x1c)
    iVar12 = *index;
    iVar8 = *(int *)(iVar4 + 8) + iVar13;
    fVar11 = *(float *)(iVar8 + 0x48 + iVar12); // Some value at +0x48+index
    if (fVar11 < *(float *)(iVar8 + 0x40 + iVar12)) {
        *(float *)(iVar8 + iVar12 + 0x40) = fVar11; // Clamp at +0x40+index
    }
    if (*(int *)(this + 0xac) != 0) { // Another array (maybe effect IDs)
        *(undefined4 *)(*(int *)(this + 0xac) + (uint)*(ushort *)((int)pfVar3 + 0x36) * 4) = 0;
    }
    pfVar3[0xc] = 0.0f; // pfVar3[12] = 0.0 (at +0x20+index+0x30)
    switch(*(byte *)(this + 0x5b) - 1) { // Behavior type at +0x5b
    case 0: // AI behavior 0
        if (*(int *)(this + 0x60) != 0) {
            stack_local_70 = *(int *)(*(int *)(this + 4) + 0xc4); // Get some value from sub-object
            if (stack_local_70 == 0) {
                stack_local_70 = 0;
            }
            else {
                stack_local_70 = stack_local_70 + -0x48; // Adjust
            }
            uVar5 = *(uint *)(*(int *)(this + 0x24) + 0x10c); // Flags
            stack_local_6c = 0xffffffff;
            if ((uVar5 & 0x200000) == 0) {
                if ((uVar5 & 0x400000) != 0) {
                    stack_local_6c = *(undefined4 *)(*(int *)(this + 4) + 0xb8);
                }
            }
            else {
                stack_local_70 = 0;
            }
            FUN_004f3c20(local_50); // Some initialization? (maybe matrix?)
            FUN_00414aa0(); // Possibly update global time?
            local_14 = DAT_00e2b1a4; // Constant
            if ((*(byte *)(*(int *)(this + 0x10) + *(int *)(iVar4 + 8)) & 4) != 0) {
                iVar12 = *(int *)(this + 0x10) + *(int *)(iVar4 + 8) + 0x50;
                FUN_0056b420(iVar12, local_20, local_20); // Matrix operation
                if ((*(uint *)(*(int *)(this + 0x24) + 0x104) & 0x200) != 0) {
                    iVar12 = extraout_EDX + 0x10; // Probably not correct - need to check
                }
                FUN_0044c4c0(iVar12, pfVar3 + 4, pfVar3 + 4); // Transform point
            }
            stack_local_68 = 0;
            if ((*(uint *)(*(int *)(this + 4) + 0xc) & 0x400000) != 0) {
                stack_local_68 = 4;
            }
            fStack_5c = (float)stack_local_70;
            stack_local_60 = 2.8026e-45f; // Almost zero? likely a placeholder
            fStack_58 = (float)stack_local_6c;
            fStack_54 = 0.0f;
            uVar19 = FUN_0051d730(); // Some parameter
            iVar12 = FUN_0051c7c0(*(undefined4 *)(this + 0x60),
                                  *(undefined4 *)(*(int *)(this + 4) + 0x84),
                                  stack_local_68, &stack_local_60, uVar19);
            *(int *)(*(int *)(this + 0xac) + (uint)*(ushort *)((int)pfVar3 + 0x36) * 4) = iVar12;
            if (iVar12 != 0) {
                piVar2 = (int *)(*(int *)(this + 0xac) + (uint)*(ushort *)((int)pfVar3 + 0x36) * 4);
                *(int **)(*piVar2 + 8) = piVar2; // Link list?
                FUN_00414aa0(); // Update time again?
                iVar12 = FUN_004e0750(0x40); // Allocate memory? size 0x40
                if ((iVar12 != 0) && (iVar12 = FUN_00509260(), iVar12 != 0)) {
                    *(undefined4 *)(iVar12 + 0x2c) = *(undefined4 *)(*(int *)(iVar4 + 8) + iVar13 + 0x40 + *index);
                    if ((*(byte *)(*(int *)(this + 0x24) + 0x10c) & 0x20) != 0) {
                        iVar4 = *(int *)(this + 0x28);
                        uVar10 = *(undefined4 *)(iVar4 + 0x44);
                        uVar6 = *(undefined4 *)(iVar4 + 0x48);
                        uVar7 = *(undefined4 *)(iVar4 + 0x4c);
                        *(undefined4 *)(iVar12 + 0x10) = *(undefined4 *)(iVar4 + 0x40);
                        *(undefined4 *)(iVar12 + 0x14) = uVar10;
                        *(undefined4 *)(iVar12 + 0x18) = uVar6;
                        *(undefined4 *)(iVar12 + 0x1c) = uVar7;
                    }
                    FUN_004deb00(); // Add to some list?
                }
                FUN_00510110(this, index, objSlot, 0); // Recursive? (this, index, slot, param)
                return 1;
            }
        }
        break;
    case 1: // AI behavior 1
        if (*(int *)(this + 0x60) != 0) {
            FUN_00414aa0();
            pbVar9 = (byte *)(*(int *)(this + 0x10) + *(int *)(iVar4 + 8));
            fStack_54 = DAT_00e2b1a4;
            if ((*pbVar9 & 4) != 0) {
                fVar11 = fStack_5c * *(float *)(pbVar9 + 0x68);
                fVar15 = fStack_5c * *(float *)(pbVar9 + 0x6c);
                fVar14 = stack_local_60 * *(float *)(pbVar9 + 0x54);
                fVar16 = stack_local_60 * *(float *)(pbVar9 + 0x58);
                fVar17 = stack_local_60 * *(float *)(pbVar9 + 0x5c);
                fVar18 = fStack_58 * *(float *)(pbVar9 + 0x7c);
                stack_local_60 = fStack_5c * *(float *)(pbVar9 + 0x60) + stack_local_60 * *(float *)(pbVar9 + 0x50) +
                                 fStack_58 * *(float *)(pbVar9 + 0x70) + DAT_00e2b1a4 * *(float *)(pbVar9 + 0x80);
                fStack_5c = fStack_5c * *(float *)(pbVar9 + 100) + fVar14 +
                            fStack_58 * *(float *)(pbVar9 + 0x74) + DAT_00e2b1a4 * *(float *)(pbVar9 + 0x84);
                fStack_58 = fVar11 + fVar16 + fStack_58 * *(float *)(pbVar9 + 0x78) +
                            DAT_00e2b1a4 * *(float *)(pbVar9 + 0x88);
                fStack_54 = fVar15 + fVar17 + fVar18 + DAT_00e2b1a4 * *(float *)(pbVar9 + 0x8c);
                *pfVar3 = stack_local_60;
                pfVar3[1] = fStack_5c;
                pfVar3[2] = fStack_58;
                FUN_0044c4c0(*(int *)(iVar4 + 8) + 0x50 + *(int *)(this + 0x10), pfVar3 + 4, pfVar3 + 4);
            }
            FUN_00510f60(this, index, objSlot);
            uVar10 = FUN_004e9720(local_50);
            *(undefined4 *)(*(int *)(this + 0xac) + (uint)*(ushort *)((int)pfVar3 + 0x36) * 4) = uVar10;
            if (*(int *)(*(int *)(this + 0xac) + (uint)*(ushort *)((int)pfVar3 + 0x36) * 4) != 0) {
                return 1;
            }
        }
        break;
    case 5: // AI behavior 5
        FUN_00412d90(local_50);
        fVar11 = (float)FUN_0050a630(this, *(uint *)(*(int *)(this + 0x24) + 0x10c) >> 0x1a & 0xffffff01);
        *(float *)(*(int *)(this + 0xac) + (uint)*(ushort *)((int)pfVar3 + 0x36) * 4) = fVar11;
        if (fVar11 == 0.0f) {
            return 0;
        }
        pfVar3[0xc] = fVar11;
        // Fall through to case 3
    case 3: // AI behavior 3
        result = 1;
        break;
    }
    return result;
}