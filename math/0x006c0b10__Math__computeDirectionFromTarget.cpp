// FUNC_NAME: Math::computeDirectionFromTarget
// Function at 0x006c0b10: Computes a direction vector (x,0,z) pointing away from a target point relative to a global position (likely player's X/Z stored at 0x00e44564).
// Uses custom angle normalization and atan2 functions.
void __fastcall computeDirectionFromTarget(float* outVector, float* pTargetX, float* pTargetZ, float param) {
    // Global position (likely player or camera) X coordinate
    // DAT_00e44564 is presumably a global float (player position X or Z?)
    float deltaX = DAT_00e44564 - *pTargetX; // dx = playerX - targetX
    double doubleDZ = (double)(DAT_00e44564 - *pTargetZ); // dz = playerZ - targetZ -> double

    // Normalize/clamp the param (maybe an angle or time)
    FUN_00b9a9fa(param);
    float deltaZ = (float)doubleDZ;
    // Normalize/clamp deltaZ
    FUN_00b9a9fa(deltaZ);

    // Compute combined angle using a custom atan2-like function (takes dx, dz, and param)
    float10 angle = FUN_006c89d0((float)deltaX, deltaZ, param);

    // Construct output direction vector: sin/cos with negated signs, y=0
    outVector[0] = -(float)fsin(angle); // -sin(angle)
    outVector[1] = 0.0f;                // y component always zero
    outVector[2] = -(float)fcos(angle); // -cos(angle)
}