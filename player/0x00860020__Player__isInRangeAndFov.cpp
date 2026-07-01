// FUNC_NAME: Player::isInRangeAndFov
// Address: 0x00860020
// Role: Tests if a 3D target position is within a given range and forward-facing cone of the player

bool __thiscall Player::isInRangeAndFov(float *targetPos)
{
    // Player entity singleton (0x30 = position offset)
    Entity *playerEntity = getPlayerEntity(); // FUN_00471610
    float *playerPos = (float *)((uint)playerEntity + 0x30);

    // Player's forward direction vector (3 floats)
    float forwardVec[3];
    getForwardVector(forwardVec); // FUN_008750c0 fills forwardVec

    // Squared distance between target and player
    float dx = targetPos[0] - playerPos[0];
    float dy = targetPos[1] - playerPos[1];
    float dz = targetPos[2] - playerPos[2];
    float distSq = dx*dx + dy*dy + dz*dz;

    // Compare with squared interact range (stored at +0x11a4)
    if (distSq <= this->interactRange * this->interactRange) // +0x11a4 (float)
    {
        // Compute angle between forward vector and direction from player to target
        // FUN_004a0cd0 likely returns the angle (in radians) or a dot product
        float angle = computeDirectionAngle(playerPos, forwardVec, targetPos, &DAT_00d75690);
        // Allow if within field of view threshold stored at +0x11a8 (float, radians)
        if (fabs(angle) <= this->interactFov) // +0x11a8
        {
            return true;
        }
    }
    return false;
}