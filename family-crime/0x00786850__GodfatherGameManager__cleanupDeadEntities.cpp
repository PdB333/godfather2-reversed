// FUNC_NAME: GodfatherGameManager::cleanupDeadEntities
void __fastcall GodfatherGameManager::cleanupDeadEntities(int this)
{
    uint entityCount;
    int currentEntity;
    int compareEntity;
    char isEntityDead;
    int *entityArray;
    int *currentPtr;
    uint idx;
    uint innerIdx;
    uint outerIdx;

LAB_00786860:
    entityCount = *(uint *)(this + 0x1a3c);
    outerIdx = 0;
    if (entityCount != 0) {
        entityArray = (int *)(this + 0x193c);
        do {
            currentEntity = *entityArray;
            idx = outerIdx + 1;
            currentPtr = entityArray;
            for (innerIdx = idx; innerIdx < entityCount; innerIdx = innerIdx + 1) {
                currentPtr = currentPtr + 1;
                compareEntity = *currentPtr;
                isEntityDead = FUN_00787e70(compareEntity); // isEntityDead(compareEntity)
                if (isEntityDead != '\0') {
                    if (*(float *)(currentEntity + 0x1c) < *(float *)(compareEntity + 0x1c) ||
                        *(float *)(currentEntity + 0x1c) == *(float *)(compareEntity + 0x1c)) {
                        FUN_007891e0(currentEntity); // entityDeinit(currentEntity)
                        if (currentEntity == *(int *)(this + 0x2c74)) {
                            *(undefined4 *)(this + 0x2c74) = 0;
                        }
                        entityCount = *(uint *)(this + 0x1a3c);
                        if (outerIdx < entityCount) {
                            if (outerIdx < entityCount - 1) {
                                *(undefined4 *)(this + 0x193c + outerIdx * 4) =
                                     *(undefined4 *)(this + 0x1938 + entityCount * 4);
                            }
                            *(int *)(this + 0x1a3c) = *(int *)(this + 0x1a3c) + -1;
                        }
                        FUN_00788c50(); // notifyEntityListChanged()
                        (**(code **)(*(int *)(this + 0x1914) + 4))(currentEntity,0); // entity->vtable->onRemoved(0)
                    }
                    else {
                        FUN_007891e0(compareEntity); // entityDeinit(compareEntity)
                        if (compareEntity == *(int *)(this + 0x2c74)) {
                            *(undefined4 *)(this + 0x2c74) = 0;
                        }
                        entityCount = *(uint *)(this + 0x1a3c);
                        if (innerIdx < entityCount) {
                            if (innerIdx < entityCount - 1) {
                                *(undefined4 *)(this + 0x193c + innerIdx * 4) =
                                     *(undefined4 *)(this + 0x1938 + entityCount * 4);
                            }
                            *(int *)(this + 0x1a3c) = *(int *)(this + 0x1a3c) + -1;
                        }
                        FUN_00788c50(); // notifyEntityListChanged()
                        (**(code **)(*(int *)(this + 0x1914) + 4))(compareEntity,0); // entity->vtable->onRemoved(0)
                    }
                    goto LAB_00786860;
                }
            }
            entityArray = entityArray + 1;
            outerIdx = idx;
        } while (idx < entityCount);
    }
    return;
}