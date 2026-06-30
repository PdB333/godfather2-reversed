// FUNC_NAME: EntityManager::findNearestInteractableEntity
int* __thiscall EntityManager::findNearestInteractableEntity(int* thisPtr, int* excludeEntity) {
    int* entityListHead;
    int* currentNode;
    int* entityPtr;
    int checkResult1;
    float threshold;
    float distanceSq;
    float dx, dy, dz;
    int checkResult2;
    int* someHandlePtr;
    int* targetEntity;
    float closestDistSq = 0x44794; // DAT_00e44794, likely initial max distance

    // Get entity manager interface (type 2)
    int* entityManager = (int*)FUN_008c6d20(2);
    // Get head of active entity list
    entityListHead = (int*)*(int*)FUN_0043c2c0(entityManager);
    // Get player transform (for distance comparison)
    int* playerTransform = (int*)FUN_00471610();

    int* closestEntity = 0;

    for (currentNode = entityListHead; currentNode != 0; currentNode = (int*)currentNode[1]) {
        entityPtr = (int*)*currentNode;
        if (entityPtr == excludeEntity) continue;

        checkResult1 = 0;
        // Query entity for first capability (0x55859efa)
        if ( (*(int (**)(void))(*(int*)*entityPtr + 0x10))(0x55859efa, &checkResult1) ) {
            // If capability exists, call a method on this manager (offset 0xC0) that returns a float threshold
            threshold = (float)(*(int (**)(void))(*(int*)*thisPtr + 0xC0))();
            if (threshold > 0.0f) {
                // Perform visibility or other check
                if (FUN_007f4800()) {
                    checkResult2 = 0;
                    // Query entity for second capability (0x369ac561)
                    if ( (*(int (**)(void))(*(int*)*entityPtr + 0x10))(0x369ac561, &checkResult2) && checkResult2 != 0 ) {
                        // Access a structured list from this manager at offset 0x5c, then 0x40
                        int* someList = *(int**)(*(int*)(thisPtr + 0x5c) + 0x40);
                        int handle = (someList != 0) ? (int)(someList - 0x48) : 0;
                        // Convert handle to entity pointer
                        targetEntity = (int*)FUN_0071ce70(handle);
                        if (targetEntity == 0) {
                            // Compute squared distance from entity to player
                            dx = *(float*)(entityPtr + 0x30) - *(float*)(playerTransform + 0x30);
                            dy = *(float*)(entityPtr + 0x34) - *(float*)(playerTransform + 0x34);
                            dz = *(float*)(entityPtr + 0x38) - *(float*)(playerTransform + 0x38);
                            distanceSq = dx*dx + dy*dy + dz*dz;
                            if (distanceSq < closestDistSq) {
                                closestDistSq = distanceSq;
                                closestEntity = entityPtr;
                            }
                        }
                    }
                }
            }
        }
    }
    return closestEntity;
}