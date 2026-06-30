// FUNC_NAME: EntityManager::tryCreateEntity
undefined4 __thiscall EntityManager::tryCreateEntity(int entityManager, int createInfo) {
    int *newEntity;
    int iVar1;
    int iVar2;
    int *piVar5;
    undefined4 *puVar6;
    undefined8 *puVar7;
    undefined4 uStack_28;
    int iStack_24;
    undefined8 uStack_20;
    undefined4 uStack_18;
    int local_14[3];
    code *local_8;

    // Verify pointers at +4 (resource) and +8 (validator) are valid
    if (*(int *)(entityManager + 8) == 0 || *(int *)(entityManager + 4) == 0) {
        return 0;
    }

    // Allocate new entity (size 0x2c0 bytes)
    newEntity = (int *)FUN_009c8e50(0x2c0);
    if (newEntity == nullptr) {
        newEntity = nullptr;
    } else {
        // Call constructor on the new memory
        newEntity = (int *)FUN_005dcca0();
    }

    // Prepare creation callback context from createInfo
    FUN_004d3bc0(createInfo);
    FUN_004d3e20(local_14);
    // If callback pointer was set, invoke it
    if (local_14[0] != 0) {
        (*local_8)(local_14[0]);
    }

    // Copy configuration fields into new entity
    uVar4 = FUN_004dafd0(createInfo + 0x20);   // offset +0x20: field A
    *(undefined4 *)(newEntity + 0x2b0) = uVar4;
    createInfo = FUN_004dafd0(createInfo + 0x40);   // offset +0x40: field B
    *(int *)(newEntity + 0x2b4) = createInfo;
    *(undefined4 *)(newEntity + 0x2b8) = *(undefined4 *)(createInfo + 0x60);  // offset +0x60: field C

    // Validate and potentially link from an existing entity reference (entityManager+0xC)
    iVar1 = *(int *)(entityManager + 0xc);
    if (iVar1 != 0) {
        iStack_24 = *(int *)(iVar1 + 0x1c);
        piVar5 = (int *)FUN_005df150(&createInfo);
        if (*piVar5 == 0 || *piVar5 != iVar1) {
            FUN_00b97aea();
        }
        if (piVar5[1] != iStack_24) {
            puVar6 = (undefined4 *)FUN_005df050(&createInfo);
            *(undefined4 *)(newEntity + 0x29c) = *puVar6;   // offset +0x29c: linked field
        }
    }

    // Attempt to finalize/validate entity via validator + callback
    uVar4 = FUN_004dafd0(createInfo);
    uStack_28 = uVar4;
    iStack_24 = (int)newEntity;
    puVar7 = (undefined8 *)FUN_005deb50(*(undefined4 *)(entityManager + 8), local_14, &uStack_28);
    uStack_20 = *puVar7;
    uStack_18 = *(undefined4 *)(puVar7 + 1);
    if ((char)uStack_18 != '\0') {
        // Validation succeeded – complete creation
        FUN_005dbc10(createInfo, uVar4);
        return 1;
    }

    // Validation failed – rollback
    FUN_005dcdc0();
    FUN_009c8eb0(newEntity);   // free memory
    return 0;
}