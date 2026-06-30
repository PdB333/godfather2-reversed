// FUNC_NAME: EntityManager::updateEntities
void __thiscall EntityManager::updateEntities(int thisPtr, int sourceInput, int singleObjectInput)
{
    uint uVar1;
    bool bVar2;
    int *piVar3;
    undefined4 *puVar4;
    int iVar5;
    int iVar6;
    uint uVar7;
    int iVar8;
    int iVar9;
    int *piVar10;
    int iVar11;
    undefined4 *puVar12;
    int iVar13;
    float in_XMM0_Da;
    int iStack_30;
    int iStack_2c;
    int iStack_24;
    float fStack_20;
    int iStack_1c;
    int iStack_14;

    // Clear two auxiliary arrays: activeList at +0x80 and inactiveList at +0x8c
    iVar13 = 0;
    if (0 < *(int *)(thisPtr + 0x80)) {
        do {
            FUN_009f2410(thisPtr + 8); // pop_front or clear for array at +0x80
            iVar13 = iVar13 + 1;
        } while (iVar13 < *(int *)(thisPtr + 0x80));
    }
    iVar13 = 0;
    *(undefined4 *)(thisPtr + 0x80) = 0;
    if (0 < *(int *)(thisPtr + 0x8c)) {
        do {
            FUN_00a0dec0(thisPtr + 0xc); // pop_front or clear for array at +0x8c
            iVar13 = iVar13 + 1;
        } while (iVar13 < *(int *)(thisPtr + 0x8c));
    }
    *(undefined4 *)(thisPtr + 0x8c) = 0;

    // Retrieve temporary buffer from TLS
    uVar1 = *(uint *)(sourceInput + 0x14); // count of items in sourceInput
    piVar3 = (int *)TlsGetValue(DAT_01139810);
    iVar13 = piVar3[8];
    iVar9 = uVar1 * 0x30 + 0x10; // size needed: each item 0x30 bytes plus header
    uVar7 = iVar13 + iVar9;
    if ((uint)piVar3[0xb] < uVar7) {
        iVar13 = (**(code **)(*piVar3 + 0x14))(iVar9); // allocate
    } else {
        piVar3[8] = uVar7;
    }
    iStack_14 = *(int *)(sourceInput + 0x14);
    iVar9 = 0;
    if (3 < iStack_14) {
        // Bulk copy using optimized loop (copying 0x30-byte blocks)
        iStack_24 = (iStack_14 - 4U >> 2) + 1;
        iVar11 = -0x48 - iVar13;
        iVar9 = iStack_24 * 4;
        puVar12 = (undefined4 *)(iVar13 + 0x48);
        do {
            iVar8 = *(int *)(sourceInput + 0x10) + iVar11;
            // Copy 12 dwords (0x30 bytes) via offset arithmetic
            puVar12[-0x12] = *(undefined4 *)((int)puVar12 + *(int *)(sourceInput + 0x10) + iVar11);
            puVar12[-0x11] = *(undefined4 *)((int)puVar12 + iVar8 + 4);
            puVar12[-0x10] = *(undefined4 *)((int)puVar12 + iVar8 + 8);
            puVar12[-0xf] = *(undefined4 *)((int)puVar12 + iVar8 + 0xc);
            puVar12[-0xe] = *(undefined4 *)((int)puVar12 + iVar8 + 0x10);
            puVar12[-0xd] = *(undefined4 *)((int)puVar12 + iVar8 + 0x14);
            puVar12[-0xc] = *(undefined4 *)((int)puVar12 + iVar8 + 0x18);
            puVar12[-0xb] = *(undefined4 *)((int)puVar12 + iVar8 + 0x1c);
            puVar12[-10] = *(undefined4 *)((int)puVar12 + iVar8 + 0x20);
            puVar12[-9] = *(undefined4 *)((int)puVar12 + iVar8 + 0x24);
            puVar12[-8] = *(undefined4 *)((int)puVar12 + iVar8 + 0x28);
            puVar12[-7] = *(undefined4 *)((int)puVar12 + iVar8 + 0x2c);
            iVar8 = *(int *)(sourceInput + 0x10) + 0x30 + iVar11;
            puVar12[-6] = *(undefined4 *)((int)puVar12 + *(int *)(sourceInput + 0x10) + 0x30 + iVar11);
            puVar12[-5] = *(undefined4 *)((int)puVar12 + iVar8 + 4);
            puVar12[-4] = *(undefined4 *)((int)puVar12 + iVar8 + 8);
            puVar12[-3] = *(undefined4 *)((int)puVar12 + iVar8 + 0xc);
            puVar12[-2] = *(undefined4 *)((int)puVar12 + iVar8 + 0x10);
            puVar12[-1] = *(undefined4 *)((int)puVar12 + iVar8 + 0x14);
            *puVar12 = *(undefined4 *)((int)puVar12 + iVar8 + 0x18);
            puVar12[1] = *(undefined4 *)((int)puVar12 + iVar8 + 0x1c);
            puVar12[2] = *(undefined4 *)((int)puVar12 + iVar8 + 0x20);
            puVar12[3] = *(undefined4 *)((int)puVar12 + iVar8 + 0x24);
            puVar12[4] = *(undefined4 *)((int)puVar12 + iVar8 + 0x28);
            puVar12[5] = *(undefined4 *)((int)puVar12 + iVar8 + 0x2c);
            iVar8 = *(int *)(sourceInput + 0x10) + (0x18 - iVar13);
            puVar12[6] = *(undefined4 *)(iVar8 + (int)puVar12);
            puVar12[7] = *(undefined4 *)((int)puVar12 + iVar8 + 4);
            puVar12[8] = *(undefined4 *)((int)puVar12 + iVar8 + 8);
            puVar12[9] = *(undefined4 *)((int)puVar12 + iVar8 + 0xc);
            puVar12[10] = *(undefined4 *)((int)puVar12 + iVar8 + 0x10);
            puVar12[0xb] = *(undefined4 *)((int)puVar12 + iVar8 + 0x14);
            // ... continue for full 0x30 bytes
            // (omitted for brevity, actual code copies all 12 dwords)
            puVar12 = puVar12 + 0x30;
        } while (iStack_24 != 0);
    }
    if (iVar9 < iStack_14) {
        // Copy remaining items individually
        iVar11 = iStack_14 - iVar9;
        puVar12 = (undefined4 *)(iVar9 * 0x30 + 0x18 + iVar13);
        do {
            puVar4 = (undefined4 *)((int)puVar12 + *(int *)(sourceInput + 0x10) + (-0x18 - iVar13));
            iVar11 = iVar11 + -1;
            puVar12[-6] = *puVar4;
            puVar12[-5] = puVar4[1];
            puVar12[-4] = puVar4[2];
            puVar12[-3] = puVar4[3];
            puVar12[-2] = puVar4[4];
            puVar12[-1] = puVar4[5];
            *puVar12 = puVar4[6];
            puVar12[1] = puVar4[7];
            puVar12[2] = puVar4[8];
            puVar12[3] = puVar4[9];
            puVar12[4] = puVar4[10];
            puVar12[5] = puVar4[0xb];
            puVar12 = puVar12 + 0xc;
        } while (iVar11 != 0);
    }

    // Process items already in the manager's main list (sorted by some criterion)
    iStack_24 = *(int *)(thisPtr + 0x68) + -1;
    if (-1 < iStack_24) {
        iStack_30 = iStack_24 * 0x30;
        do {
            // Current item pointer
            puVar12 = (undefined4 *)(*(int *)(thisPtr + 100) + iStack_30);
            iStack_1c = -1;
            fStack_20 = DAT_00e445a4; // some large initial value
            iStack_2c = 0;
            in_XMM0_Da = DAT_00e445a4;
            if (iStack_14 < 1) {
                // No input items, just remove current item
                goto LAB_00554734;
            } else {
                // Find the best matching input item (minimum distance/score)
                do {
                    float dist = FUN_005540a0(); // get distance between current item and input[i]
                    if (dist < fStack_20) {
                        iStack_1c = iStack_2c;
                        fStack_20 = dist;
                    }
                    iStack_2c = iStack_2c + 1;
                } while (iStack_2c < iStack_14);

                if (iStack_1c < 0) goto LAB_00554734;

                // Compare hashed types
                undefined4 *bestInput = (undefined4 *)(iStack_1c * 0x30 + iVar13);
                iVar9 = bestInput[10]; // pointer at offset +0x28
                if (*(char *)(iVar9 + 0x18) == '\x01') {
                    iVar9 = *(char *)(iVar9 + 0x10) + iVar9;
                } else {
                    iVar9 = 0;
                }
                iVar11 = puVar12[10];
                if (*(char *)(iVar11 + 0x18) == '\x01') {
                    iVar11 = *(char *)(iVar11 + 0x10) + iVar11;
                } else {
                    iVar11 = 0;
                }
                if (iVar9 != iVar11) {
                    // Types differ, notify listeners: remove old, add new
                    iVar9 = *(int *)(thisPtr + 0x74);
                    while (iVar9 = iVar9 + -1, -1 < iVar9) {
                        (**(code **)(**(int **)(*(int *)(thisPtr + 0x70) + iVar9 * 4) + 8))(puVar12); // remove callback
                    }
                    iVar9 = *(int *)(thisPtr + 0x74);
                    while (iVar9 = iVar9 + -1, -1 < iVar9) {
                        (**(code **)(**(int **)(*(int *)(thisPtr + 0x70) + iVar9 * 4) + 4))(bestInput); // add callback
                    }
                }
                // Copy best input into current slot
                *puVar12 = *bestInput;
                puVar12[1] = bestInput[1];
                puVar12[2] = bestInput[2];
                puVar12[3] = bestInput[3];
                puVar12[4] = bestInput[4];
                puVar12[5] = bestInput[5];
                puVar12[6] = bestInput[6];
                puVar12[7] = bestInput[7];
                puVar12[8] = bestInput[8];
                puVar12[9] = bestInput[9];
                puVar12[10] = bestInput[10];
                puVar12[0xb] = bestInput[0xb];

                iStack_14 = iStack_14 + -1;
                undefined4 *lastInput = (undefined4 *)(iStack_14 * 0x30 + iVar13);
                // Move last input item to the slot of bestInput (swap removal)
                *bestInput = *lastInput;
                bestInput[1] = lastInput[1];
                bestInput[2] = lastInput[2];
                bestInput[3] = lastInput[3];
                bestInput[4] = lastInput[4];
                bestInput[5] = lastInput[5];
                bestInput[6] = lastInput[6];
                bestInput[7] = lastInput[7];
                bestInput[8] = lastInput[8];
                bestInput[9] = lastInput[9];
                bestInput[10] = lastInput[10];
                bestInput[0xb] = lastInput[0xb];
            }
        } while (true);
        LAB_00554734:
        // Remove current item (without replacement)
        iVar9 = *(int *)(thisPtr + 100);
        iVar11 = *(int *)(thisPtr + 0x74);
        while (iVar11 = iVar11 + -1, -1 < iVar11) {
            (**(code **)(**(int **)(*(int *)(thisPtr + 0x70) + iVar11 * 4) + 8))(iVar9 + iStack_30);
        }
        *(int *)(thisPtr + 0x68) = *(int *)(thisPtr + 0x68) + -1;
        iVar9 = *(int *)(thisPtr + 100);
        iVar11 = *(int *)(thisPtr + 0x68) * 0x30;
        iVar8 = iVar11 + iVar9;
        // Copy last item to the removed slot
        *(undefined4 *)(iVar9 + iStack_30) = *(undefined4 *)(iVar11 + iVar9);
        *(undefined4 *)(iVar9 + 4 + iStack_30) = *(undefined4 *)(iVar8 + 4);
        *(undefined4 *)(iVar9 + 8 + iStack_30) = *(undefined4 *)(iVar8 + 8);
        *(undefined4 *)(iVar9 + 0xc + iStack_30) = *(undefined4 *)(iVar8 + 0xc);
        *(undefined4 *)(iVar9 + 0x10 + iStack_30) = *(undefined4 *)(iVar8 + 0x10);
        *(undefined4 *)(iVar9 + 0x14 + iStack_30) = *(undefined4 *)(iVar8 + 0x14);
        *(undefined4 *)(iVar9 + 0x18 + iStack_30) = *(undefined4 *)(iVar8 + 0x18);
        *(undefined4 *)(iVar9 + 0x1c + iStack_30) = *(undefined4 *)(iVar8 + 0x1c);
        *(undefined4 *)(iVar9 + 0x20 + iStack_30) = *(undefined4 *)(iVar8 + 0x20);
        *(undefined4 *)(iVar9 + 0x24 + iStack_30) = *(undefined4 *)(iVar8 + 0x24);
        *(undefined4 *)(iVar9 + 0x28 + iStack_30) = *(undefined4 *)(iVar8 + 0x28);
        *(undefined4 *)(iVar9 + 0x2c + iStack_30) = *(undefined4 *)(iVar8 + 0x2c);
    }

    // Now process remaining input items (not matched) and add to main list
    if (0 < iStack_14) {
        undefined4 *inputItem = (undefined4 *)(iVar13 + 0x18);
        int inputCount = iStack_14;
        do {
            iVar9 = inputItem[4]; // pointer at +0x28? Actually index 4? Wait: inputItem is offset +0x18 from start, so inputItem[4] is at offset 0x18+0x10=0x28
            if ((((*(char *)(iVar9 + 0x18) != '\x01') ||
                 (iVar9 = *(char *)(iVar9 + 0x10) + iVar9, iVar9 == 0)) ||
                (*(float *)(iVar9 + 0x1a0) * *(float *)(iVar9 + 0x1a0) +
                 *(float *)(iVar9 + 0x1a4) * *(float *)(iVar9 + 0x1a4) +
                 *(float *)(iVar9 + 0x1a8) * *(float *)(iVar9 + 0x1a8) <= DAT_00e2b05c)) ||
               (*(char *)(iVar9 + 0xd8) != '\x06')) {
                bVar2 = false;
            } else {
                bVar2 = true;
            }
            in_XMM0_Da = (float)inputItem[1] - *(float *)(thisPtr + 0x58);
            if (((in_XMM0_Da < DAT_00e44598) || (bVar2)) &&
               (iVar9 = FUN_00554200(thisPtr, inputItem + -6), iVar9 < 0)) {
                // Should be added: notify listeners
                iVar9 = *(int *)(thisPtr + 0x74);
                while (iVar9 = iVar9 + -1, -1 < iVar9) {
                    (**(code **)(**(int **)(*(int *)(thisPtr + 0x70) + iVar9 * 4) + 4))(inputItem + -6);
                }
                // Grow array if needed
                if (*(uint *)(thisPtr + 0x68) == (*(uint *)(thisPtr + 0x6c) & 0x3fffffff)) {
                    FUN_00aa4190((int *)(thisPtr + 100), 0x30);
                }
                // Append to main list
                puVar4 = (undefined4 *)(*(int *)(thisPtr + 0x68) * 0x30 + *(int *)(thisPtr + 100));
                *(int *)(thisPtr + 0x68) = *(int *)(thisPtr + 0x68) + 1;
                *puVar4 = inputItem[-6];
                puVar4[1] = inputItem[-5];
                puVar4[2] = inputItem[-4];
                puVar4[3] = inputItem[-3];
                puVar4[4] = inputItem[-2];
                puVar4[5] = inputItem[-1];
                puVar4[6] = *inputItem;
                puVar4[7] = inputItem[1];
                puVar4[8] = inputItem[2];
                puVar4[9] = inputItem[3];
                puVar4[10] = inputItem[4];
                puVar4[0xb] = inputItem[5];
            }
            inputItem = inputItem + 0xc; // 0xc dwords = 0x30 bytes
            inputCount = inputCount + -1;
        } while (inputCount != 0);
    }

    // Handle singleObjectInput (param_3)
    if (0 < *(int *)(singleObjectInput + 0x14)) {
        puVar12 = *(undefined4 **)(singleObjectInput + 0x10);
        iVar9 = FUN_00554200(thisPtr, puVar12);
        if (iVar9 == -1) {
            // Add as new
            iVar9 = *(int *)(thisPtr + 0x74);
            while (iVar9 = iVar9 + -1, -1 < iVar9) {
                (**(code **)(**(int **)(*(int *)(thisPtr + 0x70) + iVar9 * 4) + 4))(puVar12);
            }
            if (*(uint *)(thisPtr + 0x68) == (*(uint *)(thisPtr + 0x6c) & 0x3fffffff)) {
                FUN_00aa4190((int *)(thisPtr + 100), 0x30);
            }
            puVar4 = (undefined4 *)(*(int *)(thisPtr + 0x68) * 0x30 + *(int *)(thisPtr + 100));
            *(int *)(thisPtr + 0x68) = *(int *)(thisPtr + 0x68) + 1;
            *puVar4 = *puVar12;
            puVar4[1] = puVar12[1];
            puVar4[2] = puVar12[2];
            puVar4[3] = puVar12[3];
            puVar4[4] = puVar12[4];
            puVar4[5] = puVar12[5];
            puVar4[6] = puVar12[6];
            puVar4[7] = puVar12[7];
            puVar4[8] = puVar12[8];
            puVar4[9] = puVar12[9];
            puVar4[10] = puVar12[10];
            puVar4[0xb] = puVar12[0xb];
        } else {
            // Replace existing
            iVar11 = puVar12[10];
            puVar4 = (undefined4 *)(iVar9 * 0x30 + *(int *)(thisPtr + 100));
            if (*(char *)(iVar11 + 0x18) == '\x01') {
                iVar11 = *(char *)(iVar11 + 0x10) + iVar11;
            } else {
                iVar11 = 0;
            }
            iVar9 = puVar4[10];
            if (*(char *)(iVar9 + 0x18) == '\x01') {
                iVar9 = *(char *)(iVar9 + 0x10) + iVar9;
            } else {
                iVar9 = 0;
            }
            if (iVar11 != iVar9) {
                iVar9 = *(int *)(thisPtr + 0x74);
                while (iVar9 = iVar9 + -1, -1 < iVar9) {
                    (**(code **)(**(int **)(*(int *)(thisPtr + 0x70) + iVar9 * 4) + 8))(puVar12);
                }
                iVar9 = *(int *)(thisPtr + 0x74);
                while (iVar9 = iVar9 + -1, -1 < iVar9) {
                    (**(code **)(**(int **)(*(int *)(thisPtr + 0x70) + iVar9 * 4) + 4))(puVar4);
                }
            }
            *puVar4 = *puVar12;
            puVar4[1] = puVar12[1];
            puVar4[2] = puVar12[2];
            puVar4[3] = puVar12[3];
            puVar4[4] = puVar12[4];
            puVar4[5] = puVar12[5];
            puVar4[6] = puVar12[6];
            puVar4[7] = puVar12[7];
            puVar4[8] = puVar12[8];
            puVar4[9] = puVar12[9];
            puVar4[10] = puVar12[10];
            puVar4[0xb] = puVar12[0xb];
        }
    }

    // Remove items that are too far or no longer relevant (similar to earlier removal loop)
    iVar9 = *(int *)(thisPtr + 0x68) + -1;
    if (0 < iVar9) {
        iVar11 = iVar9 * 0x30;
        do {
            iVar8 = iVar9 + -1;
            iStack_1c = iVar8;
            if (0 < iVar9) {
                float dist2 = FUN_005540a0();
                if (dist2 >= DAT_00e2b334) {
                    iStack_1c = iStack_1c + -1;
                    if (iStack_1c < 0) goto LAB_00554b9c;
                    // continue loop to re-evaluate? Actually fall through to recalc? This is confusing.
                    goto FUN_005540a0; // actually it jumps back to compare again - unusual
                }
                // Remove this item
                iVar9 = *(int *)(thisPtr + 100);
                iVar5 = *(int *)(thisPtr + 0x74);
                while (iVar5 = iVar5 + -1, -1 < iVar5) {
                    (**(code **)(**(int **)(*(int *)(thisPtr + 0x70) + iVar5 * 4) + 8))(iVar9 + iVar11);
                }
                *(int *)(thisPtr + 0x68) = *(int *)(thisPtr + 0x68) + -1;
                iVar9 = *(int *)(thisPtr + 100);
                iVar5 = *(int *)(thisPtr + 0x68) * 0x30;
                iVar6 = iVar5 + iVar9;
                // Copy last item to removed slot
                *(undefined4 *)(iVar11 + iVar9) = *(undefined4 *)(iVar5 + iVar9);
                *(undefined4 *)(iVar11 + 4 + iVar9) = *(undefined4 *)(iVar6 + 4);
                // ... continue for remaining fields
            }
LAB_00554b9c:
            iVar11 = iVar11 + -0x30;
            iVar9 = iVar8;
        } while (0 < iVar8);
    }

    // Build auxiliary arrays: activeList and inactiveList based on type flag
    iStack_1c = 0;
    if (0 < *(int *)(thisPtr + 0x68)) {
        iStack_30 = 0;
        do {
            iVar9 = *(int *)(iStack_30 + 0x28 + *(int *)(thisPtr + 100)); // object pointer at +0x28
            if ((*(char *)(iVar9 + 0x18) == '\x01') &&
               (iVar9 = *(char *)(iVar9 + 0x10) + iVar9, iVar9 != 0)) {
                // Type 0x01: add to activeList
                piVar3 = (int *)(thisPtr + 0x7c);
                iVar11 = 0;
                if (0 < *(int *)(thisPtr + 0x80)) {
                    piVar10 = (int *)*piVar3;
                    do {
                        if (*piVar10 == iVar9) {
                            if (iVar11 != -1) goto LAB_00554c35;
                            break;
                        }
                        iVar11 = iVar11 + 1;
                        piVar10 = piVar10 + 1;
                    } while (iVar11 < *(int *)(thisPtr + 0x80));
                }
                FUN_009f2330(thisPtr + 8); // push_back on activeList
                if (*(uint *)(thisPtr + 0x80) == (*(uint *)(thisPtr + 0x84) & 0x3fffffff)) {
                    FUN_00aa4190(piVar3, 4);
                }
                *(int *)(*piVar3 + *(int *)(thisPtr + 0x80) * 4) = iVar9;
                *(int *)(thisPtr + 0x80) = *(int *)(thisPtr + 0x80) + 1;
            }
LAB_00554c35:
            iVar9 = *(int *)(iStack_30 + 0x28 + *(int *)(thisPtr + 100));
            if ((*(char *)(iVar9 + 0x18) == '\x02') &&
               (iVar9 = *(char *)(iVar9 + 0x10) + iVar9, iVar9 != 0)) {
                // Type 0x02: add to inactiveList
                piVar3 = (int *)(thisPtr + 0x88);
                iVar11 = 0;
                if (0 < *(int *)(thisPtr + 0x8c)) {
                    piVar10 = (int *)*piVar3;
                    do {
                        if (*piVar10 == iVar9) {
                            if (iVar11 != -1) goto LAB_00554ca7;
                            break;
                        }
                        iVar11 = iVar11 + 1;
                        piVar10 = piVar10 + 1;
                    } while (iVar11 < *(int *)(thisPtr + 0x8c));
                }
                FUN_00a0df80(thisPtr + 0xc); // push_back on inactiveList
                if (*(uint *)(thisPtr + 0x8c) == (*(uint *)(thisPtr + 0x90) & 0x3fffffff)) {
                    FUN_00aa4190(piVar3, 4);
                }
                *(int *)(*piVar3 + *(int *)(thisPtr + 0x8c) * 4) = iVar9;
                *(int *)(thisPtr + 0x8c) = *(int *)(thisPtr + 0x8c) + 1;
            }
LAB_00554ca7:
            iStack_30 = iStack_30 + 0x30;
            iStack_1c = iStack_1c + 1;
        } while (iStack_1c < *(int *)(thisPtr + 0x68));
    }

    // Clean up TLS buffer
    piVar3 = (int *)TlsGetValue(DAT_01139810);
    piVar3[8] = iVar13;
    if (iVar13 == piVar3[10]) {
        (**(code **)(*piVar3 + 0x18))(iVar13); // free
    }
    if (-1 < (int)(uVar1 | 0x80000000)) {
        TlsGetValue(DAT_01139810);
        FUN_00aa26e0(iVar13, (uVar1 & 0x3fffffff) * 0x30, 0x17);
    }
    return;

    // Jump target for re-evaluation (this is weird, but we replicate the code flow)
code_r0x00554aee:
    iStack_1c = iStack_1c + -1;
    if (iStack_1c < 0) goto LAB_00554b9c;
    goto // actually goes to the distance comparison again
}