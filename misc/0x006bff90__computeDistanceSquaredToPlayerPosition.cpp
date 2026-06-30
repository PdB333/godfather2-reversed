// FUNC_NAME: computeDistanceSquaredToPlayerPosition
// Function address: 0x006bff90
// Role: Computes the squared Euclidean distance between a given 3D point and the player's current position.
// The player's position is retrieved via an engine call (FUN_00424fb0) which likely returns the world-space position.

/**
 * Computes squared distance from the given world-space point to the player's current position.
 * @param worldPos Pointer to an array of three floats (x, y, z) representing the point.
 * @return Squared distance as a double (float10 in original x87).
 */
double computeDistanceSquaredToPlayerPosition(float* worldPos)
{
    float posX; // local_c: player's world-space X
    float posY; // local_8: player's world-space Y
    float posZ; // local_4: player's world-space Z

    // Retrieve the player's position (flag 0 indicates world coordinates?)
    // FUN_00424fb0 fills posX, posY, posZ from an internal reference (probably player transform).
    FUN_00424fb0(&posX, 0);

    // Squared distance: (worldPos - playerPos)^2
    float dx = worldPos[0] - posX;
    float dy = worldPos[1] - posY;
    float dz = worldPos[2] - posZ;

    return (double)(dx * dx + dy * dy + dz * dz);
}