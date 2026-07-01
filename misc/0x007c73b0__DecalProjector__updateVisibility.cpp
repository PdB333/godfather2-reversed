//FUNC_NAME: DecalProjector::updateVisibility
void __thiscall DecalProjector::updateVisibility(int this, double* transformData)
{
    float* directionPtr;
    float scale;
    char testResult1;
    char testResult2;
    int visibilityState;
    float crossX, crossY, crossZ;
    float corner1X, corner1Y, corner1Z, corner2X, corner2Y, corner2Z;
    float normalizedDir[3];
    float dummy[3];
    float frustumBuffer[3]; // 12 bytes
    float frustumBuffer2[3]; // 12 bytes
    float direction[3];
    float pad1, pad2, pad3;

    // Copy 4 doubles (32 bytes) from transformData into this's transform fields
    *(double*)(this + 0x74) = transformData[0]; // position or orientation
    *(double*)(this + 0x7c) = transformData[1]; // direction or scale
    *(double*)(this + 0x84) = transformData[2]; // additional data
    *(double*)(this + 0x8c) = transformData[3]; // additional data

    // Zero out the low 4 bytes of the third double (likely to clear a component)
    *(int*)(this + 0x84) = 0;

    // Extract a 3-component direction vector from the second and third doubles
    direction[0] = *(float*)(this + 0x80); // from high part of second double
    direction[1] = *(float*)(this + 0x84); // from low part of third double
    direction[2] = *(float*)(this + 0x88); // from high part of third double
    pad3 = 0;

    // Normalize the direction vector
    FUN_0056afa0(direction, direction); // normalizeVector

    // Write back normalized direction
    *(float*)(this + 0x80) = direction[0];
    *(float*)(this + 0x84) = direction[1];
    *(float*)(this + 0x88) = direction[2];

    // Get scale from some global manager (this+0x58 points to a manager)
    scale = *(float*)(*(int*)(this + 0x58) + 0x1f90);

    // Compute a point along the direction at distance scale
    *(float*)(this + 0x94) = direction[0] * scale + *(float*)(this + 0x74);
    *(float*)(this + 0x98) = direction[1] * scale + *(float*)(this + 0x78);
    *(float*)(this + 0x9c) = direction[2] * scale + *(float*)(this + 0x7c);

    // Get camera position from global camera manager
    int cameraManager = FUN_00471610(); // getCameraManager
    float cameraY = *(float*)(cameraManager + 0x34);
    *(float*)(this + 0x98) = cameraY; // override computed Y with camera Y? (maybe for billboard)

    // Compute inverse direction (1.0 - direction)
    float one = DAT_00e44564; // likely 1.0f
    *(float*)(this + 0xa0) = one - direction[0];
    *(float*)(this + 0xa4) = one - direction[1];
    *(float*)(this + 0xa8) = one - direction[2];

    // Compute cross product components for a perpendicular quad
    // Using cross product with (0,0,1) or similar
    crossX = direction[1] * 0.0f - direction[2]; // -direction.z
    crossY = direction[0] - 0.0f; // direction.x
    crossZ = direction[2] * 0.0f - direction[0] * 0.0f; // 0

    // Compute four corners of a rectangle perpendicular to direction
    corner1X = (one - crossX) + *(float*)(this + 0x74); // position + (1 - crossX)
    corner1Y = *(float*)(this + 0x78) + crossZ; // position + crossZ
    corner1Z = *(float*)(this + 0x7c) + crossY; // position + crossY

    corner2X = *(float*)(this + 0x74) + crossX; // position + crossX
    corner2Y = *(float*)(this + 0x78) + (one - crossZ); // position + (1 - crossZ)
    corner2Z = *(float*)(this + 0x7c) + (one - crossY); // position + (1 - crossY)

    // Get frustum manager
    int frustumManager = FUN_007ab120(); // getFrustumManager

    // Initialize frustum buffer
    FUN_008970a0(frustumBuffer); // initFrustum

    // Test two corners against frustum
    testResult1 = FUN_007e92f0(frustumManager, frustumBuffer, &corner1X, direction, 0x10000, 8, frustumBuffer2);
    testResult2 = FUN_007e92f0(frustumManager, frustumBuffer, &corner2X, direction, 0x10000, 8, frustumBuffer2);

    // Determine visibility state
    if (testResult1 == testResult2) {
        visibilityState = 2 - (uint)(*(char*)(this + 0x90) != '\0');
    } else {
        visibilityState = (testResult1 != '\0') + 1;
    }
    *(int*)(this + 0x118) = visibilityState;

    // Enable/disable two render layers based on visibility
    if (*(int*)(this + 0x118) == 1) {
        FUN_007f63e0(0x1d); // enableLayer(0x1d)
        FUN_007f6420(0x1e); // disableLayer(0x1e)
        return;
    }
    FUN_007f63e0(0x1e); // enableLayer(0x1e)
    FUN_007f6420(0x1d); // disableLayer(0x1d)
}