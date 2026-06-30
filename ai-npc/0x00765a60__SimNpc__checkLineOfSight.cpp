// FUNC_NAME: SimNpc::checkLineOfSight
bool SimNpc::checkLineOfSight() {
    // Offsets from this NPC
    // +0x24c4: m_targetIndex (some identifier)
    // +0x21dc: m_pTargetEntity (pointer to target entity)
    int targetIndex = *(int*)(this + 0x24c4);
    int targetEntity = *(int*)(this + 0x21dc);

    // If no target, return true (default visible)
    if (targetEntity == 0) {
        return true;
    }

    // Compute actual target pointer from index (handle conversion?)
    int targetBase = (targetIndex == 0) ? 0 : (targetIndex - 0x48);
    if (targetBase == 0) {
        return true;
    }

    char targetState = *(char*)(targetEntity + 0x88); // +0x88: m_aiState
    // Skip check for dead (0x08) or disabled (0x01) targets
    if (targetState == 0x08 || targetState == 0x01) {
        return true;
    }

    // Extract target position (x,z packed at 0x38, y at 0x40)
    // Using reinterpret cast to get two floats from 8 bytes
    struct Vec2 { float x, y; };
    Vec2 targetPosXZ = *(Vec2*)(targetEntity + 0x38); // +0x38: m_position.xz
    float targetPosY = *(float*)(targetEntity + 0x40); // +0x40: m_position.y (or z in world?)

    // Get player entity (may be current camera or player)
    void* player1 = FUN_00471610(); // likely getPlayer()
    Vec2 playerPosXZ = *(Vec2*)(player1 + 0x30); // +0x30: player position.xz
    float playerPosY = *(float*)(player1 + 0x38); // +0x38: player position.y

    // Second call to same function (maybe gets camera or another reference)
    void* player2 = FUN_00471610();
    float refX = *(float*)(player2 + 0x30); // +0x30: second reference x
    float refY = *(float*)(player2 + 0x38); // +0x38: second reference y

    // Compute 2D cross product (in world XZ plane) to determine orientation
    // fVar5 = targetX * (playerY - refY) - (playerX - refX) * targetY
    float cross = targetPosXZ.x * (playerPosY - refY) - (playerPosXZ.x - refX) * targetPosY;

    // Handle different AI states
    float angleThreshold; // later used as part of cone check
    if (targetState == 0x04) { // maybe "alert" state
        // Global constants: field of view thresholds
        extern float g_fovMax;  // 0x00d577a0
        extern float g_fovMin;  // 0x00d5f534
        if (cross >= g_fovMax) return true;
        if (cross < g_fovMin)  return false;
        angleThreshold = *(float*)(targetEntity + 0x4c); // +0x4c: m_angleThreshold (yaw speed?)
    }
    else if (targetState == 0x02) { // maybe "idle" state
        extern float g_fovZero; // 0x00d5ef54
        if (cross <= 0.0f) return true;
        if (cross > g_fovZero) return false;
        angleThreshold = *(float*)(targetEntity + 0x4c);
    }
    else {
        return false; // unknown state
    }

    // Build a direction vector from target orientation (packed at +0x44)
    uint64_t orientationPacked = *(uint64_t*)(targetEntity + 0x44); // +0x44: m_orientation (two floats)
    float orientX = (float)(orientationPacked & 0xFFFFFFFF);
    float orientZ = (float)((orientationPacked >> 32) & 0xFFFFFFFF);

    // Compute summed vectors for angle check
    Vec2 sumPos;
    sumPos.x = orientX + targetPosXZ.x;
    sumPos.y = orientZ + targetPosXZ.y; // note: targetPosXZ.y is actually z in world

    // Also compute combined angle threshold
    float combinedThreshold = angleThreshold + targetPosY;

    // Call function to compute angle between vectors (likely 
    //   FUN_0084cb90(&playerPosXZ, &orientation, &sumPos, 0, 0))
    // This returns the cosine or sine of the angle.
    float angleResult = FUN_0084cb90(&playerPosXZ, &orientationPacked, &sumPos, 0, 0);

    // Compare with global threshold
    extern float g_angleLimit; // 0x00d5fb0c
    if (angleResult < g_angleLimit) {
        return false;
    }

    return true;
}