// FUNC_NAME: Constraint::applyPositionConstraint
void __thiscall Constraint::applyPositionConstraint(void* this, float* wantedPos, float* forwardDir) {
    float diffX, diffY, diffZ;
    float normalizedDiff[3];
    float dotProduct;
    float factor;
    float alt1X, alt1Y, alt1Z;
    float alt2X, alt2Y, alt2Z;
    float* playerTransform;
    float worldPosX, worldPosY, worldPosZ;
    float worldRightX, worldUpX, worldForwardX; // Only x-components used? Actually full vectors used later.

    playerTransform = (float*)FUN_00471610(); // Get player transform matrix (or camera)
    // Player world position at +0x30
    worldPosX = playerTransform[0x30/4];
    worldPosY = playerTransform[0x34/4];
    worldPosZ = playerTransform[0x38/4];

    diffX = wantedPos[0] - worldPosX;
    diffY = wantedPos[1] - worldPosY;
    diffZ = wantedPos[2] - worldPosZ;

    // Store diff in a vec3 for normalization
    normalizedDiff[0] = diffX;
    normalizedDiff[1] = diffY;
    normalizedDiff[2] = diffZ;
    FUN_0056afa0(normalizedDiff, normalizedDiff); // In-place normalize

    dotProduct = forwardDir[0] * normalizedDiff[0] + forwardDir[1] * normalizedDiff[1] + forwardDir[2] * normalizedDiff[2];
    if ((float)(double)*(float*)((char*)this + 0x6c) < dotProduct) { // threshold = some angle cosine? Note: cast to double? Actually double on stack, but comparison is float.
        // Inside cone – keep wanted position
        *(double*)((char*)this + 0x70) = *(double*)wantedPos;
        *(float*)((char*)this + 0x78) = wantedPos[2];
        return;
    }

    // Outside cone – compute two alternative positions by rotating around the player's axes
    playerTransform = (float*)FUN_00471610(); // Re-fetch transform (maybe changed? Probably not)
    factor = *(float*)((char*)this + 0x68); // Rotation speed or distance factor

    // Compute cross products with player's right/up/forward axes from transform at +0x10, +0x14, +0x18
    // These expressions compute components of cross(diff, axis) but only the x components? It's messy – assume they compute a perpendicular vector.
    float crossX = factor * (playerTransform[0x14/4] * diffZ - playerTransform[0x18/4] * diffY);
    float crossY = factor * (playerTransform[0x18/4] * diffX - playerTransform[0x10/4] * diffZ);
    float crossZ = factor * (playerTransform[0x10/4] * diffY - playerTransform[0x14/4] * diffX);

    // Two alternative positions: add or subtract perpendicular offset to wanted position
    float alt1X = wantedPos[0] + crossX;
    float alt1Y = wantedPos[1] + crossY;
    float alt1Z = wantedPos[2] + crossZ;

    float alt2X = wantedPos[0] - crossX;
    float alt2Y = wantedPos[1] - crossY;
    float alt2Z = wantedPos[2] - crossZ;

    // Evaluate which alternative is more in front (or has larger dot product relative to forwardDir)
    // Compute dot product difference for alt1 and alt2 with the original direction from player to wantedPos
    float dotAlt1 = forwardDir[0] * (wantedPos[0] - alt1X) + forwardDir[1] * (wantedPos[1] - alt1Y) + forwardDir[2] * (wantedPos[2] - alt1Z);
    float dotAlt2 = forwardDir[0] * (wantedPos[0] - alt2X) + forwardDir[1] * (wantedPos[1] - alt2Y) + forwardDir[2] * (wantedPos[2] - alt2Z);

    // Choose the alternative with the smaller dot product (meaning less behind the plane?)
    if (dotAlt2 < dotAlt1) {
        // Use alt2
        *(double*)((char*)this + 0x70) = *(double*)(&alt2X); // Write alt2X and alt2Y
        *(float*)((char*)this + 0x78) = alt2Z;
    } else {
        // Use alt1
        *(double*)((char*)this + 0x70) = *(double*)(&alt1X);
        *(float*)((char*)this + 0x78) = alt1Z;
    }
}