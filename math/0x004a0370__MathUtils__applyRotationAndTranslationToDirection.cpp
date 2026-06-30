// FUNC_NAME: MathUtils::applyRotationAndTranslationToDirection
void __fastcall MathUtils::applyRotationAndTranslationToDirection(float *outPosition, const float *rotation, const float *direction, float scale)
{
    // Input direction components
    float inX = direction[0];
    float inY = direction[1];
    float inZ = direction[2];

    // Adjust scale by global multiplier
    float adjustedScale = scale * g_scaleFactor;                  // DAT_00e2cd54

    // FPU state save (likely changes rounding mode for sqrt/division)
    startFPUProperMode();                                         // FUN_00b99e20
    float scaleCopy = adjustedScale;
    float doubleScale = (float)(double)adjustedScale;             // redundant, but kept as decompiled
    endFPUProperMode();                                           // FUN_00b99fcb

    // Normalize direction and scale by adjusted value
    float invLength = adjustedScale / sqrt(inX * inX + inY * inY + inZ * inZ);
    float scaledDirX = inX * invLength;
    float scaledDirY = inY * invLength;
    float scaledDirZ = inZ * invLength;

    // Load rotation quaternion (3 components from input, 4th from global constant)
    float qx = rotation[0];
    float qy = rotation[1];
    float qz = rotation[2];
    float qw = g_quaternionW;                                     // DAT_00e2b1a4

    // Store extra copy of scale for later (used as rotation component? reassigned later)
    float extraScale = scaleCopy;                                 // fStack_44

    // Compute translation offset: world position minus scaled direction
    float transX = g_worldPosition - scaledDirX;                  // DAT_00e44564
    float transY = g_worldPosition - scaledDirY;
    float transZ = g_worldPosition - scaledDirZ;

    // Temporary transform buffer (28 bytes in original, likely a 4x4 matrix or quat+vec)
    char tempTransform[28];                                       // local_20

    // First transform: rotate the scaled direction by the quaternion
    transformVector(tempTransform, &scaledDirX, &qx);            // FUN_0056cba0

    // Second transform: combine the rotated result with the translation
    transformVector(&qx, tempTransform, &transX);                // FUN_0056cba0 (overwrites qx..qz with output)

    // Write final position (output from second transform)
    outPosition[0] = qx;
    outPosition[1] = qy;
    outPosition[2] = qz;
}