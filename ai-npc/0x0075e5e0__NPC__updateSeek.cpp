// FUNC_NAME: NPC::updateSeek
void __thiscall NPC::updateSeek(float deltaTime, const float* targetPos)
{
    // Global player/camera object (likely from FUN_00471610)
    void* player = getPlayerCharacter(); // returns pointer to player object
    float* playerPos = reinterpret_cast<float*>(player + 0x30); // position: +0x30 x, +0x34 y, +0x38 z

    // Vector from player to target
    float toTarget[3];
    toTarget[0] = targetPos[0] - playerPos[0];
    toTarget[1] = targetPos[1] - playerPos[1];
    toTarget[2] = targetPos[2] - playerPos[2];

    // Vector from player to this entity
    float directionToSelf[3];
    directionToSelf[0] = this->position[0] - playerPos[0];
    directionToSelf[1] = this->position[1] - playerPos[1];
    directionToSelf[2] = this->position[2] - playerPos[2];

    // Normalize directionToSelf, ignoring returned length
    float unused = vectorNormalizeInPlace(directionToSelf);

    // Distance from player to target, scaled by global speed factor (DAT_00e51af8)
    float distanceToTarget = sqrt(toTarget[0]*toTarget[0] + toTarget[1]*toTarget[1] + toTarget[2]*toTarget[2]) * g_speedFactor;

    // Desired position: playerPos + directionToSelf * distanceToTarget
    float desiredPos[3];
    desiredPos[0] = directionToSelf[0] * distanceToTarget + playerPos[0];
    desiredPos[1] = directionToSelf[1] * distanceToTarget + playerPos[1];
    desiredPos[2] = directionToSelf[2] * distanceToTarget + playerPos[2];

    // Offset for start of ray (slightly behind desiredPos relative to target direction)
    float rayStart[3];
    rayStart[0] = desiredPos[0] - toTarget[0];
    rayStart[1] = desiredPos[1];
    rayStart[2] = desiredPos[2] - toTarget[2];

    // Cast ray from rayStart to desiredPos, using this entity's collision shape (handle at +0x58)
    int collision = rayCast(this->collisionHandle, rayStart, desiredPos, 0);
    if (collision == 0)
    {
        // No obstacle, update velocity with damping
        float velocity[3];
        velocity[0] = this->velocityX;
        velocity[1] = this->velocityY;
        velocity[2] = this->velocityZ;

        float speed = vectorNormalizeInPlace(velocity); // returns length, normalize velocity direction

        // Apply damping: reduce speed by g_dampingFactor * deltaTime
        float dampedSpeed = speed - g_dampingFactor * deltaTime;
        if (dampedSpeed < 0.0f)
            dampedSpeed = 0.0f;

        // Set new velocity along the same direction
        this->velocityX = velocity[0] * dampedSpeed;
        this->velocityY = velocity[1] * dampedSpeed;
        this->velocityZ = velocity[2] * dampedSpeed;

        // Check flag at +0xa8, bit 18 (0x40000) - if set, zero out velocity (e.g., grounded or disabled)
        if ((this->flags & 0x40000) != 0) // bit 18 == 0x12? Actually 1<<18 = 0x40000
        {
            this->velocityX = 0.0f;
            this->velocityY = 0.0f;
            this->velocityZ = 0.0f;
        }
    }
    // If collision found, do not update velocity (keeps previous)
    return;
}