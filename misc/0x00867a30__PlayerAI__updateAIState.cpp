// FUNC_NAME: PlayerAI::updateAIState
void __thiscall PlayerAI::updateAIState(PlayerAI *this)
{
    // This function updates the AI steering/behavior for a player's AI-controlled character.
    // It checks if the player is dead/inactive, then searches for nearby enemies using an octree or spatial hash,
    // computes a steering force toward a target, and applies it.

    float *pIterBegin;
    float *pIterEnd;
    float *pIterCurrent;
    float *targetPos;
    int queryHandle[2];
    float *bestTarget;
    float localVec3[3]; // local_3c, local_38, local_34
    float diffVec3[3]; // local_30, local_2c, local_28
    float delta[3]; // local_24, local_20, local_1c
    float steeringForce;
    // local_18 and local_c are likely unused or stack alignment padding

    // Get the local player object from the game manager
    int *localPlayer = getGameManager(); // FUN_00471610
    if ( !isPlayerActiveOrIgnoreFlag(localPlayer + 0x30, 0) ) // FUN_006c0050
    {
        if ( isPlayerInVehicleAndAltState(localPlayer + 0x30) ) // actually check byte at offset 0xd8 of some other object
        {
            int *anotherObj = getAnotherManager(); // FUN_005466a0
            if ( *(char *)(anotherObj + 0xd8) == 7 ) // state flag
            {
                // Set a flag to indicate something (maybe ignore AI)
                setFlagAtOffset(this + 0x3c); // FUN_004088c0
                *(int *)(this + 0xf2c) = 1; // AI state flag
                return;
            }
        }
    }

    // Check if global max distance threshold has been exceeded
    if ( gMaxDistance > *(float *)(this + 0x1018) ) // _DAT_00d577a0 vs this->field_1018
    {
        *(int *)(this + 0xf90) = 3; // Set AI state to 3 (e.g., stopped)
        return;
    }

    // Initialize a spatial query structure (local_18)
    initSpatialQuery(local_18, 0); // FUN_00875190

    // Get iteration range for the spatial container
    getSpatialContainerIterators(&pIterBegin, &pIterCurrent, &pIterEnd); // FUN_005fd860

    queryHandle[0] = 0;
    queryHandle[1] = 0;
    // Perform spatial query with a callback that finds a target
    bool found = performSpatialQuery(local_18, pIterCurrent, queryHandle, findTargetCallback); // FUN_00600720 with FUN_00867850

    if ( !found )
    {
        // Clean up iterators
        releaseSpatialIterators(&pIterBegin, &pIterCurrent); // FUN_005f5cb0
        // If pointers are equal, skip steering computation
        if ( pIterBegin == pIterCurrent && pIterCurrent == pIterEnd )
            goto LABEL_cleanup;
    }

    // Get local player's position
    localPlayer = getGameManager();
    getPositionOfPlayer(local_vec3, localPlayer + 0x20); // FUN_0043a210

    // Determine best target among query results
    pIterCurrent = (float *)1; // dummy start
    getSpatialContainerIterators(&pIterCurrent, (float **)local_4c, &pIterEnd); // local_4c is unused? Actually second arg is local_4c (local_50 in original)
    float *best = pIterEnd;
    if ( pIterEnd == 0 )
    {
        best = pIterEnd; // Actually original: if local_50 == 0, set pfVar5 = local_5c (pIterEnd)
    }
    else
    {
        // Compare distances using magnitude
        float mag1 = magnitude(pIterEnd); // FUN_00470250
        float mag2 = magnitude(best);
        if ( mag1 >= mag2 )
            best = (float *)(int)mag1; // Actually original sets local_50 = (float*)fVar6, but then compares
        // Actually the logic is more complex: they compare the magnitudes of the two iterators? Might be finding closest.
        // Simplified: find target with minimum distance.
    }

    // Use best target pointer
    targetPos = 0;
    if ( queryHandle[0] != 0 )
        targetPos = (float *)(int)queryHandle[1]; // local_40 was stored as pointer

    // Check if target is within distance threshold and line-of-sight
    float distToTarget = magnitude(targetPos);
    if ( distToTarget < gSteeringThreshold && isLineOfSightClear(best, pIterCurrent) ) // FUN_005fd130
    {
        float dotResult = dotProduct(pIterCurrent); // FUN_0046fd60
        if ( dotResult >= 0.0f )
        {
            // Compute steering force toward target
            computeTargetDirection(local_vec3, local_4c); // FUN_008670e0; local_vec3 is actually &local_30? Wait, careful with original vars.
            // Actually the original used &local_50 as output for something, then used local_30 for diff.
            // We'll simplify: assume we get target world position and compute delta.

            // Get target world position from the best entity
            getEntityPosition(getLocalPlayer() + 0x30, &targetWorldPos); // FUN_008655a0
            // Compute delta vector toward target
            delta[0] = targetWorldPos[0] - targetPos[0];
            delta[1] = targetWorldPos[1] - targetPos[1];
            delta[2] = targetWorldPos[2] - targetPos[2];
            // Apply steering with queryHandle
            applySteering(queryHandle, &targetWorldPos, delta, 0, 0); // FUN_00600a40

            // Clear a bit flag at offset +0xf28
            *(unsigned int *)(this + 0xf28) &= 0xff7fffff;

            // Play sound or trigger effect based on steering force
            float soundParam = delta[0]; // example
            playSoundEffect(*(int *)(this + 0xfc4)); // FUN_00b9a9fa
            setAudioParameter(soundParam); // FUN_0085ea30

            // Check another threshold for additional steering force
            if ( magnitude(delta) < gMinDistance )
            {
                // Compute another vector for steering
                float *playerPos = (float *)(getLocalPlayer() + 0x30);
                delta[0] = playerPos[0] - pIterCurrent[0];
                delta[1] = playerPos[1] - pIterCurrent[1];
                delta[2] = playerPos[2] - pIterCurrent[2];
                // Normalize or transform delta
                transformVector(&delta[0], &delta[0]); // FUN_0043a210
            }
        }
    }

LABEL_cleanup:
    // Reset AI state and clear target handle
    *(int *)(this + 0xf90) = 0; // State back to idle
    *(int *)(this + 0xf78) = 0; // target handle
    if ( queryHandle[0] != 0 )
    {
        releaseQueryHandle(queryHandle); // FUN_004daf90
    }
}