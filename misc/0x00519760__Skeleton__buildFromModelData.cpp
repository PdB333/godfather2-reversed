// FUNC_NAME: Skeleton::buildFromModelData
// Function address: 0x00519760
// Role: Initializes a skeleton structure from model data, building bone hierarchy arrays.

void Skeleton::buildFromModelData(int param_1, int param_2, undefined4 param_3, int *param_4)
{
    int *piVar1;
    char cVar2;
    undefined4 in_EAX;
    undefined4 *puVar3;
    undefined4 uVar4;
    int iVar5;
    int iVar6;
    int iVar7;
    int iVar8;
    int iVar9;
    undefined4 *unaff_EDI;
    int iVar10;
    int iStack_14; // flags for allocator (0x2 = allocate? )
    int iStack_10; // temp counter
    int iStack_c;  // node value
    int iStack_8;  // index

    piVar1 = param_4;
    // Call base constructor
    FUN_005195b0(param_1, in_EAX, param_3, param_4);

    // Set vtable pointer
    *unaff_EDI = &PTR_FUN_00e38238;

    // Store the model data pointer at +0x34
    unaff_EDI[0x34] = piVar1;
    // Clear fields: +0x36, +0x38, +0x37
    unaff_EDI[0x36] = 0;
    unaff_EDI[0x38] = 0;
    unaff_EDI[0x37] = 0;

    if (piVar1 != (int *)0x0) {
        param_4 = (int *)0x0;
        // Check if model data is valid and param_2 exists
        cVar2 = (**(code **)(*piVar1 + 0x10))(0xae986323, &param_4);
        if ((cVar2 == '\0') || (param_2 == 0)) {
            iVar10 = 0;
        } else {
            // Get bone count from param_2's field at +0x218
            iVar10 = *(int *)(param_2 + 0x218);
        }
        unaff_EDI[0x35] = iVar10; // store bone count at +0x35

        if (iVar10 != 0) {
            // Get bone count from this object's field at +0x1c (previously set?)
            unaff_EDI[0x36] = *(undefined4 *)(param_1 + 0x1c);
            iVar10 = *(int *)(param_1 + 0x1c);

            // Allocate array of ints for bone IDs (size: boneCount * 4)
            puVar3 = (undefined4 *)FUN_009c8f80(); // get allocator
            iStack_14 = 2; // flags: allocate with alignment?
            iStack_10 = 4;
            iStack_c = 0;
            uVar4 = (**(code **)*puVar3)(iVar10 * 4, &iStack_14);
            unaff_EDI[0x38] = uVar4; // store pointer at +0x38

            // Allocate array of bone nodes (size: boneCount * 0x20)
            iVar10 = *(int *)(param_1 + 0x1c);
            puVar3 = (undefined4 *)FUN_009c8f80();
            iStack_14 = 0; // flag zero
            uVar4 = (**(code **)*puVar3)(iVar10 << 5, &stack0xffffffe4); // &stack0xffffffe4 likely same as &iStack_14
            unaff_EDI[0x37] = uVar4; // store pointer at +0x37

            iVar9 = 0;
            iVar8 = 0;
            iStack_8 = 1;
            iVar10 = 0;

            // Loop over each bone entry (based on count from allocation handle? Actually iStack_14+0x18)
            if (0 < *(int *)(iStack_14 + 0x18)) {
                do {
                    iStack_c = *(int *)(iStack_14 + 0x20 + iVar9 * 4); // read node value from table
                    iVar5 = iVar8 * 0x20;

                    // Clear the 0x20-byte node structure at unaff_EDI[0x37] + offset
                    puVar3 = (undefined4 *)(unaff_EDI[0x37] + iVar5);
                    puVar3[3] = 0;
                    puVar3[2] = 0;
                    puVar3[1] = 0;
                    *puVar3 = 0;
                    puVar3 = (undefined4 *)(unaff_EDI[0x37] + 0x10 + iVar5);
                    puVar3[3] = 0;
                    puVar3[2] = 0;
                    puVar3[1] = 0;
                    *puVar3 = 0;

                    // Set node fields: short at +0xc = 0, byte at +0xe = node value, byte at +0xf = 1 (leaf)
                    *(undefined2 *)(unaff_EDI[0x37] + 0xc + iVar5) = 0;
                    *(char *)(unaff_EDI[0x37] + 0xe + iVar5) = (char)iStack_c;
                    *(undefined1 *)(unaff_EDI[0x37] + 0xf + iVar5) = 1;

                    // Compute bone ID from some lookup
                    iVar5 = unaff_EDI[0x35]; // bone count from param_2
                    if ((iVar5 == 0) || (*(int *)(iVar5 + 0x70) == 0)) {
                        iVar5 = -1;
                    } else {
                        iVar5 = *(int *)(*(int *)(*(int *)(iVar5 + 0x70) + 0x1c) + 0x14 +
                                        *(short *)(iVar5 + 0x74) * 0x18);
                        iVar6 = FUN_005828a0(*(undefined4 *)(iStack_14 + 0x20 + (iVar9 + 1) * 4), iVar5);
                        if ((iVar6 == -1) || (iVar5 = *(int *)(iVar5 + 0x10 + iVar6 * 0x14), iVar5 == -1)) {
                            iVar5 = -1;
                        }
                    }
                    // Store bone ID in the int array at +0x38
                    *(int *)(unaff_EDI[0x38] + iVar8 * 4) = iVar5;

                    iVar8 = iVar8 + 1;
                    iVar9 = iVar9 + 2; // skip every other entry? (pairs?)
                    if (1 < iStack_c) {
                        // If node has children (value >1), process them
                        iStack_10 = iStack_c + -1;
                        iVar5 = iVar8 * 0x20;
                        iStack_c = iStack_8 << 5; // shift?
                        iStack_8 = iStack_8 + iStack_10;
                        do {
                            // Initialize child node (type 2)
                            iVar6 = unaff_EDI[0x37];
                            *(undefined4 *)(iVar6 + 0xc + iVar5) = 0;
                            *(undefined4 *)(iVar6 + 8 + iVar5) = 0;
                            *(undefined4 *)(iVar6 + 4 + iVar5) = 0;
                            *(undefined4 *)(iVar6 + iVar5) = 0;
                            puVar3 = (undefined4 *)(iVar5 + 0x10 + unaff_EDI[0x37]);
                            puVar3[3] = 0;
                            puVar3[2] = 0;
                            puVar3[1] = 0;
                            *puVar3 = 0;

                            // Set child node fields: ushort at +0x1c = index & 0xff, short at +0xc = 0, byte at +0xf = 2
                            *(ushort *)(iStack_c + 0x1c + unaff_EDI[0x37]) = (ushort)iVar8 & 0xff;
                            *(undefined2 *)(iVar5 + 0xc + unaff_EDI[0x37]) = 0;
                            *(undefined1 *)(iVar5 + 0xf + unaff_EDI[0x37]) = 2;

                            // Compute bone ID for child
                            iVar6 = unaff_EDI[0x35];
                            if ((iVar6 == 0) || (*(int *)(iVar6 + 0x70) == 0)) {
LAB_00519a4b:
                                iVar6 = -1;
                            } else {
                                iVar6 = *(int *)(*(int *)(*(int *)(iVar6 + 0x70) + 0x1c) +
                                                 *(short *)(iVar6 + 0x74) * 0x18 + 0x14);
                                iVar7 = FUN_005828a0(*(undefined4 *)(iStack_14 + 0x20 + iVar9 * 4), iVar6);
                                if ((iVar7 == -1) || (iVar6 = *(int *)(iVar6 + 0x10 + iVar7 * 0x14), iVar6 == -1))
                                    goto LAB_00519a4b;
                            }
                            *(int *)(unaff_EDI[0x38] + iVar8 * 4) = iVar6;
                            iVar8 = iVar8 + 1;
                            iVar5 = iVar5 + 0x20;
                            iVar9 = iVar9 + 1;
                            iStack_10 = iStack_10 + -1;
                        } while (iStack_10 != 0);
                        iStack_10 = 0;
                    }
                    iVar10 = iVar10 + 1;
                } while (iVar10 < *(int *)(iStack_14 + 0x18));
            }

            // Set a flag or count at the end of the bone array (ushort at +0x1c)
            *(ushort *)(unaff_EDI[0x37] + 0x1c) =
                 (ushort)(byte)(*(char *)(unaff_EDI + 0x36) - *(char *)(iStack_14 + 0x18));

            // Call post-init function
            FUN_00519b60();
            return;
        }
    }
    // On failure, set error flag at +0x04 (bit 1)
    unaff_EDI[4] = unaff_EDI[4] | 1;
    return;
}