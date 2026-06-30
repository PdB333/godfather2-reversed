// FUNC_NAME: CharacterController::handleCollisionRecovery
void CharacterController::handleCollisionRecovery(const float* inputPos, int32_t unused, float radius) {
    int32_t state = *(int32_t*)((uint8_t*)this + 0x20); // +0x20: movement state
    switch (state) {
    case 0:
    case 1:
    case 2:
    case 0xF:
    case 0x12:
        return;
    case 3:
    case 0xB:
        // Called from idle/walk state: just update some state and return
        FUN_0044f250(radius);
        return;
    case 4:
    case 5:
    case 0xE:
        break; // fall through to main logic
    default:
        return;
    }

    FUN_0044f250(radius); // Update before collision

    // Global threshold: maybe minimum speed or distance
    if (g_someSpeedThreshold < in_XMM0_Da) {
        // Get per-actor offset: pointer to a data array from TLS
        int32_t perActorOffset = *(int32_t*)(*(uint8_t**)(__readfsdword(0x2c)) + 8);
        int32_t actorDataBase = *(int32_t*)((uint8_t*)this + 0x18); // +0x18: pointer to actor transform/data
        float* actorOrigin = (float*)(actorDataBase + perActorOffset + 0x30); // +0x30: origin (4 floats)
        
        // Input position
        float dx = inputPos[0] - actorOrigin[0];
        float dy = inputPos[1] - actorOrigin[1];
        float dz = inputPos[2] - actorOrigin[2];
        float diff[3] = {dx, dy, dz};
        FUN_0044d680(diff, diff); // normalize diff vector

        // Compute dot product with actor's facing direction (at +0x20, +0x24, +0x28)
        float* actorDir = (float*)(actorDataBase + perActorOffset + 0x20);
        float dot = actorDir[0] * diff[0] + actorDir[1] * diff[1] + actorDir[2] * diff[2];

        // Get max distance (likely radius) from actor data
        float maxDist = *(float*)(actorDataBase + perActorOffset + 0x6C);
        FUN_00b99e20(); // maybe sqrt? (assumed)

        float factor;
        if (dot <= maxDist) {
            factor = 0.0f;
        } else {
            factor = g_someConstant; // DAT_00e2b1a4
            float stopDist = *(float*)(actorOrigin + 0x74); // +0x74: stopping distance
            if (dot < stopDist || dot == stopDist) {
                factor = *(float*)(*(int32_t*)((uint8_t*)this + 0x18) + 0x74 + perActorOffset);
                factor = g_someConstant - (dot - stopDist) / (maxDist - stopDist);
            }
        }

        if (factor * in_XMM0_Da <= g_anotherThreshold) {
            // Normalize actor's direction
            float actorNormDir[4];
            FUN_0044d680(actorDataBase + perActorOffset + 0x20, actorNormDir);

            // Recompute difference for projection
            dx = inputPos[0] - actorOrigin[0];
            dy = inputPos[1] - actorOrigin[1];
            dz = inputPos[2] - actorOrigin[2];
            float dw = inputPos[3] - actorOrigin[3]; // 4th component
            float dotProject = dx * actorNormDir[0] + dy * actorNormDir[1] + dz * actorNormDir[2];

            if (dotProject < g_minProjectionThreshold || dotProject > g_maxProjectionThreshold) {
                // Project input onto the line from actor origin in actor direction
                float projPoint[4];
                projPoint[0] = dotProject * actorNormDir[0];
                projPoint[1] = dotProject * actorNormDir[1];
                projPoint[2] = dotProject * actorNormDir[2];
                projPoint[3] = dotProject * actorNormDir[3];

                // Perpendicular component
                float perp[4];
                perp[0] = dx - projPoint[0];
                perp[1] = dy - projPoint[1];
                perp[2] = dz - projPoint[2];
                perp[3] = dw - projPoint[3];
                FUN_0044d680(perp, perp); // normalize perpendicular

                float scale = (float)FUN_00b9c041((double)maxDist); // sqrt or other function
                float newPoint[4];
                newPoint[0] = scale * perp[0] + projPoint[0];
                newPoint[1] = scale * perp[1] + projPoint[1];
                newPoint[2] = scale * perp[2] + projPoint[2];
                newPoint[3] = scale * perp[3] + projPoint[3];

                // Re-normalize the result (unclear purpose)
                float resultDir[4];
                FUN_0044d680(newPoint, resultDir);

                // Final dot product
                float newDot = dx * resultDir[0] + dy * resultDir[1] + dz * resultDir[2];
                // World movement
                float worldMove[4];
                worldMove[0] = newDot * resultDir[0] - dx;
                worldMove[1] = newDot * resultDir[1] - dy;
                worldMove[2] = newDot * resultDir[2] - dz;
                // Check if movement magnitude squared < radius^2
                float magSq = worldMove[0]*worldMove[0] + worldMove[1]*worldMove[1] + worldMove[2]*worldMove[2];
                if (magSq < radius * radius) {
                    return; // Movement within tolerance – exit
                }
            }
        }
    }
    return;
}