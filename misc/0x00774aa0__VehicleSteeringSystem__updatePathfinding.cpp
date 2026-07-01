// FUNC_NAME: VehicleSteeringSystem::updatePathfinding

// Function at 0x00774aa0: updates vehicle steering by performing a navigation query
// if the current target waypoint is too far from the player or invalid
void __fastcall VehicleSteeringSystem::updatePathfinding(VehicleSteeringSystem* thisPtr)
{
    // +0x0c: possibly pointer to current target/command (type ID or pointer)
    // +0x14: flags bitfield
    // +0x18: index into arrays (waypointIndex)
    // +0x1c: array of 8-byte entries (maybe target identifiers)
    // +0x34: array of Vec3 (waypoint positions)

    int* currentTarget = thisPtr->field_0c;  // +0x0c
    if (!currentTarget || *currentTarget == 0x48) {
        return; // no valid target or target is 'none'
    }

    int waypointIndex = thisPtr->field_18;   // +0x18
    // Check target type at this index (8-byte entries)
    int* targetEntry = (int*)( (char*)thisPtr + 0x1c + waypointIndex * 8 );
    int targetType = *targetEntry;
    if (targetType == 0 || targetType == 0x48) {
        // No target type or 'none' – proceed; 
        // Also need distance check against player position
    }

    // Get player entity (returns pointer to player transform/position at +0x30)
    PlayerEntity* playerEntity = getPlayerEntity(); // 0x00471610
    if (!playerEntity) return;

    Vec3* waypointPos = (Vec3*)((char*)thisPtr + 0x34 + waypointIndex * 0xc);
    float dx = waypointPos->x - playerEntity->position.x; // +0x30
    float dy = waypointPos->y - playerEntity->position.y; // +0x34
    float dz = waypointPos->z - playerEntity->position.z; // +0x38
    float distSq = dz*dz + dy*dy + dx*dx;

    // Global threshold for distance check (DAT_00e51cb4)
    if (distSq <= g_steeringDistanceThreshold) {
        return; // close enough, no need to update
    }

    // Build navigation query structure
    NavQuery query; // 12 bytes
    constructNavigationQuery(&query); // 0x00774730

    Vec3 startPos = Vec3Zero();   // 0x0043b490
    Vec3 desiredDir = Vec3Zero(); // 0x0043b490
    Vec3 endPos = Vec3Zero();     // will be set based on target
    int numResults = 0;

    // If currentTarget is non-zero, adjust to get parent object (target entity)
    if (currentTarget) {
        // Subtract offset 0x48 to get base of a containing structure
        TargetEntity* targetEntity = (TargetEntity*)( (char*)currentTarget - 0x48 );
        if (targetEntity->field_e8 != 0 && targetEntity->field_e8 != 0x48) {
            endPos = Vec3Zero(); // maybe set a different end position
            // uVar5 becomes 3 instead of 2
        }
    }

    // Perform navigation query (navmesh pathfinding or raycast)
    // Parameters: from player position, query struct, type hash 0x40136, flags 0x2020000,
    // startPos, desiredDir, endPos, numResults, etc.
    bool queryResult = performNavigationQuery(
        &playerEntity->position, // +0x30
        &query,
        0x40136,                 // Navigation query type hash
        0x2020000,               // Flags
        &startPos,
        2,                       // uVar5 (2 or 3)
        &numResults,
        nullptr,
        nullptr
    ); // 0x0054ebf0

    if (!queryResult) {
        // Query failed – but maybe we got some results
        if (numResults != 0) {
            processNavigationResults(numResults); // 0x0044b210
            // Update the current waypoint to match player position
            playerEntity->position.copyTo(waypointPos); // copy 12 bytes
        }
        finishSteeringUpdate(); // 0x00774650
        return;
    }

    // Query succeeded – set flag that path was updated (bit 3 of flags)
    thisPtr->field_14 |= 0x8;
}