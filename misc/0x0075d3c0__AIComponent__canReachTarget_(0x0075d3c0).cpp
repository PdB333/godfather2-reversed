// FUNC_NAME: AIComponent::canReachTarget (0x0075d3c0)
// This function checks if an AI entity can reach or see a target position,
// considering distance, line-of-sight, and optional obstacle entity.
// Return 1 if reachable/visible, 0 otherwise.
bool AIComponent::canReachTarget(AIComponent* thisObj, const Vector2* targetPos, float minDistance, float heightThreshold, Entity* obstacleEntity) {
    if (thisObj == nullptr) {
        return false;
    }

    // Get current position from a global manager (likely player/crew leader position)
    int* managerPtr = FUN_00471610(); // Returns pointer to some manager or player
    float currentX = *(float*)(managerPtr + 0x30); // +0x30: current X position
    float currentY = *(float*)(managerPtr + 0x38); // +0x38: current Y position

    // Target position (assume targetPos points to a float[2] or Vector2)
    float targetX = targetPos->x; // *(float*)targetPos
    float targetY = targetPos->y; // *(float*)(targetPos + 4) ?? but decompiler reads 8-byte offset; actual struct likely 4-byte alignment
    // Note: The decompiler shows param_2 as undefined8*, causing offset issues.
    // We trust that the layout is two consecutive floats.
    // Example: struct Vector2 { float x; float y; }; // sizeof=8

    float dx = currentX - targetX;
    float dy = currentY - targetY;
    float dist = sqrt(dx * dx + dy * dy);

    if (dist < minDistance) {
        return true;
    }

    // Get a speed or sight range from the AI component's vtable
    float speedOrSight = (thisObj->vtable->getSomeValue)(thisObj); // vtable offset 0x1c0

    // Calculate some factor from the target (maybe time to reach or path length)
    float pathFactor = FUN_0075cd80(thisObj, targetPos, obstacleEntity); // Returns a float

    // If speed/sight ratio is less than direct distance, consider unreachable
    if ((speedOrSight / pathFactor) <= dist) {
        return false;
    }

    // Additional height/perspective check
    if ((dist * dist - heightThreshold) <= DAT_00d651e4) {
        return false;
    }

    // If an obstacle entity is provided, perform a proximity check against it
    if (obstacleEntity != nullptr) {
        float obstacleX = obstacleEntity->position.x; // +0x10
        float obstacleY = obstacleEntity->position.y; // +0x14
        float obstacleRadius = obstacleEntity->collisionRadius; // +0x18

        float relX = targetX - obstacleX;
        float relY = targetY - obstacleY;
        float sqDistToObstacle = relX * relX + relY * relY;

        // Check if target is inside obstacle radius
        if (obstacleRadius * obstacleRadius <= sqDistToObstacle) {
            // Not inside, but also check scaled radius
            float scaledRadius = obstacleRadius * DAT_00d5eee4;
            if (scaledRadius <= minDistance) {
                return false;
            }
            if (scaledRadius * scaledRadius <= dist * dist) {
                return false;
            }
        } else {
            // Inside obstacle radius => blocked
            return false;
        }
    }

    return true;
}