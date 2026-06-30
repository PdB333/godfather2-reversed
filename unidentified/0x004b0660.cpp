// FUN_004b0660: GameWorld::queryEntitiesInArea
void __thiscall GameWorld::queryEntitiesInArea(undefined4 *param_1, undefined4 param_2, undefined4 param_3,
                                              int *outputEntityPtrArray, int *outputEntityPairArray,
                                              undefined4 userData, char bIncludeDerived)
{
    char cVar1;
    int iVar2;
    int *piVar3;
    char *pcVar4;
    int iVar5;
    int iVar6;
    int iVar7;
    undefined1 *puVar8;
    uint uVar9;
    int *piVar10;
    undefined4 uVar11;
    undefined1 uStack_5b1;
    int *piStack_5b0; // pointer to this? or something
    int iStack_5ac;   // base of entity ID list
    uint uStack_5a8;  // count of IDs
    uint uStack_5a4;  // capacity of ID list
    undefined1 *local_598;
    undefined4 local_594;
    undefined4 local_590;
    undefined1 local_58c [48]; // buffer for something
    int aiStack_55c [5];
    int *local_548; // pointer to entity? or vtable?
    undefined4 local_544;
    undefined1 *local_540; // pointer to entity?
    undefined4 local_53c;
    undefined1 local_538;
    undefined1 local_537;
    undefined2 local_536;
    undefined4 local_534;
    undefined1 local_530;
    char local_52f;
    undefined2 local_52e;
    undefined4 local_52c; // param_3 stored here
    int aiStack_50c [2];
    int iStack_504;  // base of entity pointer list
    uint local_500;  // count of pointers
    uint uStack_4fc; // capacity of pointer list
    undefined1 *local_4f0;
    undefined4 local_4ec;
    undefined4 local_4e8;
    undefined1 local_4e4 [48];
    undefined **ppuStack_4b4;
    int local_4a0 [8]; // maybe a vtable or query results?
    undefined1 local_480 [48];
    undefined4 local_450; // from param_1[0]
    undefined4 local_44c; // from param_1[1]
    undefined4 local_448; // from param_1[2]
    undefined4 local_444; // from param_1[3]
    undefined1 local_440 [12]; // buffer for callback
    int iStack_434;    // handle for heap allocation?
    int iStack_430;    // count of something from callback
    undefined1 *puStack_42c; // pointer to list from callback
    undefined4 uStack_428;
    undefined4 uStack_424;
    undefined1 auStack_420 [1052]; // scratch buffer for entities?

    // Initialize box filter from param_1 (position/radius?)
    local_598 = local_58c;
    local_590 = 0x80000010;
    local_4f0 = local_4e4;
    local_4e8 = 0x80000010;
    local_450 = *param_1;              // +0x00: min x (or left)
    local_44c = param_1[1];            // +0x04: max x (or right)
    local_448 = param_1[2];            // +0x08: min y (or bottom)
    local_444 = param_1[3];            // +0x0c: max y (or top)
    local_594 = 0;
    local_4ec = 0;

    // Access singleton game world manager
    iVar6 = *(int *)(*(int *)(DAT_01223480 + 0x24) + 0x6c); // some object from singleton
    iVar2 = *(int *)(iVar6 + 0x54); // pointer to a manager (e.g., spatial hash)

    // Lock or begin operation
    FUN_00aa5450(&DAT_00ef3f00);  // likely lock global mutex
    FUN_00a64b00(param_2);        // set filter type

    // Initialize query structures
    local_540 = local_480;
    local_548 = local_4a0;        // vtable-like pointer
    local_53c = 0;
    local_544 = 0xffffffff;
    local_538 = 0;
    local_534 = 0;
    local_530 = 0;
    local_52c = 0;
    local_52e = 0;
    local_52f = 0x7f;            // placeholder
    FUN_00a64fd0();              // possibly set up query flags
    local_52f = (char)&local_548 - (char)&local_534; // compute size of query block?
    local_52c = param_3;         // store user parameter

    // Global counter for results
    local_500 = *(uint *)&DAT_00e2eff4; // load existing count
    local_537 = 0;
    local_536 = 0;

    // Call a method on the query object (via vtable at +0x1c)
    (**(code **)(*local_548 + 0x1c))(local_540, *(undefined4 *)(iVar2 + 4), local_440);

    // Query the spatial manager (e.g., spatial hash) for entities in the area
    puStack_42c = auStack_420;
    uStack_428 = 0;
    uStack_424 = 0x80000080;
    (**(code **)(**(int **)(iVar6 + 0x54) + 0x40))(&local_44c, &puStack_42c);
    // puStack_42c now holds a list of entity pointers, iStack_430 = count, iStack_434 = handle for memory

    iVar2 = iStack_430 - 1;
    uVar9 = uStack_5a8; // current number of collected IDs
    if (iVar2 >= 0) {
        piVar3 = (int *)(iStack_434 + 4); // start of entity pointer array
        do {
            // Get entity pointer from list
            piVar10 = (int *)(*(char *)(*piVar3 + 5) + *piVar3); // offset to entity base (maybe object header)

            // Filter: must be different from existing list (aiStack_55c) and pass type check
            if (((aiStack_55c != piVar10) &&
                 (pcVar4 = (char *)(**(code **)(*(int *)(*(int *)(iVar6 + 0x70) + 8) + 4))
                                     (&uStack_5b1, aiStack_55c, piVar10), uVar9 = uStack_5a8,
                 *pcVar4 != '\0')) && (*piVar10 != 0) &&
                ((int)(char)piVar10[4] + (int)piVar10 != 0)) {

                // Create a packet/identifier for this entity (maybe its unique ID)
                FUN_004af8c0(aiStack_50c, 0x2001); // 0x2001 could be entity type constant
                iVar7 = 0;
                if (aiStack_50c[0] != 0) {
                    iVar7 = aiStack_50c[0];
                }
                uVar9 = uStack_5a8;
                if (iVar7 != 0) {
                    // If not including derived entities, skip if already in list
                    if ((bIncludeDerived == '\0') && (iVar5 = 0, (int)uStack_5a8 > 0)) {
                        do {
                            if (iVar7 == *(int *)(iStack_5ac + iVar5 * 4)) goto LAB_004b0940;
                            iVar5 = iVar5 + 1;
                        } while (iVar5 < (int)uStack_5a8);
                    }
                    // Add to ID list
                    if (uStack_5a8 == (uStack_5a4 & 0x3fffffff)) {
                        FUN_00aa4190(&iStack_5ac, 4); // grow array
                    }
                    *(int *)(iStack_5ac + uStack_5a8 * 4) = iVar7;
                    uStack_5a8 = uStack_5a8 + 1;

                    // Add entity pointer to corresponding list
                    if (local_500 == (uStack_4fc & 0x3fffffff)) {
                        FUN_00aa4190(&iStack_504, 4); // grow array
                    }
                    *(int **)(iStack_504 + local_500 * 4) = piVar10;
                    local_500 = local_500 + 1;
                    uVar9 = uStack_5a8;
                }
            }
LAB_004b0940:
            piVar3 = piVar3 + 2; // advance by two ints? entity list structure?
            iVar2 = iVar2 + -1;
        } while (iVar2 >= 0);
    }

    // Now process collected entities
    iVar2 = 0;
    if ((int)uVar9 > 0) {
        do {
            iVar6 = iVar2 * 4;
            // Call virtual method on param_1? (actually this object's vtable at +0xc)
            cVar1 = (**(code **)(*piStack_5b0 + 0xc))
                        (param_1, *(undefined4 *)(iVar6 + iStack_5ac), 0, userData);
            if (cVar1 != '\0') {
                if (outputEntityPairArray == (int *)0x0) {
                    // Only output to the simple array (outputEntityPtrArray)
                    if (outputEntityPtrArray != (int *)0x0) {
                        if (bIncludeDerived == '\0') {
                            (**(code **)(*outputEntityPtrArray + 4))(*(undefined4 *)(iVar6 + iStack_5ac), 0);
                        }
                        else {
                            (**(code **)(*outputEntityPtrArray + 4))
                                (*(undefined4 *)(iVar6 + iStack_5ac), *(undefined4 *)(iVar6 + iStack_504));
                        }
                    }
                }
                else {
                    // Output to pair array: first element is entity pointer, second is something
                    if (*(int *)(iVar6 + iStack_5ac) == 0) {
                        iVar6 = 0;
                    }
                    else {
                        iVar6 = *(int *)(iVar6 + iStack_5ac) + 0x48; // offset 0x48 in entity?
                    }
                    uVar11 = 0;
                    if (iVar6 != 0) {
                        uVar11 = *(undefined4 *)(iVar6 + 4);
                        *(undefined1 **)(iVar6 + 4) = &stack0xfffffa40; // temporary sentinel
                    }
                    iVar7 = outputEntityPairArray[2]; // capacity
                    if (outputEntityPairArray[1] == iVar7) { // if count == capacity, grow
                        if (iVar7 == 0) {
                            iVar7 = 1;
                        }
                        else {
                            iVar7 = iVar7 * 2;
                        }
                        FUN_004b1440(iVar7); // reallocate array
                    }
                    piVar3 = (int *)(*outputEntityPairArray + outputEntityPairArray[1] * 8);
                    outputEntityPairArray[1] = outputEntityPairArray[1] + 1;
                    if (piVar3 != (int *)0x0) {
                        *piVar3 = iVar6;          // store entity pointer
                        piVar3[1] = 0;             // second slot initially zero
                        if (iVar6 != 0) {
                            piVar3[1] = *(int *)(iVar6 + 4); // store second field from entity
                            *(int **)(iVar6 + 4) = piVar3;   // update linked list
                        }
                    }
                    // Restore the sentinel
                    if (iVar6 != 0) {
                        puVar8 = *(undefined1 **)(iVar6 + 4);
                        if (puVar8 == &stack0xfffffa40) {
                            *(undefined4 *)(iVar6 + 4) = uVar11;
                        }
                        else {
                            while (*(undefined1 **)(puVar8 + 4) != &stack0xfffffa40) {
                                puVar8 = *(undefined1 **)(puVar8 + 4);
                            }
                            *(undefined4 *)(puVar8 + 4) = uVar11;
                        }
                    }
                }
            }
            iVar2 = iVar2 + 1;
        } while (iVar2 < (int)uStack_5a8);
    }

    // Clean up spatial query result list
    puVar8 = puStack_42c;
    if ((int)puStack_42c >= 0) {
        TlsGetValue(DAT_01139810);
        FUN_00aa26e0(iStack_434, (int)puVar8 * 8, 0x17); // free memory
    }
    ppuStack_4b4 = &PTR_LAB_00d96914;
    if ((int)uStack_4fc >= 0) {
        TlsGetValue(DAT_01139810);
        FUN_00aa26e0(iStack_504, uStack_4fc * 4, 0x17);
    }
    if ((int)uStack_5a4 >= 0) {
        TlsGetValue(DAT_01139810);
        FUN_00aa26e0(iStack_5ac, uStack_5a4 * 4, 0x17);
    }
    return;
}