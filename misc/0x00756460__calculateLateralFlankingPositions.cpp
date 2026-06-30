// FUNC_NAME: calculateLateralFlankingPositions
void calculateLateralFlankingPositions(float *from, float *to, float *outPos1, float *outPos2)
{
    // Get pointer to global structure containing up vector at offsets 0x10, 0x14, 0x18
    int *globalUpPtr = FUN_00471610(); // likely returns address of some manager/camera

    float dx = to[0] - from[0];
    float dy = to[1] - from[1];
    float dz = to[2] - from[2];

    // Normalize direction vector
    float dir[3] = {dx, dy, dz};
    FUN_0056afa0(dir, dir); // in-place normalize

    // Extract up vector from global structure
    float upX = *(float *)(globalUpPtr + 0x10); // +0x10
    float upY = *(float *)(globalUpPtr + 0x14); // +0x14
    float upZ = *(float *)(globalUpPtr + 0x18); // +0x18

    // Cross product: up × dir
    float crossX = upY * dir[2] - upZ * dir[1];
    float crossY = upZ * dir[0] - upX * dir[2];
    float crossZ = upX * dir[1] - upY * dir[0];

    // Normalize perpendicular vector
    float cross[3] = {crossX, crossY, crossZ};
    FUN_0056afa0(cross, cross);

    // Scale by global lateral distance constant
    float scale = DAT_00d64e78;
    float offsetX = cross[0] * scale;
    float offsetY = cross[1] * scale;
    float offsetZ = cross[2] * scale;

    // First flanking position (e.g., left side)
    outPos1[0] = from[0] + offsetX;
    outPos1[1] = from[1] + offsetY;
    outPos1[2] = from[2] + offsetZ;

    // Second flanking position (e.g., right side) – uses a constant base (likely 0.0f) to flip offset
    float base = DAT_00e44564; // often 0.0f
    outPos2[0] = from[0] + (base - offsetX);
    outPos2[1] = from[1] + (base - offsetY);
    outPos2[2] = from[2] + (base - offsetZ);
}