// FUNC_NAME: Sentient::checkLineOfSight
char __thiscall Sentient::checkLineOfSight(float *fromPos, float *toPos, int someFlags, int ignoreEntityId) {
    // Compute direction vector from fromPos to toPos
    float diff[3];
    diff[0] = fromPos[0] - toPos[0];
    diff[1] = fromPos[1] - toPos[1];
    diff[2] = fromPos[2] - toPos[2];
    float dummy = 0.0f; // unused alignment

    // Normalize the direction vector
    FUN_0056afa0(diff, diff); // likely Math::normalize

    // Get pointer to obstacle container from some manager at this+0x10
    int *pManager = *(int **)(this + 0x10); // +0x10: pointer to game world / navigation manager
    int *obstacleContainer = *(int **)((int)pManager + 0x1ed8); // +0x1ed8: pointer to current level's obstacle list

    // Adjust the container pointer if non-null (likely offset to embedded struct)
    if (obstacleContainer != NULL) {
        obstacleContainer = (int *)((int)obstacleContainer - 0x48);
    }

    // Normalized direction for raycasts
    float normalDir[3];
    normalDir[0] = diff[0];
    normalDir[1] = diff[1];
    normalDir[2] = diff[2];

    // First check: against the global static obstacle set
    void *navMesh = (void *)FUN_0043c2c0(*(int *)((int)obstacleContainer + 0x88)); // get collision mesh from obstacle container
    char visible = FUN_007144e0(fromPos, toPos, someFlags, ignoreEntityId, normalDir, navMesh); // raycast against static obstacles

    if (visible) {
        // If in multiplayer (game mode 2), check against a different mesh
        int gameMode = FUN_00806440();
        if (gameMode == 2) {
            void *multiplayerNavMesh = (void *)FUN_0043c2c0(FUN_008c6d20(0));
            visible = FUN_007144e0(fromPos, toPos, someFlags, ignoreEntityId, normalDir, multiplayerNavMesh);
        }

        if (visible) {
            // Check additional sub‑obstacles (e.g., doors, destructibles)
            int subCount = *(int *)((int)obstacleContainer + 100); // +0x64: number of sub‑obstacle lists
            int **subList = (int **)((int)obstacleContainer + 0x58); // +0x58: array of sub‑obstacle pointers
            for (int i = 0; i < subCount; ++i) {
                int *subObj = subList[i];
                if (subObj != NULL) {
                    int *entity = (int *)FUN_008c74d0((int)subObj); // get entity from sub‑obstacle
                    if (entity != NULL) {
                        void *subNavMesh = (void *)FUN_0043c2c0(*(int *)((int)entity + 0x88));
                        visible = FUN_007144e0(fromPos, toPos, someFlags, ignoreEntityId, normalDir, subNavMesh);
                        if (!visible) break; // early exit if blocked
                    }
                }
            }
        }
    }

    // Now check against other dynamic entities (NPCs, players, etc.)
    // Global entity list manager
    int *entityManager = DAT_012233a0; // global pointer to entity manager
    int entityCount = FUN_0043ff40(); // number of active entities
    int *entityArray = *(int **)(entityManager + 4); // +4: pointer to array of entity pointers
    for (unsigned int i = 0; i < entityCount; ++i) {
        int *entity = (int *)entityArray[i];
        if (entity != NULL) {
            int adjustedEntity = (int)entity - 0x1f30; // subtract offset to get base
            if (adjustedEntity != 0 && visible) {
                // Compare entity type/ID with our own (stored at this+0x10->0x1ed4)
                int ourEntityId = *(int *)(*(int *)(this + 0x10) + 0x1ed4);
                int entityId = *(int *)((int)entity - 0x5c); // entity's ID field at -0x5c
                if (entityId == ourEntityId && adjustedEntity != ignoreEntityId) {
                    visible = FUN_00713f90(fromPos, toPos, someFlags, adjustedEntity, normalDir);
                }
            }
        }
    }

    return visible;
}