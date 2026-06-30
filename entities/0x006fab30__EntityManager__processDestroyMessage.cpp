// FUNC_NAME: EntityManager::processDestroyMessage
void __thiscall EntityManager::processDestroyMessage(void *this, int *message) {
    int *piVar1;
    undefined4 *puVar2;
    int iVar3;
    uint *puVar4;
    int iVar5;
    int iVar6;
    uint uVar7;
    int *piVar8;
    int iVar9;
    uint uVar10;
    bool bVar11;

    if ((*message == DAT_01206768) || (*message == DAT_01206780)) {
        int destroyEntityId = message[1];
        int *entityArray = *(int **)((int)this + 0x1c); // +0x1c: pointer to array of entity pointers (e.g., m_activeEntities)
        int entityCount = *(int *)((int)this + 0x20);   // +0x20: count of entities in first array

        int *endPtr = entityArray + entityCount;
        for (piVar8 = entityArray; piVar8 < endPtr; piVar8++) {
            piVar1 = piVar8 + 1;
            bVar11 = false;
            if (destroyEntityId != 0) {
                int curId = entityManagerContextId(); // FUN_00411710 returns some context ID
                bVar11 = curId == *(int *)(*piVar8 + 0xc); // entity ID at +0xc
            }
            int entityPtr = *piVar8; // entity base pointer
            uint entityId = *(uint *)(entityPtr + 0xc);
            // Hash table lookup (entity database)
            uint *bucketPtr = *(uint **)(*(int *)(DAT_0122337c + 0x50) + (entityId % *(uint *)(DAT_0122337c + 0x54)) * 4);
            for (puVar4 = bucketPtr; puVar4 != (uint *)0x0; puVar4 = (uint *)puVar4[2]) {
                if (*puVar4 == entityId) {
                    if (puVar4 != (uint *)0x0 && puVar4[1] != 0) {
                        iVar6 = *(int *)(puVar4[1] + 0x24); // state/type at +0x24
                        goto checkState;
                    }
                    break;
                }
            }
            iVar6 = -1; // not found => state -1
checkState:
            if (((bVar11) || (iVar6 == -1)) || (iVar6 == 4) || (iVar6 == 2)) {
                if (entityId == *(uint *)((int)this + 0x38)) { // +0x38: current entity ID
                    entityManagerClearCurrentEntity(); // FUN_006faa40
                }
                // Release materials associated with entity
                uint materialCount = 0;
                if (*(int *)(entityPtr + 0x24) != 0) {
                    do {
                        int materialId = *(int *)(*(int *)(entityPtr + 0x20) + materialCount * 8);
                        if (materialId != 0 && materialId != 0x48) {
                            entityReleaseMaterial(); // FUN_0072cf40
                        }
                        materialCount++;
                    } while (materialCount < *(uint *)(entityPtr + 0x24));
                }
                // Remove entity pointer from the array by shifting
                uint arrCount = *(uint *)((int)this + 0x20);
                uint idx = 0;
                if (arrCount != 0) {
                    int *arrBase = *(int **)((int)this + 0x1c);
                    do {
                        if (arrBase[idx] == entityPtr) {
                            if (idx != 0xffffffff) {
                                if (idx < arrCount - 1) {
                                    do {
                                        puVar2 = (undefined4 *)(*(int *)((int)this + 0x1c) + idx * 4);
                                        *puVar2 = puVar2[1];
                                        idx++;
                                    } while (idx < *(int *)((int)this + 0x20) - 1U);
                                }
                                *(int *)((int)this + 0x20) = *(int *)((int)this + 0x20) - 1;
                            }
                            break;
                        }
                        idx++;
                    } while (idx < arrCount);
                }
                entityDestroy(entityPtr); // FUN_006f9f90
                // Re-read global after potential corruption
                iVar9 = DAT_0122337c;
            }
            piVar8 = piVar1; // advance iterator (piVar1 = piVar8+1)
        } while ((int)piVar1 < (int)(*(int *)((int)this + 0x1c) + *(int *)((int)this + 0x20) * 4));

        // Now process second array at +0x10 (count at +0x14) identically
        entityArray = *(int **)((int)this + 0x10); // +0x10: second array (e.g., m_pendingDestroy)
        entityCount = *(int *)((int)this + 0x14);   // +0x14: count for second array
        endPtr = entityArray + entityCount;
        for (piVar8 = entityArray; piVar8 < endPtr; piVar8++) {
            piVar1 = piVar8 + 1;
            bVar11 = false;
            if (destroyEntityId != 0) {
                int curId = entityManagerContextId();
                bVar11 = curId == *(int *)(*piVar8 + 0xc);
            }
            int entityPtr = *piVar8;
            uint entityId = *(uint *)(entityPtr + 0xc);
            uint *bucketPtr = *(uint **)(*(int *)(iVar9 + 0x50) + (entityId % *(uint *)(iVar9 + 0x54)) * 4);
            for (puVar4 = bucketPtr; puVar4 != (uint *)0x0; puVar4 = (uint *)puVar4[2]) {
                if (*puVar4 == entityId) {
                    if (puVar4 != (uint *)0x0 && puVar4[1] != 0) {
                        iVar6 = *(int *)(puVar4[1] + 0x24);
                        goto checkState2;
                    }
                    break;
                }
            }
            iVar6 = -1;
checkState2:
            if (((bVar11) || (iVar6 == -1)) || (iVar6 == 4) || (iVar6 == 2)) {
                if (entityId == *(uint *)((int)this + 0x38)) {
                    entityManagerClearCurrentEntity();
                }
                uint materialCount = 0;
                if (*(int *)(entityPtr + 0x24) != 0) {
                    do {
                        int materialId = *(int *)(*(int *)(entityPtr + 0x20) + materialCount * 8);
                        if (materialId != 0 && materialId != 0x48) {
                            entityReleaseMaterial();
                        }
                        materialCount++;
                    } while (materialCount < *(uint *)(entityPtr + 0x24));
                }
                uint arrCount = *(uint *)((int)this + 0x14);
                uint idx = 0;
                if (arrCount != 0) {
                    int *arrBase = *(int **)((int)this + 0x10);
                    do {
                        if (arrBase[idx] == entityPtr) {
                            if (idx != 0xffffffff) {
                                if (idx < arrCount - 1) {
                                    do {
                                        puVar2 = (undefined4 *)(*(int *)((int)this + 0x10) + idx * 4);
                                        *puVar2 = puVar2[1];
                                        idx++;
                                    } while (idx < *(int *)((int)this + 0x14) - 1U);
                                }
                                *(int *)((int)this + 0x14) = *(int *)((int)this + 0x14) - 1;
                            }
                            break;
                        }
                        idx++;
                    } while (idx < arrCount);
                }
                entityDestroy(entityPtr); // FUN_006f9f90
                iVar9 = DAT_0122337c;
            }
            // Note: iterator advance is done by the outer loop condition; the decompiled code uses a do-while but we re-synthesized as for loop.
        }
    }
    return;
}