// FUNC_NAME: CoverHintNodeManager::updateClosestCoverTarget
// Address: 0x0076a790
// Purpose: Finds the closest cover node to the player/camera and stores its position and distance.

char __fastcall CoverHintNodeManager::updateClosestCoverTarget(void* thisPtr)
{
    char result;
    int iterBase;
    int* containerPtr;
    float bestDistSq = 0.0f;
    float nodePosX, nodePosY, nodePosZ; // Stack variables for position components
    float bestNodeX, bestNodeY, bestNodeZ;
    float* bestPosPtr;
    int* baseObj;
    float playerPos[3]; // From FUN_00471610 + 0x30
    int unknown;
    int params[4]; // For FUN_0054ebf0

    playerPos[0] = *(float*)(FUN_00471610() + 0x30);
    playerPos[1] = *(float*)(FUN_00471610() + 0x34);
    playerPos[2] = *(float*)(FUN_00471610() + 0x38);

    nodePosX = 0.0f;
    nodePosY = 0.0f;
    nodePosZ = DAT_00d5f6f0; // Default search radius or maximum

    // offset +0x70: pointer to a node container (e.g., linked list or array with embedded object)
    if (*(int*)(thisPtr + 0x70) != 0)
    {
        // The pointer points to a member of a larger object; get base by subtracting 0x48
        containerPtr = (int*)(*(int*)(thisPtr + 0x70) - 0x48);
    }
    else
    {
        containerPtr = 0;
    }

    bestPosPtr = &nodePosX; // Stack address for storing best position? Unclear

    // vtable+0x260: check if container has any nodes (e.g., isEmpty?)
    result = (*(char(__fastcall**)(int*))(*(int*)containerPtr + 0x260))(containerPtr);

    if (result != 0)
    {
        // Get position of first node (vtable+0xa4) – returns a 3D position via param1 and param2? 
        // Actually writes to nodePosX and nodePosY (and likely nodePosZ is set elsewhere)
        if (*(int*)(thisPtr + 0x70) == 0)
            containerPtr = 0;
        else
            containerPtr = (int*)(*(int*)(thisPtr + 0x70) - 0x48);

        (*(void(__fastcall**)(int*, float*, float*))(*(int*)containerPtr + 0xa4))(containerPtr, &nodePosX, &nodePosY);

        // Compute squared distance from player position to first node position
        bestDistSq = (nodePosX - playerPos[0]) * (nodePosX - playerPos[0]) +
                     (nodePosY - playerPos[1]) * (nodePosY - playerPos[1]) +
                     (nodePosZ - playerPos[2]) * (nodePosZ - playerPos[2]);

        // Store best node coordinates
        bestNodeX = nodePosX;
        bestNodeY = nodePosY;
        bestNodeZ = nodePosZ;
    }

    // Iterate over remaining nodes
    while (true)
    {
        if (*(int*)(thisPtr + 0x70) == 0)
            containerPtr = 0;
        else
            containerPtr = (int*)(*(int*)(thisPtr + 0x70) - 0x48);

        // vtable+0x1bc: advance to next node and check validity (return bool)
        result = (*(char(__fastcall**)(int*, int*))(*(int*)containerPtr + 0x1bc))(containerPtr, &nodePosZ);

        if (result == 0)
            break;

        // Get position of the new node
        (*(void(__fastcall**)(int*, float*, float*))(*(int*)containerPtr + 0xa4))(containerPtr, &nodePosX, &nodePosY);

        float tempDistSq = (nodePosX - playerPos[0]) * (nodePosX - playerPos[0]) +
                           (nodePosY - playerPos[1]) * (nodePosY - playerPos[1]) +
                           (nodePosZ - playerPos[2]) * (nodePosZ - playerPos[2]);

        if (tempDistSq < bestDistSq)
        {
            bestPosPtr = (float*)0x01000000; // Some flag? Unclear.
            bestNodeX = nodePosX;
            bestNodeY = nodePosY;
            bestDistSq = tempDistSq;
        }

        // vtable+0x1c0: continue iteration? Actually it's called with stack0xffffffb4 which is likely a buffer. 
        // This looks like a duplicate call; probably a loop condition update.
        if (*(int*)(thisPtr + 0x70) == 0)
            containerPtr = 0;
        else
            containerPtr = (int*)(*(int*)(thisPtr + 0x70) - 0x48);

        (*(char(__fastcall**)(int*, int*))(*(int*)containerPtr + 0x1c0))(containerPtr, &unknown);
    }

    // Now bestDistSq is the squared distance to the closest node (or first if no iteration)
    // bestNodeX/Y/Z hold the best position.
    // The condition: if (bestDistSq was valid and initial result true)
    result = (char)((uint)bestNodeZ >> 24); // Actually this is from unaff_ESI, likely the initial result
    if (result != 0)
    {
        // Store best position in member variables +0x78, +0x7c (2D projection? or x,z)
        *(float*)(thisPtr + 0x78) = bestNodeX;
        *(float*)(thisPtr + 0x7c) = bestNodeY;
        // Get position relative to something (vtable+0xa4 again) – stores to thisPtr+0x7c? Actually it writes +0x7c as output
        if (*(int*)(thisPtr + 0x70) == 0)
            containerPtr = 0;
        else
            containerPtr = (int*)(*(int*)(thisPtr + 0x70) - 0x48);

        (*(void(__fastcall**)(int*, int*))(*(int*)containerPtr + 0xa4))(containerPtr, &playerPos[0], (float*)(thisPtr + 0x7c));

        // Call some function to convert to world space? FUN_0054ebf0 likely does matrix transform.
        // FUN_00471610 returns some global state (e.g., player camera info)
        int globalPtr = FUN_00471610();
        FUN_0054ebf0(&nodePosX, globalPtr + 0x30, 0x20, 0x20000, 0, 0, &nodePosZ, &nodePosX, 0);

        // Compute final distance from player to the cover point, subtract global constant _DAT_00e51bd4
        if (*(int*)(thisPtr + 0x70) == 0)
            containerPtr = 0;
        else
            containerPtr = (int*)(*(int*)(thisPtr + 0x70) - 0x48);

        if (containerPtr == 0)
        {
            // Compute Euclidean distance in x-z plane
            *(float*)(thisPtr + 0x80) = sqrtf((playerPos[1] - playerPos[0]) * (playerPos[1] - playerPos[0]) +
                                               (playerPos[2] - nodePosX) * (playerPos[2] - nodePosX)) - _DAT_00e51bd4;
            return (char)((uint)bestPosPtr >> 24); // Return flag from bestPosPtr
        }
        *(int*)(thisPtr + 0x80) = 0;
        result = (char)((uint)bestPosPtr >> 24);
    }
    return result;
}