// FUNC_NAME: calculateYawToTarget
// Function address: 0x00799270
// Computes the yaw angle (in degrees) from the current player/camera position to a given target point.
// Uses a global singleton getter (FUN_00471610) to retrieve the player/camera object, then reads its position at offsets +0x30 (x) and +0x38 (z).
// The constant DAT_00e44748 is likely 180.0f / PI (57.2958) to convert radians to degrees.

double calculateYawToTarget(float *targetPos)
{
    // Get pointer to player/camera object (likely a singleton)
    int playerObj = FUN_00471610(); // returns pointer to some object

    // Compute delta vector (target - player) in the XZ plane
    float dx = *targetPos - *(float *)(playerObj + 0x30); // +0x30: player position X
    float dz = targetPos[2] - *(float *)(playerObj + 0x38); // +0x38: player position Z

    // Compute yaw angle using atan2(dx, dz) (standard for yaw in game engines)
    double yawRad = fpatan((double)dx, (double)dz);

    // Convert radians to degrees using the global constant
    double yawDeg = yawRad * (double)DAT_00e44748;

    return yawDeg;
}