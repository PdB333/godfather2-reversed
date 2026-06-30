// FUNC_NAME: TargetingManager::findNearestTarget
bool __fastcall TargetingManager::findNearestTarget(int thisPtr)
{
    int *entityManager;
    int *entityArray;
    int entityCount;
    int i;
    int candidateEntity;
    int closestEntity;
    float closestDistSq;
    float dx, dy, dz;
    float distSq;
    bool found;
    int *targetListNode;
    int newTargetNode;
    int *simManager;
    int tempInt;
    char testResult;
    int debugCount;

    // Offset 0x0C: pointer to entity manager
    entityManager = *(int **)(thisPtr + 0x0C);
    // Call to get the simulation manager singleton
    simManager = (int *)FUN_00471610(); // SimManager::getInstance()

    // Offset 0x2004 in entityManager: pointer to an array of entity nodes
    entityArray = (int *)*(int *)(entityManager + 0x2004);
    if (entityArray == NULL) {
        entityArray = NULL;
    } else {
        // Subtract 0x48 to get base of the first element (intrusive list node offset)
        entityArray = (int *)((char *)entityArray - 0x48);
    }

    // --- Debug drawing setup ---
    // Build a transform from entityArray + 0x148 and global constants
    *(int *)(0x??? /* local_2f0 */) = *(int *)(entityArray + 0x148 / 4);
    *(int *)(0x??? /* local_2ec */) = _DAT_00d5780c;
    *(int *)(0x??? /* local_2e4 */) = _DAT_00d5780c;
    *(int *)(0x??? /* local_2e8 */) = *(int *)(entityArray + 0x148 / 4);
    FUN_00a66df0(/* address of local_2f0 */ &local_2f0, _DAT_00ef3a9c);
    FUN_00540bc0(0x400, 0x80000000, 0, 0);
    // Get camera position from simManager (offset 0x30, 0x34, 0x38)
    long long cameraPosXY = *(long long *)(simManager + 0x30 / 4);
    float cameraZ = *(float *)(simManager + 0x38 / 4);
    float cameraY = (float)((unsigned long long)cameraPosXY >> 32);
    float cameraX = (float)(int)cameraPosXY;
    // Add offset to Y
    cameraY += _DAT_00d5842c;
    // Build a point for debug line
    struct {
        float x, y, z;
    } debugPoint;
    debugPoint.x = cameraX;
    debugPoint.y = cameraY;
    debugPoint.z = cameraZ; // Actually local_2fc was set using CONCAT44, likely a 3D vector
    // ... (the decompiler showed a complex assignment, but it's essentially the camera pos with Y offset)
    FUN_00549bf0();
    FUN_00549cf0(/* some buffer */);
    int debugToken = FUN_00540cc0(/* some buffer */);
    FUN_00549d40(&debugPoint);
    // --- End debug drawing setup ---

    // Prepare entity list query
    void **funcTable = &PTR_FUN_00e35734; // vtable or function pointer array
    int *entityPtrArray = (int *)malloc(??); // local_170
    int *outEntityCount = &entityCount; // local_178
    *outEntityCount = 0;
    // Query for entities (likely returns array of entity pointers and count)
    FUN_00549ea0(&funcTable, 0); // This sets entityCount and fills entityPtrArray
    entityCount = debugCount; // Actually debugCount is the same as local_178 set inside the function? The decompiler shows local_178 = 0 before call, but then later used. We'll assume it's set by FUN_00549ea0.

    // Initialize state
    closestEntity = 0;
    closestDistSq = 0.0f;
    found = false;

    if (0 < entityCount) {
        for (i = 0; i < entityCount; i++) {
            // Get entity pointer from array
            int *entity = *(int **)(entityPtrArray + i);
            // Call virtual function at vtable+0x10 with hash 0x4ecfbe13
            // This likely checks if the entity is a valid target
            testResult = ((char (*)(int, int*))(*(int **)(*entity + 0x10 / 4)))(0x4ecfbe13, &candidateEntity);
            // candidateEntity is set by the function (maybe the entity itself or a derived pointer)
            if (testResult != 0 && candidateEntity != 0) {
                // Check entity state: offset +0x1A8 must be 1 (active)
                // and offset +0x1D4 bit 2 (0x4) must be clear
                if (*(char *)(candidateEntity + 0x1A8 / 4) == 1 && (*(unsigned char *)(candidateEntity + 0x1D4 / 4) & 0x04) == 0) {
                    // Compute distance from simManager position (camera position)
                    dx = *(float *)(simManager + 0x30 / 4) - *(float *)(candidateEntity + 0x30 / 4);
                    dy = *(float *)(simManager + 0x34 / 4) - *(float *)(candidateEntity + 0x34 / 4);
                    dz = *(float *)(simManager + 0x38 / 4) - *(float *)(candidateEntity + 0x38 / 4);
                    distSq = dx*dx + dy*dy + dz*dz;
                    if (closestEntity == 0 || distSq < closestDistSq) {
                        closestEntity = candidateEntity;
                        closestDistSq = distSq;
                    }
                }
            }
        }
        if (closestEntity != 0) {
            // Insert closest entity into target list
            targetListNode = (int *)(thisPtr + 0x10); // Offset 0x10: next pointer in linked list
            newTargetNode = closestEntity + 0x48; // Entity has an embedded list node at +0x48
            if (*(int *)(thisPtr + 0x10) != newTargetNode) {
                if (*(int *)(thisPtr + 0x10) != 0) {
                    FUN_004daf90(targetListNode); // Possibly release previous target
                }
                *targetListNode = newTargetNode;
                if (newTargetNode != 0) {
                    *(int *)(thisPtr + 0x14) = *(int *)(closestEntity + 0x4C); // Offset 0x14: prev pointer
                    *(int **)(closestEntity + 0x4C) = targetListNode; // Link back
                }
            }
            found = true;
        }
    }

    // Cleanup debug drawing
    FUN_004b0580();
    FUN_00549cb0();
    FUN_00a66870();
    // Return whether a target was found
    return found;
}