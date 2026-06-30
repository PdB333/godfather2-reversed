// FUNC_NAME: SimNpc::updateMovement
void __thiscall SimNpc::updateMovement(int thisPtr, float deltaTime, Vector3* targetPos, bool* outResult)
{
    float* srcVelX; // inlined
    float* srcPosY; // inlined
    float* srcPosZ; // inlined
    float* playerPos; // from getPlayerTransform()
    float dx, dy, dz; // to player
    float px, py, pz; // projected position
    float projToCurrX, projToCurrY, projToCurrZ; // projected - current
    float sqVelMag; // velocity magnitude squared
    char rayResult; // result from collision raycast

    playerPos = (float*)getPlayerTransform();
    // Compute target position after current velocity: currentPos + velocity
    float targetX = *(float*)(thisPtr + 0x60) + *(float*)(thisPtr + 0xfc);
    float targetY = *(float*)(thisPtr + 0x64) + *(float*)(thisPtr + 0x100);
    float targetZ = *(float*)(thisPtr + 0x68) + *(float*)(thisPtr + 0x104);

    // Project movement toward the player? (uses some path prediction)
    projectMovement(&px, (float*)(thisPtr + 0x60), playerPos + 0x30, &targetX);
    // Now px, py, pz are projected coordinates (py and pz stored in local_14, local_10)
    // Using the correct order from decomp: py = local_14, pz = local_10
    // But need to retrieve them from registers; in decomp they are local_18, local_14, local_10
    // After call, local_18 = px, local_14 = py, local_10 = pz
    // Then compute distances

    dx = *(float*)(thisPtr + 0x60) - playerPos[0x30/4]; // position.x - player.x
    dy = *(float*)(thisPtr + 0x64) - playerPos[0x34/4]; // position.y - player.y
    dz = *(float*)(thisPtr + 0x68) - playerPos[0x38/4]; // position.z - player.z

    // Actually the decomp used fVar4, fVar5, fVar6 for dx, dy, dz
    // And then later used local_14 and local_10 updated incorrectly.
    // Reconstruct:
    projToCurrX = px - *(float*)(thisPtr + 0x60);
    projToCurrY = py - *(float*)(thisPtr + 0x64);
    projToCurrZ = pz - *(float*)(thisPtr + 0x68);

    // Check if distance to player is less than distance to projected point + radius
    if (SQRT(dx*dx + dy*dy + dz*dz) < SQRT(projToCurrX*projToCurrX + projToCurrY*projToCurrY + projToCurrZ*projToCurrZ) + *(float*)(thisPtr + 0x6c))
    {
        // Close enough to stop
        *(float*)(thisPtr + 0xfc) = 0.0f;
        *(float*)(thisPtr + 0x100) = 0.0f;
        *(float*)(thisPtr + 0x104) = 0.0f;
        performRaycast((uchar*)&targetX, 0); // using local buffer
        rayResult = processMovementResult(targetPos, (uchar*)&targetX, deltaTime, (void*)(thisPtr + 0xf8));
        *outResult = rayResult;
        return;
    }

    // Check if current velocity magnitude squared exceeds threshold
    sqVelMag = *(float*)(thisPtr + 0xfc) * *(float*)(thisPtr + 0xfc) +
               *(float*)(thisPtr + 0x100) * *(float*)(thisPtr + 0x100) +
               *(float*)(thisPtr + 0x104) * *(float*)(thisPtr + 0x104);
    if (sqVelMag > kMaxVelocitySquared) // DAT_00e44598
    {
        performRaycast((uchar*)&targetX, 1); // aggressive raycast
        rayResult = processMovementResult(targetPos, (uchar*)&targetX, deltaTime, (void*)(thisPtr + 0xf8));
        *outResult = rayResult;
        if (rayResult != 0)
        {
            // Obstacle hit: stop and re-check
            *(float*)(thisPtr + 0xfc) = 0.0f;
            *(float*)(thisPtr + 0x100) = 0.0f;
            *(float*)(thisPtr + 0x104) = 0.0f;
            performRaycast((uchar*)&targetX, 0);
            rayResult = processMovementResult(targetPos, (uchar*)&targetX, deltaTime, (void*)(thisPtr + 0xf8));
            *outResult = rayResult;
            return;
        }
        // No obstacle: apply movement with velocity
        applyMovement(deltaTime, targetPos);
    }
    else
    {
        performRaycast((uchar*)&targetX, 0);
        rayResult = processMovementResult(targetPos, (uchar*)&targetX, deltaTime, (void*)(thisPtr + 0xf8));
        *outResult = rayResult;
        if (rayResult != 0)
        {
            // Set new velocity toward target (based on some offset from a stored target)
            int targetPtr = *(int*)(thisPtr + 0xb0);
            float targX = *(float*)(targetPtr + 0x10);
            float targY = *(float*)(targetPtr + 0x0c); // note offset order
            float targZ = *(float*)(targetPtr + 0x14);
            *(float*)(thisPtr + 0xfc) = targetPos->x - targX;
            *(float*)(thisPtr + 0x100) = targetPos->y - targY;
            *(float*)(thisPtr + 0x104) = targetPos->z - targZ;
            // Check bit 18 of flags at +0xa8
            if ((*(uint*)(thisPtr + 0xa8) >> 0x12 & 1) != 0)
            {
                *(float*)(thisPtr + 0xfc) = 0.0f;
                *(float*)(thisPtr + 0x100) = 0.0f;
                *(float*)(thisPtr + 0x104) = 0.0f;
                return;
            }
        }
    }
}